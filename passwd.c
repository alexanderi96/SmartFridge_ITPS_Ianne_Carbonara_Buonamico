#include "stdio.h"
#include "string.h"

//consiglerei di usare dei nomi più anglofoni giusto per fare i fighi con il prof hahaha
char setPassword(/*char x[]*/){ //come mai gli passi quel char?
    char psw[15];
    char confirm[15];
    _Bool flag;
    do{
        flag=1;
        printf("Inserire password");
        //dany non dimenticarti come si fanno le scanf!
        scanf("%s", psw);
        printf("inserisci nuovamente la password\n");
        scanf("%s", confirm);
        if(strncmp(psw, confirm, 15)!=0){
            printf("Le due passwd non corrispondono\n");
            flag=0;
        }
    }while(flag);
    return psw[15];
}

char modifyPassword(char x[]){
    char vecchia_password[15];
    char nuova_password[15];
    char nuova_password2[15];
    printf("Inserire la vecchia password\n"); //daniela gli \n!!!
    scanf("%s", vecchia_password);
    if(strncmp(x,vecchia_password, 15)==0){ //mi raccomando, la comparazione tra stringhe si fa con lo strncmp
        printf("Inserire nuova password\n");
        scanf("%s", nuova_password);
        printf("Inserire nuovamente la password\n");
        scanf("%s", nuova_password2);
        if(strcmp(nuova_password, nuova_password2)==0){
            printf("Password modificata correttamente\n");
        }else{
            printf("Le due password inserite non corrispondono\n");
        }
    }else{
        printf("La vecchia password inserita non è corretta");
    }
    return nuova_password[15];
}