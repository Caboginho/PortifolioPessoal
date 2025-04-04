#include <stdio.h>

// Função auxiliar que conta a quantidade de bits 1 na representação de 'valor'
int contaBitsUm(int valor) {
    int contador = 0;
    // Enquanto ainda houver bits em 'valor'
    while (valor) {
        // Verifica se o bit menos significativo é 1 e incrementa o contador, se for o caso
        contador += (valor & 1);
        // Desloca 'valor' para a direita, descartando o bit já verificado
        valor >>= 1;
    }
    return contador;
}

// Função auxiliar que calcula o número de inteiros de 30 bits em conformidade com um número 'padrao'
// Se 'padrao' possui 1 em algumas posições, os inteiros em conformidade devem ter obrigatoriamente 1 nessas posições.
// Assim, para cada posição com 0 em 'padrao', há duas opções (0 ou 1). Portanto, o total é 2^(30 - número_de_bits_1).
int contaConformidade(int padrao) {
    // Calcula quantos bits 1 estão presentes em 'padrao'
    int bitsUm = contaBitsUm(padrao);
    // O número de posições "livres" é 30 - bitsUm; para cada posição livre há 2 possibilidades
    return 1 << (30 - bitsUm);  // equivalente a 2^(30 - bitsUm)
}

// Função que, dados três inteiros de 30 bits sem sinal A, B e C, retorna o número de inteiros de 30 bits que
// estão em conformidade com pelo menos um dos inteiros fornecidos.
int solucao(int A, int B, int C) {
    // Calcula a quantidade de inteiros em conformidade com cada um dos padrões individualmente:
    int conformesA = contaConformidade(A);
    int conformesB = contaConformidade(B);
    int conformesC = contaConformidade(C);

    // Para os casos em que o inteiro deve estar em conformidade com dois padrões ao mesmo tempo,
    // é necessário que ele esteja em conformidade com a união dos bits definidos.
    // Por exemplo, para A e B, o inteiro deve ter 1 em todas as posições onde A ou B têm 1:
    int conformesAB = contaConformidade(A | B);
    int conformesAC = contaConformidade(A | C);
    int conformesBC = contaConformidade(B | C);

    // Para o caso em que o inteiro deve estar em conformidade com os três padrões (A, B e C),
    // o inteiro deve ter 1 em todas as posições onde pelo menos um deles tem 1:
    int conformesABC = contaConformidade(A | B | C);

    // Aplicamos o princípio da inclusão-exclusão para obter a quantidade de inteiros que estão em conformidade
    // com pelo menos um dos padrões A, B ou C:
    //
    // Quantidade = (conformesA + conformesB + conformesC)
    //              - (conformesAB + conformesAC + conformesBC)
    //              + (conformesABC)
    int totalConformes = conformesA + conformesB + conformesC 
                         - conformesAB - conformesAC - conformesBC 
                         + conformesABC;

    return totalConformes;
}

// Exemplo de uso da função solucao
int main() {
    // Exemplo fornecido:
    // A = 11 1111 1111 1111 1111 1111 1001 1111 (BIN)
    // B = 11 1111 1111 1111 1111 1111 0011 1111 (BIN)
    // C = 11 1111 1111 1111 1111 1111 0110 1111 (BIN)
    // Conforme o problema, o resultado deve ser 8.
    int A = 1073741727;  // Representa o número 11 1111 1111 1111 1111 1111 1001 1111
    int B = 1073741631;  // Representa o número 11 1111 1111 1111 1111 1111 0011 1111
    int C = 1073741679;  // Representa o número 11 1111 1111 1111 1111 1111 0110 1111

    int resultado = solucao(A, B, C);
    printf("Quantidade de inteiros em conformidade: %d\n", resultado);
    // Saída esperada: 8

    return 0;
}
