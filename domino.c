#include <stdio.h>
#include <stdlib.h>//for rand
#include <time.h>//for rand
#include <string.h>
#include <stdbool.h>

#define n 2
#define default 21
//la seguente funzione popola l'array bidimensionale ricevuto in input con valori random da 1 a 6

/// @brief a a bidimensional array that rappresents tiles in the domino game
/// @param a a bidimensional array that rappresents tiles in the domino game
/// @param num_tessere the number of tiles
void popolamento(int (*a)[n], int num_tessere) {
    for (int i = 0; i < num_tessere; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = (rand() % 6) + 1;
        }
    }
}

//la seguente funzione stampa in una riga l'array nel formato che desideriamo
/// @brief this function print the array in a line in the right format
/// @param a a bidimensional array that rappresents tiles in the domino game 
/// @param num_tessere the number of tiles
void stampaArray(int (*a)[n], int num_tessere) {
    printf("\n");
    for (int i = 0; i < num_tessere; i++) {
        for (int j = 0; j < n; j++) {
            if (j==0){
                printf("[%d|", a[i][j]);
            }
            else{
                printf("%d", a[i][j]);
            }
        }
        printf("] ");
    }
}

//codice per poter ruotare una tessera a piacere
/// @brief this function rotate the tile that is in the position given from the calling code
/// @param a a bidimensional array that rappresents tiles in the domino game
/// @param pos the position of the tile that we have to rotate
void ruota_tessera(int (*a)[n], int pos){
    int temp;
    temp=a[pos][0];
    a[pos][0]=a[pos][1];
    a[pos][1]=temp;
}

//stampa una parte di array, fino alla posizione che vogliamo
/// @brief print only a part of the array, until it reach the pos given fromthe calling code
/// @param a a bidimensional array that rappresents tiles in the domino game
/// @param pos the position of the tile where we have to stop printing
void stamp(int (*a)[n], int pos) {
    if (pos == 0) {
        printf("[%d|%d]", a[pos][0], a[pos][1]);
    } else {
        for (int i = 0; i <= pos; i++) {
            if (a[i][0] != 0 || a[i][1] != 0) {
                for (int j = 0; j < n; j++) {
                    if (j == 0) {
                        printf("[%d|", a[i][j]);
                    } else {
                        printf("%d", a[i][j]);
                    }
                }
                printf("] ");
            }
        }
    }
}

/// @brief initialize the array game with all the tiles =0
/// @param game a bidimensional array that rappresents tiles in the domino game, this is the final array where we count the result
/// @param num_tessere the number of tiles
void inizializzaArrayGame(int (*game)[n], int num_tessere) {
    for (int i = 0; i < num_tessere; i++) {
        for (int j = 0; j < n; j++) {
            game[i][j] = 0;
        }
    }
}

//gameplay senza ai
/// @brief gameplay of the domino without the ai
/// @param a a bidimensional array that rappresents tiles in the domino game
/// @param num_tessere the number of tiles
void gioco(int (*a)[n], int num_tessere){
    int game[num_tessere][n];
    int inizio=0; //tessera di inizio
    int sum=0;

    for (int i=0; i < num_tessere; i++) {
        if(i==0){
            printf("\ninserisci la tessera(sottoforma di posizione dell'array) con cui vuoi iniziare:\n");
            scanf("%d", &inizio);

            game[i][0]=a[inizio][0];
            game[i][1]=a[inizio][1];
            sum+=a[inizio][0];
            sum+=a[inizio][1];
            a[inizio][0]=0;
            a[inizio][1]=0;
            
            stamp(game, i);
        }else{
            stampaArray(a, num_tessere);

            char dove[1];
            int pos=0;
            char r[1];

            printf("\ninserisci nell'ordine seguente: posizione rispetto alla prima tessera('p' per prima,'d' per dopo), quale tessera(posizione nell'array) e 'r' se vuoi ruotarla, 'n' se non vuoi farlo\n");
            scanf(" %c %d %c", &dove[0], &pos, &r[0]);
            getchar();  // Consuma il carattere di nuova riga nel buffer
            if (pos >= num_tessere || a[pos][0] == 0 || a[pos][1] == 0 || (dove[0] != 'p' && dove[0] != 'd') || (r[0] != 'r' && r[0] != 'n')) {
                printf("Invalid input. Please enter 'r' or 'n' for rotation.\n");
                printf("il risultato e' %d", sum);
                
                exit(0);
            }

            if(dove[0] == 'p' && r[0] == 'r'){
                ruota_tessera(a, pos);
                if(a[pos][1]==game[0][0]){
                    for(int z=i;z>0;z--){//sposta tutti avanti di 1 in modo da mettere in posizione 0 dell'array in questo momento la nuova tessera
                        game[z][0]=game[z-1][0];
                        game[z][1]=game[z-1][1];
                    }
                    game[0][0]=a[pos][0];
                    game[0][1]=a[pos][1];
                    sum+=a[pos][0];
                    sum+=a[pos][1];
                    a[pos][0]=0;
                    a[pos][1]=0;
                    
                    stamp(game, i);
                }else{
                    ruota_tessera(a, pos);
                    i--;
                    printf("impossibile inserire quella tessera");
                    printf("\nl'array di gioco al momento e':\n");
                    stamp(game, i);
                }
            }else if(dove[0] == 'p' && r[0] == 'n'){
                if(a[pos][1]==game[0][0]){
                    for (int z = i; z > 0; z--) {
                        game[z][0] = game[z - 1][0];
                        game[z][1] = game[z - 1][1];
                    }
                    game[0][0] = a[pos][0];
                    game[0][1] = a[pos][1];
                    sum+=a[pos][0];
                    sum+=a[pos][1];
                    a[pos][0] = 0;
                    a[pos][1] = 0;
                    stamp(game, i);
                }else{
                    i--;
                    printf("impossibile inserire quella tessera");
                    printf("\nl'array di gioco al momento e':\n");
                    stamp(game, i);
                }
            } else if (dove[0] == 'd' && r[0] == 'r') {
                ruota_tessera(a, pos);
                if(a[pos][0]==game[i-1][1]){
                    game[i][0] = a[pos][0];
                    game[i][1] = a[pos][1];
                    sum+=a[pos][0];
                    sum+=a[pos][1];
                    a[pos][0] = 0;
                    a[pos][1] = 0;
                    stamp(game, i);
                }else{
                    ruota_tessera(a, pos);
                    i--;
                    printf("impossibile inserire quella tessera");
                    printf("\nl'array di gioco al momento e':\n");
                    stamp(game, i);
                }
            } else if (dove[0] == 'd' && r[0] == 'n') {
                if(a[pos][0]==game[i-1][1]){
                    game[i][0] = a[pos][0];
                    game[i][1] = a[pos][1];
                    sum+=a[pos][0];
                    sum+=a[pos][1];
                    a[pos][0] = 0;
                    a[pos][1] = 0;
                    stamp(game, i);
                }else{
                    i--;
                    printf("impossibile inserire quella tessera");
                    printf("\nl'array di gioco al momento e':\n");
                    stamp(game, i);
                }
            }
            if(i!=num_tessere-1){
                char esci[5];

                printf("\nse vuoi smettere di giocare scrivi 'esci'\n");
                scanf("%s", &esci);
                if(strcmp(esci, "esci") == 0){
                    printf("il risultato e' %d", sum);
                    
                    exit(0);
                }
            }
        }
    }
    printf("\nil risultato e' %d", sum);
    
    exit(0);
}

//gameplay con ai
//first match
/// @brief gameplay of the domino with the ai
/// @param a a bidimensional array that rappresents tiles in the domino game
/// @param num_tessere the number of tiles
void giocaAI(int (*a)[n], int num_tessere) {
    int game[num_tessere][n];
    inizializzaArrayGame(game, num_tessere);
    printf("\nBIP BOP\nOra l'AI risolvera' il domino in modo da ottenere il massimo punteggio possibile\n");

    int sum = 0;
    bool coppia_trovata = false;
    // Find and place the first two tiles with consecutive numbers
    for (int i = 0; i < num_tessere; i++) {
        for (int j = i + 1; j < num_tessere; j++) {
            if (a[i][1] == a[j][0]) {
                game[0][0] = a[i][0];
                game[0][1] = a[i][1];
                game[1][0] = a[j][0];
                game[1][1] = a[j][1];
                printf("\n\nle due tessere da cui l'ai iniziera' sono: \n[%d|%d] [%d|%d]\n", a[i][0], a[i][1], a[j][0],a[j][1]);

                sum += a[i][0] + a[i][1] + a[j][0] + a[j][1];
                a[i][0] = a[i][1] = a[j][0] = a[j][1] = 0;
                coppia_trovata=true;
                break;
            }else if(a[i][1] == a[j][1]){
                ruota_tessera(a,j);
                game[0][0] = a[i][0];
                game[0][1] = a[i][1];
                game[1][0] = a[j][0];
                game[1][1] = a[j][1];
                printf("\n\nle due tessere da cui l'ai iniziera' sono: \n[%d|%d] [%d|%d]\n", a[i][0], a[i][1], a[j][0],a[j][1]);

                sum += a[i][0] + a[i][1] + a[j][0] + a[j][1];
                a[i][0] = a[i][1] = a[j][0] = a[j][1] = 0;
                coppia_trovata=true;
                break;
            }
        }
        if (coppia_trovata) {
            break;
        }
    }

    // If no consecutive tiles are found, choose the tile with the highest sum
    if (game[0][0] == 0) {
        int indice = 0;
        printf("\nNon ci sono tessere che permettono di continuare il gioco. Tessera che permette il miglior punteggio:\n");

        int somma = 0;
        int sommamax = INT_MIN; // Inizializza con un valore molto basso

        for (int i = 0; i < num_tessere; i++) {
            somma = a[i][0] + a[i][1];
            if (somma > sommamax) {
                indice = i;
                sommamax = somma;
            }
        }

        printf("[%d|%d]\n", a[indice][0], a[indice][1]);
        printf("\nrisultato: %d", sommamax);
        return;
    }

    for (int i = 1; i < num_tessere - 1; i++) {
        for (int j = 0; j < num_tessere; j++) {
            if (game[i][1] == a[j][0]) {
                game[i + 1][0] = a[j][0];
                game[i + 1][1] = a[j][1];
                if(a[j][0] != 0 && a[j][1] != 0 && game[i][0] != 0 && game[i][1] != 0){
                    printf("\nla tessera [%d|%d], verra' posizionata dopo la tessera [%d|%d]\n\n", a[j][0], a[j][1], game[i][0], game[i][1]);
                }

                sum += a[j][0] + a[j][1];
                a[j][0] = 0;
                a[j][1] = 0;
                break;
            } else if (game[i][1] == a[j][1]) {
                if(a[j][0] != 0 && a[j][1] != 0 && game[i][0] != 0 && game[i][1] != 0){
                    printf("\nla tessera [%d|%d] ruotata, verra' posizionata dopo la tessera [%d|%d]\n\n", a[j][0], a[j][1], game[i][0], game[i][1]);
                }
                ruota_tessera(a, j);
                game[i + 1][0] = a[j][0];
                game[i + 1][1] = a[j][1];
                
                sum += a[j][0] + a[j][1];
                a[j][0] = 0;
                a[j][1] = 0;
                break;
            }
        }
    }

    for (int i = 0; i < num_tessere; i++) {
        if (game[0][0] == a[i][1]) {
            for (int z = i + 1; z > 0; z--) {
                game[z][0] = game[z - 1][0];
                game[z][1] = game[z - 1][1];
            }
            game[0][0] = a[i][0];
            game[0][1] = a[i][1];
            if(a[i][0] != 0 && a[i][1] != 0 && game[1][0] != 0 && game[1][1] != 0){
                printf("\nla tessera [%d|%d], verra' posizionata prima della tessera [%d|%d]\n\n", a[i][0], a[i][1], game[1][0], game[1][1]);
            }
            

            sum += a[i][0] + a[i][1];
            a[i][0] = 0;
            a[i][1] = 0;
            break;
        } else if (game[0][0] == a[i][0]) {
            if(a[i][0] != 0 && a[i][1] != 0 && game[1][0] != 0 && game[1][1] != 0){
                printf("\nla tessera [%d|%d] ruotata, verra' posizionata prima della tessera [%d|%d]\n\n", a[i][0], a[i][1], game[1][0], game[1][1]);
            }
            ruota_tessera(a, i);
            for (int z = i + 1; z > 0; z--) {
                game[z][0] = game[z - 1][0];
                game[z][1] = game[z - 1][1];
            }
            game[0][0] = a[i][0];
            game[0][1] = a[i][1];

            sum += a[i][0] + a[i][1];
            a[i][0] = 0;
            a[i][1] = 0;
            break;
        }
    }

    // Ora stampa l'array alla fine della funzione
    stamp(game, num_tessere - 1);

    printf("\nIl risultato e': %d\n", sum);
}


int main(){
    srand(time(NULL));//serve alla funzione random per evitare di ripetere le stesse combinazioni ogni volta che testiamo il codice

    printf("\nscegliere come voler giocare attraverso il numero proposto, se si vuole scegliere la prima si inserisca: '1', se la seconda '2'\n\n");
    printf("Modalita' di gioco:\n1)Utilizzare un num_tessere di default;\n2)Inserire quante tessere utilizzare;\n");
    int pos=0;
    int pos1=0;
    int pos2=0;
    do{
        scanf("%d", &pos);
    }while(pos!=1 && pos!=2);
    
    if(pos==1){
        printf("scegli quante tessere utilizzare:\n1)21\n2)14\n3)7\n");
        do{
            scanf("%d", &pos2);
        }while(pos2!=1 && pos2!=2 && pos2!=3);
        if(pos2==1){

            printf("chi gioca:\n1)tu\n2)ai\n");
        
            do{
                scanf("%d", &pos1);
            }while(pos1!=1 && pos1!=2);
            if(pos1==1){
                printf("verranno utilizzate 21 tessere:\n");
                int a[default][n];
                popolamento(a, default);
                stampaArray(a, default);
                gioco(a, default);
            }else if(pos1==2){
                printf("verranno utilizzate 21 tessere:\n");
                int a[default][n];
                popolamento(a, default);
                stampaArray(a, default);
                giocaAI(a, default);
            }
        }else if(pos2==2){

            printf("chi gioca:\n1)tu\n2)ai\n");
        
            do{
                scanf("%d", &pos1);
            }while(pos1!=1 && pos1!=2);
            if(pos1==1){
                printf("verranno utilizzate 14 tessere:\n");
                int a[14][n];
                popolamento(a, 14);
                stampaArray(a, 14);
                gioco(a, 14);
            }else if(pos1==2){
                printf("verranno utilizzate 14 tessere:\n");
                int a[14][n];
                popolamento(a, 14);
                stampaArray(a, 14);
                giocaAI(a, 14);
            }
        }else if(pos2==3){
            
            printf("chi gioca:\n1)tu\n2)ai\n");
        
            do{
                scanf("%d", &pos1);
            }while(pos1!=1 && pos1!=2);
            if(pos1==1){
                printf("verranno utilizzate 7 tessere:\n");
                int a[7][n];
                popolamento(a, 7);
                stampaArray(a, 7);
                gioco(a, 7);
            }else if(pos1==2){
                printf("verranno utilizzate 7 tessere:\n");
                int a[7][n];
                popolamento(a, 7);
                stampaArray(a, 7);
                giocaAI(a, 7);
            }
        }
    }else if(pos==2){
        int tastiera=0;
        printf("\ninserisci il numero di tessere:\n");
        scanf("%d", &tastiera);
        printf("chi gioca:\n1)tu\n2)ai\n");
        int pos1=0;
        do{
            scanf("%d", &pos1);
        }while(pos1!=1 && pos1!=2);
        if(pos1==1){
            printf("verranno utilizzate %d tessere:\n", tastiera);
            int a[tastiera][n];
            popolamento(a, tastiera);
            stampaArray(a, tastiera);
            gioco(a, tastiera);
        }else if(pos1==2){
            printf("verranno utilizzate %d tessere:\n", tastiera);
            int a[tastiera][n];
            popolamento(a, tastiera);
            stampaArray(a, tastiera);
            giocaAI(a, tastiera);
        }
    }
    return 0;
}