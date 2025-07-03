/*
 * Funcionalidades:
 * 1. Cadastrar carros (codigo, modelo, cor)
 * 2. Listar todos os carros cadastrados
 * 3. Editar cadastros existentes
 * 4. Excluir cadastros com confirma��o
 */

#include <stdio.h>  // Biblioteca padr�o para entrada e sa�da (ex: printf, scanf)

#define MAX 100  // Define o n�mero m�ximo de cadastros permitidos

// Estrutura que representa um carro com c�digo, modelo e cor
struct Carro {
    int codigo;
    char modelo[50];  // String de at� 49 caracteres + 1 para o caractere '\0' de finaliza��o
    char cor[20];
};

// Vetor que armazena at� 100 carros
struct Carro carros[MAX];
// Vari�vel que armazena quantos carros j� foram cadastrados
int qtd = 0;

// Fun��o que cadastra um novo carro
void cadastrar() {
    // Verifica se o limite de cadastros foi atingido
    if (qtd >= MAX) {
        printf("\nLimite de carros atingido (%d cadastros)!\n", MAX);
        return; // Encerra a fun��o
    }

    printf("\n--- NOVO CADASTRO ---\n");

    // Pede os dados do carro: c�digo, modelo e cor
    printf("Codigo: ");
    scanf("%d", &carros[qtd].codigo);
    while(getchar() != '\n'); // Limpa o "lixo" do buffer do teclado

    printf("modelo: ");
    scanf(" %49[^\n]", carros[qtd].modelo); // L� at� 49 caracteres com espa�os
    while(getchar() != '\n'); // Limpa o "lixo" do buffer do teclado
    
    printf("cor: ");
    scanf("%19[^\n]", &carros[qtd].cor);

    // Aumenta o n�mero de carros cadastrados
    qtd++;

    printf("\nCadastro realizado com sucesso!\n");
}

// Fun��o que busca um carro pelo c�digo informado
int buscarPorCodigo(int codigo) {
    int i;
    for (i = 0; i < qtd; i++) {
        if (carros[i].codigo == codigo) {
            return i; // Retorna o �ndice do carro no vetor
        }
    }
    return -1; // Retorna -1 se n�o encontrou
}

// Fun��o que edita os dados de um carro
void editar() {
    int codigo, index;

    printf("\n--- EDITAR CADASTRO ---\n");
    printf("Digite o codigo do carro: ");
    scanf("%d", &codigo);

    // Procure o carro com o c�digo digitado
    index = buscarPorCodigo(codigo);

    // Se n�o encontrar, avisa e retorna
    if (index == -1) {
        printf("\ncarro nao encontrada!\n");
        return;
    }

    // Mostra os dados atuais
    printf("\nEDITANDO CADASTRO:\n");
    printf("Codigo: %d\n", carros[index].codigo);
    printf("modelo: %s\n", carros[index].modelo);
    printf("cor: %s\n\n", carros[index].cor);

    // Pede os novos dados
    printf("Novo nome: ");
    scanf(" %49[^\n]", carros[index].modelo);

    printf("Nova cor: ");
    scanf("%s", &carros[index].cor);

    printf("\nCadastro atualizado com sucesso!\n");
}

// Fun��o que exclui um carro do sistema
void excluir() {
    int codigo, index;
    char confirmacao;

    printf("\n--- EXCLUIR CADASTRO ---\n");
    printf("Digite o codigo do carro: ");
    scanf("%d", &codigo);

    index = buscarPorCodigo(codigo);

    if (index == -1) {
        printf("\ncarro nao encontrada!\n");
        return;
    }

    // Mostra os dados do carro e pede confirma��o
    printf("\nCONFIRMAR EXCLUSAO:\n");
    printf("Codigo: %d\n", carros[index].codigo);
    printf("modelo: %s\n", carros[index].modelo);
    printf("cor: %s\n", carros[index].cor);

    printf("\nTem certeza que deseja excluir? (s/n): ");
    scanf(" %c", &confirmacao);

    // Se confirmar, remove o carro do vetor e ajusta a quantidade
    if (confirmacao == 's' || confirmacao == 'S') {
        int i;
        for (i = index; i < qtd - 1; i++) {
            carros[i] = carros[i + 1]; // Desloca os dados para "tapar o buraco"
        }
        qtd--; // Diminui a quantidade total
        printf("\nCadastro excluido com sucesso!\n");
    } else {
        printf("\nOperacao cancelada.\n");
    }
}

// Fun��o que lista todo os carros cadastradas
void listar() {
    printf("\n--- CARROS CADASTRADOS ---\n");
    printf("Total: %d\n\n", qtd);

    if (qtd == 0) {
        printf("Nenhum carro cadastrada.\n");
        return;
    }

    // Cabe�alho da tabela
    printf("CODIGO  MODELO%-42s COR\n", "");
    printf("--------------------------------------------------\n");

    // Mostra os dados de cada carro
    int i;
    for (i = 0; i < qtd; i++) {
        printf("%-8d%-45s%-15s\n",
               carros[i].codigo,
               carros[i].modelo,
               carros[i].cor);
    }
}

// Fun��o principal (ponto de entrada do programa)
int main() {
    int op;

    printf("\n----------------------------------------");
    printf("\n    SISTEMA DE CADASTRO DE CARROS");
    printf("\n----------------------------------------\n");

    // Loop principal do menu
    do {
        printf("\n----------- MENU PRINCIPAL -----------\n");
        printf("1. Cadastrar novo carro\n");
        printf("2. Listar todos os carros\n");
        printf("3. Editar cadastro existente\n");
        printf("4. Excluir cadastro\n");
        printf("0. Sair do sistema\n");
        printf("--------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &op);
        while(getchar() != '\n'); // Limpa o buffer do teclado

        // Executa a op��o escolhida
        switch (op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: editar(); break;
            case 4: excluir(); break;
            case 0: printf("\nEncerrando sistema...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (op != 0); // Repete at� o usu�rio escolher sair

    printf("\nObrigado por utilizar o sistema!\n");
    return 0; // Finaliza o programa
}
