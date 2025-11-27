#include <stdio.h>
#include "conta.h"

#pragma execution_character_set("utf-8")

void limpar_terminal() {                //ANSI
    printf("\033[2J\033[H");
    fflush(stdout);
}

long long ler_centavos() {                //essa funcao scaneia uma string transforma em double e depois typecasta
    char texto[32];                      //pra long long centavos multiplicando por 100. Bom uso do sscanf 
    double valor;                       
    scanf("%31s", texto);

    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') 
            texto[i] = '.';       
    }

    sscanf(texto, "%lf", &valor);
    return (long long)(valor * 100 + 0.5);
}

void imprimir_reais(long long centavos);   //esta na conta.c

int menu(){
    char opcao;
    
    printf("\n1.Depositar\n");
    printf("2.Sacar\n");
    printf("3.Aplicar na Poupança\n");
    printf("4.Resgatar da Poupança\n");
  //printf("5.Fazer PIX\n");
    printf("5.Consultar Saldos\n");
    printf("6.Extrato\n");
    printf("7.SAIR\n");
    printf(">> ");
    
    scanf(" %c", &opcao);
    
    return opcao;
}

int main(){
    char opcao;
    long long valor = 0;
    int retornos;
    char destinoPIX[128];
    
    conta_init();
    limpar_terminal();
    
    printf("\n--------VOID BANK--------\n");
    do{
        opcao = menu();
        
        switch(opcao){
            case '1': 
                printf("Digite o valor que deseja depositar\n>> ");
                valor = ler_centavos();
                retornos = depositar(valor);
                if (retornos != 0) printf("Valor Inválido! Tente Novamente\n");
                else{
                    printf("Valor depositado com sucesso!: R$"); imprimir_reais(valor);
                }
                limpar_terminal();
                break;
                
            case'2':
                printf("Digite o valor que deseja sacar\n>> ");
                valor = ler_centavos();
                retornos = sacar(valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                else{
                    printf("Valor sacado com sucesso!: R$"); imprimir_reais(valor);
                }
                limpar_terminal();
                break;
            
            case '3':
                printf("Digite o valor que deseja aplicar\n>> ");
                valor = ler_centavos();
                retornos = aplicar_poupanca(valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                else{
                    printf("Valor aplicado na poupança com Sucesso: R$"); imprimir_reais(valor);
                }
                limpar_terminal();
                break;
            
            case '4':
                printf("Digite o valor que deseja resgatar\n>> ");
                valor = ler_centavos();
                retornos = resgatar_poupanca(valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                else{
                    printf("Valor resgatado da poupança com sucesso!: R$"); imprimir_reais(valor);
                }
                limpar_terminal();
                break;
            
            /*case '5':
                printf("Digite a chave PIX de destino\n>> ");
                scanf("%128s", destinoPIX);
                printf("Digite o valor do PIX\n>> ");
                valor = ler_centavos();
                retornos = fazer_pix(destinoPIX, valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                else{
                    printf("Valor enviado com sucesso!: R$"); imprimir_reais(valor);
                }
                break; */
            
            case '5':
                printf("Saldo em conta corrente: R$");
                imprimir_reais(saldo_corrente());
                printf("Saldo na poupança: R$");
                imprimir_reais(saldo_poupanca());
                limpar_terminal();
                break;
                
            case '6':
                limpar_terminal();
                extrato_imprimir();
                break;
                
            case '7':
                printf("\nSaindo . . .\n\n");
                break;
                
            default:
                printf("\nOpção Inválida! Tente Novamente\n");
                break;              
        }
        
    }while(opcao !='7');
    
    return 0;
}