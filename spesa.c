#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spesa.h"

void showList(Spesa Elementlista[], int totElem){
	printf("\nNome\tCategoria\tQuantità\n");
	for (int i = 0; i < totElem; ++i){
		printf("%s\t%s\t%d\n", Elementlista[i].nome, Elementlista[i].categoria, Elementlista[i].quantita);
	}
	printf("\n");
}

int addtoList(Spesa Elementlista[], int totElem){
    char elementTemp[25], scelta;
    int pos, num;
    _Bool flag=0;
    printf("Che prodotto vuoi aggiungere?\n");
    scanf("%s", elementTemp);
    pos = searchElement(Elementlista, totElem, elementTemp); 
    if(pos==-1){
        strcpy(Elementlista[totElem].nome, elementTemp);
        printf("A che categoria appartiene?\n");
        scanf("%s", Elementlista[totElem].categoria);
        printf("Quanti te ne servono?\n");
        scanf("%d", &Elementlista[totElem].quantita);
        return 1;
    }else{
    	while(flag){
    		flag=0;
    		fputs("<!> Il prodotto è già presente, nella lista della spesa. Vuoi aggiungerne altri da aquistare?\n"
        		"s/n\n"
	        	">>> ", stdout);
    	   	scelta = getchar();
        	switch(scelta){
        		case 's':
        			fputs("Quanti elementi vuoi aggiungere al determinato prodotto\n"
        				">>> ", stdout);
       				num = getchar();
       				if (num > 0){
       					Elementlista[pos].quantita = Elementlista[pos].quantita + num;
       					return 1; 
       				}else{
       					system("@cls||clear");
       					puts("<!> Inserisci un nummero di elementi valido\n");
       					flag=1;
       				}
        		break;
        		case 'n':
        			return 0;
        		break;
        		default:
        			system("@cls||clear");
       				flag=1;
        		break;
        	}
    		
    	}
        //da continuare
        return 0;
    }
}

int searchElement(Spesa Elementlista[], int totElem, char elemento[]){
	for (int i = 0; i < totElem; ++i) {
        if(0 == strcmp(elemento, Elementlista[i].nome)){
            return i;
        }
    }
    return -1;
}

int rimElem(Spesa lista[], int totElem){
	char elementTemp[25], scelta;
	int nElem, pos;
	_Bool flag;
	system("@cls||clear");
	while(1){
		showList(lista, totElem);
		fputs("Quale dei seguenti alimenti vuoi rimuovere dalla lista della spesa?\n"
			">>> ", stdout);
		scanf("%s", elementTemp);
		clearBuffer();
		pos = searchElement(lista, totElem, elementTemp); 
		system("@cls||clear");
		if(pos >= 0){
			while(!flag){
				flag = 1;
				fputs("Quanti alimenti vuoi che rimangano nella lista della spesa?\n"
					">>> ", stdout);
				scanf("%d", &nElem);
				clearBuffer();
				if(nElem == 0){
					scalaStruct(lista, totElem, pos);
					return 2;
				}
				system("@cls||clear");
				if (getQuantity(lista, totElem, elementTemp, pos) - nElem <= 0){
					fputs("Il numero di elementi che vuoi rimuovere e' maggiore/uguale del numero degli elementi presenti\n"
						"Vuoi rimuovere interamente il prodotto? s/n\n"
						"premi 0 per annullare l'operazione\n"
						">>> ", stdout);
					scelta = getchar();
					clearBuffer();
					switch(scelta){
						case 's':
							scalaStruct(lista, totElem, pos);
							return 2;
						break;
						case 'n':
							flag = 0;
							system("@cls||clear");
						break;
						case '0':
							return 0;
						break;
						default:
							flag = 0;
							system("@cls||clear");
							puts("<!> Seleziona tra s/n\n\n");
						break;
					}
				}else{
					lista[pos].quantita = lista[pos].quantita - nElem;
					getchar();
					return 1; 
				}
			}
		}else{
			puts("<!> Alimento non presente nella lista della spesa\n\n");
		}
	}
}

int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos){
	if(pos>=0){
		return Elementlista[pos].quantita;
	}else{
		for (int i = 0; i < totElem; ++i) {
     	    if(0 == strcmp(elemento, Elementlista[i].nome)){
        	    return Elementlista[i].quantita;
        	}
    	}
	}
    return -1;
}

void scalaStruct (Spesa Elementlista[], int totElem, int startPoint){
	for (int i = startPoint; i < totElem-1; ++i){
		Elementlista[i] = Elementlista[i+1];
	}
}
