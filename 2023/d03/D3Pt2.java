import java.io.File;
import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import java.util.regex.*;

public class D3Pt2 {
    public static void main(String[] args) {
        String nomeArquivo = "input.txt";
		String[] strAr= new String[140];
		char[][] charAr= new char[140][140];
		
		try {
			String tempString = "";
			for (int i = 0; i < 140; i++){ // passando o vetor de Strings das linhas do input, para um vetor igual no main
				tempString = processaArquivoEntrada(nomeArquivo, i);
				for (int j = 0; j < 140; j++) {
					charAr[i][j] = tempString.charAt(j);
				}
			}
        } catch (IOException e) {
            e.printStackTrace();
        }
		
		// 1. Impressão do vetor 2d de char
		for (int i = 0; i < 140; i++) {
			for (int j = 0; j < 140; j++) {
				System.out.print(charAr[i][j]); // imprimindo o vetor...
			}
			System.out.println("");
		}
		
		System.out.println("\n ACABOU a impressao \n");
		
		// 2. Loop e Condicionais para a soma
		// variaveis usadas
		int soma = 0; // para a soma final
		int tempNum = -1; // variavel temporaria para numero em String
		String tempString = "";
		
		int colTempo = 0;
		
		for (int i = 0; i < 140; i++) { // loop de coluna
			for (int j = 0; j < 140; j++) {	// loop de linha
				// checa se for um asterisco
				if (charAr[i][j]) == '*'){
					// Procura a "vizinhanca" por numeros
					for (int x = -1; x <= 1; x++) {
						for (int y = -1; y <= 1; y++) {
							// Traca a sequencia completa deles
							if ( ( (i + (x) >= 0) && (j + (y) >= 0) && (i + (x) < 140) && (j + (y) < 140) ) && ( (Character.isDigit(charAr[i + (x)][j + (y)]) == true) ) ) { // 
								colTempo = y;
								while (charAr[i][colTempo] == ){
									
								}
							}
						}
					}
				} 
			}
		}

		// 3. Imprimindo a Soma Final
		System.out.println("\nSoma: "+soma);
	}
	
	// processaArquivoEntrada() - Processa o arquivo de entrada.
	public static String processaArquivoEntrada(String nomeArquivo, int numLinha) throws IOException {
		String linha;
		try (BufferedReader reader = new BufferedReader(new FileReader(nomeArquivo))) {
			for(int x = 0; x < numLinha; x++){ // lê até o numLinha específicado
				reader.readLine();
			}
			linha = reader.readLine(); // passa para a linha atual
        }
		return linha; // e retorna para tacar no vetor de Strings strAr[] na classe principal
	}
}