#include "JonSnow.h"


void OrdenNatural(WinterIsHere W){

  W->first = 0;
  // Copiamos los index para dar un orden natural, ya que los 
  // mismos estan siempre ordenados en W, al igual que los nombres.
  for(u32 i = 0; i < W->nVertex; i++)
    W->pVertex[i].next = (W->pVertex[i].index) + 1;
}

void OrdenWelshPowell(WinterIsHere W){

  pOrdenX ArrayWelshPowell = calloc(W->nVertex , sizeof(struct OrdenX));

  // creamos el arreglo a ser usado en qsort, el cual contiene el index 
  // del vertice, y su grado.
  for(u32 i = 0; i < W->nVertex; i++){
    ArrayWelshPowell[i].index = i;
    ArrayWelshPowell[i].cmp = W->pVertex[i].grade;
  }
  //Ordenamos por grade
  qsort(ArrayWelshPowell, W->nVertex, sizeof(struct OrdenX), Aymiranarene);

  // Asignamos el primer elemento de la lista
  W->first = ArrayWelshPowell[0].index;

  // Asignamos la los next en el orden de los grados  
  for(u32 i = 0; i < W->nVertex - 1; i++)
    W->pVertex[ArrayWelshPowell[i].index].next = ArrayWelshPowell[i+1].index;

  free(ArrayWelshPowell);
  ArrayWelshPowell = NULL;
}

void AleatorizarVertices(WinterIsHere W,u32 x){
  u32 temp;
  u32 *indexRandom = calloc(W->nVertex, sizeof(u32));
  u32 leng = W->nVertex;

  // Damos a sran como semilla x, para que vaya generando numeros
  // aleatorios.
  srand(x);

  // arreglo a ser swapeado en forma random
  for(u32 i = 0; i < leng; i++)
    indexRandom[i] = i;

  // ordenamos aleatoriamente los vertices 
  for(u32 i = 1, j; i < leng/2; i++){
    j = rand() % (leng/2);
    temp = indexRandom[j];
    indexRandom[j] = indexRandom[leng - i];
    indexRandom[leng - i] = temp;
  }
  
  // Asignamos el primer elemento de la lista
  W->first = indexRandom[0];

  // Asignamos lo indices para que quede ordenado aleatoriamente
  for(u32 i = 0; i < leng - 1; i++)
    W->pVertex[indexRandom[i]].next = indexRandom[i+1];

  free(indexRandom);
  indexRandom = NULL;
}

void ColorOrd0(WinterIsHere W);
void ColorOrd1(WinterIsHere W);
void ColorOrd2(WinterIsHere W);
void ColorOrd3(WinterIsHere W);
void colorOrdRandom(WinterIsHere W, u32 x);

void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x){
  if(x == 0)
    ColorOrd0(W);
  else if(x == 1)
    ColorOrd1(W);
  else if(x == 2)
    ColorOrd2(W);
  else if(x == 3)
    ColorOrd3(W);
  else
    colorOrdRandom(W, x);
}

void ColorOrd0(WinterIsHere W){
  u32 nVertex = W->nVertex;
  pOrdenX ColorRcreciente = calloc(W->nVertex, sizeof(struct OrdenX));
  
  // arreglo a ser ordenado en qsort por el campo color
  for(u32 i = 0; i < W->nVertex; i++){
    ColorRcreciente[i].index = i;
    ColorRcreciente[i].cmp = W->pVertex[i].color;
  }
  // Ordenamos por colores
  qsort(ColorRcreciente, W->nVertex, sizeof(struct OrdenX), Aymiranarene);

  // Color R primero  
  W->first = ColorRcreciente[0].index;
  u32 R;

  // Asigna la lista de los vertices con el color r, luego sale cuando llega al primer
  // vertice con color r-1.
  for(R = 0; ColorRcreciente[R+1].cmp == ColorRcreciente[0].cmp && R < W->nVertex; R++)
        W->pVertex[ColorRcreciente[R].index].next = ColorRcreciente[R+1].index;

  // Asigna el siguiente vertice que es del color 1, el cual sera el ultimo del
  // array ColorRcreciente.
  W->pVertex[ColorRcreciente[R].index].next = ColorRcreciente[nVertex-1].index;

  // Recorremos el array desde el ultimo vertice (color 1), hasta llegar al color R
  for(u32 i = nVertex-1; i > R; i--)
    W->pVertex[ColorRcreciente[i].index].next = ColorRcreciente[i-1].index;

  free(ColorRcreciente);
  ColorRcreciente = NULL;
}


void ColorOrd1(WinterIsHere W){
  u32 nVertex = W->nVertex;
  pOrdenX ColorDecreciente = calloc(W->nVertex, sizeof(struct OrdenX));
  
  // array a ser ordenado por qsort de forma decreciente por color
  for(u32 i = 0; i < W->nVertex; i++){
    ColorDecreciente[i].index = i;
    ColorDecreciente[i].cmp = W->pVertex[i].color;
  }

  qsort(ColorDecreciente, W->nVertex, sizeof(struct OrdenX), Aymiranarene);

  // Primero color R
  W->first = ColorDecreciente[0].index;
   
  // array para formar la lista 
  for(u32 i = 0; i < nVertex-1; i++)
    W->pVertex[ColorDecreciente[i].index].next = ColorDecreciente[i+1].index;

  free(ColorDecreciente);
  ColorDecreciente = NULL;
}

struct Rainbow *LoadsRainbow(WinterIsHere W){

  struct Rainbow *ColorArray = calloc(W->ownColor, sizeof(struct Rainbow));
  pOrdenX a = calloc(W->nVertex, sizeof(struct OrdenX));

  // array a ser ordenado por qsort y evitar swaper estructuras
  for(u32 i = 0; i < W->nVertex; i++){
    a[i].index = i;
    a[i].cmp = W->pVertex[i].color;
  }

  u32 numVertex = W->nVertex;
  u32 colorActual = 0;
  u32 SumadorDelColorActual = 0;

  /* Ordenamos los vertices por colores */
  qsort(a, numVertex, sizeof(struct OrdenX), Aymiperrito);

  // variable que nos indica cuando pasamos a otro color
  colorActual = a[0].cmp;
  u32 indiceAnterior = 0;

  /*  i : recorre los vertices en pVertex.
      j : recorre el arreglo ColorArray, o sea iterando en los conjuntos.
      p : recorre el arreglo IndexsColor para ir guardando los index.
  */
  u32 i = 0, j = 0, p = 0;

  // llenamos la estructura Rainbow
  for(i = 0, j = 0, p = 0; i < numVertex; i++){
    if(colorActual != a[i].cmp){
      //Cuando encontramos otro color, se crea el arreglo de indices y se lo guarda.
      ColorArray[j].IndexsColor = calloc(SumadorDelColorActual, sizeof(u32));
      ColorArray[j].length = SumadorDelColorActual;

      // Recorre los vertices con el color actual guardando sus indices.
      for(u32 i2 = indiceAnterior; i2 < i; i2++, p++)
        ColorArray[j].IndexsColor[p] = a[i2].index;

      p = 0;
      indiceAnterior = i;
      SumadorDelColorActual = 0;
      colorActual = a[i].cmp;
      j++;
    }
    SumadorDelColorActual++;
  }
  // Cargamos el ultimo conjunto de vertices
  ColorArray[j].IndexsColor = calloc(SumadorDelColorActual, sizeof(u32));
  ColorArray[j].length = SumadorDelColorActual;
  
  // Recorre los vertices con el color actual guardando sus indices.
  for(u32 i2 = indiceAnterior; i2 < i; i2++, p++){
    ColorArray[j].IndexsColor[p] = a[i2].index;
  }

  free(a);
  a = NULL;
  return ColorArray;
}

void ColorOrd2(WinterIsHere W){

  struct Rainbow *ColorArray;
  ColorArray = LoadsRainbow(W);
  pOrdenX b = calloc(W->ownColor, sizeof(struct OrdenX));

  // Array a ser ordenado por qsort y evitar swaper estructuras
  for(u32 i = 0; i < W->ownColor; i++){
    b[i].index = i;
    b[i].cmp = ColorArray[i].length;
  }

  qsort(b, W->ownColor, sizeof(struct OrdenX), Aymiperrito);

  // Asignamos el primer elemento de la lista
  W->first = ColorArray[b[0].index].IndexsColor[0];

 /* Recorremos el arreglo ColorArray con los conjuntos de colores y vamos formando el orden
    con el que se va a recorrer el arreglo de vertices. */
  for(u32 i = 0; i < W->ownColor; i++)
    // Recorremos el arreglo con los indices de los vecinos de un color
    for(u32 j = 0; j < ColorArray[b[i].index].length; j++){
      // Analisamos por casos para los bordes de los arreglos recorridos, vamos asignando los campos next
      // pasando por todo el array de vertices de un color y luego pasamos al siguiente color
      if(i < W->ownColor - 1 && j == ColorArray[b[i].index].length - 1)
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = ColorArray[b[i+1].index].IndexsColor[0];
      
      else if(i == W->ownColor - 1 && j == ColorArray[b[i].index].length - 1)
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next;
      
      else
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = ColorArray[b[i].index].IndexsColor[j+1];
    }

  // Eliminacion de ColorArray
  for(u32 i = 0; i < W->ownColor; i++){
    free(ColorArray[i].IndexsColor);
    ColorArray[i].IndexsColor = NULL;
  }
  
  free(b); b = NULL;
  free(ColorArray);
  ColorArray = NULL;
}

void ColorOrd3(WinterIsHere W){

  struct Rainbow *ColorArray;
  ColorArray = LoadsRainbow(W);
  pOrdenX b = calloc(W->ownColor, sizeof(struct OrdenX));

  // array a ser ordenado por qsort y evitar swaper estructuras
  for(u32 i = 0; i < W->ownColor; i++){
    b[i].index = i;
    b[i].cmp = ColorArray[i].length;
  }

  qsort(b, W->ownColor, sizeof(struct OrdenX), Aymiranarene);

  W->first = ColorArray[b[0].index].IndexsColor[0];

  // Los for's anidados recorren los arreglos con los conjuntos de colores, es analogo los for
  // del ColorOrd2.
  for(u32 i = 0; i < W->ownColor; i++)

    for(u32 j = 0; j < ColorArray[b[i].index].length; j++){

      if(i < W->ownColor - 1 && j == ColorArray[b[i].index].length - 1)
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = ColorArray[b[i+1].index].IndexsColor[0];
      
      else if(i == W->ownColor - 1 && j == ColorArray[b[i].index].length - 1)
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next;
      
      else
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = ColorArray[b[i].index].IndexsColor[j+1];
    }

  // Eliminacion de ColorArray
  for(u32 i = 0; i < W->ownColor; i++){
    free(ColorArray[i].IndexsColor);
    ColorArray[i].IndexsColor = NULL;
  }
  
  free(b); b = NULL;
  free(ColorArray);
  ColorArray = NULL;
}


void colorOrdRandom(WinterIsHere W, u32 x){
  
  struct Rainbow *ColorArray;
  ColorArray = LoadsRainbow(W);
  pOrdenX b = calloc(W->ownColor, sizeof(struct OrdenX));

  // Array que sera ordenado random para evitar swaper las estructuras
  for(u32 i = 0; i < W->ownColor; i++){
    b[i].index = i;
    b[i].cmp = ColorArray[i].length;
  }

  struct OrdenX temp;
  u32 leng = W->ownColor;

  srand(x);

  // Ordenamos aleatoriamente los vertices
  for(u32 i = 1, j; i < leng/2; i++){
    j = rand() % (leng/2);
    temp = b[j];
    b[j] = b[leng - i];
    b[leng - i] = temp;
  }

  W->first = ColorArray[b[0].index].IndexsColor[0];

  // Los for's anidados recorren los arreglos con los conjuntos de colores, es analogo los for
  // del ColorOrd2.
  for(u32 i = 0; i < W->ownColor; i++)
    for(u32 j = 0; j < ColorArray[b[i].index].length; j++){
      // Caso en el que i es menor a la cantidad de colores y j es el ultimo vertice de color i
      if(i < W->ownColor - 1 && j == ColorArray[b[i].index].length - 1)
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = ColorArray[b[i+1].index].IndexsColor[0];
      // Caso en el que i sea el ultimo color y j sea el ultimo vertice de color i next a si mismo
      else if(i == W->ownColor - 1 && j == ColorArray[b[i].index].length - 1)
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next;
      else
        W->pVertex[ColorArray[b[i].index].IndexsColor[j]].next = ColorArray[b[i].index].IndexsColor[j+1];
    }
    
  // Eliminacion de ColorArray
  for(u32 i = 0; i < W->ownColor; i++){
    free(ColorArray[i].IndexsColor);
    ColorArray[i].IndexsColor = NULL;
  }
  free(b); b = NULL;
  free(ColorArray);
  ColorArray = NULL;

}