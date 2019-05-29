#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){
  return Puntuacion(jugador, estado);
}


// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}






// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }

    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    int accionAuxiliar = -1;
    valor = Poda_AlfaBeta(actual_,PROFUNDIDAD_ALFABETA, accionAuxiliar, menosinf, masinf);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    cout << accionAuxiliar;

    switch (accionAuxiliar){
      case 0: accion = Environment::PUT1; break;
      case 1: accion = Environment::PUT2; break;
      case 2: accion = Environment::PUT3; break;
      case 3: accion = Environment::PUT4; break;
      case 4: accion = Environment::PUT5; break;
      case 5: accion = Environment::PUT6; break;
      case 6: accion = Environment::PUT7; break;
      case 7: accion = Environment::BOOM; break;
    }

    return accion;
}



double Player::Poda_AlfaBeta(Environment tablero , int profundidad ,int &accion, double alpha , double beta ){

	//cout << " Accion -> " << accion << endl;
	Environment hijo ;
	double aux;
	int ult_accion = -1;

  if(profundidad == 0 || tablero.JuegoTerminado())
	 return comprueba(tablero,jugador_);

	else{
    if(tablero.JugadorActivo() == jugador_ ){

  		hijo = tablero.GenerateNextMove(ult_accion);
  		aux = alpha;

  		while(ult_accion<8){
  			int nueva_accion = ult_accion;

  			double valorHijo = Poda_AlfaBeta(hijo , profundidad-1 ,nueva_accion, aux , beta);

  			if(valorHijo > aux && profundidad >= 0){
  				accion = ult_accion;
  			}

  			aux = max( aux , valorHijo);

  			if (beta <= aux)
          break;

  			hijo = tablero.GenerateNextMove(ult_accion);


  		}

  	}else{

  		hijo = tablero.GenerateNextMove(ult_accion);
  		aux = beta;

  		while(ult_accion<8){
  			int nueva_accion = ult_accion;

  			double valorHijo = Poda_AlfaBeta(hijo , profundidad-1 ,nueva_accion, alpha , aux);

  			if(valorHijo < aux && profundidad >= 0){
  				accion = ult_accion;
  			}

  			aux = min( aux , valorHijo);
        if (aux <= alpha)
            break;

  			hijo = tablero.GenerateNextMove(ult_accion);

  		}

  	}
  }

	return aux;

}


double Player::comprueba(const Environment &estado, int jugador){

  int ganador = estado.RevisarTablero();

  if (ganador==jugador)
     return 99999999.0; // Gana el jugador que pide la valoracion
  else if (ganador!=0)
          return -99999999.0; // Pierde el jugador que pide la valoracion
  else if (estado.Get_Casillas_Libres()==0)
          return 0;  // Hay un empate global y se ha rellenado completamente el tablero
  else{

  double suma = ValoracionTablero(estado,0,0);

  for (int i=0; i<7; i++)
      for (int j=0;j<7; j++){

        if (estado.See_Casilla(i,j)!=0 && suma > ValoracionTablero(estado,i,j) )
          suma += ValoracionTablero(estado,i,j);

      }

  	return suma;
  }


}



double Player::ValoracionTablero(const Environment &estado ,int fila, int columna){

    if (estado.See_Casilla(fila,columna)==0)
        return 0.0;

    //Comprueba 4 en la fila
    if (columna<4 && estado.See_Casilla(fila,columna) ){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila,columna+1)) &&
          (estado.See_Casilla(fila,columna+1)) == (estado.See_Casilla(fila,columna+2)) &&
          (estado.See_Casilla(fila,columna+2)) == (estado.See_Casilla(fila,columna+3))){


          if(estado.See_Casilla(fila,columna) == jugador_){
              return -99999.0;
          }else{
              return 99999.0;
          }

      }
    }

    //Comprueba 4 en la columna
        if (fila<4){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila+1,columna)) &&
          (estado.See_Casilla(fila+1,columna)) == (estado.See_Casilla(fila+2,columna)) &&
          (estado.See_Casilla(fila+2,columna)) == (estado.See_Casilla(fila+3,columna))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -99999.0;
          }else{
              return 99999.0;
          };
      }
    }

    //Comprueba 4 en una diagonal
    if (fila<4 && columna<4){
      if ((estado.See_Casilla(fila,columna))     == (estado.See_Casilla(fila+1,columna+1)) &&
          (estado.See_Casilla(fila+1,columna+1)) == (estado.See_Casilla(fila+2,columna+2)) &&
          (estado.See_Casilla(fila+2,columna+2)) == (estado.See_Casilla(fila+3,columna+3))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -99999.0;
          }else{
              return 99999.0;
          };
      }
    }


    //Comprueba 4 en nueva_accion diagonal
    if (fila>2 && columna<4){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila-1,columna+1)) &&
          (estado.See_Casilla(fila-1,columna+1)) == (estado.See_Casilla(fila-2,columna+2)) &&
          (estado.See_Casilla(fila-2,columna+2)) == (estado.See_Casilla(fila-3,columna+3))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -99999.0;
          }else{
              return 99999.0;
          };
      }
    }

	//Comprueba 3 en la fila
    if (columna<5 && estado.See_Casilla(fila,columna) ){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila,columna+1)) &&
          (estado.See_Casilla(fila,columna+1)) == (estado.See_Casilla(fila,columna+2))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -999.0;
          }else{
              return 999.0;
          }

      }
    }

	//Comprueba 3 en la columna
    if (fila<5){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila+1,columna)) &&
          (estado.See_Casilla(fila+1,columna)) == (estado.See_Casilla(fila+2,columna))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -999.0;
          }else{
              return 999.0;
          };
      }
    }

    //Comprueba 3 en la diagonal
    if (fila<5 && columna<5){
      if ((estado.See_Casilla(fila,columna))     == (estado.See_Casilla(fila+1,columna+1)) &&
          (estado.See_Casilla(fila+1,columna+1)) == (estado.See_Casilla(fila+2,columna+2))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -999.0;
          }else{
              return 999.0;
          };
      }
    }

    //Comprueba 3 en la diagonal
    if (fila>1 && columna<5){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila-1,columna+1)) &&
          (estado.See_Casilla(fila-1,columna+1)) == (estado.See_Casilla(fila-2,columna+2))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -999.0;
          }else{
              return 999.0;
          };
      }
    }


	//Comprueba 2 en la fila
    if (columna<6 && estado.See_Casilla(fila,columna) ){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila,columna+1))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -9.0;
          }else{
              return 9.0;
          }

      }
    }
    //Comprueba 2 en la columna
    if (fila<6){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila+1,columna))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -9.0;
          }else{
              return 9.0;
          };
      }
    }
    //Comprueba 2 en diagonal
    if (fila<6 && columna<6){
      if ((estado.See_Casilla(fila,columna))     == (estado.See_Casilla(fila+1,columna+1))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -9.0;
          }else{
              return 9.0;
          };
      }
    }

    //Comprueba 2 en diagonal
    if (fila>0 && columna<6){
      if ((estado.See_Casilla(fila,columna))   == (estado.See_Casilla(fila-1,columna+1))){

          if(estado.See_Casilla(fila,columna) == jugador_){
              return -9.0;
          }else{
              return 9.0;
          };
      }
    }

    return 0.0;

}
