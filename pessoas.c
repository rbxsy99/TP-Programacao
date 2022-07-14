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
#include <time.h>
#include <ctype.h>
#include <math.h>
#include "espaco.h"
#include "utils.h"
#define MAX 150

//int countP=0; // Numero de pessoas em análise
//int countIt = 0; //Número de iterações já feitas
//int maior, menor,count; // Guarda o maior e o menor valor de ID dos locais
//int *allID, *allCapacidade; //Cria dois vetores globais para serem armazenados todos os ID's e as Capacidades dos locais


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

pUtentes transfLista(pUtentes p, pUtentes aux){
    pUtentes temp = NULL, aux2 = NULL;
    while(p != NULL){
        temp = malloc(sizeof(utentes));
        strcpy(temp->identi,p->identi);
        temp->idade = p->idade;
        temp->est = p->est;
        temp->dias = p->dias;
        temp->id_utente = p->id_utente;
        temp->id_espaco = p->id_espaco;
        temp->prox = NULL;
        //Inserir no fim
        if(aux == NULL){ // Lista Vazia
            aux = temp;
        }else{
            aux2 = aux;
            while(aux2->prox != NULL){
                aux2 = aux2->prox;
            }
            aux2->prox = temp;
        }
        p = p->prox;
    }
    return aux;
}

void voltaIter(pUtentes *p,pUtentes lista_1,pUtentes lista_2,pUtentes lista_3, int *countIt){
    pUtentes original = NULL;
    int t;
    do{
        printf("\nQuantas iteracoes pretende voltar atras:");
        scanf("%d",&t);
    }while(t > 3 || t <= 0);
    
    if((*countIt) == 1 && lista_1 == NULL){
        t = 3;
    }else if((*countIt) == 1 && lista_2 != NULL && t != 1){
        t = 2;
    }else if((*countIt) == 2 && lista_3 != NULL){
        if(t == 1 || t ==2){
            t = 3;
        }else{
            t = 0;
        }
    }else if((*countIt) == 3){
        if(t == 1){
            t = 2;
        }else if(t == 2){
            t = 3;
        }
    }else if(t == 3){
        if( lista_1 != NULL){
            t = 1;
        }
    }
    if((*countIt) != 0){
        if(t == 1 && lista_1 != NULL){
            original = transfLista(lista_1,original); 
        }else if(t == 2 && lista_2 != NULL){
            original = transfLista(lista_2,original); 
        }else if(t == 3 && lista_3 != NULL){
            original = transfLista(lista_3,original); 
        } 
        printf("\nIteracoes Recuperadas\n");
        *p = original;
    }else{
        printf("\nAinda nao foram executadas iteracoes, impossivel voltar atras.\n");
    }
}

void guardaIteracao(pUtentes p,pUtentes *lista_1,pUtentes *lista_2,pUtentes *lista_3, int *countIt){
    pUtentes p1 = NULL, p2 = NULL, p3 = NULL; 
    if((*countIt) == 3){
        //printf("\n P1 \n");
        p1 = transfLista(p,p1); //Guarda em último lugar
        *lista_1 = p1;
    }else if((*countIt) == 2){
        //printf("\n P2 \n");
        p2 = transfLista(p,p2); //Guarda em segundo lugar
        *lista_2 = p2;
    }else if((*countIt) == 1){
        //printf("\n P3 \n");
        p3 = transfLista(p,p3); //Guarda em primeiro lugar
        *lista_3 = p3;
    }
}

void gravaPopulacao(pUtentes p){ // Grava num ficheiro as informações de toda a população no final de todas as análises
    pUtentes aux = p;
    int totalP = 0;
    while(p !=  NULL){
        totalP++;
        p = p->prox;
    }
    p = aux;
    char nomeF[80];
    printf("Introduza o nome do ficheiro onde pretende gravar a populacao existente:");
    scanf("%s",nomeF);
    FILE *f;
    f = fopen(nomeF,"w");
    if(f == NULL){
        printf("\nErro no acesso ao ficheiro.\n");
        fclose(f);
    }
    fprintf(f,"Pessoas:\n");
    while(p != NULL){
        fprintf(f,"-Nome:%s \tIdade:%d \tEstado:%c \tDias:%d \tEspaco:%d \n",p->identi,p->idade,p->est,p->dias,p->id_espaco);
        p = p->prox;
    }
    fprintf(f,"\nTotal de Pessoas Analisadas:%d\n",totalP);
    fclose(f);
    // Libertar memória alocada para os vetores com informações dos espaços
    //free(allID);
    //free(allCapacidade);
}

void gravaReport(pUtentes p,local tab[],int total, int countItT){ // Cria o ficheiro report.txt com informações sobre a população analisada
    float t_saud = 0, t_doen = 0, t_imun = 0; //Guardas as taxas sobre as pessoas
    pUtentes aux = p;
    int totalP = 0;
    while(p != NULL){
        totalP++;
        p = p->prox;
    }
    p = aux;
    float saud = 0,doen = 0,imun = 0;
    char estado;
    while(aux != NULL){
        estado = aux->est;
        if(estado == 'D'){
            doen++;
        }else if(estado == 'I'){
            imun++;
        }else if(estado == 'S'){
            saud++;
        }
        aux = aux->prox;
    }
    t_saud = (float)(saud/totalP)*100;
    t_doen = (float)(doen/totalP)*100;
    t_imun = (float)(imun/totalP)*100;
    FILE* f;
    f = fopen("report.txt","w");
    if(f == NULL){
        printf("Nao foi possivel aceder ao ficheiro");
        fclose(f);
    }
    fprintf(f,"Report: Simulacao do Modelo de Propagacao do Virus\n");
    fprintf(f,"\n-Espacos-\n");
    for(int i=0;i<total;i++){
        fprintf(f,"ID:%d \tCapacidade:%d \n",tab[i].id_sala,tab[i].capacidade);
    }
    fprintf(f,"\n-Pessoas-\n");
    while(p != NULL){
        fprintf(f,"Nome:%s \tIdade:%d \tEstado:%c \tDias:%d \tEspaco:%d \n",p->identi,p->idade,p->est,p->dias,p->id_espaco);
        p = p->prox;
    }
    fprintf(f,"\nTaxa de Saudaveis:%.1f %%\n",t_saud);
    fprintf(f,"Taxa de Doentes:%.1f %%\n",t_doen);
    fprintf(f,"Taxa de Imunes:%.1f %%\n",t_imun);
    fprintf(f,"Total de Pessoas analisadas:%d\n",totalP);
    fprintf(f,"Total de Iteracoes Realizadas:%d\n",countItT);
    fprintf(f,"\nDesenvolvido por Ruben Almeida 2019130955 - ISEC 2019/20");
    fclose(f);
}

void transfUtentes(pUtentes p,local tab[],int total){ //Transfere utentes de um local para outro escolhidos pelo utilizador, verificando se as ligações correspondem
    pUtentes p_aux = p, p_aux2 = p,p_aux3 = p;
    int orig = 0,dest = 0,totalP = 0;
    printf("\nIntroduza o local de origem:");
    scanf("%d",&orig);
    printf("Introduza o local de destino:");
    scanf("%d",&dest);
    int n_ut = 0;
    printf("Introduza o numero de utentes que pretende transferir:");
    scanf("%d", &n_ut);
    int *CapOcupada;
    CapOcupada = (int*)malloc(total*sizeof(int)); // Array para guardar as capacidades já ocupadas em cada espaço
    for(int i=0;i<total;i++){
        CapOcupada[i] = 0; //Iniciar o vetor a 0
    }
    while(p != NULL){
        for(int i=0;i<total;i++){
            if(p->id_espaco == tab[i].id_sala){
                CapOcupada[i]++;
            }
        }
        p = p->prox;
    }
    p = p_aux;
    while(p != NULL){
        totalP++;
        p = p->prox;
    }
    p = p_aux;
    int *idArray, allID_p[totalP];
    idArray = (int*)malloc(n_ut*sizeof(int)); // O array irá guardar todos os ids de pessoas que estejam no espaço de origem
    int aux = 0;
    int l_orig = 0, l_dest = 0, count_pOri = 0;
    while(p_aux3 != NULL){
        if(p_aux3->id_espaco == orig){
            count_pOri++;
        }
        p_aux3 = p_aux3->prox;
    }
    if(n_ut <= count_pOri){ // Verifica se é possivel tranferir o numero indicado pelo utilizador
        verLig(tab,orig, dest, &aux,total); // Verificar se o espaço de origem tem ligações com o espaço de destino
    }else{
        printf("\nNao pode ser feita a transferencia de utentes.\n");
    }
    int randomP = 0, n = 0, n2=0, temp = 3, maior = 0;
    if(aux == 1){
        for(int i=0;i<total;i++){ //Guardar as localizações dos espaços dentro dos vetores dinamicos com os id's e capacidades dos espaços
            if(tab[i].id_sala == orig){
                l_orig = i;
            }else if(tab[i].id_sala == dest){
                l_dest = i;
            }
        }
        while(p != NULL){
            if(p->id_espaco == orig){ //Guarda no array todos aqueles que pertencem ao espaço de origem
                allID_p[n] = p->id_utente;
                n++;
            }
            p = p->prox;
        }
        for(int i=0;i<totalP;i++){
            if(i > n){
                allID_p[i] = 0;
            }
        }
        
        for(int i=0;i<n;i++){
            if(maior < allID_p[i]){
                maior = allID_p[i];
            }
        }
        while(n2 < n_ut){ //Enquanto o contador for inferior ou igual a numero de pessoas a transferir faz...
            randomP = intUniformRnd(1,maior); // Random de um numero entre 1 e o maior número do array
            for(int i=0;i<n;i++){ // Corre o vetor de todos os ids presente no local de origem da transferencia 
                if(randomP == allID_p[i] && n2 <= n_ut){ // Faz a verificação se o numero random pertence ao vetor
                    if(n2 == 0){
                        idArray[n2] = randomP;
                        n2++;
                    }
                    for(int i=0;i<n2;i++){
                        if(idArray[i] == randomP){
                            temp = 1;
                        }
                    }
                    if(temp == 0){
                        idArray[n2] = randomP;
                        n2++;
                    }
                }
                temp = 0;
            }
        }
        /*for(int i = 0;i<n_ut;i++){ // Ver os dados no vetor com os ids das pessoas que vao ser transferidas 
            printf("\nid:%d\n",idArray[i]);
        }*/
        for(int i = 0;i<n_ut;i++){
            p_aux = p_aux2;
            while(p_aux != NULL){
                if(p_aux->id_utente == idArray[i] && p_aux->id_espaco == orig){
                    for(int i = 0;i<total;i++){
                        if(tab[i].id_sala == p_aux->id_espaco){
                            if((tab[l_dest].capacidade - CapOcupada[l_dest]) >0){
                                p_aux->id_espaco = dest;
                                CapOcupada[l_dest]++;
                                //printf("\n%d - %d - %d - ID:%d\n",CapOcupada[l_dest],(tab[l_dest].capacidade - CapOcupada[l_dest]), tab[l_dest].capacidade, tab[l_dest].id_sala);
                            }else{
                                printf("\nNao ha espaco no local destino.\nTransferencia nao efectuada\n");
                            }
                        }
                    }
                }
                p_aux = p_aux->prox;
            }
        }
    }
    free(CapOcupada);
    free(idArray);
}

void addDoente(pUtentes p, local tab[],int total){ // Adiciona um novo doente à população atual
    pUtentes novo=NULL, aux=NULL, aux2 = p;
    int *CapOcupada;
    CapOcupada = (int*)malloc(total*sizeof(int)); // Array para guardar as capacidades já ocupadas em cada espaço
    for(int i=0;i<total;i++){
        CapOcupada[i] = 0; //Iniciar o vetor a 0
    }
    while(p != NULL){
        for(int i=0;i<total;i++){
            if(p->id_espaco == tab[i].id_sala){
                CapOcupada[i] = CapOcupada[i]+1;
            }
        }
        p = p->prox;
    }
    p = aux2;
    int totalP = 0;
    while(p != NULL){
        totalP++;
        p = p->prox;
    }
    p = aux2;
    char identidade[MAX];
    //Descobrir o maior e menor ID de todos os espaços
    int menor = tab[0].id_sala,maior = tab[0].id_sala;
    for(int i=0;i<total;i++){
        if(tab[i].id_sala > maior){
            maior = tab[i].id_sala;
        }
        if(tab[i].id_sala < menor){
            menor = tab[i].id_sala;
        }
    }
    printf("\nIntroduza o nome do doente:");
    scanf("%s",identidade);
    int ida = 0,dia = 0;
    printf("\nIntroduza a idade do doente:");
    scanf("%d",&ida);
    printf("\nIntroduza a quantos dias o utente esta doente:");
    scanf("%d",&dia);
    char estado = 'D';
    int randomEspaco = 0;
    novo = malloc(sizeof(utentes)); //Alocar espaço para o novo doente
    novo->id_utente = totalP+1;
    strcpy(novo->identi,identidade);
    novo->idade = ida;
    novo->est = estado;
    novo->dias = dia;
    //Função para atribuir de forma aleatória um espaço a cada utente
    int espVer = 0;
    randomEspaco = intUniformRnd(menor,maior);
    do{
        for(int i=0;i<total;i++){
            if(tab[i].id_sala == randomEspaco){
                if((tab[i].capacidade - CapOcupada[i]) > 0){
                    espVer = 1;
                    CapOcupada[i]++;
                    i=total;
                }else{
                    espVer = 2;
                    i=total;
                }
            }else{
                espVer = 0;
            }
        }
        if(espVer == 0){
            randomEspaco = intUniformRnd(menor,maior);
        }
    }while(espVer == 0);
    if(espVer == 2){
        novo->id_espaco = 0;
    }else{
        novo->id_espaco = randomEspaco;
    }
    randomEspaco = 0;
    novo->prox = NULL;
    if(novo->id_espaco != 0 && !isdigit(novo->est) ){
        if(p == NULL){
            p = novo;
        }else{
            aux = p;
            while(aux->prox != NULL){
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
    free(CapOcupada);
}

void calcTaxas(pUtentes p){ // Calcula a taxa de saudaveis, doentes e imunes ao virus
    pUtentes aux = p;
    float saud = 0,doen = 0,imun = 0, totalP = 0;
    float t_saud = 0, t_doen = 0, t_imun = 0; //Guardas as taxas sobre as pessoas
    while(p != NULL){
        totalP++;
        p = p->prox;
    }
    p = aux;
    char estado;
    while(p != NULL){
        estado = p->est;
        if(estado == 'D'){
            doen++;
        }else if(estado == 'I'){
            imun++;
        }else if(estado == 'S'){
            saud++;
        }
        p = p->prox;
    }
    //printf("\n S:%f D:%f I:%f C:%d", saud,doen,imun,totalP);
    t_saud = (float)(saud/totalP)*100;
    printf("\nTaxa de Pessoas Saudaveis: %.2f %%",t_saud);
    t_doen = (float)(doen/totalP)*100;
    printf("\nTaxa de Pessoas Doentes: %.2f %%",t_doen);
    t_imun = (float)(imun/totalP)*100;
    printf("\nTaxa de Pessoas Imunes: %.2f %% \n",t_imun);
}

void mostraPessPespaco(pUtentes p, int i,int idTemp[]){ // Mostra na consola as pessoas por espaço
    int espA;
    int id = idTemp[i];
    while(p != NULL){
        espA = p->id_espaco;
        if(espA == id){
            printf("-%s \t %d \t %c \t %d \t %d \n",p->identi,p->idade,p->est,p->dias,p->id_espaco);
        }
        p = p->prox;
    }
}

void mostraPessoaPespaco(pUtentes p,local tab[],int total){ // Cria um novo vetor e coloca por onde crescente os id's dos espaços todos
    int idTemp[total];
    for(int i=0;i<total;i++){
        idTemp[i] = tab[i].id_sala;
    }
    //Ordenar o array dos ID's dos espaços do menor para maior
    int temp;
    for(int i=0;i<total;i++){
        for(int j=0;j<total;j++){
            if(idTemp[j] > idTemp[i]){
                temp = idTemp[i];
                idTemp[i] = idTemp[j];
                idTemp[j] = temp;
            }
        }
    }
    for(int i=0;i<total;i++){
        printf("\nEspaco %d:\n", idTemp[i]);
        mostraPessPespaco(p,i,idTemp);
    }
}

void calcImun(pUtentes p, int *countIt, int *countItT){  // Com probabilidade de 20% se for =1 a pessoa torna-se imune ao virus
    float probI = 0;
    char estado;
    while(p != NULL){
        probI = probEvento(0.2);
        estado = p->est;
        if(estado == 'S' && probI == 1){ // Se a pessoa estiver saudável tem 20% de probabilidade de se tornar imune ao virus
            p->est = 'I';
        }else if(estado == 'D'){ // Se a pessoa continuar doente no final da iteração adiciona mais 1 dia que está doente
            (p->dias)++;
        }
        p=p->prox;
    }
    if((*countIt) == 3){
        *countIt = 1;
    }else{
        (*countIt)++; // Atualiza o valor do total de iterações já realizadas
    }
    (*countItT)++;
}

void calcDurMax(pUtentes p){ // Calcula o tempo máxima que cada pessoa fica doente quando chega esse limite a pessoa volta a tornar-se saudável
    int idade, unidades, dezenas, total;
    while(p != NULL){
        idade = p->idade;
        unidades = idade%10;
        dezenas = (idade - unidades)/10;
        total = 5 + dezenas;
        if(total <= p->dias && p->est == 'D'){
            p->est = 'S';
            p->dias = 0;
        }
        idade = 0;
        unidades = 0;
        dezenas = 0;
        total = 0;
        p = p->prox;
    }
}

void probRecup(pUtentes p){ // Verifica a probabilidade de cada pessoa ser infetada 1/idade
    float probF = 0,prob = 0;
    float idade;
    while(p != NULL){
        idade =  (float) p->idade;
        prob = 1/idade;
        probF = probEvento(prob);
        if(probF == 1){
            p->est = 'S';
            p->dias = 0;
        }
        idade = 0;
        prob = 0;
        probF = 0;
        p = p->prox;
    }
}

void infetaP(pUtentes p, int tab[], int n, int idEspaco){
    while(p != NULL){
        for(int i=0;i<n;i++){
            if(p->id_utente == tab[i] && p->est == 'S' && p->id_espaco == idEspaco){
                p->est = 'D';
                p->dias = 0;
            }
        }
        p = p->prox;
    }
}

void randP(int tab[], int n, int maior){
    for(int i=0;i<n;i++){
        tab[i] = intUniformRnd(1,maior);
    }
}

void calcIDinf(pUtentes p, int idEspaco, int tab[], int *n){
    int i=0;
    while(p != NULL){
        if(p->id_espaco == idEspaco){
            tab[i] = p->id_utente;
            i++;
        }
        p = p->prox;
    }
    *n = i;
}

void taxaDisseminacao(local tab[],pUtentes p,int total){ // Cada doente tem 5% de transmitir o virus por cada iteração as pessoas que estiverem no local
    int pInf=0,idEspaco = 0, n=0;
    pUtentes aux = p, aux2 = p; 
    while(p != NULL){
        n++; //total de pessoas na lista
        p = p->prox;
    }
    p = aux;
    int randomPessoa[n];
    int pessoasInf[n];
    int maior;
    while(p != NULL){
        if(p->est == 'D'){
            idEspaco = p->id_espaco;
            pInf = calcPinf(tab,p->id_espaco,total);
            //printf("\n PessoasInfetadas: %d \n", pInf);
        }
        if(pInf > 0){
            calcIDinf(aux, idEspaco,pessoasInf,&n);
            if(n >= 2){
                for(int i=0;i<n;i++){
                    if(pessoasInf[i] > maior){
                        maior = pessoasInf[i];
                    }
                }
                randP(randomPessoa, n , maior);
                infetaP(aux2, randomPessoa,n,idEspaco);
            }
        }
        maior = 0;
        pInf = 0;
        p = p->prox;
    }
}

void mostraDadosTxt(pUtentes p){ //Mostra conteudo da lista ligada
    if(p == NULL){
        printf("Lista Vazia \n");
    }else{
        while(p != NULL){
            printf("%s \t %d \t %c \t %d \t %d \n", p->identi,p->idade,p->est,p->dias,p->id_espaco);
            p = p->prox;
        }
    }
}

pUtentes lerFichTxt(char *nomeF,local tab[],int total){
    pUtentes p = NULL,novo=NULL,aux = NULL;
    FILE* filetxt;
    filetxt = fopen(nomeF,"r");
    if(filetxt == NULL){
        printf("Erro no acesso ao ficheiro de texto.\n");
        exit(EXIT_SUCCESS); // Senão conseguir aceder ao ficheiro o programa é terminado
    }
    //Criar um vetor para alocar todas as capacidades dos espaços e atualizar
    int *allCapacidade;
    allCapacidade = (int*)malloc(total*sizeof(int)); // Array para guardar as capacidades de cada espaço inserido
    for(int i=0;i<total;i++){
        allCapacidade[i] = tab[i].capacidade;
    }
    //Descobrir o maior e menor ID de todos os espaços
    int menor = tab[0].id_sala,maior = tab[0].id_sala;
    for(int i=0;i<total;i++){
        if(tab[i].id_sala > maior){
            maior = tab[i].id_sala;
        }
        if(tab[i].id_sala < menor){
            menor = tab[i].id_sala;
        }
    }
    //Variaveis a ler do Ficheiro de Texto
    char identidade[MAX];
    int ida = 0,dia = 0;
    char estado;
    int n = 1;
    int randomEspaco = 0;
    while(fscanf(filetxt,"%s %d %c %d",identidade,&ida,&estado,&dia) != EOF ){
        novo = malloc(sizeof(utentes));
        if(novo == NULL){
            fclose(filetxt);
            return p;
        }
         if(estado != 'D'){
            dia = 0;
        }
        novo->id_utente = n;
        strcpy(novo->identi,identidade);
        novo->idade = ida;
        novo->est = estado;
        novo->dias = dia;
        //Função para atribuir de forma aleatória um espaço a cada utente
        int espVer = 0;
        randomEspaco = intUniformRnd(menor,maior);
        do{
            for(int i=0;i<total;i++){
                if(tab[i].id_sala == randomEspaco){
                    if(allCapacidade[i] > 0){
                        espVer = 1;
                        allCapacidade[i]--; // A capacidade do espaço será diminuida e fica atualizada
                        i=total;
                    }else{
                        espVer = 2;
                        i=total;
                    }
                }else{
                    espVer = 0;
                }
            }
            if(espVer == 0){
                randomEspaco = intUniformRnd(menor,maior);
            }
        }while(espVer == 0);
        if(espVer == 2){
            novo->id_espaco = 0; // Se não houver espaço no local escolhido não é inserido na lista ligada
        }else{
            novo->id_espaco = randomEspaco;
        }
        randomEspaco = 0;
        novo->prox = NULL;
        // Insere no final da lista ligada
        if(novo->id_espaco != 0 && !isdigit(novo->est) ){
            if(p == NULL){
                p = novo;
            }else{
                aux = p;
                while(aux->prox != NULL){
                    aux = aux->prox;
                }
                aux->prox = novo;
            }
        }
        n++;
    }
    free(allCapacidade);
    fclose(filetxt);
    return p;
}




