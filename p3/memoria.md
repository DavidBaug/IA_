# Desconecta4 BOOM



##### David Gil Bautista

##### 45925324M

##### [Contacto](mailto:davidgilbautista@gmail.com)



## Índice

#### [Introducción y análisis del problema](#id1)

#### [Búsqueda en Anchura](#id2)

#### [Coste Uniforme](#id3)



<div id='id1' />

## Introducción y análisis del problema

Para el desarrollo y resolución de esta práctica se nos presenta un juego de información perfecta en el que debemos ganar a diversos adversarios. El juego es similar al mítico 4 en raya, pero en este caso debemos conseguir que sea el oponente el que coloque 4 fichas consecutivas. Adicionalmente se introduce un nuevo concepto, las fichas bomba, que nos ayudarán a eliminar todas las fichas de un color de una fila determinada.



<div id='id2' />

## Poda Alfa-Beta

Para resolver este juego he optado por implementar una poda alfabeta con una profundidad límite de 8 niveles. Para esta función he usado una función recursiva que recorre el árbol de posibles jugadas expandiendo los valores de alfa y beta, una vez llegados a un nodo hoja o al límite de la profundidad se comprueban los valores del nodo y en consecuencia modificamos alfa o beta. Conforme vamos expandiendo el árbol los valores de poda son más restrictivos por lo que evitamos recorrer ramas que nunca van a ser recorridas.

<div id='id3' />

## Función de valoración

Para darle un valor a cada estado uso una función en la que recorro todas las posiciones y desde cada una de ellas compruebo las fichas adyacentes horizontales, verticales y diagonales. Para cada 