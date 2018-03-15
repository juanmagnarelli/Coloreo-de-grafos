#include "JonSnow.h"


u32 NumeroDeVertices(WinterIsHere W){
  assert(W != NULL);
  return W->nVertex;
}

u32 NumeroDeLados(WinterIsHere W){
  assert(W != NULL);
  return W->mEdge;
}

u32 NumeroVerticesDeColor(WinterIsHere W, u32 i){
  assert(W != NULL);
  u32 kColor = 0;

  if(i > W->ownColor)
    return kColor;

  // contamos la cantidad de colores.
  for(u32 j = 0; j < W->nVertex; j++)
    if(W->pVertex[j].color == i)
      kColor++;

  return kColor;
}

u32 NumeroDeColores(WinterIsHere W){
  assert(W != NULL);
  return W->ownColor;
}

u32 IesimoVerticeEnElOrden(WinterIsHere W,u32 i){
  assert(W != NULL);

  if(i > W->nVertex)
    abort();

  pVertex vertex = W->pVertex + W->first;

  for(u32 j = 0; j < i; j++)
    vertex = W->pVertex + vertex->next;

  return vertex->index;
}
