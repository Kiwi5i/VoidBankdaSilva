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
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente + valor);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int sacar(long long valor){
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;

    conta_global.saldo_corrente -= valor;
     
    conta_global.log[conta_global.nlog].tipo = SAQ; 
    conta_global.log[conta_global.nlog].valor = valor;
    conta_global.log[conta_global.nlog].saldo_corrente_apos = (conta_global.saldo_corrente)
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int aplicar_poupanca(long long valor){
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

int  resgatar_poupanca(long long valor){
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

int fazer_pix(const char destino[], long long valor){
    if (valor > conta_global.saldo_corrente) return ERRO_SALDO_INSUFICIENTE;

    conta_global.saldo_corrente -= valor;





}

void render_poupanca(double rendimento_mensal){
    if (conta_global.saldo_poupanca <= 0) return ERRO_SALDO_INSUFICIENTE;

    long long render = long long rendimento_mensal;

    conta_global.saldo_poupanca += render;
    conta_global.log[conta_global.nlog].tipo = REND;
    conta_global.log[conta_global.nlog].valor = render;
    conta_global.log[conta_global.nlog].saldo_poupanca_apos = (conta_global.saldo_poupanca);
    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

int  receber_pix(long long valor){
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
   
   if (conta_global.saldo_corrente <= 0) {
     printf("---> Você não possui saldo na conta corrente :c <---\n");
   }
    return conta_global.saldo_corrente;

    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}

long long saldo_poupanca(void){
    if (conta_global.saldo_corrente <= 0) {
     printf("---> Você não possui saldo na conta corrente poupança :c <---\n");
   }
    return conta_global.saldo_poupanca;

    data_hora_agora(conta_global.log[conta_global.nlog].quando);
    conta_global.nlog++;
    return OK;
}


void extrato_imprimir(void){
    printf("---> Extrato da sua conta! <---\n");

    for(int i=0; i < conta_global.nlog; i++){
        printf("--> Compra %d:\n", i+1);
        printf("--> Valor: %lld:\n", conta_global.log[i].valor);
        printf("---> Tipo: %s", conta_global.log[i].tipo)
    }

}
