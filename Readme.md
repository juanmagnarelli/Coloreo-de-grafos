## Proyecto de Matematica discreta II
### Integrantes
Juan Ignacio Magnarelli | juanmagnarelli@gmail.com
Cristian Contrera | cristiancontrera95@gmail.com
Lucas Agustin de Francesca | lucasdfrancesca@gmail.com
#### Como esta organizado el proyecto
**AyNuestrasBonitasFunciones.c** Se encuentran todas las funciones que son para comparar en el uso de ***qsort()*** y ***bsearch()***.
**Coloreo.c** Se encuentran bipartito y greedy.
**ConstruccionDestruccion.c** Aqui se crea el grafo y se destruye(liberación de memoria).
**InfoGrafo.c** Funciones que devuelven información del grafo.
**Ordenacion.c** Todas las funciones que determinan un orden de sus vertices al grafo.
**VerticesFunc.c** Funciones que devuelven información de un vertice especificado.
### Estructura del grafo
```
struct WinterSt{
  u32 nVertex;
  u32 mEdge;
  u32 ownColor;
  u32 first;
  struct VertexSt *pVertex;
};
```
**nVertex** Contiene número de vértices del grafo
**mEdge** Contiene número de aristas del grafo
**ownColor** Contiene el coloreo propio del grafo
**first** Indica cuál es el primer vértice que va procesar greedy
**pVertex** Contiene todos los vértices del grafo
```
  struct VertexSt{
  u32 name;
  u32 index;
  u32 color;
  u32 grade;
  u32 iVecino;
  u32 next;
  u32 *pVecinos;
};
```
name Nombre original del vértice
index Posición en el que se encuentra el vértice
color Color que tiene el vértice
grade Cantidad de vecinos que tiene el vértice
iVecino Hasta que cantidad de vecinos se agregó
next Este campo determina en el orden que se tiene que recorrer el grafo
pVecinos Contiene los índices de los vecinos del vértice
Cómo cargamos el grafo
En la función WinterIscoming() creamos dos arreglos auxiliares(aristas, aristasTemp). aristas representa las aristas tomadas del input, es decir el par de vértices vecinos (2i, 2i + 1). aristasTemp el cual es el arreglo aristas ordenado de menor a mayor, al tenerlo ordenado de forma ascendente nos sirve para ver la cantidad de vecinos que tiene cada vértice.
Luego creamos el arreglo de vértices del grafo, dándole su información. Una vez cargados los datos del arreglo de vértices, se utiliza qsort() para darle un orden natural, utilizando como referencia el nombre del vértice para facilitar la búsqueda binaria a la hora de agregar vecinos. Este arreglo quedará en este orden hasta que se libere el grafo, dado que los vecinos serán guardados con una referencia a sus índices en cada vértice.
Para ver los vecinos de cada vértice buscamos en pGraph->pVertex con búsqueda binaria los vértices aristas[i] y aristas[i+1], y agregamos a ambos como vecinos con la función newVecinos().
Las funciones de ordenación
#### CAMPO NEXT
La idea de este campo surge al querer mantener la estructura original del grafo. En cual el grafo tiene su campo first que indica por cual vértice empieza el recorrido, luego cada vértice tiene su campo next que indica cual es el siguiente vértice a procesar por greedy, generando así una ruta.
ALGORITMOS DE ORDENACIÓN EN GENERAL
Para evitar modificar el arreglo original de vértices, creamos estructuras auxiliares, OrdenX, Rainbow.
```
struct Rainbow{
  u32 length;
  u32* IndexsColor;
};
```
La estructura Rainbow la utilizamos para agrupar los índices del mismo color.
Se carga en la función LoadsRainbow(). Primero cargamos cada índice del vértice y su color en el arreglo a, ordenando por color. Recorremos el arreglo a contando la cantidad de vértices con determinado color, y agregamos sus índices al arreglo IndexsColor.
```
struct OrdenX{
  u32 index;
  u32 cmp;
};
```
La estructura OrdenX se utiliza para pasarle los índices y el parámetro de comparación a la función que le dará un orden. Estos parámetros pueden ser el grado y el color. Esta función generará un arreglo con el orden de los índices de los vértices.
Una vez calculado el orden en que serán ejecutados los vértices, se pasa esta información a los campos first del grafo y next de cada vértice.
#### Cómo coloreamos el grafo
En la función Greedy, en primer lugar “se despinta” todo el grafo, dandole color 0 a cada vértice. Luego pintamos de color 1 el primer vértice del recorrido, cuyo índice se encuentra en el campo first de la estructura del grafo. Se crea un arreglo de colores con tamaño del grado del grafo más dos, porque es la máxima cantidad de colores que tendra el grafo, ya que el color cero no se usa. Luego se recorren los vecinos de un vértice, usando sus colores como índice del arreglo en el cual se indica con 1 si éste fue usado. Posteriormente recorremos el arreglo buscando un cero, el cual nos indica que ese índice del arreglo es igual a un color no usado por los vecinos. Se resetea el arreglo de colores y se procede a procesar los siguientes vértices.

#### Bipartito
La función bipartito funciona con dos funciones auxiliares. Estas funciones pintan el vértice dado y llaman de manera recursiva a la otra función. Bipartito llama a la primera de estas PintaDe1(). Aquí se pinta de color 1 el vértice dado, y se llama a PintaDe2() de todos sus vecinos, que hará lo mismo pintando de 2 y llamando a PintaDe1()… Las dos funciones van pintando todo el grafo de dos colores hasta que se encuentra una inconsistencia, es decir, que por ejemplo se quiera pintar de 1 un vértice que ya está pintado de 2, esto quiere decir que el grafo no es bipartito, por lo tanto el resultado de las funciones será falso. En caso de que se termine de pintar de 2 colores el grafo (O esa parte conexa del grafo) se devuelve verdadero. En Bipartito hay un for que revisa que todos los vértices tengan color diferente de 0 en caso de que no sea un grafo conexo. De ser no conexo llamara de nuevo a las funciones recursivas para el vértice no pintado y sus vecinos.