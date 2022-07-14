/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pessoas.h
 * Author: Utilizador
 *
 * Created on 19 de Maio de 2020, 2:25
 */
//Desenvolvido por Rúben Rodrigues Almeida 2019130955

#ifndef PESSOAS_H
#define PESSOAS_H
#include "espaco.h"
#include "utils.h"
#define MAX 150


typedef struct utente utentes, *pUtentes;
struct utente{
    char identi[MAX];
    int idade;
    char est;
    int dias;
    int id_espaco;
    int id_utente;
    pUtentes prox;
};


pUtentes transfLista(pUtentes p, pUtentes aux);

void voltaIter(pUtentes *p,pUtentes p1,pUtentes p2,pUtentes p3, int *countIt);

void guardaIteracao(pUtentes p,pUtentes *p1,pUtentes *p2,pUtentes *p3, int *countIt);

void gravaPopulacao(pUtentes p);

void gravaReport(pUtentes p,local tab[],int total, int countItT);

void transfUtentes(pUtentes p,local tab[],int total);

void addDoente(pUtentes p,local tab[],int total);

void calcTaxas(pUtentes p);

void calcImun(pUtentes p, int *countIt, int *countItT);

void calcDurMax(pUtentes p);

void mostraPessoaPespaco(pUtentes p,local tab[],int total);

void mostraPessPespaco(pUtentes p, int i,int idTemp[]);

void probRecup(pUtentes p);

void randP(int tab[], int n, int maior);

void infetaP(pUtentes p, int tab[], int n, int idEspaco);

void calcIDinf(pUtentes p, int idEspaco,int tab[], int *n);

void taxaDisseminacao(local tab[],pUtentes p, int total);

void mostraDadosTxt(pUtentes p);

pUtentes lerFichTxt(char *nomeF,local tab[],int total);

#endif /* PESSOAS_H */

