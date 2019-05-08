# Preguntas primer parcial IA Curso 18/19



### 1. Concepto de agente. Agente Racional vs Agente Inteligente. Arquitectura de agentes.

Un agente es un sistema situada en un entorno con capacidad para percibirlo mediante una serie de sensores, procesar la información obtenida y actuar en consecuencia gracias a un conjunto de actuadores.

Un agente racional es aquel que responde de forma correcta al entorno y que de un conjunto de acciones posibles escoge la más favorable para conseguir su objetivo. Un agente inteligente es un agente racional que consigue pasar el test de Turing. Dicho test prueba si el agente presenta un comportamiento inteligente como el de un ser humano si otro ser humano no es capaz de distinguir si está tratando con otro humano o con una máquina.

Podemos dividir la arquitectura de los agentes por topología o por nivel de abstracción:

- Topología
  - **Arquitectura horizontal:** En esta arquitectura todas las capas tienen acceso a los sensores y a los actuadores. Cada capa es experta en una acción y produce una acción específica. Esta arquitectura presenta una salida consistente aunque también un cuello de botella a la hora de procesar la información.
  - **Arquitectura vertical: **Solo una capa tiene acceso a los sensores y actuadores, a través de paso de mensajes la información se va enviando a las distintas capas hasta llegar a conseguir la acción. El problema de esta arquitectura es que no es tolerante a fallos.
  - **Arquitectura híbrida:** Combinación de las anteriores.
- Nivel de abstracción
  - **Arquitectura reactiva:** Se caracteriza porque opera rápidamente y efectivamente sin la necesidad de procesar una representación simbólica del entorno. La decisión que toman está basada en el presente (aunque pueden hacer uso de acciones anteriores). Su actuación es estímulo-respuesta.
  - **Arquitectura deliberativa:** Contiene un mundo representado explícitamente y un modelo lógico del mismo, y en la cual las acciones son tomadas por medio de un razonamiento lógico.
  - **Arquitectura híbrida: **Combinación de las anteriores.



### 2.  Características de los Agentes reactivos y deliberativos. Similitudes y diferencias. Arquitecturas.

Un agente reactivo decide en cada instante su próxima acción en función de la última información recibida del entorno (y en algunos casos, de la información recibida anteriormente), de forma que en su diseño están contempladas multitud de situaciones que pueden darse para las que se establece una acción lo más adecuada posible. Estos agentes presentan una arquitectura horizontal.

En el caso de los agentes deliberativos, los cuales presentan un modelo del entorno, son capaces de establecer objetivos y crear secuencias de acciones mediante algoritmos de planificación que son capaces de llevarlos a conseguir dichos objetivos. Estos agentes serán mucho más complicados porque incluyen, además de la planificación, la monitorización de los planes creados (actualizarlos para adaptarlos a las circunstancias cambiantes del entorno). Los agentes deliberativos presentan una arquitectura vertical.

Ambos tipos de agentes suelen tener un modelo del entorno (aunque en el caso del agente reactivo no es indispensable) y tienen una medida de del desempeño que define el éxito de sus decisiones. Por lo general los agentes deliberativos son mucho más
lentos (en cuanto al tiempo necesario para elegir una acción) debido al tiempo empleado en planificar y al tiempo empleado en determinar cuando y qué planificar (aunque también pueden encapsular un comportamiento reactivo en caso de que no tengan un plan que ejecutar). Sin embargo, los agentes reactivas no procesan planes y toman sus acciones basadas en los estímulos que reciben en ese instante, por ello son mucho más rápidos.



### 3.- Describir brevemente los métodos de búsqueda no informada. 



Podemos distinguir 4 métodos distintos de búsqueda no informada.

- **Anchura:** Desde el estado inicial se exploran todos los nodos hijos antes de pasar al siguiente nivel.
- **Profundidad:** Desde el estado inicial se irán explorando los nodos hijo del nodo escogido. En caso de no encontrar la solución se escogerá otro hijo y se realizará el mismo proceso. Dentro de este método podemos diferenciar otras dos variantes.
  - Profundidad limitad: Al igual que profundidad aunque limitando el nivel de nodos a explorar.
  - Profundidad iterativa: En este método se exploran los nodos nivel a nivel al igual que en la búsqueda en anchura, aunque en cada iteración se expande la frontera en caso de no haber encontrado la solución.
- **Coste Uniforme:** En este método se supone que los arcos que conectan los nodos del árbol tienen un coste. Se escogerá explorar aquel nodo cuyo coste sea mínimo.
- **Bidireccional:** Usando este método se realizan dos búsquedas simultáneas, una desde el estado inicial hacia delante y otra desde el objetivo hacia atrás. Se encuentra la solución una vez se encuentren las dos búsquedas.



### 4.- El concepto de heurística. Como se construyen las heurísticas. Uso de las heurísticas en IA.



Una heurística es un criterio, método o principio para decidir cual, entre una serie de alternativas acciones, promete ser la más efectiva a la hora de lograr alguna meta. Es importante que la heurística elegida funcione bien ya que una mala decisión puede causar un gran problema para el funcionamiento del algoritmo.

La construcción de funciones heurísticas normalmente son a través de modelos simplificados. Es difícil encontrar una buena nada más empezar, ya que la iremos descubriendo poco a poco.

La Inteligencia Artificial se basa mayormente en el uso de algoritmos de búsqueda los cuales usan heurísticas para aportar un criterio más a la hora de seleccionar una acción en un momento dado. Aunque es cierto que no garantizan la solución óptima siempre produce resultados que satisfacen el problema. Incluso en ciertas ocasiones la heurística puede dar soluciones óptimas.

Las heurísticas se utilizan en Inteligencia Artificial para guiar las búsquedas, ofreciendo información adicional, y reducir el número de decisiones que procesar. Una buena heurística puede proporcionar una solución óptima a un problema de forma mucho más rápido que otro algoritmo que no use una heurística.



### 5.- Los métodos de escalada. Caracterización general. Variantes.

Los métodos de escalada son un tipo de algoritmos de búsqueda local con conocimiento que se basan en la búsqueda en profundidad, ya que parten de un nodo inicial y seleccionan de entre sus hijos al mejor de ellos para continuar la búsqueda con él.

Podemos diferenciar los siguientes métodos de escalada:

- **Escalada Simple:** En este método, al encontrar un nodo más favorable al actual, se expande ignorando el resto de nodos no explorados. Una vez hecho esto se vuelve a realizar el mismo proceso sobre ese nodo.
- **Escalada por la máxima pendiente:** En este caso, se generan todos los hijos de un nodo, y
  se calculan sus valores heurísticos. Se determina uno de los nodos de mejor valor, y se
  compara dicho valor con el del nodo explorado. Si es mejor, éste pasa a ser el nodo en curso
  y sigue el proceso.



Para evitar la posibilidad de encontrar sólo óptimos locales surgen ciertas variantes:

- **Estocástica:** Escoge aleatoriamente entre los sucesores con mejor valoración que el estado actual.

- **Primera opción:** Se generan aleatoriamente sucesores, escogiendo el primero con mejor valoración que el estado actual.

- **Reinicio aleatorio:** Se repite varias veces la búsqueda partiendo cada vez desde un nodo inicial distinto, generado aleatoriamente. El mejor nodo inicial es guardado y si posteriormente hay un nodo mejor que el guardado, lo reemplaza.

  

### 6.- Características esenciales de los métodos “primero el mejor”.

Estos métodos se basan en variantes del algoritmo de Dijkstra, en el que generamos dos listas, una para almacenar los nodos que se han generado y otra para almacenar los ya explorados.

A la primera la llamaremos lista de abiertos, la cual es una lista de nodos que se han generado aplicando una función heurística pero que aún no han sido explorados. Se explorará aquél nodo que presente un mejor valor heurístico ("primero el mejor").

En la segunda lista, que llamaremos lista de cerrados, almacenamos los nodos ya explorados, y nos permitirá reconstruir el camino una vez hallada la solución.

En estos métodos se simula una búsqueda en profundidad en la que buscamos expandir los nodos más cercanos a la solución, y en caso de no ser los idóneos volveremos atrás para explorar otros.



### 7.- Elementos esenciales del algoritmo A*.



Se trata de un algoritmo “primero el mejor” donde f(n) es la suma de dos componentes, g(n) y h(n).

En este algoritmo g(n) representará la distancia/coste desde el nodo inicial al actual. Y h(n) representará una estimación de la distancia/coste desde el nodo actual hasta el objetivo.

Dicho algoritmo usa dos listas, una destinada para almacenar los nodos generados y otra para guardar los que ya han sido explorados. Al ser un algoritmo "primero el mejor", ordenaremos la lista de nodos generados, que llamaremos lista de abiertos, por los que presenten un f(n) mejor. Y usaremos la lista de nodos ya explorados, a la que llamaremos lista de cerrados, para poder reconstruir el camino una vez hallada la solución.

El funcionamiento de este algoritmo es idéntico al de la búsqueda de costo uniforme suponiendo que no usamos una heurística para estimar la distancia desde el nodo actual al objetivo.

El rendimiento de este algoritmo depende de la calidad de la función heurística usada, en caso de escoger la idónea seremos capaces de encontrar una solución óptima en un tiempo razonable, al contrario, si escogemos una mala heurística, el propio algoritmo saldrá perjudicado y tendrá peor rendimiento que otros algoritmos más básicos.



### 8.- Elementos esenciales de un algoritmo genético.



Los algoritmos genéticos son métodos de optimización basados en una simulación parcial de los
mecanismos de la evolución natural. Por lo que presentan una serie de elementos inspirados en la evolución biológica y su base genético-molecular.

Podemos distinguir los siguientes elementos:

- **Cromosoma:** Vector representación de una solución al problema.
- **Gen:** Característica concreta del valor de representación de una solución.
- **Población:** Conjunto de soluciones al problema.
- **Adecuación al entorno**: Valor de función objetivo.
- **Selección natural:** Operador de selección.
- **Reproducción sexual:** Operador de cruce.
- **Mutación**: Operador de mutación.
- **Cambio generacional**: Operador de reemplazamiento.



Estos algoritmos parten de una población inicial, y con el paso del tiempo mediante mutaciones y cruces la población obtiene una mejor adecuación al entorno. Son algoritmos de tipo "generar y probar" con un componente estocástico basado en poblaciones que permite reducir la diversidad y obtener soluciones óptimas.