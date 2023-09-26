// Creator: Henrique Lima Volponi
// Created: <2023-09-05 Mon 10:10>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <conio.h>

#define TAM 100

typedef struct
{
    int numero;
    char nome[50];
    float saldo;
} Conta;

void limpaTela()
{
    system("cls");
}

void pausaTela()
{
    system("pause");
}

void limpaBuffer()
{
    fflush(stdin);
}

void validaNumeroConta(int *numero)
{
    while (*numero <= 0)
    {
        printf("Numero da conta invalido!\n");
        printf("Digite novamente: ");
        scanf("%d", numero);
    }
}

void validaValor(float *valor)
{
    while (*valor <= 0)
    {
        printf("Valor invalido!\n");
        printf("Digite novamente: ");
        scanf("%f", valor);
    }
}

void validaNome(char *nome)
{
    int i, tamanho;
    tamanho = strlen(nome);
    for (i = 0; i < tamanho; i++)
    {
        if (isdigit(nome[i]))
        {
            printf("Nome invalido!\n");
            printf("Digite novamente: ");
            limpaBuffer();
            gets(nome);
            i = -1;
        }
    }
}

void criarConta(Conta *contas, int *quantidade)
{
    int numero;
    char nome[50];
    float saldo;
    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    validaNumeroConta(&numero);
    printf("Digite o nome do cliente: ");
    limpaBuffer();
    gets(nome);
    validaNome(nome);
    printf("Digite o saldo inicial: ");
    scanf("%f", &saldo);
    validaValor(&saldo);
    contas[*quantidade].numero = numero;
    strcpy(contas[*quantidade].nome, nome);
    contas[*quantidade].saldo = saldo;
    (*quantidade)++;
    printf("Conta criada com sucesso!\n");
    pausaTela();
}

void depositar(Conta *contas, int quantidade)
{
    int numero, i;
    float valor;
    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    validaNumeroConta(&numero);
    for (i = 0; i < quantidade; i++)
    {
        if (contas[i].numero == numero)
        {
            printf("Digite o valor do deposito: ");
            scanf("%f", &valor);
            validaValor(&valor);
            contas[i].saldo += valor;
            printf("Deposito realizado com sucesso!\n");
            pausaTela();
            return;
        }
    }
    printf("Conta nao encontrada!\n");
    pausaTela();
}

void sacar(Conta *contas, int quantidade)
{
    int numero, i;
    float valor;
    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    validaNumeroConta(&numero);
    for (i = 0; i < quantidade; i++)
    {
        if (contas[i].numero == numero)
        {
            printf("Digite o valor do saque: ");
            scanf("%f", &valor);
            validaValor(&valor);
            if (contas[i].saldo >= valor)
            {
                contas[i].saldo -= valor;
                printf("Saque realizado com sucesso!\n");
                pausaTela();
                return;
            }
            else
            {
                printf("Saldo insuficiente!\n");
                pausaTela();
                return;
            }
        }
    }
    printf("Conta nao encontrada!\n");
    pausaTela();
}

void transferir(Conta *contas, int quantidade)
{
    int numeroOrigem, numeroDestino, i;
    float valor;
    printf("Digite o numero da conta de origem: ");
    scanf("%d", &numeroOrigem);
    validaNumeroConta(&numeroOrigem);
    for (i = 0; i < quantidade; i++)
    {
        if (contas[i].numero == numeroOrigem)
        {
            printf("Digite o numero da conta de destino: ");
            scanf("%d", &numeroDestino);
            validaNumeroConta(&numeroDestino);
            for (i = 0; i < quantidade; i++)
            {
                if (contas[i].numero == numeroDestino)
                {
                    printf("Digite o valor da transferencia: ");
                    scanf("%f", &valor);
                    validaValor(&valor);
                    if (contas[i].saldo >= valor)
                    {
                        contas[i].saldo -= valor;
                        contas[i].saldo += valor;
                        printf("Transferencia realizada com sucesso!\n");
                        pausaTela();
                        return;
                    }
                    else
                    {
                        printf("Saldo insuficiente!\n");
                        pausaTela();
                        return;
                    }
                }
            }
            printf("Conta de destino nao encontrada!\n");
            pausaTela();
            return;
        }
    }
    printf("Conta de origem nao encontrada!\n");
    pausaTela();
}

void consultarSaldo(Conta *contas, int quantidade)
{
    int numero, i;
    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    validaNumeroConta(&numero);
    for (i = 0; i < quantidade; i++)
    {
        if (contas[i].numero == numero)
        {
            printf("Saldo: %.2f\n", contas[i].saldo);
            pausaTela();
            return;
        }
    }
    printf("Conta nao encontrada!\n");
    pausaTela();
}

void excluirConta(Conta *contas, int *quantidade)
{
    int numero, i;
    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    validaNumeroConta(&numero);
    for (i = 0; i < *quantidade; i++)
    {
        if (contas[i].numero == numero)
        {
            contas[i] = contas[*quantidade - 1];
            (*quantidade)--;
            printf("Conta excluida com sucesso!\n");
            pausaTela();
            return;
        }
    }
    printf("Conta nao encontrada!\n");
    pausaTela();
}

void salvarDados(Conta *contas, int quantidade)
{
    FILE *arquivo;
    int i;
    arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        pausaTela();
        return;
    }
    fprintf(arquivo, "%d\n", quantidade);
    for (i = 0; i < quantidade; i++)
    {
        fprintf(arquivo, "%d\n", contas[i].numero);
        fprintf(arquivo, "%s\n", contas[i].nome);
        fprintf(arquivo, "%.2f\n", contas[i].saldo);
    }
    fclose(arquivo);
}

void lerDados(Conta *contas, int *quantidade)
{
    FILE *arquivo;
    int i;
    arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        pausaTela();
        return;
    }
    fscanf(arquivo, "%d\n", quantidade);
    for (i = 0; i < *quantidade; i++)
    {
        fscanf(arquivo, "%d\n", &contas[i].numero);
        fgets(contas[i].nome, 50, arquivo);
        contas[i].nome[strlen(contas[i].nome) - 1] = '\0';
        fscanf(arquivo, "%f\n", &contas[i].saldo);
    }
    fclose(arquivo);
}

void menu()
{
    printf("1-Criar conta\n");
    printf("2-Depositar\n");
    printf("3-Sacar\n");
    printf("4-Transferir\n");
    printf("5-Consultar saldo\n");
    printf("6-Excluir conta\n");
    printf("7-Sair\n");
    printf("Digite a opcao desejada: ");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Conta contas[TAM];
    int quantidade = 0, opcao;
    lerDados(contas, &quantidade);
    do
    {
        limpaTela();
        menu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            limpaTela();
            criarConta(contas, &quantidade);
            break;
        case 2:
            limpaTela();
            depositar(contas, quantidade);
            break;
        case 3:
            limpaTela();
            sacar(contas, quantidade);
            break;
        case 4:
            limpaTela();
            transferir(contas, quantidade);
            break;
        case 5:
            limpaTela();
            consultarSaldo(contas, quantidade);
            break;
        case 6:
            limpaTela();
            excluirConta(contas, &quantidade);
            break;
        case 7:
            limpaTela();
            salvarDados(contas, quantidade);
            break;
        default:
            printf("Opcao invalida!\n");
            pausaTela();
            break;
        }
    } while (opcao != 7);
    return 0;
}
//fim
