/*
Juan Ignacio Magnarelli | juanmagnarelli@gmail.com

Cristian Contrera | cristiancontrera95@gmail.com

Lucas Agustin de Francesca | lucasdfrancesca@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


typedef unsigned int u32;

// Estructura usada para ordenar arreglos con qsort
struct OrdenX{
  u32 index;         // campo index del vertice
  u32 cmp;           // campo a comparar en qsort
};

// Estructura que contendra conjuntos de vertices con el mismo color 
struct Rainbow{
  u32 length;
  u32* IndexsColor;
};

// Estructura de un vertice
struct VertexSt{
  u32 name;          // numero del vertice en archivo
  u32 index;         // Etiqueta. numero de 0 a n-1
  u32 color;
  u32 grade;         // Cantidad de vecinos
  u32 iVecino;       // iesimo-vecino agregado en pVecinos
  u32 next;          // Siguiente vertice en el orden
  u32 *pVecinos;     // los index de los vecinos
};

// Estructura del grafo
struct WinterSt{
  u32 nVertex;
  u32 mEdge;
  u32 ownColor;      // Cantidad de colores en el coloreo propio actual
  u32 first;         // Primer vertice en el orden actual
  u32 grade;	     // Grado del vertice
  struct VertexSt *pVertex;
};

typedef struct WinterSt *WinterIsHere;
typedef struct VertexSt *pVertex;
typedef struct OrdenX *pOrdenX;

// Funciones de construccion/destruccion del grafo
WinterIsHere WinterIsComing();

int Primavera(WinterIsHere W);

// Funciones de coloreo
u32 Greedy(WinterIsHere W);

int Bipartito(WinterIsHere W);

// Funciones para extraer informacion de datos del grafo

u32 NumeroDeVertices(WinterIsHere W);

u32 NumeroDeLados(WinterIsHere W);

u32 NumeroVerticesDeColor(WinterIsHere W, u32 i);

u32 NumeroDeColores(WinterIsHere W);

u32 IesimoVerticeEnElOrden(WinterIsHere W,u32 i);

// Funciones de ordenacion

void OrdenNatural(WinterIsHere W);

void OrdenWelshPowell(WinterIsHere W);

void AleatorizarVertices(WinterIsHere W,u32 x);

void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x);

// Funciones de los vertices

u32 NombreDelVertice(WinterIsHere W, u32 x);

u32 ColorDelVertice(WinterIsHere W, u32 x);

u32 GradoDelVertice(WinterIsHere W, u32 x);

u32 IesimoVecino(WinterIsHere W, u32 x,u32 i);

// Funciones de comparacion para ordenar

/* Compara por el campo grade de la estructura VertexSt 
   para ordenar de menor a mayor */
int Aymiperrito(const void *a, const void *b);

/* Compara por el campo grade de la estructura VertexSt
   para ordenar de mayor a menor */
int Aymiranarene(const void *a, const void *b);

/* Compara int, para ordenar de menor a mayor*/
int Aymisapito(const void *a, const void *b);

/* Compara u32, para ordenar de menor a mayor */
int Aymitortuguita(const void *a, const void *b);

/* Compara por el campo name de la estructura VertexSt  y un u32
   en busqueda bianria de menor a mayor*/
int AymiSolitariaVacaCubana(const void * a, const void * b);