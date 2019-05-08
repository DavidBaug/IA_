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