#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player{
    public:
      Player(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
      double Poda_AlfaBeta(const Environment & tablero, int jugador, int profundidad, int profundidad_maxima, Environment::ActionType & accion, double alfa, double beta);

    private:
      int jugador_;
      int contrario_;
      Environment actual_;
};
#endif
