import java.io.File;
import java.io.FileNotFoundException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import java.util.Scanner;

import java.util.regex.*;

public class D2Pt2 {

    public static void main(String[] args) {
        List<String> gameStrings = readGameStringsFromFile("input.txt");
		
		int setTotal = 0;
        int jogosTotal = 0;

        for (String gameString : gameStrings) {
            List<Map<String, Integer>> setsColorCounts = extractSetsColorCounts(gameString);

            System.out.println("Game String: " + gameString);

            // Display sets and color counts
            for (int i = 0; i < setsColorCounts.size(); i++) {
                System.out.println("Set " + (i + 1) + ": " + setsColorCounts.get(i));
            }

            jogosTotal = jogoPoderResultado(setsColorCounts) + jogosTotal;
			
			setTotal = jogoPoderResultado(setsColorCounts);
			System.out.println("Valor do set: "+setTotal);
        }

        System.out.println("Poder total dos jogos: " + jogosTotal);
    }

    private static List<String> readGameStringsFromFile(String filename) {
        List<String> gameStrings = new ArrayList<>();

        try (Scanner scanner = new Scanner(new File(filename))) {
            while (scanner.hasNextLine()) {
                gameStrings.add(scanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.err.println("File not found: " + filename);
            e.printStackTrace();
        }

        return gameStrings;
    }

    private static List<Map<String, Integer>> extractSetsColorCounts(String gameString) {
        List<Map<String, Integer>> setsColorCounts = new ArrayList<>();

        // Define the regex pattern for extracting colors within each game set
        String gamePattern = "\\b(\\d+)\\s(\\w+)\\b";
        Pattern gameRegexPattern = Pattern.compile(gamePattern);

        // Split the game string by ";" to get individual game sets
        String[] games = gameString.split(";");

        // Process each game set
        for (String game : games) {
            // Create a Matcher object for each game set
            Matcher matcher = gameRegexPattern.matcher(game);

            // Map to store color counts for each set
            Map<String, Integer> colorCounts = new HashMap<>();

            // Find matches and update color counts
            while (matcher.find()) {
                int count = Integer.parseInt(matcher.group(1));
                String color = matcher.group(2);

                colorCounts.put(color, colorCounts.getOrDefault(color, 0) + count);
            }

            // Add color counts for the current set to the list
            setsColorCounts.add(colorCounts);
        }

        return setsColorCounts;
    }

    private static int jogoPoderResultado(List<Map<String, Integer>> setsColorCounts) {
        /* Deletar
		int redThreshold = 12;
        int greenThreshold = 13;
        int blueThreshold = 14;
		
				
        for (Map<String, Integer> colorCounts : setsColorCounts) { // apenas checa se alguma cor passou do limite
            if (colorCounts.getOrDefault("red", 0) > redThreshold || colorCounts.getOrDefault("green", 0) > greenThreshold || colorCounts.getOrDefault("blue", 0) > blueThreshold) {
                return false;  // Game is not won
            }
        }
		*/
		
		int redMaxPrev = 0;
		int blueMaxPrev = 0;
		int greenMaxPrev = 0;
		int total = 0;
		
		for (Map<String, Integer> colorCounts : setsColorCounts) {
			if (colorCounts.getOrDefault("red", 0) > redMaxPrev) {
				redMaxPrev = colorCounts.getOrDefault("red", 0);
			}
			
			if (colorCounts.getOrDefault("blue", 0) > blueMaxPrev) {
				blueMaxPrev = colorCounts.getOrDefault("blue", 0);
			}
			
			if (colorCounts.getOrDefault("green", 0) > greenMaxPrev) {
				greenMaxPrev = colorCounts.getOrDefault("green", 0);
			}
		}
		
		total = redMaxPrev * blueMaxPrev * greenMaxPrev;
		
        return total;  // Sai do método
    }

    private static int extractGameId(String gameString) {
        // Extract the game ID from the game string
        String gameIdPattern = "^Game (\\d+):.*$";
        Pattern pattern = Pattern.compile(gameIdPattern);
        Matcher matcher = pattern.matcher(gameString);

        if (matcher.matches()) {
            return Integer.parseInt(matcher.group(1));
        }

        return -1; // Return -1 if no match is found
    }
}
