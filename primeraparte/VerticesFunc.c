#include "JonSnow.h"


u32 NombreDelVertice(WinterIsHere W, u32 x){
  assert(W != NULL);
  if(x < W->nVertex)
    return W->pVertex[x].name;
  abort();
}

u32 ColorDelVertice(WinterIsHere W, u32 x){
  assert(W != NULL);
  if(x < W->nVertex)
    return W->pVertex[x].color;
  abort();
}

u32 GradoDelVertice(WinterIsHere W, u32 x){
  assert(W != NULL);
  if(x < W->nVertex)
    return W->pVertex[x].grade;
  abort();
}

u32 IesimoVecino(WinterIsHere W, u32 x, u32 i){
 assert(W != NULL);
  if(x < W->nVertex)
    return W->pVertex[x].pVecinos[i];
  abort();
}
