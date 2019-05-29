double Poda_AlfaBeta(Environment &t, int jugador, int profundidad, int limite, double alfa, double beta, Environment::ActionType & accion){

  Environment::ActionType accion_anterior;

  if (t.JuegoTerminado() || profundidad == limite) {
    if(entorno.JuegoTerminado())
      return ValoracionTest(entorno,jugador_);
    else
      return Valoracion(entorno,jugador_);
  }

  Environment v[8];
  int n_hijos = t.GenerateAllMoves(v);

  // NODO MAX
  if (profundidad%2==0) {

    for (size_t i = 1; i < n_hijos; i++) {
      double aux = minmax(v[i], jugador, profundidad+1, limite, alfa, beta);

      if (aux>alfa){
        alfa=aux;
        accion = static_cast <Environment::ActionType > (ult_act);
      }

      //Poda beta
      if (beta<=alfa) {
        break;
      }

    }

    return alfa;

  }else{ // NODO MIN
    for (size_t i = 1; i < n_hijos; i++) {
      double aux = minmax(v[i], jugador, profundidad+1, limite, alfa, beta);

      if (aux<beta){
        beta=aux;
        accion = static_cast <Environment::ActionType > (ult_act);
      }

      //Poda alfa
      if (beta<=alfa) {
        break;
      }

    }

    return beta;

  }

}
