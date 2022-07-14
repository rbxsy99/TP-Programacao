/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   espaco.h
 * Author: Utilizador
 *
 * Created on 19 de Maio de 2020, 2:25
 */

#ifndef ESPACO_H
#define ESPACO_H
// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//Desenvolvido por Rúben Rodrigues Almeida 2019130955

//extern int maior, menor,count; // Guarda o maior e o menor valor de ID dos locais
//extern int *allID, *allCapacidade; //Cria dois vetores globais para serem armazenados todos os ID's e as Capacidades dos locais


typedef struct sala local, *pLocal;
struct sala{
    int id_sala;
    int capacidade;
    int liga[3];
};


int verLigacoes(local a, int orig, int dest);

void verLig(local tab[], int orig,int dest,int *aux, int total);

int calcPinf(local tab[],int idEsp, int total);

void escreve_info(local a);

void mostraDadosBin(local tab[],int total);

//void addVetor(local a, int i);

local* lerFichBin(local *tab,int *total);

#endif /* ESPACO_H */

