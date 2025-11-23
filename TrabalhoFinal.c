#include <stdio.h>
#include "LibConta.h"

int menu(){ //menu mostrar iniciar
    char opcao;
    
    printf("\n--------VOID BANK--------\n");
    printf("1.Depositar\n");
    printf("2.Sacar\n");
    printf("3.Aplicar na Poupança\n");
    printf("4.Resgatar da Poupança\n");
    printf("5.Fazer PIX\n");
    printf("6.Consultar Saldos\n");
    printf("7.Extrato\n");
    printf("8.SAIR\n");
    
    scanf("%c", &opcao);
        
    return opcao;
}

int main(){
    char opcao;
    long long valor = 0;
    int retornos;
    conta_init();
    
    do{
        opcao = menu();
        
        switch(opcao){
            case '1': 
            printf("Digite o valor desejado\n");
            scanf("%lld" &valor);
            retornos = depositar(valor);
            if (retornos == 0) printf("foi\n");
            else printf("deu ruim\n");
            extrato_imprimir();
            break;
            
        }
    }while (1)
    return 0;
}
