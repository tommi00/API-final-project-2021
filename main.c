#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


typedef struct nodo{
    int indicegrafo;
    long cammino;
    struct nodo * next;
    struct nodo * prec;
} grafo_t;


long cammini(long * madiac, int numnodi);
void inserimento_ordinato(grafo_t ** testalistatopk, grafo_t ** codalistatopk, long valore, int numerografo);
void visualizza(grafo_t * l);


int main() {
    int d, k, dimchar;
    int dimint;
    char * str;
    char * ptr;
    long * matrix;

    char azione[15];

    int i, j;
    int countgrafo, flag;
    long retsomma;

    grafo_t * topktesta = NULL;
    grafo_t * topkcoda = NULL;
    grafo_t * topk = NULL;
    grafo_t * tmp;

    countgrafo = -1;
    flag = 1;


    (void)!scanf("%d %d", &d, &k);
    dimchar = d * 11;
    dimint = d * d;

    matrix = malloc(dimint * (sizeof(long)));
    str = malloc(dimchar * (sizeof(char)));

    while (flag == 1) {
        //if( scanf("%s", azione) != 1 ){
        //     break;
        //}
        if( fgets(azione, 15, stdin) == NULL ){
            break;
        }
        //  printf("azione: '%s'\n", azione);

        if (azione[0] == 'A') { //strlen oppure strcmp
            countgrafo++;
            //  printf("%d\n", countgrafo);

            //SCANSIONE:
            for(i = 0; i < d; i++){
                //(void)!scanf("%s", str);
                (void)!fgets(str, dimchar, stdin);
                //printf("%s\n", str);
                j = 0;
                ptr = str;
                while ( *ptr != EOF && j < d ) {
                    if ( *ptr == ',' ) {
                        ptr++;
                    }
                    *(matrix + d * i + j) = (int)strtol(ptr, &ptr, 10);
                    j++;
                }
            }

            retsomma = cammini(matrix, d);
            //printf("somma: %li\n", retsomma);
            if(k != 0) {
                inserimento_ordinato(&topktesta, &topkcoda, retsomma, countgrafo);
                // visualizza(topktesta);
                if (countgrafo > k + 10) {
                    // printf("count>k\n");
                    tmp = topkcoda;
                    // printf("address coda %p\n", topkcoda);
                    // printf("address testa %p\n", topktesta);
                    topkcoda = topkcoda->prec;
                    // printf("address2 coda %p\n", topkcoda);
                    topkcoda->next = NULL;
                    // printf("address3 coda %p\n", topkcoda);

                    free(tmp);
                }
            }

        }else if(azione[0] == 'T') {
            topk = topktesta;
            for (i = 0; (i < k) && (i <= countgrafo); i++) {
                printf("%d", (topk->indicegrafo) );
                topk = topk->next;
                if (!(i == k - 1 || i == countgrafo)) {
                    printf(" ");
                }
            }
            printf("\n");

        }else if( azione[0] == EOF ) {
            flag = 0;
        }
    }
    free(matrix);
    free(str);

    //libero ciò che rimane
    topk = topktesta;
    while(topk != NULL) {
        tmp = topk;
        topk = topk->next;
        free(tmp);
    }

    return 0;
}



long cammini(long * madiac, int numnodi) {      //passo matrice e numero nodi grafi ->num nodi come var globale?
    long distanza[numnodi];
    long distanzaminore, somma;
    int flag[numnodi];
    int i, j, migliore;
    //int flag;
    //long bigger;
    //int ibigger;

    somma = 0;
    flag[0] = 1;
    //flag[0] = 0;
    distanzaminore = 0;
    migliore = 0;

    distanza[0] = 0;       //se stesso nullo
    for (i = 0 + 1; i < numnodi; i++) {
        if (*(madiac + i) == 0) {
            distanza[i] = LONG_MAX;
        }else{
            distanza[i] = *(madiac + i);
        }
        flag[i] = 0;
        //distanzaminore[i] = 0;

        //printf("distanza[%d]: %li\n", i, distanza[i]);
        //printf("cammino[%d]: %d\n", i, cammino[i]);
    }

    for(i = 1; i < numnodi -1; i++){
        distanzaminore = LONG_MAX;
        for (j = 0; j < numnodi; j++) {
            if (distanza[j] < distanzaminore && flag[j] == 0) {
                distanzaminore = distanza[j];
                migliore = j;
                //printf("distanzamin: %li\n", distanzaminima);
                //printf("migliore: %d\n", migliore);

            }/*else{
                migliore = j - 1;
            }*/
        }
        //flag = migliore + 1;
        flag[migliore] = 1;
        for (j = 0; j < numnodi; j++) {
            if (flag[j] == 0) {
                if( (*(madiac + migliore * numnodi + j) != 0) && (distanzaminore + *(madiac + migliore * numnodi + j) < distanza[j]) ) {        //DA CONTROLLARE
                    distanza[j] = distanzaminore + *(madiac + migliore * numnodi + j);
                    //printf("val matrice: %li\n", *(madiac + migliore * numnodi + j) );
                    //printf("distanzamin: %li\n", distanzaminima);
                    //printf("distanza%d: %li\n", j, distanza[j]);
                }
            }/*else{
                printf("cammino != 0\n");
                flag[migliore] = 2;
            }
            bigger = madiac->cammino; ////grafo_t
            */
        }
    }
    for (i = 1; i < numnodi; i++) {        //i=0 non serve
        if (distanza[i] != LONG_MAX) {
            somma = somma + distanza[i];
        }
    }
    return somma;
}


void inserimento_ordinato(grafo_t ** testalistatopk, grafo_t ** codalistatopk, long valore, int numerografo) {
    grafo_t * nuovonodo;
    grafo_t * precedente;
    grafo_t * attuale;

    nuovonodo = malloc(sizeof(grafo_t));

    nuovonodo->cammino = valore;
    nuovonodo->indicegrafo = numerografo;
    nuovonodo->next = NULL;

    precedente = NULL;
    attuale = *testalistatopk;

    while(attuale != NULL && valore >= attuale->cammino) {
        precedente = attuale;
        attuale = attuale->next;
    }
    if(*codalistatopk == NULL){
        *codalistatopk = nuovonodo;
    }
    if (precedente == NULL) {       //inserimento per primo
        nuovonodo->next = *testalistatopk;
        nuovonodo->prec = NULL;
        if(attuale != NULL){
            attuale->prec = nuovonodo;      //attuale == testa
        }
        *testalistatopk = nuovonodo;
    } else {
        precedente->next = nuovonodo;
        nuovonodo->next = attuale;
        nuovonodo->prec = precedente;
        if(attuale != NULL){
            attuale->prec = nuovonodo;
        }
        if(attuale == NULL){
            *codalistatopk = nuovonodo;
        }
    }
}

void visualizza(grafo_t * l){
    if(!l)
        return;
    printf("(cammino: %li\t", l->cammino);
    printf("indice: %d\t", l->indicegrafo);
    printf("prec: %p\t", l->prec);
    printf("next: %p)\t", l->next);
    visualizza(l->next);
}