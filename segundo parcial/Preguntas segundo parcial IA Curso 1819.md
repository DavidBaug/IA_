# Preguntas segundo parcial IA Curso 18/19



### 1. Componentes de un juego.

Un juego es un entorno compuesto por varios agentes (llamados **jugadores**) y un **conjunto de reglas** que pueden usar los jugadores para generar **estrategias** con el fin de llevarles a obtener un cierto **beneficio**. 

En un juego también podemos encontrar la existencia o no de movimientos de **azar**, la **información** disponible para los jugadores (**perfecta o imperfecta**), el **reparto de beneficios** y la existencia o no de **pagos colaterales** (equilibrio de Nash).



### 2.  Qué es el factor de ramificación y cómo afecta a la complejidad de un juego? Describe en líneas generales el algoritmo minimax y el de la poda alfa-beta

El factor de ramificación en un juego hace referencia al máximo número de sucesores que puede tener un nodo. Cuanto mayor sea este factor más complicado, computacionalmente hablando, será encontrar una solución ya que el número de nodos a expandir y explorar aumenta exponencialmente en cada nivel.

El algoritmo minimax es un algoritmo recursivo que avanza en profundidad hasta llegar a un nodo hoja o hasta el límite de exploración y devuelve los valores de ese nodo hacia arriba. En cada nivel tomaremos el mínimo o el máximo de los sucesores, lo que nos garantiza que tomamos la mejor decisión suponiendo que el oponente también busca obtener el máximo beneficio.

El algoritmo de poda alfa-beta es exactamente que el algoritmo minimax, pero en este caso introducimos dos variables auxiliares que iremos modificando tras recorrer el árbol y que dependiendo de los valores obtenidos en los nodos nos ayudará a decidir si explorarlos o no.



### 3. ¿Que problemas plantea el cálculo de predicados en la resolución de problemas de IA?

Resolver una problema de inteligencia artificial requiere de un proceso de análisis del dominio del problema y un estudio sobre la elección del vocabulario y codificación de los axiomas que necesita para inferir. Por esto mismo no suele ser buena idea usar cálculo de predicados en un modelo del mundo con información incompleta o que se vaya a actualizar constantemente.



### 4. Modelos de conocimiento heredable ¿Qué tipo de conocimiento organizan las redes semánticas? Describir en líneas generales el concepto de “frame”.

Las redes semánticas buscan representar el lenguaje natural. Existen diversas variantes, pero todas son capaces de representar objetos individuales, categorías de objetos y relaciones entre ellos.

Un frame es una forma de expresar la información de una red semántica textualmente, es decir, una estructura de datos que nos permite representar el conocimiento de forma que el ordenador pueda operar con él. Además de la parte declarativa un frame puede añadir una procedimental, que mediante funciones y métodos que ayudan a calcular soluciones y reducir el coste de la inferencia.

---

Un frame es una entidad compleja que nos permite representar el conocimiento relevante de un concepto. Proporcionan un formalismo para agrupar explícitamente todo el conocimiento concerniente a las propiedades de objetos individuales o clases de objetos. Podemos discernir frames clase, que representan conocimiento de clases de objetos y frames instancia, que representan conocimiento de objetos individuales.



### 5. Estructura y componentes de un sistema experto

![img](https://ciberconta.unizar.es/LECCION/sistexpat/DIBUJOS/sist1.GIF)



Base de conocimiento: Contiene el conocimiento que se extrae del experto codificado en la base de datos. Generalmente se representa mediante reglas.

Base de hechos: Contiene la información que se genera tras una consulta. A una información dada el sistema la empareja con su conocimiento y genera una salida.

Motor de inferencia: Es el encargado de trabajar con la información de la base de conocimiento y la base de hechos para deducir nuevos hechos.

Subsistema de explicación:

Interfaz de usuario: La interacción entre un sistema experto y un usuario se realiza en lenguaje natural. La interfaz de usuario es la encargada de facilitar al usuario la comunicación con el sistema.



### 6. Paradigmas de Aprendizaje Automático.

**Aprendizaje supervisado:** El aprendizaje supervisado busca inferir una función determinada dados unos datos de aprendizaje. Es decir, teniendo una **x** y una **y** deducir una **f** tal que **f(x) = y**. Podemos diferenciar clasificación,cuando la salida es categórica, y regresión cuando la salida es cuantitativa.

**Aprendizaje no supervisado:** En el aprendizaje no supervisado sólo tenemos datos de entrada, por lo que se busca modelar una distribución que nos permita distribuir los datos. Podemos diferenciar los siguientes algoritmos:

- Agrupación: el objetivo es descubrir agrupaciones en los datos
- Análisis de asociaciones: queremos ir y descubrir las reglas que mejor describen la mayor parte de los datos posibles
- Estimación cuantil

**Aprendizaje por refuerzo:** Se aprende a partir de la información obtenida al realizar procesos de ensayo-error en los que se obtienen señales de beneficio/coste.



### 7. Describir el problema del ruido y el del sobreajuste en aprendizaje automático.

El ruido puede causar que nuestro algoritmo no pueda encontrar una función que resuelva el problema, o que la solución encontrada no sea buena. En cuanto al sobreajuste, el aumentar la complejidad polinómica puede hacer que reduzcamos el error de entrenamiento y creamos que tenemos una solución muy buena, después al testear la solución descubrimos que no es la óptima. Al sobreajustar tendemos a aprender ciertos patrones que presentan los datos que se usan en el entrenamiento, por lo que la solución no va a ser apta para nuevos datos que no hayan sido explorados previamente.

### 8. ¿Qué son y como se construyen los arboles de decisión?

Un árbol de decisión es como una caja negra que toma como entrada un objeto o una situación descrita a través de un conjunto de atributos y devuelve una decisión, el valor previsto de salida dada esa entrada.

En un árbol de decisión contamos con situaciones en los nodos intermedios del árbol, que pueden estar conectadas con soluciones finales u otras decisiones mediante arcos. Al crear un árbol de decisión buscamos poner los nodos cuyos arcos son más restrictivos al comienzo y conforme vayamos explorando los niveles nos acerquemos a una solución más óptima.

Por ejemplo, pongamos que dos amigos salen a cenar y uno es vegetariano, si primero comprobamos que el restaurante no tiene clientes, está cerca, es barato...etc, y lo último que hacemos es comprobar si ofrece un menú vegetariano puede que tengamos suerte, pero en caso contrario habremos realizado muchos cálculos previamente que no eran necesarios. 