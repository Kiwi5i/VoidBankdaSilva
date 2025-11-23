#include <stdio.h>
#include "conta.h"

void limpar_terminal() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

long long ler_centavos() {
    char texto[32];
    double valor;

    scanf("%31s", texto);

    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') 
            texto[i] = '.';       
    }

    sscanf(texto, "%lf", &valor);
    return (long long)(valor * 100 + 0.5);
}

int menu(){ //menu mostrar iniciar
    char opcao;
    
    printf("\n--------VOID BANK--------\n\n");
    printf("1.Depositar\n");
    printf("2.Sacar\n");
    printf("3.Aplicar na Poupança\n");
    printf("4.Resgatar da Poupança\n");
    printf("5.Fazer PIX\n");
    printf("6.Consultar Saldos\n");
    printf("7.Extrato\n");
    printf("8.SAIR\n");
    
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
    
    do{
        opcao = menu();
        
        switch(opcao){
            case '1': 
                printf("Digite o valor que deseja depositar\n>> ");
                valor = ler_centavos();
                retornos = depositar(valor);
                if (retornos != 0) printf("Valor Inválido! Tente Novamente\n");
                break;
                
            case'2':
                printf("Digite o valor que deseja sacar\n>> ");
                valor = ler_centavos();
                retornos = sacar(valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                break;
            
            case '3':
                printf("Digite o valor que deseja aplicar\n>> ");
                valor = ler_centavos();
                retornos = aplicar_poupanca(valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                break;
            
            case '4':
                printf("Digite o valor que deseja resgatar\n>> ");
                valor = ler_centavos();
                retornos = resgatar_poupanca(valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                break;
            
            case '5':
                printf("Digite a chave PIX de destino\n>> ");
                scanf("%128s", destinoPIX);
                printf("Digite o valor do PIX\n>> ");
                valor = ler_centavos();
                retornos = fazer_pix(destinoPIX, valor);
                if (retornos != 0) printf("Saldo Insuficiente! Tente Novamente\n");
                break;
            
            case '6':
                printf("Saldo em conta corrente: %lld\n", saldo_corrente());
                printf("Saldo na poupança: %lld\n", saldo_poupanca());
                break;
                
            case '7':
                limpar_terminal();
                extrato_imprimir();
                break;
                
            case '8':
                printf("Saindo . . .");
                break;
                
            default:
                printf("\nOpção Inválida! Tente Novamente\n");
                break;              
        }
        
    }while(opcao !='8');
    
    return 0;
}
