#include <stdio.h>
#include <stdlib.h>
#define MAXS 17
#define MAXS_2 64 //counting sort

typedef struct tagTree{
    char *key;
    struct tagTree *padre, *left, *right, *next;
}tree;


tree *pNil = NULL;
int lung, sz, comp;
char *wrd, *parola;
//la stringa parola non viene mai modificata durante la partita
//quando si usa insertnode si sta inserendo sempre la stringa wrd.
//tree *insertnode(tree*, char*, int lung); senza le var.globl.
void inorder_tree_walk(tree*);
tree *newnode(char*);
void InitNil(tree **p);
void counting_sort(char*, int*);
tree *search_rb(tree *head);
tree *minimum(tree *x);
tree *successor(tree *x);
void distruggiAlbero(tree *head);
void insertnode_fast(tree **node);
void insertnode2(tree **node, tree **utile);


int main(){
    int x, trovato, i, k, j, p, appo, appo_2, y;
    char *wrd_2, *indovina, flags[MAXS_2+1];
    int cunt[MAXS_2], cunts_2[MAXS_2], cunts_3[MAXS_2], cunts_4[MAXS_2], cunts_5[MAXS_2];
    int *posizioni[MAXS_2];
    tree *pTreeee[MAXS_2];
    tree *pTree_2 = NULL;
    tree *filtrati[MAXS_2];
    tree *scorri = NULL;
    tree *elimina = NULL;

    sz = 1;
    sz = scanf("%d", &lung);

    if(lung > MAXS){
        wrd = malloc(sizeof(char)*lung+1);
    }else{
        wrd = malloc(sizeof(char)*MAXS+1);
    }

    if(!wrd){
        printf("Errore allocazione stringa iniziale\n");
        return 0;
    }

    wrd_2 = malloc(sizeof(char)*lung+1);
    if(!wrd_2){
        printf("errore allocazione stringa iniziale 2\n");
        return 0;
    }

    indovina = malloc(sizeof(char)*lung+1);
    if(!indovina){
        printf("errore allocazione stringa iniziale 3\n");
        return 0;
    }

    InitNil(&pNil);

    for(i=0; i<MAXS_2; i++){
        pTreeee[i] = pNil;
        filtrati[i] = pNil;
    }

    scorri = pNil;
    pTree_2 = pNil;
    comp = 0;
    k = 0;

    for(i=0;i<MAXS_2;i++)
        posizioni[i] = malloc(sizeof(int)*(lung+1));

    sz = scanf("%s", wrd);
    while(wrd[0]!= '+'){
        if(wrd[0] == '-')
            k = 0;
        else if(wrd[0]>='0' && wrd[0]<='9')
            k = 1 + wrd[0] -'0';
        else if(wrd[0]>='A' && wrd[0]<='Z')
            k = 1 + 10 + wrd[0] - 'A';
        else if(wrd[0] == '_')
            k = 1 + 10 + 26;
        else if(wrd[0]>='a' && wrd[0]<='z')
            k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
        insertnode_fast(&pTreeee[k]);
        sz = scanf("%s", wrd);
    }

    parola = malloc(sizeof(char)*lung+1);
    if(!parola){
        printf("err. allocazione parola riferim.\n");
        return 0;
    }

    //modificare la condizione in base a clion o sito
    while(sz == 1){
        if(wrd[0] == '+' && wrd[1] == 'i'){
            //inserisci_inizio
            sz = scanf("%s", wrd);
            while(wrd[0]!='+'){
                if(wrd[0] == '-')
                    k = 0;
                else if(wrd[0]>='0' && wrd[0]<='9')
                    k = 1 + wrd[0] -'0';
                else if(wrd[0]>='A' && wrd[0]<='Z')
                    k = 1 + 10 + wrd[0] - 'A';
                else if(wrd[0] == '_')
                    k = 1 + 10 + 26;
                else if(wrd[0]>='a' && wrd[0]<='z')
                    k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
                insertnode_fast(&pTreeee[k]);
                sz = scanf("%s", wrd);
            }
        }else if(wrd[0] == '+' && wrd[1]=='n'){
            //nuova partita
            for(i=0; i<MAXS_2; i++)
                cunts_4[i] = 0;
            for(i=0; i<MAXS_2; i++)
                filtrati[i] = pNil;
            scorri = pNil;
            p = 0;
            for(i=0;i<MAXS_2;i++)
                for(j=0;j<=lung;j++)
                    posizioni[i][j] = 0;
            //parola è da indovinare, x è il numero di tentativi.
            sz = scanf("%s", parola);
            sz = scanf("%d", &x);
            trovato = 0;
            for(i=0; i<MAXS_2; i++){
                cunts_2[i] = 0;
                cunts_3[i] = 0;
                flags[i] = '#';
            }
            counting_sort(parola, cunts_5);
            for(i=0; i<lung; i++)
                indovina[i] = '%';
            indovina[lung] = '\0';

            while(x>0 && !trovato){
                sz = scanf(" %s", wrd);
                if(wrd[0]!='+'){
                    if(wrd[0] == '-')
                        k = 0;
                    else if(wrd[0]>='0' && wrd[0]<='9')
                        k = 1 + wrd[0] -'0';
                    else if(wrd[0]>='A' && wrd[0]<='Z')
                        k = 1 + 10 + wrd[0] - 'A';
                    else if(wrd[0] == '_')
                        k = 1 + 10 + 26;
                    else if(wrd[0]>='a' && wrd[0]<='z')
                        k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
                    pTree_2 = search_rb(pTreeee[k]);
                }

                while(wrd[0] == '+' || pTree_2 == pNil){
                    if(wrd[0] == '+' && wrd[1] == 's'){
                        //stampa_filtrate;
                        if(p){
                            i=0;
                            while(i<MAXS_2){
                                for(scorri = filtrati[i]; scorri!=pNil; scorri = scorri->next)
                                    printf("%s\n", scorri->key);
                                i++;
                            }
                        }else{
                            for(i=0; i<MAXS_2; i++)
                                inorder_tree_walk(pTreeee[i]);
                        }
                    }else if(wrd[0] == '+' && wrd[1] == 'i'){
                        //inserisci_inizio;
                        sz = scanf("%s", wrd);
                        // "&& wrd[11]!='f'", condizione completa, ma l'input è corretto
                        while(wrd[0]!='+'){
                            if(p){
                                appo_2 = 1;
                                for(i=0; i<lung && appo_2; i++){
                                    if(indovina[i]!='%'){
                                        if(wrd[i] != indovina[i])
                                            appo_2 = 0;
                                    }else{
                                        if(wrd[i] == '-')
                                            k = 0;
                                        else if(wrd[i]>='0' && wrd[i]<='9')
                                            k = 1 + wrd[i] -'0';
                                        else if(wrd[i]>='A' && wrd[i]<='Z')
                                            k = 1 + 10 + wrd[i] - 'A';
                                        else if(wrd[i]>='a' && wrd[i]<='z')
                                            k = 1 + 10 + 26 + wrd[i] - 'a';
                                        else if(wrd[i] == '_')
                                            k = MAXS_2-1;

                                        if(posizioni[k][i] == 1)
                                            appo_2 = 0;
                                    }
                                }
                                if(appo_2){
                                    counting_sort(wrd, cunt);
                                    for(i=0; i<MAXS_2 && appo_2; i++){
                                        if(flags[i]=='*'){
                                            if(cunt[i]<cunts_2[i])
                                                appo_2 = 0;
                                        }else if(flags[i]=='$'){
                                            if(cunt[i] != cunts_2[i])
                                                appo_2 = 0;
                                        }
                                    }
                                }
                                if(appo_2){
                                    if(wrd[0] == '-')
                                        k = 0;
                                    else if(wrd[0]>='0' && wrd[0]<='9')
                                        k = 1 + wrd[0] -'0';
                                    else if(wrd[0]>='A' && wrd[0]<='Z')
                                        k = 1 + 10 + wrd[0] - 'A';
                                    else if(wrd[0] == '_')
                                        k = 1 + 10 + 26;
                                    else if(wrd[0]>='a' && wrd[0]<='z')
                                        k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
                                    insertnode2(&pTreeee[k], &pTree_2);
                                    //elimina sarebbe prev, il precedente
                                    elimina = filtrati[k];
                                    scorri = elimina;
                                    j=1;
                                    y = cunts_4[k];
                                    //appo_2 flag dello scorrimento
                                    while(appo_2 && y!=0){
                                        if(scorri->key[j] < wrd[j]){
                                            elimina = scorri;
                                            scorri = scorri->next;
                                            j = 1;
                                            y--;
                                        }else if(scorri->key[j] > wrd[j]){
                                        //interrompo lo scorrimento della "lista"
                                            appo_2 = 0;
                                        }else{
                                            j++;
                                        }
                                    }
                                    //la parola inserita diventa la testa
                                    if(elimina == scorri){
                                        pTree_2->next = scorri;
                                        filtrati[k] = pTree_2;
                                    }else{
                                        elimina->next = pTree_2;
                                        pTree_2->next = scorri;
                                    }
                                    comp++;
                                    cunts_4[k]++;
                                }else{
                                    if(wrd[0] == '-')
                                        k = 0;
                                    else if(wrd[0]>='0' && wrd[0]<='9')
                                        k = 1 + wrd[0] -'0';
                                    else if(wrd[0]>='A' && wrd[0]<='Z')
                                        k = 1 + 10 + wrd[0] - 'A';
                                    else if(wrd[0] == '_')
                                        k = 1 + 10 + 26;
                                    else if(wrd[0]>='a' && wrd[0]<='z')
                                        k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
                                    insertnode_fast(&pTreeee[k]);
                                }
                            }else{
                                if(wrd[0] == '-')
                                    k = 0;
                                else if(wrd[0]>='0' && wrd[0]<='9')
                                    k = 1 + wrd[0] -'0';
                                else if(wrd[0]>='A' && wrd[0]<='Z')
                                    k = 1 + 10 + wrd[0] - 'A';
                                else if(wrd[0] == '_')
                                    k = 1 + 10 + 26;
                                else if(wrd[0]>='a' && wrd[0]<='z')
                                    k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
                                insertnode_fast(&pTreeee[k]);
                            }
                            sz = scanf("%s", wrd);
                        }
                    }else{
                        printf("not_exists\n");
                    }
                    sz = scanf("%s", wrd);

                    if(wrd[0]!='+'){
                        if(wrd[0] == '-')
                            k = 0;
                        else if(wrd[0]>='0' && wrd[0]<='9')
                            k = 1 + wrd[0] -'0';
                        else if(wrd[0]>='A' && wrd[0]<='Z')
                            k = 1 + 10 + wrd[0] - 'A';
                        else if(wrd[0] == '_')
                            k = 1 + 10 + 26;
                        else if(wrd[0]>='a' && wrd[0]<='z')
                            k = 1 + 10 + 26 + 1 + wrd[0] - 'a';
                        pTree_2 = search_rb(pTreeee[k]);
                    }
                }
                trovato = 1;
                for(i=0; i<MAXS_2; i++)
                    cunt[i] = cunts_5[i];
                if(!p){
                    for(i=0, k=0; i<lung; i++){
                        //copio wrd in wrd_2 che mi servirà dopo per la compatibilità
                        wrd_2[i] = wrd[i];
                        if(wrd[i] == parola[i]){
                            if(wrd[i] == '-')
                                k = 0;
                            else if(wrd[i]>='0' && wrd[i]<='9')
                                k = 1 + wrd[i] -'0';
                            else if(wrd[i]>='A' && wrd[i]<='Z')
                                k = 1 + 10 + wrd[i] - 'A';
                            else if(wrd[i]>='a' && wrd[i]<='z')
                                k = 1 + 10 + 26 + wrd[i] - 'a';
                            else if(wrd[i] == '_')
                                k = MAXS_2-1;

                            cunt[k]--;
                            wrd[i]='+';
                            indovina[i] = parola[i];
                            cunts_2[k]++;
                            flags[k] = '*';

                        }else
                            trovato = 0;
                    }

                    if(!trovato){
                        for(i=0; i<lung; i++){
                            if(wrd[i]!='+'){
                                if(wrd[i] == '-')
                                    k = 0;
                                else if(wrd[i]>='0' && wrd[i]<='9')
                                    k = 1 + wrd[i] -'0';
                                else if(wrd[i]>='A' && wrd[i]<='Z')
                                    k = 1 + 10 + wrd[i] - 'A';
                                else if(wrd[i]>='a' && wrd[i]<='z')
                                    k = 1 + 10 + 26 + wrd[i] - 'a';
                                else if(wrd[i] == '_')
                                    k = MAXS_2 - 1;
                                cunt[k]--;
                                if(cunt[k]>=0){     //potenziale bug, va il >=
                                    wrd[i] = '|';
                                    cunts_2[k]++;
                                    flags[k] = '*';
                                }else{
                                    wrd[i] = '/';
                                    flags[k] = '$';
                                }
                                posizioni[k][i] = 1;
                            }
                        }
                    }
                }else{
                    for(i=0; i<MAXS_2; i++)
                        cunts_3[i] = 0;
                    for(i=0; i<lung; i++){
                        //copio wrd in wrd_2 che mi servirà dopo per la compatibilità
                        wrd_2[i] = wrd[i];
                        if(wrd[i] == parola[i]){
                            if(wrd[i] == '-')
                                k = 0;
                            else if(wrd[i]>='0' && wrd[i]<='9')
                                k = 1 + wrd[i] -'0';
                            else if(wrd[i]>='A' && wrd[i]<='Z')
                                k = 1 + 10 + wrd[i] - 'A';
                            else if(wrd[i]>='a' && wrd[i]<='z')
                                k = 1 + 10 + 26 + wrd[i] - 'a';
                            else if(wrd[i] == '_')
                                k = MAXS_2-1;

                            cunt[k]--;
                            wrd[i]='+';
                            indovina[i] = parola[i];
                            cunts_3[k]++;
                            flags[k] = '*';

                        }else
                            trovato = 0;
                    }

                    if(!trovato){
                        for(i=0; i<lung; i++){
                            if(wrd[i]!='+'){
                                if(wrd[i] == '-'){
                                    k = 0;
                                }else if(wrd[i]>='0' && wrd[i]<='9'){
                                    k = 1 + wrd[i] -'0';
                                }else if(wrd[i]>='A' && wrd[i]<='Z'){
                                    k = 1 + 10 + wrd[i] - 'A';
                                }else if(wrd[i]>='a' && wrd[i]<='z'){
                                    k = 1 + 10 + 26 + wrd[i] - 'a';
                                }else if(wrd[i] == '_'){
                                    k = MAXS_2 - 1;
                                }
                                cunt[k]--;
                                if(cunt[k]>=0){     //potenziale bug, va il >=
                                    wrd[i] = '|';
                                    cunts_3[k]++;
                                    flags[k] = '*';
                                }else{
                                    wrd[i] = '/';
                                    flags[k] = '$';
                                }
                                posizioni[k][i] = 1;
                            }
                        }
                    }
                    for(i=0; i<MAXS_2; i++)
                        if(cunts_2[i]<cunts_3[i])
                            cunts_2[i] = cunts_3[i];
                }

                if(trovato)
                    printf("ok\n");
                else{
                    //calcolare numero parole compatibili;                    
                    if(!p){
                        //se albero 2 è vuoto mi controllo tutto l'albero 1;
                        comp = 0;
                        pTree_2 = pNil;
                        i=0;
                        pTree_2 = minimum(pTreeee[i]);
                        while(pTree_2 == pNil && i<MAXS_2){
                            i++;
                            pTree_2 = minimum(pTreeee[i]);
                        }
                        scorri = pNil;

                        while(pTree_2 != pNil){
                            appo = 1;
                            for(j=0; appo && j<lung; j++){
                                if(pTree_2->key[j] == wrd_2[j]){
                                    if(wrd[j] != '+')
                                        appo = 0;
                                }else{
                                    if(wrd[j] == '+')
                                        appo = 0;
                                }
                            }
                            if(appo){
                                counting_sort(pTree_2->key, cunt);
                                for(j=0; appo && j<lung; j++){
                                    if(wrd[j] == '+'){
                                        if(parola[j] == '-'){
                                            k = 0;
                                        }else if(parola[j]>='0' && parola[j]<='9'){
                                            k = 1 + parola[j] -'0';
                                        }else if(parola[j]>='A' && parola[j]<='Z'){
                                            k = 1 + 10 + parola[j] - 'A';
                                        }else if(parola[j]>='a' && parola[j]<='z'){
                                            k = 1 + 10 + 26 + parola[j] - 'a';
                                        }else if(parola[j] == '_'){
                                            k = MAXS_2 - 1;
                                        }
                                        cunt[k]--;
                                        if(cunt[k]<0)
                                            appo = 0;
                                    }else if(wrd[j] == '|'){
                                        if(wrd_2[j] == '-'){
                                            k = 0;
                                        }else if(wrd_2[j]>='0' && wrd_2[j]<='9'){
                                            k = 1 + wrd_2[j] -'0';
                                        }else if(wrd_2[j]>='A' && wrd_2[j]<='Z'){
                                            k = 1 + 10 + wrd_2[j] - 'A';
                                        }else if(wrd_2[j]>='a' && wrd_2[j]<='z'){
                                            k = 1 + 10 + 26 + wrd_2[j] - 'a';
                                        }else if(wrd_2[j] == '_'){
                                            k = MAXS_2 - 1;
                                        }
                                        cunt[k]--;
                                        if(cunt[k]<0)
                                            appo = 0;
                                    }
                                }
                                
                                for(j=0; appo && j<lung; j++){
                                    if(wrd[j] == '/'){
                                        if(wrd_2[j] == '-'){
                                            k = 0;
                                        }else if(wrd_2[j]>='0' && wrd_2[j]<='9'){
                                            k = 1 + wrd_2[j] -'0';
                                        }else if(wrd_2[j]>='A' && wrd_2[j]<='Z'){
                                            k = 1 + 10 + wrd_2[j] - 'A';
                                        }else if(wrd_2[j]>='a' && wrd_2[j]<='z'){
                                            k = 1 + 10 + 26 + wrd_2[j] - 'a';
                                        }else if(wrd_2[j] == '_'){
                                            k = MAXS_2 - 1;
                                        }
                                        if(cunt[k]>0)
                                            appo = 0;
                                    }
                                }
                            }

                            if(appo){
                                comp++;
                                cunts_4[i]++;
                                if(filtrati[i] == pNil){
                                    filtrati[i] = pTree_2;
                                    scorri = filtrati[i];
                                }else{
                                    scorri->next = pTree_2;
                                    scorri = scorri->next;
                                }
                            }
                            do{
                                pTree_2 = successor(pTree_2);
                                if(pTree_2 == pNil){
                                    i++;
                                    if(i<MAXS_2)
                                        pTree_2 = minimum(pTreeee[i]);
                                }
                            }while(i<MAXS_2 && pTree_2==pNil);
                        }
                    }else{
                        // l'albero 2 non è vuoto
                        scorri = pNil;
                        elimina = pNil;
                        i = 0;
                        while(p){
                            if(cunts_4[i]>0)
                                break;
                            else
                                i++;
                        }
                        scorri = filtrati[i];
/*                        while(scorri == pNil && i<MAXS_2){
                            i++;
                            scorri = filtrati[i];
                        }*/
                        elimina = scorri;
                        while(scorri != pNil){
                            appo = 1;
                            for(j=0; j<lung; j++){
                                if(wrd[j] == '+'){
                                    if(scorri->key[j] != parola[j]){
                                        appo=0;
                                        break;
                                    }
                                }else if(wrd[j] == '|'){
                                    if(wrd_2[j] == scorri->key[j]){
                                        appo = 0;
                                        break;
                                    }
                                }else if(wrd[j] == '/'){
                                    if(wrd_2[j] == scorri->key[j]){
                                        appo = 0;
                                        break;
                                    }
                                }
                            }
                            if(appo){
                                counting_sort(scorri->key, cunt);
                                for(j=0; j<lung; j++){
                                    if(wrd[j] == '+'){
                                        if(parola[j] == '-'){
                                            k = 0;
                                        }else if(parola[j]>='0' && parola[j]<='9'){
                                            k = 1 + parola[j] -'0';
                                        }else if(parola[j]>='A' && parola[j]<='Z'){
                                            k = 1 + 10 + parola[j] - 'A';
                                        }else if(parola[j]>='a' && parola[j]<='z'){
                                            k = 1 + 10 + 26 + parola[j] - 'a';
                                        }else if(parola[j] == '_'){
                                            k = MAXS_2 - 1;
                                        }
                                        cunt[k]--;
                                        if(cunt[k]<0){
                                            appo = 0;
                                            break;
                                        }
                                    }else if(wrd[j] == '|'){
                                        if(wrd_2[j] == '-'){
                                            k = 0;
                                        }else if(wrd_2[j]>='0' && wrd_2[j]<='9'){
                                            k = 1 + wrd_2[j] -'0';
                                        }else if(wrd_2[j]>='A' && wrd_2[j]<='Z'){
                                            k = 1 + 10 + wrd_2[j] - 'A';
                                        }else if(wrd_2[j]>='a' && wrd_2[j]<='z'){
                                            k = 1 + 10 + 26 + wrd_2[j] - 'a';
                                        }else if(wrd_2[j] == '_'){
                                            k = MAXS_2 - 1;
                                        }
                                        cunt[k]--;
                                        if(cunt[k]<0){
                                            appo = 0;
                                            break;
                                        }
                                    }
                                }

                                for(j=0; j<lung && appo; j++){
                                    if(wrd[j] == '/'){
                                        if(wrd_2[j] == '-'){
                                            k = 0;
                                        }else if(wrd_2[j]>='0' && wrd_2[j]<='9'){
                                            k = 1 + wrd_2[j] -'0';
                                        }else if(wrd_2[j]>='A' && wrd_2[j]<='Z'){
                                            k = 1 + 10 + wrd_2[j] - 'A';
                                        }else if(wrd_2[j]>='a' && wrd_2[j]<='z'){
                                            k = 1 + 10 + 26 + wrd_2[j] - 'a';
                                        }else if(wrd_2[j] == '_'){
                                            k = MAXS_2 - 1;
                                        }
                                        if(cunt[k]>0)
                                            appo = 0;
                                    }
                                }
                            }
                            if(!appo){
                                if(scorri == filtrati[i]){
                                    filtrati[i] = filtrati[i]->next;
                                    scorri->next = pNil;
                                    scorri = filtrati[i];
                                    elimina = scorri;
                                }else{
                                    elimina->next = scorri->next;
                                    scorri->next = pNil;
                                    scorri = elimina->next;
                                }
                                comp--;
                                cunts_4[i]--;
                            }else{
                                elimina = scorri;
                                scorri = scorri->next;
                            }
                            while(scorri == pNil && i<MAXS_2){
                                i++;
                                if(i<MAXS_2)
                                    scorri = filtrati[i];
                            }
                        }
                    }
                    printf("%s\n", wrd);
                    printf("%d\n", comp);
                }
                p = 1;
                x--;
            }
            if(!trovato)
                printf("ko\n");
            i=0;
            while(i<MAXS_2){
                while(filtrati[i] != pNil){
                    scorri = filtrati[i];
                    filtrati[i] = filtrati[i]->next;
                    scorri->next = pNil;
                }
                i++;
            }
        }
        sz = scanf("%s", wrd);
    }
    free(wrd);
    free(wrd_2);
    free(indovina);
    free(parola);
    for(i=0;i<MAXS_2;i++)
        free(posizioni[i]);
    for(k=0; k<MAXS_2; k++)
    distruggiAlbero(pTreeee[k]);

//    FreeTree(pTree);
//    FreeTree(pNil);
    return 0;
}


void insertnode_fast(tree **node){
    tree *z = pNil;
    tree *y = pNil;
    tree *pRoot = pNil;
    int ordine, i;

    z = newnode(wrd);
    if(z == pNil){
        *node = pNil;
        return;
    }

    pRoot = *node;
    while(pRoot != pNil){
        y = pRoot;
        //manca i<lung nell'if del for, ma sappiamo che non ci sono mai 2 parole uguali
        ordine = 2;
        i=1;
        while(ordine==2){
            if(wrd[i] < pRoot->key[i]){
                ordine = 0;
                break;
            }else if(z->key[i] > pRoot->key[i]){
                ordine = 1;
                break;
            }
            i++;
        }
/*        for(i=1; ordine==2; i++){
            if(wrd[i] < pRoot->key[i])
                ordine = 0;
            else if(z->key[i] > pRoot->key[i])
                ordine = 1;
        }*/
        //z->wrd < pRoot->wrd
        if(!ordine){
            pRoot = pRoot->left;
        }else{
            pRoot = pRoot->right;
        }
    }
    z->padre = y;
    if(y == pNil){
        *node = z;
    }else{
        for(i=0, ordine=2; i<lung && ordine==2; i++){
            if(wrd[i] < y->key[i])
                ordine = 0;
            else if(wrd[i] > y->key[i])
                ordine = 1;
        }
        if(!ordine)
            y->left = z;
        else
            y->right = z;
    }

    z->left = pNil;
    z->right = pNil;
}


void insertnode2(tree **node, tree **utile){
    tree *z = pNil;
    tree *y = pNil;
    tree *pRoot = pNil;
    int ordine, i;

    z = newnode(wrd);
    if(z == pNil){
        *node = pNil;
        return;
    }

    pRoot = *node;
    while(pRoot != pNil){
        y = pRoot;
        for(i=0, ordine=2; i<lung && ordine==2; i++){
            if(z->key[i] < pRoot->key[i])
                ordine = 0;
            else if(z->key[i] > pRoot->key[i])
                ordine = 1;
        }
        //z->wrd < pRoot->wrd
        if(!ordine){
            pRoot = pRoot->left;
        }else{
            pRoot = pRoot->right;
        }
    }
    z->padre = y;
    if(y == pNil){
        *node = z;
    }else{
        for(i=0, ordine=2; i<lung && ordine==2; i++){
            if(z->key[i] < y->key[i])
                ordine = 0;
            else if(z->key[i] > y->key[i])
                ordine = 1;
        }
        if(!ordine)
            y->left = z;
        else
            y->right = z;
    }

    z->left = pNil;
    z->right = pNil;
    *utile = z;
}

void inorder_tree_walk(tree *t){
    if(t!=pNil){
        inorder_tree_walk(t->left);
        printf("%s\n", t->key);
        inorder_tree_walk(t->right);
    }
}

tree *newnode(char *str){
    tree *r;
    int i;

    r = malloc(sizeof(tree));
    if(!r){
        printf("Memoria insufficiente.\n");
        return pNil;
    }
    r->key = malloc(sizeof(char)*lung+1);
    if(!(r->key)){
        printf("errore allocazione stringa\n");
        return pNil;
    }
    for(i=0; i<lung; i++)
        r->key[i] = str[i];
    r->key[lung] = '\0';
    r->left = pNil;
    r->right = pNil;
    r->next = pNil;
    return r;
}


void InitNil(tree **p){
    char *nind;
    int i;

    nind = malloc(sizeof(char)*lung+1);
    if(!nind){
        printf("errore inizializzione pNil\n");
    }

    for(i=0; i<lung; i++)
        nind[i] = '$';
    nind[i] = '\0';

    *p = newnode(nind);
    if(*p){
        (*p)->key[0] = '$';
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->padre = NULL;
        (*p)->next = NULL;
    }else
        printf("errore inizializzione pNil\n");
}

void counting_sort(char *str, int *arr){
    int i, k;

    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
    arr[4] = 0;
    arr[5] = 0;
    arr[6] = 0;
    arr[7] = 0;
    arr[8] = 0;
    arr[9] = 0;
    arr[10] = 0;
    arr[11] = 0;
    arr[12] = 0;
    arr[13] = 0;
    arr[14] = 0;
    arr[15] = 0;
    arr[16] = 0;
    arr[17] = 0;
    arr[18] = 0;
    arr[19] = 0;
    arr[20] = 0;
    arr[21] = 0;
    arr[22] = 0;
    arr[23] = 0;
    arr[24] = 0;
    arr[25] = 0;
    arr[26] = 0;
    arr[27] = 0;
    arr[28] = 0;
    arr[29] = 0;
    arr[30] = 0;
    arr[31] = 0;
    arr[32] = 0;
    arr[33] = 0;
    arr[34] = 0;
    arr[35] = 0;
    arr[36] = 0;
    arr[37] = 0;
    arr[38] = 0;
    arr[39] = 0;
    arr[40] = 0;
    arr[41] = 0;
    arr[42] = 0;
    arr[43] = 0;
    arr[44] = 0;
    arr[45] = 0;
    arr[46] = 0;
    arr[47] = 0;
    arr[48] = 0;
    arr[49] = 0;
    arr[50] = 0;
    arr[51] = 0;
    arr[52] = 0;
    arr[53] = 0;
    arr[54] = 0;
    arr[55] = 0;
    arr[56] = 0;
    arr[57] = 0;
    arr[58] = 0;
    arr[59] = 0;
    arr[60] = 0;
    arr[61] = 0;
    arr[62] = 0;
    arr[63] = 0;

    k = 0;
    for(i=0; i<lung; i++){
        if(str[i] == '-')
            k = 0;
        else if(str[i]>='0' && str[i]<='9')
            k = 1 + str[i] -'0';
        else if(str[i]>='A' && str[i]<='Z')
            k = 1 + 10 + str[i] - 'A';
        else if(str[i]>='a' && str[i]<='z')
            k = 1 + 10 + 26 + str[i] - 'a';
        else if(str[i] == '_')
            k = MAXS_2-1;
        arr[k]++;
    }
}

tree *search_rb(tree *head){
    int ordine, i;
    tree *node;

    node = head;
    if(head == pNil)
        return head;
    ordine = 2;
    for(i=0; i<lung && ordine==2; i++){
        if(wrd[i] < node->key[i])
            return search_rb(node->left);
        else if(wrd[i] > node->key[i])
            return search_rb(node->right);
    }
    if(ordine == 2) //vuol dire che sono uguali;
        return node;
    else
        return pNil;
}


tree *minimum(tree *head){
    tree *node;
    tree *y;

    y = pNil;
    node = head;

    if(node == pNil)
        return y;

    y = node;
    while(node != pNil){
        y = node;
        node = node->left;
    }

    return y;
}


tree *successor(tree *current){
    tree *y, *z;

    y = pNil;
    z = current;

    if(current == pNil)
        return y;

    if(z->right != pNil)
        return minimum(z->right);
    y = z->padre;
    while(y != pNil && z == y->right){
        z = y;
        y = y->padre;
    }
    return y;
}

void distruggiAlbero(tree *head){

    if(head == pNil)
        return;

    distruggiAlbero(head->left);
    distruggiAlbero(head->right);

    free(head->key);
    free(head);
}
