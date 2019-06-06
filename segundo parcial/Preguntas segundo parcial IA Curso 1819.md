# Preguntas segundo parcial IA Curso 18/19



### 1. Componentes de un juego.

Un juego es un entorno compuesto por varios agentes (llamados **jugadores**) y un **conjunto de reglas** que pueden usar los jugadores para generar **estrategias** con el fin de llevarles a obtener un cierto **beneficio**. 

En un juego también podemos encontrar la existencia o no de movimientos de **azar**, la **información** disponible para los jugadores (**perfecta o imperfecta**), el **reparto de beneficios** y la existencia o no de **pagos colaterales** (equilibrio de Nash).



### 2.  Qué es el factor de ramificación y cómo afecta a la complejidad de un juego? Describe en líneas generales el algoritmo minimax y el de la poda alfa-beta

El factor de ramificación en un juego hace referencia al máximo número de sucesores que puede tener un nodo. Cuanto mayor sea este factor más complicado, computacionalmente hablando, será encontrar una solución ya que el número de nodos a expandir y explorar aumenta exponencialmente en cada nivel.

El algoritmo minimax es un algoritmo recursivo que avanza en profundidad hasta llegar a un nodo hoja o hasta el límite de exploración y devuelve los valores de ese nodo hacia arriba. En cada nivel tomaremos el mínimo o el máximo de los sucesores, lo que nos garantiza que tomamos la mejor decisión suponiendo que el oponente también busca obtener el máximo beneficio.

El algoritmo de poda alfa-beta es exactamente que el algoritmo minimax, pero en este caso introducimos dos variables auxiliares que iremos modificando tras recorrer el árbol y que dependiendo de los valores obtenidos en los nodos nos ayudará a decidir si explorarlos o no.



### 3. ¿Que problemas plantea el cálculo de predicados en la resolución de problemas de IA?

caca



### 4. Modelos de conocimiento heredable ¿Qué tipo de conocimiento organizan las redes semánticas? Describir en líneas generales el concepto de “frame”.



### 5. Estructura y componentes de un sistema experto



### 6. Paradigmas de Aprendizaje Automático.





### 7. Describir el problema del ruido y el del sobreajuste en aprendizaje automático.



### 8. ¿Qué son y como se construyen los arboles de decisión?

