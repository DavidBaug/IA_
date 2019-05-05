#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <vector>



struct estado {
  int fila;
  int columna;
  int orientacion;

  bool operator==(const estado &n) const{
		if (this->fila == n.fila and this->columna == n.columna)
			return true;
		else
			return false;
	}

};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;

    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado actual, destino;
    list<Action> plan;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);

    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores);
    bool pathFinding_A(const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores);


    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);
    void colocar(Sensores sensores);

    pair<int,int> devuelveK(int i);

<<<<<<< HEAD:P2/practica2/jugador.hpp
    int filc, colc;
=======
>>>>>>> master:P2/practica2/Comportamientos_Jugador/jugador.hpp

    // Mis cosicas

    Action ultimaAccion;
    bool hayPlan;

    bool primera = true;
    bool situado = false;

    bool objetivo_fijado;
    int pos_objetivo;
    Action Giro;
    int num_avances;

    char mapaAux[200][200];
<<<<<<< HEAD:P2/practica2/jugador.hpp
    int mapaCosteAux[200][200];

    // vector<int> mapaCoste;

    int getCoste(char aux);

    list<Action> acciones;
    int delibera;
    int porcentaje;
    int exitos;
    int tam;

    double porcentajeMapa();
    int porcentajeVariable;
=======

    list<Action> acciones;
>>>>>>> master:P2/practica2/Comportamientos_Jugador/jugador.hpp

    list<Action> rutaPK1(int i);
    void pintaBordes();
    void guardaMapa(Sensores sensores);
    int heuristica(estado a, estado b);
    void rutaPK(int & num_avances, Action & Giro);


};

#endif
