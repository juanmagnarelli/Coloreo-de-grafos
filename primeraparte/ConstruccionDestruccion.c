#include "JonSnow.h"

void newVecinos(pVertex v1, pVertex v2){
  // asignamos el index de un vecino a la lista de vecinos del otro
  assert(v1->name != v2->name);
  assert(v1 != NULL && v2 != NULL);
  v1->pVecinos[v1->iVecino] = v2->index;
  ++(v1->iVecino);

  v2->pVecinos[v2->iVecino] = v1->index;
  ++(v2->iVecino);
}

//Elimina el arreglo de vecinos
void byeVertex(struct VertexSt v){
  free(v.pVecinos);
  v.pVecinos = NULL;
}

int Primavera(WinterIsHere W){
  if(W == NULL)
    return 1;
  // Recorre los vertices y elimina su estructura y sus vecinos.
  for(u32 i = 0; i < W->nVertex; i++){
    byeVertex(W->pVertex[i]);
  }
  
  free(W->pVertex);
  W->pVertex = NULL;
  free(W);
  W = NULL;
  return 1;
}

WinterIsHere WinterIsComing(){

  // Buffer que guarda los 30 primeros char de una linea. Tomamos 30 para la
  // linea p edge A B, porque A y B pueden ser de hasta 10 digitos (2^32).
  char *line = calloc(30, sizeof(char));

  // Recorremos las lineas que son comentarios y nos detenemos en "p edge A B".
  while(fscanf(stdin, " %30[^\n]%*[^\n]", line) != EOF)
    if(line[0] != 'c')
      break;

  u32 numVertex = 0, numEdge = 0;

  //Verificamos que la linea este bien formada
  if(sscanf(line, "p edge %u %u%*[^\n]", &numVertex, &numEdge) != EOF)
    ;
  else { 
    printf("Error invalid input\nExit.");
    return NULL;
  }

  free(line);
  line = NULL;

  u32 x = 0, y = 0;
  u32 *aristasTemp = calloc(2*numEdge, sizeof(u32));
  u32 *aristas = calloc(2*numEdge, sizeof(u32));
  int fs = 0;

  //guardamos los vertices vecinos como elementos consecutivos del array aristas.
  for(u32 i = 0; i < 2*numEdge; i+=2){
    fs = fscanf(stdin, " e %u %u", &x, &y);
    aristas[i] = x;
    aristas[i+1] = y;
    aristasTemp[i] = x;
    aristasTemp[i+1] = y;
    if(fs != 2)
      printf("Error de input\n");
  }
  
  //Ordenamos uno de los arreglos para obtener el grado de cada vertice.
  qsort(aristasTemp, 2*numEdge, sizeof(u32), Aymitortuguita);

  // Creamos la estructura del grafo.
  WinterIsHere pGraph = NULL;
  pGraph = calloc(1, sizeof(struct WinterSt));
  pGraph->nVertex = numVertex;
  pGraph->mEdge = numEdge;
  pGraph->ownColor = numVertex;
  pGraph->pVertex = calloc(numVertex, sizeof(struct VertexSt));
  pGraph->first = 0;
  pGraph->grade = 0;

  u32 iVertex = 0; // iesimo-Vecino agregado

  pGraph->pVertex[0].name = aristasTemp[0];
  pGraph->pVertex[0].index = 0;
  pGraph->pVertex[0].color = 1;
  pGraph->pVertex[iVertex].next = iVertex + 1;
  pGraph->pVertex[0].grade = 0;
  pGraph->pVertex[0].iVecino = 0;

  
  //Creamos el arreglo de vertices con los grados y el arreglo de vecinos.
  for(u32 i = 0; i < 2*numEdge; i++){
    // mientras sea un vertice ya cargado aumentamos el grado, ya que aparecio en x lineas.
    if(aristasTemp[i] == pGraph->pVertex[iVertex].name){
      ++(pGraph->pVertex[iVertex].grade);
    // Cuando encontramos un vertice nuevo, llenamos los campos de la estructura
    } else {
      pGraph->pVertex[iVertex].pVecinos = calloc(pGraph->pVertex[iVertex].grade, sizeof(u32));
      if(pGraph->pVertex[iVertex].grade > pGraph->grade)
        pGraph->grade = pGraph->pVertex[iVertex].grade;
      iVertex++;

      pGraph->pVertex[iVertex].name = aristasTemp[i];
      pGraph->pVertex[iVertex].index = iVertex;
      pGraph->pVertex[iVertex].color = iVertex + 1; //ya que color comienza uno mas arriba.
      pGraph->pVertex[iVertex].next = iVertex + 1;
      pGraph->pVertex[iVertex].grade = 1;
      pGraph->pVertex[iVertex].iVecino = 0;
    }
  }

  //La ultima iteracion no crea el los vecinos del vertice.
  pGraph->pVertex[iVertex].pVecinos = calloc(pGraph->pVertex[iVertex].grade, sizeof(u32));
  if(pGraph->pVertex[iVertex].grade > pGraph->grade)
    pGraph->grade = pGraph->pVertex[iVertex].grade;
  iVertex++;

  if(iVertex != numVertex)
    printf("Numero de vertices agregados incorrecto %u\n", iVertex);

  free(aristasTemp);
  aristasTemp = NULL;

  pVertex nodeA, nodeB;

  // cargamos los vecinos.
  for(u32 i = 0; i < 2*numEdge; i += 2){
    //NodeA apunta al casillero en pVertex del vertice arista[i].
    nodeA = (pVertex)bsearch(&aristas[i], pGraph->pVertex, numVertex, sizeof(struct VertexSt), AymiSolitariaVacaCubana);
    nodeB = (pVertex)bsearch(&aristas[i+1], pGraph->pVertex, numVertex, sizeof(struct VertexSt), AymiSolitariaVacaCubana);
    newVecinos(nodeA, nodeB);    
  }
  
  free(aristas);
  aristas = NULL;
  return pGraph;
}
