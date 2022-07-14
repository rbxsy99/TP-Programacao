/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Utilizador
 *
 * Created on 19 de Maio de 2020, 2:23
 */
//Desenvolvido por Rúben Rodrigues Almeida 2019130955

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pessoas.h"
#include "espaco.h"
#include "utils.h"
#define MAX 150

//Desenvolvido por Rúben Rodrigues Almeida 2019130955



int menu(){
    int n;
    puts("\n");
    puts("1 - Avancar 1 iteracao na Simulacao");
    puts("2 - Apresentar Estatisticas");
    puts("3 - Adicionar um Doente");
    puts("4 - Transferir Utentes");
    puts("5 - Voltar X Iteracoes");
    puts("6 - Terminar Simulacao");

    do{
        printf("\nOpcao:");
        scanf("%d", &n);
    }while(n < 1 || n > 7);
    return n;
}

int main()
{
    initRandom();
    int n = 0 ;
    int total_esp = 0;
    int countIt = 0; //Irá contar as iterações já efectuadas com isso será possivel voltar iterações atrás
    int countItT = 0; //Irá contar as iterações efetuadas desde o inicio do programa e escrever no relatório final
    local *espaco = NULL;
    pUtentes lista = NULL; //Criar lista
    pUtentes p1 = NULL, p2 = NULL, p3 = NULL; // Criar 3 listas para armazenas até as ultimas 3 iterações podendo ser selecionadas pelo utilizador
    //ler ficheiro binario
    espaco = lerFichBin(espaco,&total_esp);
    mostraDadosBin(espaco,total_esp);
    //criaVetor(espaco, total_esp);
    //ler ficheiro de texto
    char ftxt[80];
    printf("\nIntroduza o nome do ficheiro a carregar com a lista dos utentes:");
    scanf("%s",ftxt);
    fflush(stdin);
    lista = lerFichTxt(ftxt,espaco,total_esp);
    mostraDadosTxt(lista);
    
    do{
        n = menu();
        switch(n){
            case 1: taxaDisseminacao(espaco,lista,total_esp);probRecup(lista);calcDurMax(lista);calcImun(lista,&countIt,&countItT);guardaIteracao(lista,&p1,&p2,&p3,&countIt);mostraDadosTxt(lista);break;
            case 2: mostraPessoaPespaco(lista,espaco,total_esp);calcTaxas(lista);break;
            case 3: addDoente(lista,espaco,total_esp);mostraDadosTxt(lista);break;
            case 4: transfUtentes(lista,espaco,total_esp);break;
            case 5: voltaIter(&lista,p1,p2,p3,&countIt);break;
            case 6: gravaReport(lista,espaco,total_esp,countItT);gravaPopulacao(lista);break;
            case 7: mostraDadosTxt(lista);break;
        }
    }while(n != 6);
}



