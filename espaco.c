/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//Desenvolvido por Rúben Rodrigues Almeida 2019130955

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int maior, menor,count; // Guarda o maior e o menor valor de ID dos locais
//int *allID, *allCapacidade; //Cria dois vetores globais para serem armazenados todos os ID's e as Capacidades dos locais


typedef struct sala local, *pLocal;
struct sala{
    int id_sala;
    int capacidade;
    int liga[3];
};

int verLigacoes(local a, int orig, int dest){ //Vê se o espaço de origem tem ligações com o local de destino - Secundária
    int temp = 0;
    if(a.id_sala == orig){
        for(int i=0;i<3;i++){
            if(a.liga[i] == dest){
                //printf("\nID:%d / ORIG:%d /LIGA:%d / DEST:%d",a.id_sala,orig,a.liga[i],dest);
                temp = 1;
            }
        }
    }
    return temp;
}

void verLig(local tab[], int orig,int dest,int *aux, int total){ //Vê se o espaço de origem tem ligações com o local de destino
    int temp = 0;
    for(int i=0;i<total;i++){
        temp = verLigacoes(tab[i],orig,dest);
        if(temp == 1){
            *aux = temp;
        }
    }
}

int calcPinf(local tab[],int idEsp,int total){ //Calcula a quantidade de pessoas que podem ser infetadas por espaços
    float temp = 0;
    for(int i=0;i<total;i++){
        if(idEsp == tab[i].id_sala){
            temp = (tab[i].capacidade * 5)/100;
        }
    }
    return (int)temp;
}

void escreve_info(local a){ // Mostra na consola as informações dos espaços
    printf("ID: %d | Capacidade: %d | Ligacoes: %d , %d , %d \n",a.id_sala,a.capacidade,a.liga[0],a.liga[1],a.liga[2]);
}

void mostraDadosBin(local tab[],int total){ // Chama a função para escrever na consola
    for(int i=0;i<total;i++){
        escreve_info(tab[i]);
    }
}

/*void addVetor(local a, int i){ // Adiciona aos dois vetores globais dinamicos a informação de todos os id's e capacidades para ser mais facil usar essas informações 
    allID[i] = a.id_sala; // Guarda o ID da sala
    allCapacidade[i] = a.capacidade; // Guarda a capacidade da sala
}*/

local* lerFichBin(local *tab,int *total){ //Ler dados do ficheiro binário e verifica se todas as ligações estão certas e só depois adiciona ao vetor dinamicos de estrutura
    char fbin[80];
    printf("Introduza o nome do ficheiro a carregar com espaco pretendido:");
    scanf("%s",fbin);
    fflush(stdin);
    FILE* filebin;
    filebin = fopen(fbin,"rb");
    if(filebin == NULL){
        printf("\nErro no acesso ao ficheiro\n");
        exit(EXIT_SUCCESS); // Senão conseguir aceder ao ficheiro o programa é terminado
    }
    local c;
    int idLiga[3], idSala,num; // Variaveis para guardar o id da sala e todas as suas ligações para verificar com o resto dos locais no ficheiro
    
    //Calcular numero de locais
    fseek(filebin,0,SEEK_END);
    num = ftell(filebin)/sizeof(local);
    fseek(filebin,0,SEEK_SET); //Colocar o ficheiro no inicio
    //printf("\nNUMERO TOTAL: %d \n",num);
    int n = num;
    fseek(filebin,0,SEEK_SET); //Colocar o ficheiro no inicio
    
    //Ciclo para Verificar Ligações
    while(fread(&c,sizeof(local),1,filebin) == 1){
        //Verificar ligações
        idSala = c.id_sala;
        //Cria um vetor e guarda todas as ligações do espaço a ser analisado
        for(int i=0;i<3;i++){
            idLiga[i] = c.liga[i];
        }
        //printf("\nId salaAnalise: %d \n",idSala);
        fseek(filebin,0,SEEK_SET); //Volta para o inicio do ficheiro para fazer a verificação das ligações
        //Lê o ficheiro desde o Início
        while(fread(&c,sizeof(local),1,filebin) == 1){
            for(int i=0;i<3;i++){
                if(idSala == c.liga[i]){ //Se a sala analisada for igual à uma ligação da leitura do ficheiro
                    for(int j=0;j<3;j++){
                        if(idLiga[j] == c.id_sala && c.id_sala > 0){
                           tab = realloc(tab,sizeof(local)*(*total+1));
                           tab[(*total)++] = c;
                           j=3;
                        }
                    }
                }
                i=3;
            }
            //Caso a parte: Senão tiver ligações -> -1
            if(c.liga[0] == -1 && c.liga[1] == -1 && c.liga[2] == -1 && c.id_sala > 0){
                tab = realloc(tab,sizeof(local)*(*total+1));
                tab[(*total)++] = c;
            }
        }
        n--;
        if(n >= 0){
            fseek(filebin, -(n) * sizeof(local), SEEK_END); //Em vez de colocar no inicio coloca um elemento a frente daquele que foi analisado
        }
    }
    if((num-(*total)) > 0){
       printf("\n%d Locais ilegiveis para a simulacao.\n",(num-(*total)));
    }
    
    /*//Criar arrays com informações sobre os espaços
    allID = (int*)malloc((*total)*sizeof(int)); // Array para guardar todos os IDS dos espaços
    allCapacidade = (int*)malloc((*total)*sizeof(int)); // Array para guardar as capacidades de cada espaço inserido
    for(int i=0;i<(*total);i++){
        addVetor(tab[i],i);
    }*/
    
    /*//Descobrir o maior e menor ID de todos os espaços
    menor = allID[0];
    maior = allID[0];
    for(int i=0;i<count;i++){
        if(allID[i] > maior){
            maior = allID[i];
        }
        if(allID[i] < menor){
            menor = allID[i];
        }
    }*/
    //printf("\nMaior: %d \t Menor: %d \n",maior,menor);
    
    fclose(filebin);
    return tab;
}




