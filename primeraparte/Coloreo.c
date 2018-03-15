#include "JonSnow.h"

u32 Greedy(WinterIsHere W){

  pVertex vertex = NULL;
  u32 lengVertex = W->nVertex;
  u32 XG = 0;
  u32 kcolor = 1;
  u32 leng = 0;
  u32 lengColores = W->grade + 2;     // Cantidad maxima de colores 
  u32 *colores = calloc(lengColores, sizeof(u32));  // Arreglo con la cantidad maxima de colores
  u32 colorVertice = 0;
  u32 maxColor = 0;

  // Aputamos al primer vertice a pintar en el orden actual
  vertex = W->pVertex + W->first;

  // Despintamos todo el grafo  
  for(u32 i = 0; i < lengVertex; i++)
    W->pVertex[i].color = 0;

  vertex->color = 1;

  // Recorremos los demas vertices en el orden actual
  for(u32 j = 0; j < lengVertex - 1; j++){
    vertex = W->pVertex + vertex->next;
    kcolor = 0;           // Variable que indica el color que sera dado a vertex
    leng = vertex->grade; // Grado del vertice actual
    maxColor = 0;
    colorVertice = 0;
    // Recorremos los vecinos y indicamos en el array colores, los colores usados
    // los cuales son representados por los index del array
    for(u32 i = 0; i < leng; i++){
      colorVertice = (W->pVertex + vertex->pVecinos[i])->color;
      if(colorVertice)
        // Si el color es distinto de 0, el vertice esta pintado y indicamos el color
        colores[colorVertice] = 1;
      if(colorVertice > maxColor)
        // nos quedamos con el color mas grande usado para saber hasta donde recorrer
        maxColor = colorVertice;
    }
    
    // Recorremos el array colores hasta el maximo color usado(maxColor), buscando un 
    // casillero con 0, al encontrarlo reseteamos a 0 colores[]
    for(u32 i = 1; i < maxColor + 1; i++){
      if(!colores[i]){
        kcolor = i; // Encontramos un color no usado
        memset(colores, 0, lengColores * sizeof(u32));
        break;
      }
    }
    if(!maxColor) // Si no tenemos maxColor es porque ningun color fue usado
      kcolor = 1;
    else if(!kcolor)  // Si no tenemos kcolor es porque todos los colores fueron usados
      kcolor = maxColor + 1;

    // Nos vamos quedando con el color mas grande el cual, 
    // representa la cantidad de colores usados.
    if(XG < kcolor)
      XG = kcolor;
    vertex->color = kcolor;
  }
  W->ownColor = XG;
  free(colores);
  colores = NULL;
  return XG;
}

//Bipartito y sus dos funciones auxiliares se explican en el Readme.

bool PintaDe1(WinterIsHere W, pVertex V);

bool PintaDe2(WinterIsHere W, pVertex V){
    bool result = true;
    if(V->color == 0){
      V->color = 2;
        for (u32 i = 0; i < V->grade && result; i++)
        {
        result = result && PintaDe1(W, W->pVertex + V->pVecinos[i]);
        }
      return result;  
    } else if(V->color == 2)
        return result;

    result = false;
    return result;
}

bool PintaDe1(WinterIsHere W, pVertex V){
    bool result = true;
    if(V->color == 0){
      V->color = 1;
      for (u32 i = 0; i < V->grade && result; i++){
        result = result && PintaDe2(W, W->pVertex + V->pVecinos[i]);
      }
      return result;  
    } else if(V->color == 1)
        return result;

    result = false;
    return result;
}

int Bipartito(WinterIsHere W){

    pVertex vertex = NULL;
    u32 lengVertex = W->nVertex;
    vertex = W->pVertex;
    u32 zero = 0;
    bool Bipart = true;
    // Pintamos todos los vertices del mismo color 0
    for (u32 i = 0; i < lengVertex; i++) {
      vertex = W->pVertex + i;
      vertex->color = 0;
    }
    vertex = W->pVertex;
    
    for (u32 i = 0; i < lengVertex; i++) { 
      if(vertex[i].color == zero) {
        if(PintaDe1(W, vertex + i)) 
          continue;
        else {
          Bipart = false;
          break;
        }
      }
    }

    if(Bipart){
      W->ownColor = 2;
      return 1;
    }
    // Si no es bipartito le volvemos a dar un coloreo propio al grafo
     for (u32 i = 0; i < lengVertex; i++) {
      vertex = W->pVertex + i;
      vertex->color = i + 1;
    }
  return 0;
}
