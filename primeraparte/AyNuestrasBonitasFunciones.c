#include "JonSnow.h"

// Ordena de menor a mayor
int Aymiperrito(const void *a, const void *b){
  if((*(pOrdenX)a).cmp < (*(pOrdenX)b).cmp)
    return -1;
  if((*(pOrdenX)a).cmp > (*(pOrdenX)b).cmp)
    return 1;
  return 0;
}

// Ordena de mayor a menor
int Aymiranarene(const void *a, const void *b){
  if((*(pOrdenX)a).cmp < (*(pOrdenX)b).cmp)
    return 1;
  if((*(pOrdenX)a).cmp > (*(pOrdenX)b).cmp)
    return -1;
  return 0;
}

// Ordena de menor a mayor
int Aymisapito(const void *a, const void *b){
  return *(int*)a - *(int*)b;
}

// Ordena de menor a mayor
int Aymitortuguita(const void *a, const void *b){
  if(*(u32*)a < *(u32*)b)
    return -1;
  if(*(u32*)a > *(u32*)b)
    return 1;
  return 0;
}

// Comparacion para busqueda binaria de menor a mayor
int AymiSolitariaVacaCubana(const void * a, const void * b){
  if((*(pVertex)a).name < *(u32*)b)
    return -9;
  if((*(pVertex)a).name > *(u32*)b)
    return 114;
  return 0;
}