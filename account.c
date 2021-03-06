#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "various.h"
#include "intolleranze.h"



//aggiunge un nuovo account
int createAccount(Utente utenti[], int totUtenti, int isadmin, char elencoCategorie[][maxCatLen], int *totCat){
    _Bool flag=1;
    char userTemp[25], scelta;
    int id_buffer[maxUtenti];
    fputs("Inserisci il nome utente\n"
        ">>> ", stdout);
    scanf("%s", userTemp);
    system("@cls||clear");
    
    clearBuffer();
    if(-1==searchAccount(utenti, totUtenti, userTemp)){
        utenti[totUtenti].totinto=0;
        strcpy(utenti[totUtenti].user, userTemp);
        fputs("Inserisci il tuo nome\n"
            ">>> ", stdout);
        scanf("%s", utenti[totUtenti].nome);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci il tuo cognome\n"
            ">>> ", stdout);
        scanf("%s", utenti[totUtenti].cognome);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci la tua età\n"
            ">>> ", stdout);
        scanf("%d", &utenti[totUtenti].eta);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci la password\n"
            ">>> ", stdout); 
        scanf("%s", utenti[totUtenti].password);
        system("@cls||clear");
        clearBuffer();
        utenti[totUtenti].isadmin=isadmin;
        strcpy(utenti[totUtenti].intopos, accountdir);
        strcat(utenti[totUtenti].intopos, userTemp);
        make_directory(utenti[totUtenti].intopos);
        strcat(utenti[totUtenti].intopos, "/intolleranze.txt");
        while(flag){
            system("@cls||clear");
            if(utenti[totUtenti].totinto=0){
                fputs("Desideri inserire qualche intolleranza?\n"
                    "s/n\n"
                    ">>> ", stdout);
            }else{
                fputs("Desideri inserire qualche altra intolleranza?\n"
                    "s/n\n"
                    ">>> ", stdout);
            }
            scelta=getchar();
            clearBuffer();
            switch(scelta){
                case 's':
                    if(addIntollerance(utenti[totUtenti].intolleranze[utenti[totUtenti].totinto], elencoCategorie, *&totCat)){
                        utenti[totUtenti].totinto++;
                    }
                break;
                case 'n':
                    flag=0;
                break;
                default:
                    system("@cls||clear");
                    puts("<!> Inserisci un valore corretto\n");
                break;
            }    
        }
        int id_buffer[maxUtenti];
        for (int i = 0; i < totUtenti; ++i){
            id_buffer[i]=utenti[i].id_utente;
        }
        utenti[totUtenti].id_utente=checkIdPresence(id_buffer, totUtenti, 0);
        return 1;
    }else{
        return 0;
    }
}


//permette l'autenticazione
int userAuth(Utente utenti[], int totUtenti, char user[], char passwd[]){
    for (int i = 0; i < totUtenti; ++i) {
        if(strcmp(user, utenti[i].user) == 0 && strcmp(passwd, utenti[i].password) == 0){
            return 1;
        }
    }
    return 0;
}

//consente di capire se un utente è admin o meno
int checkAdmin(Utente utenti[], int totUtenti, char user[]){
    for (int i = 0; i < totUtenti; ++i){
        if(0 == strcmp(utenti[i].user, user)){
            return utenti[i].isadmin;
        }        
    }
    return -1;
}

//restituisce la posizione dell'account se presente, altrimenti restituisce -1
int searchAccount(Utente utenti[], int totUtenti, char user[]){
    for (int i = 0; i < totUtenti; ++i) {
        if(0 == strcmp(user, utenti[i].user)){
            return i;
        }
    }
    return -1;
}

void showAccount(Utente utente){
    char isadmin[6];    
    if(utente.isadmin){
        strcpy(isadmin, "Admin");
    }else{
        strcpy(isadmin, "Normal");
    }
    printf("|------------------------------|------------------------------|------------------------------|------------------------------|\n"
        "|%-30s|%-30s|%-30s|%-30s|\n"
        "|------------------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n"
        "|%-30s|%-30s|%-30s|%-30d|%-30s|\n"
        "|------------------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n", "Username","Nome", "Cognome", "Eta'", utente.user, utente.nome, utente.cognome, utente.eta, isadmin);
}

int modifyUserPrivilege(Utente utenti[], int totUtenti){
    char user[25];
    char scelta2;
    int posUtente;
    puts("Di seguito gli utenti di cui è possibile modificarne il grado\n\n");
    while(1){
        for(int i=0; i<totUtenti; i++){
            printf("%s\n", utenti[i].user);
        }
        printf("\n\nInserisci l'username di cui vuoi modificarne il grado\nPremi 0 per annullare l'operazione\n\n>>> ", stdout);
        scanf("%s", user);
        clearBuffer();
        if(strcmp(user, "0")==0){
            system("@cls||clear");
            return 0;
        }
        posUtente=searchAccount(utenti, totUtenti, user);
        while(posUtente>-1){
            printf("Sei sicuro di voler modificare il grado utente di %s? s/n\n>>> ", utenti[posUtente].user);
            scelta2=getchar();
            system("@cls||clear");
            clearBuffer();
            switch(scelta2){
                case 's':
                    puts("siamo nel case s");
                    if(utenti[posUtente].isadmin){
                        utenti[posUtente].isadmin=0;
                    }else{
                        utenti[posUtente].isadmin=1;
                    }
                    return 1;
                break;
                case 'n': 
                    return 0;
                    break;
                default:
                    system("@cls||clear");
                    puts("<!> Per favore inserisci una scelta corretta\n");
                break;
            }
        }
        system("@cls||clear");
        puts("<!> Per favore inserisci una scelta corretta\n"); 
    }   
}



int modificaPassword(Utente *utente){
    puts("Inserisci la nuova password\n\n");
    scanf("%s", utente->password);
    system("@cls||clear");
    clearBuffer();
    return 1;
}