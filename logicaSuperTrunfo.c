#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char estado[50];
    int codigo;
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
} Carta;

void cadastrarCarta(Carta *carta) {
    printf("Estado: ");
    scanf("%s", carta->estado);
    printf("Código da carta: ");
    scanf("%d", &carta->codigo);
    printf("Nome da cidade: ");
    scanf("%s", carta->nome);
    printf("População: ");
    scanf("%d", &carta->populacao);
    printf("Área (km²): ");
    scanf("%f", &carta->area);
    printf("PIB: ");
    scanf("%f", &carta->pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);
}

void exibirCarta(Carta carta) {
    printf("\n--- Carta de %s ---\n", carta.nome);
    printf("Estado: %s\n", carta.estado);
    printf("Código: %d\n", carta.codigo);
    printf("População: %d habitantes\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f\n", carta.pib);
    printf("Pontos turísticos: %d\n", carta.pontos_turisticos);
    printf("Densidade populacional: %.2f hab/km²\n", carta.populacao / carta.area);
}

void compararDoisAtributos(Carta c1, Carta c2, int atributo1, int atributo2) {
    char *nomesAtributos[] = {
        "", "população", "área", "PIB", "pontos turísticos", "densidade populacional"
    };
    
    float valores1[2], valores2[2];
    
    // Calcular valores para o primeiro atributo
    switch(atributo1) {
        case 1: valores1[0] = c1.populacao; valores2[0] = c2.populacao; break;
        case 2: valores1[0] = c1.area; valores2[0] = c2.area; break;
        case 3: valores1[0] = c1.pib; valores2[0] = c2.pib; break;
        case 4: valores1[0] = c1.pontos_turisticos; valores2[0] = c2.pontos_turisticos; break;
        case 5: valores1[0] = c1.populacao / c1.area; valores2[0] = c2.populacao / c2.area; break;
    }
    
    // Calcular valores para o segundo atributo
    switch(atributo2) {
        case 1: valores1[1] = c1.populacao; valores2[1] = c2.populacao; break;
        case 2: valores1[1] = c1.area; valores2[1] = c2.area; break;
        case 3: valores1[1] = c1.pib; valores2[1] = c2.pib; break;
        case 4: valores1[1] = c1.pontos_turisticos; valores2[1] = c2.pontos_turisticos; break;
        case 5: valores1[1] = c1.populacao / c1.area; valores2[1] = c2.populacao / c2.area; break;
    }
    
    printf("\nComparando por %s e %s...\n", nomesAtributos[atributo1], nomesAtributos[atributo2]);
    
    // Determinar se menor ou maior valor vence para cada atributo
    bool menorVence1 = (atributo1 == 5); // Densidade populacional
    bool menorVence2 = (atributo2 == 5); // Densidade populacional
    
    // Comparar primeiro atributo
    int resultado1 = (menorVence1 ? (valores1[0] < valores2[0] ? 1 : (valores2[0] < valores1[0] ? -1 : 0)) 
                              : (valores1[0] > valores2[0] ? 1 : (valores2[0] > valores1[0] ? -1 : 0)));
    
    // Comparar segundo atributo
    int resultado2 = (menorVence2 ? (valores1[1] < valores2[1] ? 1 : (valores2[1] < valores1[1] ? -1 : 0)) 
                              : (valores1[1] > valores2[1] ? 1 : (valores2[1] > valores1[1] ? -1 : 0)));
    
    // Determinar vencedor
    if (resultado1 > 0 || (resultado1 == 0 && resultado2 > 0)) {
        printf("%s vence! ", c1.nome);
        if (resultado1 > 0) {
            printf("Melhor em %s (%.2f vs %.2f)", nomesAtributos[atributo1], valores1[0], valores2[0]);
            if (resultado2 >= 0) printf(" e ");
        }
        if (resultado2 > 0) {
            printf("melhor em %s (%.2f vs %.2f)", nomesAtributos[atributo2], valores1[1], valores2[1]);
        } else if (resultado1 > 0 && resultado2 == 0) {
            printf("empate em %s (%.2f)", nomesAtributos[atributo2], valores1[1]);
        }
        printf("\n");
    } else if (resultado2 > 0 || (resultado2 == 0 && resultado1 > 0)) {
        printf("%s vence! ", c2.nome);
        if (resultado2 > 0) {
            printf("Melhor em %s (%.2f vs %.2f)", nomesAtributos[atributo2], valores2[1], valores1[1]);
            if (resultado1 >= 0) printf(" e ");
        }
        if (resultado1 > 0) {
            printf("melhor em %s (%.2f vs %.2f)", nomesAtributos[atributo1], valores2[0], valores1[0]);
        } else if (resultado2 > 0 && resultado1 == 0) {
            printf("empate em %s (%.2f)", nomesAtributos[atributo1], valores1[0]);
        }
        printf("\n");
    } else {
        printf("Empate total! Ambas têm os mesmos valores nos atributos comparados.\n");
    }
}

int main() {
    printf("=== Super Trunfo - Países (Nível Mestre) ===\n\n");
    
    Carta carta1, carta2;
    int opcao, atributo1, atributo2;
    bool sair = false;
    
    printf("Cadastro da primeira carta:\n");
    cadastrarCarta(&carta1);
    exibirCarta(carta1);
    
    printf("\nCadastro da segunda carta:\n");
    cadastrarCarta(&carta2);
    exibirCarta(carta2);
    
    while (!sair) {
        printf("\nMenu Principal:\n");
        printf("1 - Comparar por um atributo\n");
        printf("2 - Comparar por dois atributos\n");
        printf("3 - Exibir cartas novamente\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: {
                printf("\nEscolha o atributo para comparação:\n");
                printf("1 - População\n");
                printf("2 - Área\n");
                printf("3 - PIB\n");
                printf("4 - Pontos turísticos\n");
                printf("5 - Densidade populacional\n");
                printf("Opção: ");
                scanf("%d", &atributo1);
                
                if (atributo1 >= 1 && atributo1 <= 5) {
                    compararDoisAtributos(carta1, carta2, atributo1, atributo1);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            }
            case 2: {
                printf("\nEscolha o primeiro atributo:\n");
                printf("1 - População\n");
                printf("2 - Área\n");
                printf("3 - PIB\n");
                printf("4 - Pontos turísticos\n");
                printf("5 - Densidade populacional\n");
                printf("Opção: ");
                scanf("%d", &atributo1);
                
                printf("\nEscolha o segundo atributo:\n");
                printf("1 - População\n");
                printf("2 - Área\n");
                printf("3 - PIB\n");
                printf("4 - Pontos turísticos\n");
                printf("5 - Densidade populacional\n");
                printf("Opção: ");
                scanf("%d", &atributo2);
                
                if ((atributo1 >= 1 && atributo1 <= 5) && (atributo2 >= 1 && atributo2 <= 5)) {
                    compararDoisAtributos(carta1, carta2, atributo1, atributo2);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            }
            case 3:
                exibirCarta(carta1);
                exibirCarta(carta2);
                break;
            case 0:
                sair = true;
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    
    return 0;
}