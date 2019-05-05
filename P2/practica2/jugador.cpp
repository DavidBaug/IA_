#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>


double ComportamientoJugador::porcentajeMapa(){

	int f = mapaResultado.size();
	int c = mapaResultado[0].size();
	int total = f*c;
	int cont = 0;

	for (size_t i = 0; i < f; ++i) {
		for (size_t j = 0; j < c; ++j) {
			if (mapaResultado[i][j]=='?') {
				++cont;
			}
		}
	}

	return (double) cont/total;

}


// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	Action accion = actIDLE;
	// Estoy en el nivel 1

	if (sensores.nivel != 4){
		if (sensores.mensajeF != -1){
			fil = sensores.mensajeF;
			col = sensores.mensajeC;
			ultimaAccion = actIDLE;
		}

		switch (ultimaAccion){
			case actTURN_R:
				brujula = (brujula + 1) % 4;
				break;
			case actTURN_L:
				brujula = (brujula + 3) % 4;
				break;
			case actFORWARD:
				switch (brujula){
					case 0:
						fil--; break;
					case 1:
						col++;break;
					case 2:
						fil++;break;
					case 3:
						col--;break;

			}
			cout << "fil: " << fil << "  col: " << col << " or: " << brujula << endl;
		}

		if (sensores.destinoF != destino.fila or sensores.destinoC != destino.columna) {
			destino.fila = sensores.destinoF;
			destino.columna = sensores.destinoC;
			hayPlan = false;
		}

		if (!hayPlan) {
			actual.fila = fil;
			actual.columna = col;
			actual.orientacion = brujula;
			hayPlan = pathFinding (sensores.nivel, actual, destino, plan, sensores);

		}


		// Ejecución plan
		if (hayPlan and plan.size() > 0){
			accion = plan.front();
			plan.erase(plan.begin());
		}
		else{
			if (sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or sensores.terreno[2]=='a'
						or sensores.terreno[2]=='D') {
				accion = actTURN_R;
			}else{
				accion = actFORWARD;
			}
		}

		ultimaAccion = accion;

	}
	else {	//NIVEL 22222222222222222222222222

		if (primera) {
			for(int i = 0 ; i < 200 ; i++){
					for(int j = 0 ; j < 200 ; j++){
							mapaAux[i][j] = '?' ;
							mapaCosteAux[i][j] = 0;
					}
			}
			fil = 99;
			col = 99;

			filc = colc = 99;

			primera = false;
			delibera = 0;
			porcentaje=5;
			exitos = 1;
			int tam = mapaResultado.size();
			porcentajeVariable = 1;
		}


		switch (ultimaAccion){
			case actTURN_R:
				brujula = (brujula + 1) % 4;
				break;
			case actTURN_L:
				brujula = (brujula + 3) % 4;
				break;
			case actFORWARD:
				switch (brujula){
					case 0:
						fil--; filc--;break;
					case 1:
						col++;colc++;break;
					case 2:
						fil++;filc++;break;
					case 3:
						col--;colc--;break;

			}
			cout << "fil: " << fil << "  col: " << col << " or: " << brujula << endl;
		}

		if(!situado){
				for (int i = 0; i < sensores.terreno.size(); i++) {
					if(sensores.terreno[i] == 'K' && i != 0 && i != 2 && i != 6 && i != 12){
						objetivo_fijado = true;
						pos_objetivo = i;
						std::cout << "objetivo: "<< pos_objetivo << '\n';
						rutaPK(num_avances, Giro);
						// acciones = rutaPK1(pos_objetivo);
					}
				}
			}


		if (!situado and sensores.terreno[0]=='K') {
			colocar(sensores);
		}


		guardaMapa(sensores);

		if (sensores.destinoF != destino.fila or sensores.destinoC != destino.columna) {
			destino.fila = sensores.destinoF;
			destino.columna = sensores.destinoC;
			hayPlan = false;
		}

		if (!hayPlan and situado) {
			actual.fila = fil;
			actual.columna = col;
			actual.orientacion = brujula;
			hayPlan = pathFinding (sensores.nivel, actual, destino, plan, sensores);

		}

		if(porcentajeVariable > 0.10){
			if(delibera%((int)porcentaje*(mapaResultado.size()/10))==0 and situado){
				std::cout << "DELIBERANDO OTRA VEZ" << '\n';
				actual.fila = fil;
				actual.columna = col;
				actual.orientacion = brujula;
				hayPlan = pathFinding (sensores.nivel, actual, destino, plan, sensores);
			}
		}

		// Ejecución plan
		if (hayPlan and plan.size() > 0){
			if (sensores.superficie[2]=='a' or sensores.superficie[6]=='a') {
				std::cout << "aldeano delante" << '\n';
				accion = actTURN_R;
			}if ((sensores.terreno[2]=='M' or sensores.terreno[2]=='D')and plan.front()==actFORWARD) {

				hayPlan = pathFinding (sensores.nivel, actual, destino, plan, sensores);
				accion = actTURN_R;

			}else{
				accion = plan.front();
				plan.erase(plan.begin());

			}
		}
		else{
			if (sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or sensores.terreno[2]=='a'
						or sensores.terreno[2]=='D') {
				accion = actTURN_R;
			}else{
				if(objetivo_fijado){
					std::cout << "Entrando a ejecucion objetivo" << '\n';
					if(num_avances > 0){ accion = actFORWARD; num_avances--;
					}else{
						accion = Giro; objetivo_fijado = false; }
					// std::cout << "objetivo accion: "<< accion << '\n';
					// if (!acciones.empty()) {
					// 	accion = acciones.front();
					// 	std::cout << "accion: " <<accion << '\n';
					// 	acciones.pop_front();
					// }else{
					// 	objetivo_fijado = false;
					// }

				}else{
						accion = actFORWARD;
				}


			}
		}

		if (actual == destino) {
			porcentajeVariable = porcentajeMapa();
			if(delibera > 0 and delibera <= 100)
				exitos+=1;
			else if (delibera <= 500)
			 	exitos += 2;
			else if(delibera <= 2000)
				exitos += 3;
			else exitos += 5;
		}



		++delibera;

	}
	ultimaAccion = accion;
	std::cout << "Accion:"<<accion << '\n';
  return accion;

}


// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
						return pathFinding_Anchura(origen,destino,plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
			      return pathFinding_CosteUniforme(origen,destino,plan, sensores);
						break;
		case 4: cout << "Busqueda para el reto\n";
						return pathFinding_A(origen,destino,plan, sensores);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}


//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M' or casilla =='D')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}




struct nodo{
	estado st;
	list<Action> secuencia;
};

struct nodo_cola{
	estado st;
	int coste;
	list<Action> secuencia;


};

struct ComparaCola{
	bool operator()(const nodo_cola &a,const nodo_cola &b)const{
		return a.coste < b.coste;
	}
};

struct ComparaCola1{
	bool operator()(const nodo_cola &a,const nodo_cola &b)const{
		return a.coste > b.coste;
	}
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
/*
	bool operator==(const estado &a, const estado &n) const{
		if (a.fila == n.fila and a.columna == n.columna)
			return true;
		else
			return false;
	}*/
};


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}


////////////////////////////////////////////////////////////////////////////////

// Implementación de la búsqueda en anchura.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue<nodo> cola;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.front();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}



// Implementación de la búsqueda en anchura.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	// priority_queue<nodo_cola, vector<nodo_cola>, ComparaCola> cola;			// Lista de Abiertos


	multiset<nodo_cola, ComparaCola> cola;			// Lista de Abiertos

	multiset<estado, ComparaEstados> nodos;

  nodo_cola current;

	current.st = origen;
	current.secuencia.empty();
	current.coste = 0;

	cola.insert(current);
	nodos.insert(current.st);

	int counts;

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		// cola.pop();
		cola.erase(cola.begin());
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo_cola hijoTurnR = current;
		hijoTurnR.coste += 1;

		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;

		// multiset<nodo_cola, ComparaCola>::iterator it = nodos.find(hijoTurnR.st);

		counts = nodos.count(hijoTurnR.st);
				// std::cout << "counts R " << counts << '\n';

		if (counts == 0) {
			if (generados.find(hijoTurnR.st) == generados.end()){
				hijoTurnR.secuencia.push_back(actTURN_R);
				cola.insert(hijoTurnR);
				nodos.insert(hijoTurnR.st);
			}
		}else{
			for(std::multiset<nodo_cola,ComparaCola>::iterator it = cola.begin(); it != cola.end(); ++it){
				if ((it->st == hijoTurnR.st) and (it->coste > hijoTurnR.coste)) {
					cola.erase(it);
					hijoTurnR.secuencia.push_back(actTURN_R);
					cola.insert(hijoTurnR);
					nodos.insert(hijoTurnR.st);
					break;
				}
			}
		}



		// std::cout << "uwu3" << '\n';

		// Generar descendiente de girar a la izquierda
		nodo_cola hijoTurnL = current;
		hijoTurnL.coste += 1;

		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;

		counts = nodos.count(hijoTurnL.st);

		// std::cout << "counts L " << counts << '\n';

		if (counts == 0) {
			if (generados.find(hijoTurnL.st) == generados.end()){
				hijoTurnL.secuencia.push_back(actTURN_L);
				cola.insert(hijoTurnL);
				nodos.insert(hijoTurnL.st);
			}
		}else{
			for(std::multiset<nodo_cola,ComparaCola>::iterator it = cola.begin(); it != cola.end(); ++it){
				if (it->st == hijoTurnL.st and (it->coste > hijoTurnL.coste)) {
					cola.erase(it);
					hijoTurnL.secuencia.push_back(actTURN_L);
					cola.insert(hijoTurnL);
					nodos.insert(hijoTurnL.st);
					break;
				}
			}
		}
		// std::cout << "uwu4" << '\n';

		// Generar descendiente de avanzar
		nodo_cola hijoForward = current;

		if (!HayObstaculoDelante(hijoForward.st)){
		// 	counts = nodos.count(hijoTurnR.st);
		// std::cout << "counts F " << counts << '\n';
		// 	if (counts == 0) {



		hijoForward.coste += getCoste(mapaResultado[hijoForward.st.fila][hijoForward.st.columna]);


		for(std::multiset<nodo_cola,ComparaCola>::iterator it = cola.begin(); it != cola.end(); ++it){
				if (it->st == hijoForward.st and (it->coste > hijoForward.coste)) {
					hijoForward.secuencia.push_back(actFORWARD);
					cola.insert(hijoForward);
					nodos.insert(hijoForward.st);
					break;
				}
			}



				if (generados.find(hijoForward.st) == generados.end()){
					hijoForward.secuencia.push_back(actFORWARD);
					cola.insert(hijoForward);
					nodos.insert(hijoForward.st);
				}
			// }
		}

	  // Find multiset (?)

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = *cola.begin();
		}

	}



  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}


// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int ComportamientoJugador::getCoste(char aux){
	if (aux == 'A') {
		return 10;
	}else if(aux == 'B'){
		return 5;
	}else if(aux == 'T'){
		return 2;
	}else if(aux == '?'){
		return 4;
	}else{
		return 1;
	}
}

void ComportamientoJugador::guardaMapa(Sensores sensores){
	// ESCRIBO LO QUE VEO EN EL MAPA RESULTADO.
	if(situado){
			mapaResultado[fil][col] = sensores.terreno[0] ;
			// mapaCoste.insert(fil*tam+col, getCoste(sensores.terreno[0]));
			mapaCosteAux[filc][colc] = getCoste(sensores.terreno[0]);
	}
	else{
			mapaAux[fil][col] = sensores.terreno[0] ;
			mapaCosteAux[fil][col] = getCoste(sensores.terreno[0]);
	}

	int contador = 1 ;
	int a,b,c,d,f; // a y b fila o columna e suma o resta filas.
	a = 0 ;        // c y d suma/resta columnas.
	b = 1 ;
	c = 1 ;
	f = 1 ;
	if(brujula%2 == 0){
			a = 1 ;
			b = 0 ;
	}
	if(brujula%3 == 0)
			c = -1 ;
	if(brujula>1)
			f = -1 ;
	for(int i = 1 ; i <= 3 ; i++){
			for(int j = 0-(f*i) ; j != 0+(f*i)+f ; j+= f){
					int fi = fil+ c*i*a + j*b ;
					int co = col+ j*a + c*i*b ;

					int fic = filc+ c*i*a + j*b ;
					int coc = colc+ j*a + c*i*b ;

					if(situado){
							mapaResultado[fi][co] = sensores.terreno[contador] ;
							// mapaCoste.insert(fi*mapaResultado.size()+co, getCoste(sensores.terreno[contador]);
							mapaCosteAux[fic][coc] = getCoste(sensores.terreno[contador]);

						}
					else{
							mapaAux[fi][co] = sensores.terreno[contador] ;
							mapaCosteAux[fic][coc] = getCoste(sensores.terreno[contador]);
					}
					contador++ ;
			}
	}
}

pair<int,int> ComportamientoJugador::devuelveK(int i){

	pair<int,int> pos;

	if (brujula == 0){
		if (i = 1){ pos.first=-1;pos.second=-1;
		}if (i = 2){ pos.first=-1;pos.second=0;
		}if (i = 3){ pos.first=-1;pos.second=+1;

		}if (i = 4){ pos.first=-2;pos.second=-2;
		}if (i = 5){ pos.first=-2;pos.second=-1;
		}if (i = 6){ pos.first=-2;pos.second=0;
		}if (i = 7){ pos.first=-2;pos.second=+1;
		}if (i = 8){ pos.first=-2;pos.second=+2;

		}if (i = 9){ pos.first=-3;pos.second=-3;
		}if (i = 10){ pos.first=-3;pos.second=-2;
		}if (i = 11){ pos.first=-3;pos.second=-1;
		}if (i = 12){ pos.first=-3;pos.second=0;
		}if (i = 13){ pos.first=-3;pos.second=+1;
		}if (i = 14){ pos.first=-3;pos.second=+2;
		}if (i = 15){ pos.first=-3;pos.second=+3;}
	}
	else if (brujula == 1){
		if (i = 1){ pos.first=-1;pos.second=+1;
		}if (i = 2){ pos.first=0;pos.second=+1;
		}if (i = 3){ pos.first=+1;pos.second=+1;

		}if (i = 4){ pos.first=-2;pos.second=+2;
		}if (i = 5){ pos.first=-1;pos.second=+2;
		}if (i = 6){ pos.first=0;pos.second=+2;
		}if (i = 7){ pos.first=+1;pos.second=+2;
		}if (i = 8){ pos.first=+2;pos.second=+2;

		}if (i = 9){ pos.first=-3;pos.second=+3;
		}if (i = 10){ pos.first=-2;pos.second=+3;
		}if (i = 11){ pos.first=-1;pos.second=+3;
		}if (i = 12){ pos.first=0;pos.second=+3;
		}if (i = 13){ pos.first=+1;pos.second=+3;
		}if (i = 14){ pos.first=+2;pos.second=+3;
		}if (i = 15){ pos.first=+3;pos.second=+3;}
		}
	else if (brujula == 2){
		if (i = 1){ pos.first=+1;pos.second=+1;
		}if (i = 2){ pos.first=+1;pos.second=0;
		}if (i = 3){ pos.first=+1;pos.second=-1;

		}if (i = 4){ pos.first=+2;pos.second=+2;
		}if (i = 5){ pos.first=+2;pos.second=+1;
		}if (i = 6){ pos.first=+2;pos.second=0;
		}if (i = 7){ pos.first=+2;pos.second=-1;
		}if (i = 8){ pos.first=+2;pos.second=-2;

		}if (i = 9){ pos.first=+3;pos.second=+3;
		}if (i = 10){ pos.first=+3;pos.second=+2;
		}if (i = 11){ pos.first=+3;pos.second=+1;
		}if (i = 12){ pos.first=+3;pos.second=0;
		}if (i = 13){ pos.first=+3;pos.second=-1;
		}if (i = 14){ pos.first=+3;pos.second=-2;
		}if (i = 15){ pos.first=+3;pos.second=-3;}
	}
	else if (brujula == 3){
		if (i = 1){ pos.first=+1;pos.second=-1;
		}if (i = 2){ pos.first=0;pos.second=-1;
		}if (i = 3){ pos.first=-1;pos.second=-1;

		}if (i = 4){ pos.first=+2;pos.second=-2;
		}if (i = 5){ pos.first=+1;pos.second=-2;
		}if (i = 6){ pos.first=0;pos.second=-2;
		}if (i = 7){ pos.first=-1;pos.second=-2;
		}if (i = 8){ pos.first=-2;pos.second=-2;

		}if (i = 9){ pos.first=+3;pos.second=-3;
		}if (i = 10){ pos.first=+2;pos.second=-3;
		}if (i = 11){ pos.first=+1;pos.second=-3;
		}if (i = 12){ pos.first=0;pos.second=-3;
		}if (i = 13){ pos.first=-1;pos.second=-3;
		}if (i = 14){ pos.first=-2;pos.second=-3;
		}if (i = 15){ pos.first=-3;pos.second=-3;}
	}
	return pos;
}

void ComportamientoJugador::colocar(Sensores sensores){
    int filaux = fil ;
    int colaux = col ;
    fil = sensores.mensajeF;
    col = sensores.mensajeC;

		std::cout << "orientacion: "<< brujula << '\n';

		int max_f = mapaResultado.size();
		int max_c = mapaResultado[0].size();

		std::cout << "mapa size:" <<max_c << '\n';

		situado = true ;

		int dfil = fil - filaux;
		int dcol = col - colaux;
		for(int i = 0; i < 200 ; ++i)
			for(int j = 0; j < 200 ; ++j)
				if(mapaAux[i][j] != '?')
					mapaResultado[i+dfil][j+dcol] = mapaAux[i][j];
					// mapaCoste.insert((i+dfil)*mapaResultado.size()+j+dcol, mapaCosteAux[i][j]);

    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < max_c ; j++){
            mapaResultado[i][j] = 'P' ;
            mapaResultado[j][i] = 'P' ;
            mapaResultado[max_f-1-i][j] = 'P' ;
            mapaResultado[j][max_f-1-i] = 'P' ;

						// mapaCoste[i*mapaResultado.size()+j] = 1000 ;
						// mapaCoste[j*mapaResultado.size()+i] = 1000;
						// mapaCoste[(max_f-1-i)*mapaResultado.size()+j] = 1000 ;
						// mapaCoste[j*mapaResultado.size()+max_f-1-i] = 1000 ;
        }
    }

		std::cout << "asdasd" << '\n';
}



bool ComportamientoJugador::pathFinding_A(const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores) {

	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	// priority_queue<nodo_cola, vector<nodo_cola>, ComparaCola> cola;			// Lista de Abiertos


	multiset<nodo_cola, ComparaCola> cola;			// Lista de Abiertos

	multiset<estado, ComparaEstados> nodos;

  nodo_cola current;

	current.st = origen;
	current.secuencia.empty();
	current.coste = 0;

	cola.insert(current);
	nodos.insert(current.st);

	int counts;

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		// cola.pop();
		cola.erase(cola.begin());
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo_cola hijoTurnR = current;
		hijoTurnR.coste += 1;

		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;

		// multiset<nodo_cola, ComparaCola>::iterator it = nodos.find(hijoTurnR.st);

		counts = nodos.count(hijoTurnR.st);
				// std::cout << "counts R " << counts << '\n';

		if (counts == 0) {
			if (generados.find(hijoTurnR.st) == generados.end()){
				hijoTurnR.secuencia.push_back(actTURN_R);
				cola.insert(hijoTurnR);
				nodos.insert(hijoTurnR.st);
			}
		}else{
			for(std::multiset<nodo_cola,ComparaCola>::iterator it = cola.begin(); it != cola.end(); ++it){
				if ((it->st == hijoTurnR.st) and (it->coste > hijoTurnR.coste)) {
					cola.erase(it);
					hijoTurnR.secuencia.push_back(actTURN_R);
					cola.insert(hijoTurnR);
					nodos.insert(hijoTurnR.st);
					break;
				}
			}
		}



		// std::cout << "uwu3" << '\n';

		// Generar descendiente de girar a la izquierda
		nodo_cola hijoTurnL = current;
		hijoTurnL.coste += 1;

		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;

		counts = nodos.count(hijoTurnL.st);

		// std::cout << "counts L " << counts << '\n';

		if (counts == 0) {
			if (generados.find(hijoTurnL.st) == generados.end()){
				hijoTurnL.secuencia.push_back(actTURN_L);
				cola.insert(hijoTurnL);
				nodos.insert(hijoTurnL.st);
			}
		}else{
			for(std::multiset<nodo_cola,ComparaCola>::iterator it = cola.begin(); it != cola.end(); ++it){
				if (it->st == hijoTurnL.st and (it->coste > hijoTurnL.coste)) {
					cola.erase(it);
					hijoTurnL.secuencia.push_back(actTURN_L);
					cola.insert(hijoTurnL);
					nodos.insert(hijoTurnL.st);
					break;
				}
			}
		}
		// std::cout << "uwu4" << '\n';

		// Generar descendiente de avanzar
		nodo_cola hijoForward = current;

		// hijoForward.coste += mapaCoste[hijoForward.st.fila*mapaResultado.size()+hijoForward.st.columna];

		if (!HayObstaculoDelante(hijoForward.st)){
		// 	counts = nodos.count(hijoTurnR.st);
		// std::cout << "counts F " << counts << '\n';
		// 	if (counts == 0) {
		hijoForward.coste += getCoste(mapaResultado[hijoForward.st.fila][hijoForward.st.columna]);


		for(std::multiset<nodo_cola,ComparaCola>::iterator it = cola.begin(); it != cola.end(); ++it){
				if (it->st == hijoForward.st and (it->coste > hijoForward.coste)) {
					hijoForward.secuencia.push_back(actFORWARD);
					cola.insert(hijoForward);
					nodos.insert(hijoForward.st);
					break;
				}
			}



				if (generados.find(hijoForward.st) == generados.end()){
					hijoForward.secuencia.push_back(actFORWARD);
					cola.insert(hijoForward);
					nodos.insert(hijoForward.st);
				}
			// }
		}

	  // Find multiset (?)

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = *cola.begin();
		}

	}



  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;


}




void ComportamientoJugador::rutaPK(int & num_avances, Action & Giro){

	if(1 == pos_objetivo || pos_objetivo == 3)
		num_avances = 1;
	else if (pos_objetivo >= 4 && pos_objetivo <= 8)
		num_avances = 2;
	else if(pos_objetivo != 12)
		num_avances = 3;

	if(pos_objetivo == 1 || pos_objetivo == 4 || pos_objetivo == 5 ||
		 pos_objetivo == 9 || pos_objetivo == 10 || pos_objetivo == 11)
		Giro = actTURN_L;
	else
		Giro = actTURN_R;
}

list<Action> ComportamientoJugador::rutaPK1(int i){

	list<Action> obj;

	if (i = 1){
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_L);
		obj.push_back(actFORWARD);
	}if (i = 3){
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_R);
		obj.push_back(actFORWARD);
	}if (i = 4){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_L);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
	}if (i = 5){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_L);
		obj.push_back(actFORWARD);
	}if (i = 7){
			obj.push_back(actFORWARD);
			obj.push_back(actFORWARD);
			obj.push_back(actTURN_R);
			obj.push_back(actFORWARD);
	}if (i = 8){
			obj.push_back(actFORWARD);
			obj.push_back(actFORWARD);
			obj.push_back(actTURN_R);
			obj.push_back(actFORWARD);
			obj.push_back(actFORWARD);
	}if (i = 9){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_L);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
	}if (i = 10){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_L);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
	}if (i = 11){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_L);
		obj.push_back(actFORWARD);
	}if (i = 13){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_R);
		obj.push_back(actFORWARD);
	}if (i = 14){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_R);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
	}if (i = 15){
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actTURN_R);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);
		obj.push_back(actFORWARD);}


		std::cout << "objetivo calculado" << '\n';

		obj.pop_front();

		return obj;



}
/*
bool ComportamientoJugador::pathFinding_A(const estado &origen, const estado &destino, list<Action> &plan, Sensores sensores) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo_cola, vector<nodo_cola>, ComparaCola1> cola;			// Lista de Abiertos


  nodo_cola current;

	current.st = origen;
	current.secuencia.empty();
	current.coste = 0;

	cola.push(current);


  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){


		cola.pop();
		generados.insert(current.st);

		// quitaRepetidos(cola, current);

		// std::cout << "uwu2" << '\n';

		// Generar descendiente de girar a la derecha
		nodo_cola hijoTurnR = current;
		hijoTurnR.coste += 1;

		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;

		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// std::cout << "uwu3" << '\n';

		// Generar descendiente de girar a la izquierda
		nodo_cola hijoTurnL = current;
		hijoTurnL.coste += 1;

		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// std::cout << "uwu4" << '\n';

		// Generar descendiente de avanzar
		nodo_cola hijoForward = current;

		char aux = mapaResultado[hijoForward.st.fila][hijoForward.st.columna];

		if (aux == 'A') {
			hijoForward.coste += 10;
		}else if(aux == 'B'){
			hijoForward.coste+= 5;
		}else if(aux == 'S'){
			hijoForward.coste+= 2;
		}else if(aux == '?'){
			hijoForward.coste+= 15;
		}else{
			hijoForward.coste += 1;
		}

		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

	  // Find multiset (?)

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
		}



	}



  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}*/
