import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class D1Pt2 {
    public static void main(String[] args) {
        String nomeArquivo = "input.txt";
        int somaTotal = 0;
        try {
            somaTotal = processaArquivoEntrada(nomeArquivo);
            System.out.println("Soma total: " + somaTotal);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int processaArquivoEntrada(String nomeArquivo) throws IOException {
        int somaTotal = 0;
        int somaLinha;
        try (BufferedReader reader = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                somaLinha = processaLinha(linha);
                somaTotal += somaLinha;
            }
        }
        return somaTotal;
    }

    public static int processaLinha(String linha) {
        Map<String, Integer> mapeamentoNumeros = inicializarMapeamentoNumeros();

        int mixLinha = 0;
        int primeiroNumero = -1;
        int ultimoNumero = -1;

        char caractereAtual;
        String numLiteral = "";

        for (int i = 0; i < linha.length(); i++) {
            caractereAtual = linha.charAt(i);

            numLiteral += caractereAtual;

            if (Character.isDigit(caractereAtual)) {
                ultimoNumero = Character.getNumericValue(caractereAtual);
                numLiteral = "";
            } else {
                for (int y = 0; y < numLiteral.length(); y++) { 
                    for (int x = y + 1; x <= numLiteral.length(); x++) {
                        String subString = numLiteral.substring(y, x);
                        if (mapeamentoNumeros.containsKey(subString)) {
                            ultimoNumero = mapeamentoNumeros.get(subString);
                            numLiteral = "" + caractereAtual;
                            break;
                        } else {
							for (String numero : mapeamentoNumeros.keySet()) {
								if (subString.startsWith(numero)) {
									String resto = subString.substring(numero.length());
									if (resto.isEmpty() || resto.matches("\\d+")) {
										ultimoNumero = mapeamentoNumeros.get(subString);
										numLiteral = "" + caractereAtual;
										break;
									}
								}
							}
						}
                    }
                }
            }

            if (primeiroNumero == -1) {
                primeiroNumero = ultimoNumero;
            }
        }

        if (primeiroNumero != -1) {
            mixLinha = Integer.parseInt(primeiroNumero + "" + ultimoNumero);
        }

        return mixLinha;
    }

    private static Map<String, Integer> inicializarMapeamentoNumeros() {
        Map<String, Integer> mapeamento = new HashMap<>();
        mapeamento.put("one", 1);
        mapeamento.put("two", 2);
        mapeamento.put("three", 3);
        mapeamento.put("four", 4);
        mapeamento.put("five", 5);
        mapeamento.put("six", 6);
        mapeamento.put("seven", 7);
        mapeamento.put("eight", 8);
        mapeamento.put("nine", 9);
        return mapeamento;
    }
}