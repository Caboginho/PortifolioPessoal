#include <stdio.h>

// Função que calcula a maior lacuna binária de um número inteiro positivo
int Solucao(int numero) {
    int maior_lacuna = 0;          // Armazena o comprimento da maior lacuna encontrada
    int lacuna_atual = 0;          // Contador de zeros da lacuna atual
    int encontrou_um = 0;          // Flag para indicar se já encontramos o primeiro '1' na representação binária

    // Enquanto o número ainda tiver bits para serem verificados
    while (numero > 0) {

        // Verifica se o bit menos significativo (à direita) é 1
        if (numero & 1) {
            // Se já havíamos encontrado um '1' antes, é o fim de uma lacuna
            if (encontrou_um) {
                // Verifica se a lacuna atual é maior que a maior encontrada até agora
                if (lacuna_atual > maior_lacuna)
                    maior_lacuna = lacuna_atual; // Atualiza o valor da maior lacuna
            }

            encontrou_um = 1;        // Marca que já encontramos o primeiro '1'
            lacuna_atual = 0;        // Reinicia o contador de lacuna, pois a lacuna terminou aqui
        } 
        else {
            // Se já encontramos um '1' antes, começamos a contar os zeros
            if (encontrou_um)
                lacuna_atual++;     // Incrementa a lacuna atual (mais um zero)
        }

        // Desloca os bits do número para a direita para analisar o próximo bit
        numero >>= 1;
    }

    // Retorna o comprimento da maior lacuna binária encontrada
    return maior_lacuna;
}
int main() {
    int numero = 1041;
    printf("Maior lacuna binária de %d: %d\n", numero, Solucao(numero)); // Saída: 5

    numero = 32;
    printf("Maior lacuna binária de %d: %d\n", numero, Solucao(numero)); // Saída: 0

    numero = 529;
    printf("Maior lacuna binária de %d: %d\n", numero, Solucao(numero)); // Saída: 4

    return 0;
}
