#include <stdio.h>
//#include "LibConta.h"

int menu(){ //menu mostrar iniciar
    int opcao;
    
    printf("\n--------VOID BANK--------\n");
    printf("1.Depositar\n");
    printf("2.Sacar\n");
    printf("3.Aplicar na Poupança\n");
    printf("4.Resgatar da Poupança\n");
    printf("5.Fazer PIX\n");
    printf("6.Consultar Saldos\n");
    printf("7.Extrato\n");
    printf("8.SAIR\n");
    
    scanf("%d", &opcao);
        
    return opcao;
}

int main(){
    int opcao;
    conta_init();
    
    do{
        opcao = menu();
        
        switch(opcao){
            case 1:
            
        }
    }    
    
}
