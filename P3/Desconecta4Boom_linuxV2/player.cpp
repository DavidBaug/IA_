#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;

int i_boom = -1;
int j_boom = -1;

int i_boom_contrario = -1;
int j_boom_contrario = -1;

bool explotar;
bool nobomba;

// Constructor
Player::Player(int jug){
    jugador_=jug;
    explotar = false;
    nobomba = true;
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


// Funcion de valoracion para testear Poda Poda_AlfaBeta
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void fichasAdyacentes(int jugador, const Environment &estado, int row, int col, int &juntasV, int &juntasH, int &juntasD){

	juntasV=juntasH=juntasD=0;


	//Comprobamos desde la fila de la ficha hacia arriba cuantas fichas del mismo jugador hay adyacentes verticales
	for(int i=1; row-i>=0; i++){

    if(estado.See_Casilla(row-i, col)==jugador)
			juntasV++;
		else
      break;

  }

  //Comprobamos desde la fila de la ficha hacia abajo cuantas fichas del mismo jugador hay adyacentes verticales
	for(int i=1; row+i<7; i++){

    if(estado.See_Casilla(row+i, col)==jugador)
			juntasV++;
    else
      break;


	}
	//Comprobamos desde la columna de la ficha hacia la izquierda cuantas fichas del mismo jugador hay adyacentes horizontales
	for(int i=1; col-i>=0; i++){

    if(estado.See_Casilla(row, col-i)==jugador)
			juntasH++;
    else
      break;


	}
	//Comprobamos desde la columna de la ficha hacia la derecha cuantas fichas del mismo jugador hay adyacentes horizontales
	for(int i=1; col+i<7; i++){

    if(estado.See_Casilla(row, col+i)==jugador)
      juntasH++;
    else
      break;

	}
	//Comprobamos desde la columna de la ficha hacia la derecha y abajo cuantas fichas del mismo jugador hay adyacentes diagonales
	for(int i=1; i<4; i++){

		if(row+i>6 or col+i>6) break;

		if(estado.See_Casilla(row+i, i+i)==jugador)
			juntasD++;
    else
      break;

	}

	//Comprobamos desde la columna de la ficha hacia la derecha y arriba cuantas fichas del mismo jugador hay adyacentes diagonales
	for(int i=1; i<4; i++){

		if(row-i<0 or col+i>6) break;

		if(estado.See_Casilla(row-i, col+i)==jugador)
			juntasD++;
    else
      break;

	}

	//Comprobamos desde la columna de la ficha hacia la izquierda y abajo cuantas fichas del mismo jugador hay adyacentes diagonales
	for(int i=1; i<4; i++){

		if(row+i>6 or col-i<0) break;

		if(estado.See_Casilla(row+i, col-i)==jugador)
			juntasD++;
    else
      break;

	}

	//Comprobamos desde la columna de la ficha hacia la izquierda y arriba cuantas fichas del mismo jugador hay adyacentes diagonales
	for(int i=1; i<4; i++){

		if(row-i<0 or col-i<0) break;

    if(estado.See_Casilla(row-i, col-i)==jugador)
			juntasD++;
    else
      break;

	}

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Función para comprobar las fichas adyacentes verticales
int alineadasVertical(const Environment &estado, int fil, int col,int jugador,int num_fichas, int num_vacias){

    int alineadas = 0, vacias = 0;

    for(int i=fil; i<7; ++i){
        if (estado.See_Casilla(i,col) == jugador)
            alineadas++;
        else if(estado.See_Casilla(i,col) == 0)
            vacias++;
    }

    for(int i=fil; i>=0; --i){
        if (estado.See_Casilla(i,col) == jugador)
            alineadas++;
    }

    if(alineadas >= num_fichas && vacias >= num_vacias)
        return 2;
    else if(alineadas >= num_fichas)
        return 1;
    else
        return 0;
}


int alineadasDiagonalDecreciente(const Environment &estado, int fil, int col,int jugador, int num_fichas, int num_vacias){

    int total = 0, alineadas=0, vacias = 0;

    //Diagonales ascendentes
    for(int i=fil,j=col; i>=0 && j<7; --i, ++j){
        if (estado.See_Casilla(i,j) == jugador)
            alineadas++;
        else if(estado.See_Casilla(i,j) == 0)
            vacias++;
    }

    if(alineadas >= num_fichas)
        total++;

    alineadas = 0;

    //Diagonales descendentes
    for(int i=fil,j=col; i<7 && j>=0; ++i, --j){
        if (estado.See_Casilla(i,j) == jugador)
            alineadas++;
        else if(estado.See_Casilla(i,j) == 0)
            vacias++;
    }

    if(total >= num_fichas && vacias >= num_vacias)
        return 2;
    else if(total >= num_fichas)
        return 1;
    else
        return 0;

    return total;
}


//Función para comprobar las fichas adyacentes diagonales
int alineadasDiagonalCreciente(const Environment &estado, int fil, int col,int jugador, int num_fichas, int num_vacias){

    int total = 0, alineadas=0, vacias = 0;

    //Diagonales ascendentes
    for(int i=fil,j=col; i<7 && j<7; ++i, ++j){
        if (estado.See_Casilla(i,j) == jugador)
            alineadas++;
        else if(estado.See_Casilla(i,j) == 0)
            vacias++;
    }

    if(alineadas >= num_fichas)
        total++;

    alineadas = 0;

    //Diagonales descendentes
    for(int i=fil,j=col; i>=0 && j>=0; --i, --j){
        if (estado.See_Casilla(i,j) == jugador)
            alineadas++;
    }

    if(alineadas >= num_fichas)
        total++;

    if(total >= num_fichas && vacias >= num_vacias)
        return 2;
    else if(total >= num_fichas)
        return 1;
    else
        return 0;
}


//Función para comprobar las fichas adyacentes horizontales a la derecha
int alineadasHorizontalDer(const Environment &estado, int fil, int col,int jugador,int num_fichas, int num_vacias){

    int alineadas = 0, vacias = 0;

    for(int j=col; j<7; ++j){
        if (estado.See_Casilla(fil,j) == jugador)
            alineadas++;
        else if(estado.See_Casilla(fil,j) == 0)
            vacias++;
    }

    if(alineadas >= num_fichas && vacias >= num_vacias)
        return 2;
    else if(alineadas >= num_fichas)
        return 1;
    else
        return 0;
}

//Función para comprobar las fichas adyacentes horizontales a la izquierda
int alineadasHorizontalIzq(const Environment &estado, int fil, int col,int jugador,int num_fichas, int num_vacias){

    int alineadas = 0, vacias = 0;

    for(int j=col; j>=0; --j){
        if (estado.See_Casilla(fil,j) == jugador)
            alineadas++;
        else if(estado.See_Casilla(fil,j) == 0)
            vacias++;
    }

    if(alineadas >= num_fichas && vacias >= num_vacias)
        return 2;
    else if(alineadas >= num_fichas)
        return 1;
    else
        return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------


//Función para comprobar si en una misma fila, o en las diagonales, hay tres fichas entre las cuales hay un hueco
int alineadasFichasHueco(const Environment & estado, int jugador, int fil, int col){

    int lin_hueco = 0;

    //En la misma fila
    if (col<4){
      if (estado.See_Casilla(fil,col)==jugador && estado.See_Casilla(fil,col+1)== jugador && estado.See_Casilla(fil,col+3)==jugador && estado.See_Casilla(fil,col+2) == 0)
          lin_hueco++;
      else if (estado.See_Casilla(fil,col)==jugador && estado.See_Casilla(fil,col+1)== 0 && estado.See_Casilla(fil,col+3)==jugador && estado.See_Casilla(fil,col+2) == jugador)
          lin_hueco++;
    }

    //En la diagonal creciente
    if (fil<4 && col<4){
      if (estado.See_Casilla(fil,col)==jugador && estado.See_Casilla(fil+1,col+1)== jugador && estado.See_Casilla(fil+3,col+3)==jugador && estado.See_Casilla(fil+2,col+2) == 0)
          lin_hueco++;
      else if (estado.See_Casilla(fil,col)==jugador && estado.See_Casilla(fil+1,col+1)== 0 && estado.See_Casilla(fil+3,col+3)==jugador && estado.See_Casilla(fil+2,col+2) == jugador)
          lin_hueco++;
    }

    //En la diagonal decreciente
    if (fil>2 && col<4){
      if (estado.See_Casilla(fil,col)==jugador && estado.See_Casilla(fil-1,col+1)== jugador && estado.See_Casilla(fil-3,col+3)==jugador && estado.See_Casilla(fil-2,col+2) == 0)
          lin_hueco++;
      else if (estado.See_Casilla(fil,col)==jugador && estado.See_Casilla(fil-1,col+1)== 0 && estado.See_Casilla(fil-3,col+3)==jugador && estado.See_Casilla(fil-2,col+2) == jugador)
          lin_hueco++;
    }

    return lin_hueco;
}

//Función para calcular el número alineaciones tres fichas y hueco intermedio
int alineadasHueco(const Environment & estado, int jugador){

    int lin_hueco = 0;

    for(int i=0; i < 7; ++i){
        for(int j=0; j < 7; ++j)
            lin_hueco += alineadasFichasHueco(estado,jugador,i,j);
    }

    return lin_hueco;
}

//Función para calcular el número alineaciones num_fichas
int alineadas(const Environment & estado, int jugador,int num_fichas, int num_vacias){

    int total = 0;

    for(int i=0; i < 7; ++i){
        for(int j=0; j < 7; ++j){
            if(estado.See_Casilla(i,j) == jugador){
                total+=alineadasVertical(estado,jugador,i,j,num_fichas,num_vacias);
                total+=alineadasHorizontalDer(estado,jugador,i,j,num_fichas,num_vacias);
                total+=alineadasHorizontalIzq(estado,jugador,i,j,num_fichas,num_vacias);
                total+=alineadasDiagonalCreciente(estado,jugador,i,j,num_fichas,num_vacias);
                total+=alineadasDiagonalDecreciente(estado,jugador,i,j,num_fichas,num_vacias);
            }
        }
    }

    return total;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Función para encontrar la posición de la ficha bomba
void fichasBomba(const Environment & estado){

    //Actualizamos la posicion de la ficha bomba, si la hay
    for(int i=0; i < 7; ++i){
        for(int j=0; j < 7; ++j){
            if(estado.See_Casilla(i,j) == 4){
                i_boom = i;
                j_boom = j;
            }

            else if(estado.See_Casilla(i,j) == 5){
                i_boom_contrario = i;
                j_boom_contrario = j;
            }
        }
    }
}

//Funcion para comprobar si al explotar la bomba nos sale 4 en raya
int lineaBomba(const Environment & estado, int jugador,int i_boom, int j_boom){

    int total = 0;

    //Si la ficha es una ficha bomba, comprobamos las adyacentes
    if(estado.Have_BOOM(jugador) && i_boom < 5 && i_boom > 0 && j_boom > 0 && j_boom < 5){
            if(estado.See_Casilla(i_boom+2,j_boom) == jugador
               && estado.See_Casilla(i_boom+1,j_boom-1) == jugador
               && estado.See_Casilla(i_boom-1,j_boom+1)
               && (estado.See_Casilla(i_boom,j_boom+2) == jugador || estado.See_Casilla(i_boom,j_boom-2)))
                    total++;
    }

    return total;
}

//Función para comprobar las fichas adyacentes a la ficha bomba
int adyacentesBomba(const Environment & estado, int jugador,int i_boom, int j_boom){

    int total = 0;
    int contrario;

    if(jugador == 1)
        contrario = 2;
    else
        contrario = 1;

    //Si la ficha es una ficha bomba, comprobamos las adyacentes
    if(estado.Have_BOOM(jugador) && i_boom > 1 && i_boom < 5 && j_boom > 1 && j_boom < 5){
        if(estado.See_Casilla(i_boom+1,j_boom) == contrario){
                total++;
                if(i_boom < 5 && estado.See_Casilla(i_boom+2,j_boom) == jugador)
                    total++;
        }
        if(estado.See_Casilla(i_boom-1,j_boom) == contrario){
                total++;
                if(i_boom > 2 && estado.See_Casilla(i_boom-2,j_boom) == jugador)
                    total++;
        }
        if(estado.See_Casilla(i_boom+1,j_boom) == contrario){
                total++;
                if(j_boom < 5 && estado.See_Casilla(i_boom,j_boom+2) == jugador)
                    total++;
        }
        if(estado.See_Casilla(i_boom+1,j_boom) == contrario){
                total++;
                if(j_boom > 2 && estado.See_Casilla(i_boom,j_boom-2) == jugador)
                    total++;
        }
    }

    return total;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){

	int ganador = estado.RevisarTablero();
  int contrario,cuatros,cuatros_contrario,treses,treses_contrario,doses,doses_contrario,bomba=0,bomba_contrario=0;
  int lin_hueco = 0, lin_hueco_contrario = 0;

	if(jugador == 1)
        contrario = 2;
    else
        contrario = 1;


	if(ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion

    else if (ganador!=0)
       return -99999999.0; // Pierde el jugador que pide la valoracion

    else if (estado.Get_Casillas_Libres()==0)
       return 0;  // Hay un empate global y se ha rellenado completamente el tablero

    else{
        //Comprobamos las adyacentes del jugador actual
        treses = alineadas(estado,jugador,3,1);
        doses = alineadas(estado,jugador,2,2);
        cuatros = alineadas(estado,jugador,4,0);
       	lin_hueco = alineadasHueco(estado,jugador);

        if(i_boom != -1 && j_boom != -1)
            bomba = adyacentesBomba(estado,jugador,i_boom,j_boom);

        //Comprobamos las adyacentes del jugador contrario
        treses_contrario = alineadas(estado,contrario,3,1);
        doses_contrario = alineadas(estado,contrario,2,2);
        cuatros_contrario = alineadas(estado,jugador,4,0);
        lin_hueco_contrario = alineadasHueco(estado,contrario);

        if(i_boom_contrario != -1 && j_boom_contrario != -1)
            bomba_contrario = adyacentesBomba(estado,contrario,i_boom_contrario,j_boom_contrario);

        //Calculamos el valor del tablero
        //Puntuacion de 4: 1.000.000 (contrario = 100.000)
        //Puntuacion de 3: 10.000 (contrario = 1000)
        //Puntuacion de 2: 100 (contrario = 10)
        //Puntuacion lin_hueco: 100.000 (contrario = 10.000)   			Esta variable almacena las veces que encuentras 3 fichas y un  hueco
        //Puntuacion de la ficha bomba: 1									--> ejemplo: 		1101,  1011....

        int resultado = (bomba_contrario*6+(cuatros_contrario*4)+(treses_contrario*3)+(doses_contrario*2)+lin_hueco_contrario*5 )
                      - (bomba*6+(treses*3) + (cuatros*4)+(doses*2)+lin_hueco*5);
        return resultado;
    }
}







//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------




// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA Poda_AlfaBeta
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
    double alpha, beta; // Cotas de la poda Poda_AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";

    (jugador_==1) ? contrario_=2 : contrario_=1;

    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    // cout << "\n\t";
    // int n_opciones=0;
    // JuegoAleatorio(aplicables, opciones, n_opciones);
    //
    // if (n_act==0){
    //   (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    //   cout << " No puede realizar ninguna accion!!!\n";
    //   //accion = Environment::actIDLE;
    // }
    // else if (n_act==1){
    //        (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    //         cout << " Solo se puede realizar la accion "
    //              << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
    //         accion = static_cast< Environment::ActionType > (opciones[0]);
    //
    //      }
    //      else { // Hay que elegir entre varias posibles acciones
    //         int aleatorio = rand()%n_opciones;
    //         cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
    //         accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
    //      }

    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------

    //Si la última acción fue explotar la bomba reiniciamos las posiciones a -1
    if(actual_.Last_Action(jugador_) == 7){
        i_boom = -1;
        j_boom = -1;
        nobomba = true;
    }

    if(actual_.Last_Action(contrario_) == 7){
        i_boom_contrario = -1;
        j_boom_contrario = -1;
    }

    fichasBomba(actual_);



    if(actual_.N_Jugada()%4 == 0 && nobomba){
      explotar = true;
      nobomba = false;
    }


    int lin_bomba = lineaBomba(actual_,jugador_,i_boom,j_boom);



    if(lin_bomba == contrario_)
      return Environment::BOOM;


    if(explotar){
      int diplousion = 7;
      Environment hijo = actual_.GenerateNextMove(diplousion);

      if(hijo.RevisarTablero()==jugador_){
        accion = static_cast <Environment::ActionType> (7);
        int value;
        value = Poda_AlfaBeta(actual_,jugador_,0,PROFUNDIDAD_ALFABETA,accion,menosinf,masinf);

        if(value == masinf){
          return accion;
        }
      }
    }


    //valor = miniMax(actual_,jugador_,0,PROFUNDIDAD_MINIMAX,accion);
    valor = Poda_AlfaBeta(actual_,jugador_,0,PROFUNDIDAD_ALFABETA,accion,menosinf,masinf);
    cout << "Valor: " << valor << " Accion: " << actual_.ActionStr(accion) << endl;
    return accion;


        // Opcion: Poda Poda_AlfaBeta
        // NOTA: La parametrizacion es solo orientativa
        // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
      //  cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
}


//Algoritmo de poda alfa-beta
double Player::Poda_AlfaBeta(const Environment & tablero, int jugador, int profundidad, int profundidad_maxima, Environment::ActionType & accion, double alfa, double beta) {

	Environment::ActionType accion_anterior;
	double aux;

	bool opciones[8];
	int n_act = tablero.possible_actions(opciones);

    //Si hemos llegado a un nodo terminal o no hay más acciones
	if (profundidad==profundidad_maxima || n_act==0){
		return Valoracion(tablero, jugador);

	}else{		//Recorrer árbol

		int ult_act=-1;
		Environment hijo = tablero.GenerateNextMove(ult_act); //Generamos el siguiente tablero hijo

		if (profundidad%2==0){								//Si es nodo MAX
      while (!(hijo==tablero)){

				aux = Poda_AlfaBeta(hijo, jugador, profundidad+1, profundidad_maxima, accion_anterior, alfa, beta);

				if (aux>alfa){
					alfa=aux;
					accion = static_cast <Environment::ActionType > (ult_act);
				}

                //Poda beta
				if (beta<=alfa) {
					break;
				}

				hijo = tablero.GenerateNextMove(ult_act); // Generamos el siguiente tablero hijo
			}

		  return alfa;

		}else{												//Si es nodo MIN
			while (!(hijo==tablero)){

				aux = Poda_AlfaBeta(hijo, jugador, profundidad+1, profundidad_maxima, accion_anterior, alfa, beta);

				if (aux<beta){
				  beta=aux;
				  accion = static_cast <Environment::ActionType > (ult_act);
				}

                //Poda alfa
				if (beta<=alfa) {
				  break;
				}

				hijo = tablero.GenerateNextMove(ult_act); // Generamos el siguiente tablero hijo
			}

		  return beta;
		}
	}
}
