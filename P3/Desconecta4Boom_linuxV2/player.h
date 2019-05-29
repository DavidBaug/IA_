#ifndef PLAYER_H
#define PLAYER_H

#include "environment.h"

class Player{
    public:
      Player(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
      double Poda_AlfaBeta(Environment , int ,int &, double , double);
      double comprueba(const Environment &, int);
      double ValoracionTablero(const Environment &,int , int );

    private:
      int jugador_;
      Environment actual_;
};
#endif
