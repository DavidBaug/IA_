# Los extraños mundos de Belkan

##### David Gil Bautista

##### 45925324M

##### [Contacto](mailto:davidgilbautista@gmail.com)



## Índice

#### [Introducción y análisis del problema](#id1)

#### [Búsqueda en Anchura](#id2)

#### [Coste Uniforme](#id3)



<div id='id1' />

## Introducción y análisis del problema

Para el desarrollo y resolución de esta práctica se nos presenta un escenario con un agente cuyo comportamiento actual es completamente deliberativo. 

A raíz de un algoritmo de búsqueda en profundidad se nos exige implementar una alternativa usando una búsqueda en anchura, otra búsqueda basada en la minimización del coste uniforme y una mezcla entre agente reactivo y deliberativo.

<div id='id2' />

## Búsqueda en Anchura

Para realizar una búsqueda en anchura exploramos los niveles del árbol, por lo que lo único que debemos hacer es expandir los nodos y colocar los hijos en una cola. De esta forma aseguramos que vamos a explorar los nodos nivel por nivel.

Al contrario que con la búsqueda en profundidad que buscamos expandir un nodo hasta llegar a los nodos hoja. Para esta búsqueda colocamos los elementos que vamos expandiendo en una pila, para que estos siempre sean los primeros que volvemos a expandir.



<div id='id3' />

## Coste Uniforme

Podemos relacionar el coste uniforme con una búsqueda en anchura, ya que ejercemos los mismos pasos pero añadimos una variable que nos permitirá saber en qué orden expandir los nodos.

En este algoritmo he optado por usar una cola con prioridad, en la que ordenamos los nodos por su coste (lo que cuesta llegar a él). De esta forma siempre conseguimos expandir el mejor nodo y aseguramos un resultado de coste mínimo.

Para complementar este algoritmo he decidido revisar la inserción de nodos usando un multiset en el que guardaré todos los estados abiertos, y en caso de querer introducir uno nuevo de coste mayor obviarlo y ahorrar tiempo de cómputo.
