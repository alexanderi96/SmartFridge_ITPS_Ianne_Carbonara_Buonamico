#ifndef SPESA_H
#define SPESA_H

#include "various.h"

void showList(Spesa Elementlista[], int totElem);
int addtoList(Spesa Elementlista[], int totElem);
int searchElement(Spesa Elementlista[], int totElem, char elemento[]);
int rimElem(Spesa lista[], int totElem);
int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos);
void scalaStruct (Spesa Elementlista[], int totElem, int startPoint);

#endif