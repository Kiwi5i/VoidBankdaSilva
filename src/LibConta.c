#include <stdio.h>
#include <time.h>
#include "conta.h"

static Conta conta_global; //tem que ter essa merda pq a funcao de init da conta nao recebe nada como parametro

void data_hora_agora(char quando[20]){
    time_t agora = time(NULL);
    struct tm *info = localtime(&agora);
    
    strftime(quando, 20, "%Y/%m/%d %H:%M:%S", info);
}


int depositar(long long valor){
    if (valor <=  0) return ERRO_VALOR_INVALIDO;
    
    conta_global.saldo_corrente += valor;
    
    conta_global.log[conta_global.nlog].tipo = DEP; 
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente - valor);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int sacar(long long valor){
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;
    
    conta_global.saldo_corrente -= valor;
    return OK;
}

int aplicar_poupanca(long long valor){
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;
    
    conta_global.saldo_corrente -= valor;
    conta_global.saldo_poupanca += valor;
    return OK;
}

int  resgatar_poupanca(long long valor){
    if (valor > conta_global.saldo_poupanca) return ERRO_SALDO_INSUFICIENTE;
    
    conta_global.saldo_poupanca -= valor;
    conta_global.saldo_corrente += valor;
    return OK;
}