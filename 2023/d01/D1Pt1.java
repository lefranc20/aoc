import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class D1Pt1 {
    public static void main(String[] args) {
		String nomeArquivo = "input.txt";
		try {
            int somaTotal = processaArquivoEntrada(nomeArquivo);
            System.out.println("Soma total: " + somaTotal);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
	
	// processaArquivoEntrada() - Processa o arquivo de entrada.
	public static int processaArquivoEntrada(String nomeArquivo) throws IOException {
		int somaTotal = 0;
		
		// O BufferedReader em conjunto com o FileReader previne o nosso leitor de sair caso ele veja uma linha vazia (não sendo o fim do arquivo)
		try (BufferedReader reader = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) { // executa linha por linha até chegar no fim do arquivo
                int somaLinha = processaLinha(linha);
                somaTotal += somaLinha;
            }
        }
        return somaTotal;
	}
	
	// processaLinha() - Processa e verifica uma linha, acertando as condições e resultados específicados no problema.
	public static int processaLinha(String linha) {
		int somaLinha = 0;
        int primeiroNumero = -1;
        int ultimoNumero = -1;

        for (int i = 0; i < linha.length(); i++) { // isso é apenas para uma linha
            char caractereAtual = linha.charAt(i);

            if (Character.isDigit(caractereAtual)) {
                int numeroAtual = Character.getNumericValue(caractereAtual); // checa o caractere caso seja um digito de 0-9 e armazena em uma variavel "numeroAtual"

                if (primeiroNumero == -1) { // para o primeiro número, SEMPRE ser o primeiro número...
                    primeiroNumero = numeroAtual;
				}

				ultimoNumero = numeroAtual;	// linha simples com dois objetivos: caso o último caracter lido tenha sido um número, ele será armazenado como o último número; caso ele tenha sido o primeiro (ou seja só tenha um número), ele também é armazenado nessa variável
            }
        }

        // Após a linha tenha sido processada, caso não tivesse nenhum número nela, logicamente, ela ainda continuaria no mesmo estado de declaração anterior (-1), senão ela se encontraria em qualquer outro estado, entrando nesse if para somar os primeiros e últimos números
        if (primeiroNumero != -1) {
			somaLinha = Integer.parseInt(primeiroNumero + "" + ultimoNumero);
        }

        return somaLinha;
    }
}