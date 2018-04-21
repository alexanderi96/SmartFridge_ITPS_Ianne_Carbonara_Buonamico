#include "stdio.h"
#include "string.h"


char inserire_password(char x[]){
    char psw[15];
    printf("Inserire password");
    scanf("s", psw);
    return psw[15];
}

char modifica_password(char x[]){
    char vecchia_password[15];
    char nuova_password[15];
    char nuova_password2[15];
    printf("Inserire la vecchia password");
    scanf("s", vecchia_password);
    if(x==vecchia_password){
        printf("Inserire nuova password");
        scanf("%s", nuova_password);
        printf("Inserire nuovamente la password");
        scanf("%s", nuova_password2);
        if(strcmp(nuova_password, nuova_password2)==0){
            printf("Password modificata correttamente");
        }else{
            printf("Le due password inserite non corrispondono");
        }
    }else{
        printf("La vecchia password inserita non è corretta");
    }
}