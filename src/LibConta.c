#include <stdio.h>
#include <time.h>
#include <string.h>
#include "conta.h"

static Conta conta_global; //declara conta

void data_hora_agora(char quando[20]){  //funcao do time.h
    time_t agora = time(NULL);
    struct tm *info = localtime(&agora);
    
    strftime(quando, 20, "%Y/%m/%d %H:%M:%S", info);
}

void imprimir_reais(long long centavos) {              // reais centavos
    int reais = centavos / 100;
    int cents = centavos % 100;
    printf("%d,%02d\n", reais, cents);
}

void conta_init(void){
    conta_global.saldo_corrente = 0;
    conta_global.saldo_poupanca = 0;
    
    for(int i=0; i<MAX_TRANS; i++){
        conta_global.log[i].saldo_corrente_apos = 0;
        conta_global.log[i].saldo_poupanca_apos = 0;    
    }    
}

int depositar(long long valor){                     //depositar
    if (valor <=  0) return ERRO_VALOR_INVALIDO;
    
    conta_global.saldo_corrente += valor;
    
    conta_global.log[conta_global.nlog].tipo = DEP; 
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int sacar(long long valor){                                                     //sacar
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;

    conta_global.saldo_corrente -= valor;
     
    conta_global.log[conta_global.nlog].tipo = SAQ; 
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int aplicar_poupanca(long long valor){                                         //aplicar poupanca
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;
    
    conta_global.saldo_corrente -= valor;
    conta_global.saldo_poupanca += valor;

    conta_global.log[conta_global.nlog].tipo = APLI; 
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente);
    conta_global.log[conta_global.nlog].saldo_poupanca_apos = (conta_global.saldo_poupanca);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int  resgatar_poupanca(long long valor){                                        //resgatar poupanca
    if (valor > conta_global.saldo_poupanca) return ERRO_SALDO_INSUFICIENTE;
    
    conta_global.saldo_poupanca -= valor;
    conta_global.saldo_corrente += valor;
    
    conta_global.log[conta_global.nlog].tipo = RESG;
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_poupanca_apos = (conta_global.saldo_poupanca);
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int fazer_pix(const char destino[], long long valor){                           //pix
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;

    conta_global.saldo_corrente -= valor;
    
    conta_global.log[conta_global.nlog].tipo = PIX;
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente);
    strcpy(conta_global.log[conta_global.nlog].destino, destino);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;

}

void render_poupanca(double rendimento_mensal){                             //render poupanca
    if (conta_global.saldo_poupanca <= 0) return ERRO_SALDO_INSUFICIENTE;

    long long rendimento_flat = (conta_global.saldo_poupanca * rendimento_mensal);
    conta_global.saldo_poupanca += rendimento_flat;

    conta_global.log[conta_global.nlog].tipo = REND;
    conta_global.log[conta_global.nlog].valor = rendimento_flat;
    conta_global.log[conta_global.nlog].saldo_poupanca_apos = (conta_global.saldo_poupanca);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int  receber_pix(long long valor){                  //pix
   if (valor <= 0) return ERRO_VALOR_INVALIDO;

   conta_global.saldo_corrente += valor;
   
   conta_global.log[conta_global.nlog].tipo = PIXR;
   conta_global.log[conta_global.nlog].valor = valor;
   conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente);
   data_hora_agora(conta_global.log[conta_global.nlog].quando);
   conta_global.nlog++;
   return OK;
}

long long saldo_corrente(void){
    return conta_global.saldo_corrente;
}

long long saldo_poupanca(void){
    return conta_global.saldo_poupanca;
}

void extrato_imprimir(void){
    printf("\n---> Extrato da sua conta! <---\n");

    for(int i=0; i < conta_global.nlog; i++){
        printf("--> Transação %d:\n", i+1);
        printf("--> Tipo: %d\n", conta_global.log[i].tipo);
        
        if (conta_global.log[i].tipo == 0 || conta_global.log[i].tipo == 3 || conta_global.log[i].tipo == 6)
            printf("--> Valor: R$ "); imprimir_reais(conta_global.log[i].valor);
            
        if (conta_global.log[i].tipo == 1 || conta_global.log[i].tipo == 2 || conta_global.log[i].tipo == 4)
            printf("--> Valor: R$ -"); imprimir_reais(conta_global.log[i].valor);
            
        printf("--> Saldo em conta após: R$ "); imprimir_reais(conta_global.log[i].saldo_corrente_apos);
        printf("--> Saldo em poupança após: R$ "); imprimir_reais(conta_global.log[i].saldo_poupanca_apos);
        
        if (conta_global.log[i].tipo == 4)
            printf("Destino do Pix: %s\n", conta_global.log[i].destino);
            
        printf("Data e Hora: %s", conta_global.log[i].quando);
    }
}
