
/*
 * Antonio Villanueva Segura 
 * JUEGO DE LA SERPIENTE ,SNAKE empleando ncurses y linux version compilada en UBUNTU 16.04 64BITS
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
 * instalar ncurses  sudo apt-get install libncurses5-dev libncursesw5-dev
 * g++ -std=c++11 -o serpiente serpiente.cpp -lncurses
 */
#include <iostream>
#include <string>
#include <cstring> //c_str() conversion a una cadena de texto a lo C
#include <ncurses.h> //Libreria grafica basica
#include <random> //numeros aleatorios
#include <ctime> //hora para generar numeros aleatorios
#include <unistd.h> //usleep retardos
#include <vector>//Creamos el cuerpo de la serpiente con un vector de ptos. 

#define RETARDO 200000
#define CUERPO "O"
#define COMIDA "+"
using namespace std;
//-------------------------------------------------------------------------------------
struct punto {int y;int x;}; //Estructura Definiendo un punto una coordenada y,x
//-------------------------------------------------------------------------------------
void pantalla(){
	//Crea los bordes del juego
	clear();
	//box(stdscr,'*','*');//Crea borde 			
	box(stdscr, ACS_VLINE, ACS_HLINE);//Crea borde con lineas
}
//-------------------------------------------------------------------------------------
punto creaComida(vector <punto> &serpiente){
	//Crea comida , evitando limites o el cuerpo de la serpiente
	punto pto;
	do {
		pto={2+ rand() % (LINES-3),2+ rand() % (COLS-3) };//Crea una comida aleatoria
	}
		while (mvinch(pto.y, pto.x)& A_CHARTEXT!=32);
	return pto;
}
//-------------------------------------------------------------------------------------
bool serpienteCome(punto &cabeza,punto &comida){
	//La serpiente ha encontrado comida ? verdadero o falso
	if (cabeza.y==comida.y && cabeza.x==comida.x ){
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------------------
bool estaMuerta(punto &cabeza){
	//Choca con ella misma o  con los limites del juego y no es comida	
	char objeto=mvinch(cabeza.y, cabeza.x)& A_CHARTEXT;//Cabeza
	if ( objeto!=' ' && objeto !=(const char) COMIDA[0]){
		return true;
	}	
	return false;
}
//-------------------------------------------------------------------------------------
void imprimeSerpiente(vector <punto> serpiente){
	//Imprime el vector serpiente exceptO la cola que es vacio		
	while (!serpiente.empty()){
		mvwprintw (stdscr,serpiente.back().y,serpiente.back().x, serpiente.size()>1 ? CUERPO:" ");
		serpiente.pop_back();
	}
}
//-------------------------------------------------------------------------------------
void inicializaSerpiente(vector  <punto> *serpiente){
	//Inicializa el cuerpo de la serpiente inicial , 3 segmentos
	serpiente->clear();
	for (int elemento=1;elemento>=-1;elemento--){
		serpiente->push_back({LINES/2,COLS/2+elemento});//Elementos 1 0 -1 
	}
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
int main(){	
	srand (time(NULL));//Inicializa numeros aleatorios para crear comida 
	vector  <punto> serpiente;//Cuerpo de la serpiente ,compuesto de puntos y,x
	int direccion(KEY_RIGHT);//Direccion serpiente  inicialmente derecha
	int key(KEY_RIGHT) ;//Lectura de teclas
	int puntos(1);//Puntos del jugador , cada comida incrementa los puntos
	punto cabeza;//Cabeza de la serpiente punto y,x con la posicion actual
	punto comida;//Comida coordenada y,x actual
	
	initscr();//Inicio de ncurses , el entorno grafico
	//configuraciones varias de ncurses 
	nodelay(stdscr,true);//Evita bloquear en wgetch ,lectura de una tecla
	noecho();//No aparaece tecla pulsada
	keypad(stdscr,true);//Activa teclas especiales ,flechas F1..F2
	curs_set(0);//Elimina cursor ncurses en la pantalla 

	//Crea la serpiente con 3 elementos y le da una direccion
	inicializaSerpiente(&serpiente);
	
	pantalla();//Imprime los bordes de la pantalla
	comida=creaComida (serpiente);

	while (true){//Bucle principal del juego 
		
		usleep(RETARDO);//Retardo del movimiento de la serpiente
		key = wgetch(stdscr);//Lectura de teclas 

		//Solo acepta teclas flechas en el cambio de direccion de la serpiente
        if (key ==KEY_RIGHT || key ==KEY_LEFT || key ==KEY_DOWN || key ==KEY_UP){
			direccion = key;}
           	
      	mvwprintw( stdscr , 0, 2 , ( ( "SCORE : " + to_string (puntos) ).c_str() ));//MUESTRA PUNTOS CONSEGUIDOS comidas    
		cabeza=serpiente.back();//Recupera la cabeza de la serpiente
		
		switch (direccion){	//Direccion y manipulacion de la cabeza	por las FLECHAS		
			case KEY_RIGHT:cabeza={cabeza.y,cabeza.x+1}; break;//valor direccion 261
			case KEY_LEFT:cabeza={cabeza.y,cabeza.x-1}; break;//valor direccion 260
			case KEY_DOWN:cabeza={cabeza.y+1,cabeza.x}; break;//valor direccion 258
			case KEY_UP:cabeza={cabeza.y-1,cabeza.x}; break;//valor direccion 259									
		}
				
		mvwprintw (stdscr,comida.y,comida.x,COMIDA);//Visualiza comida	
		
		if (estaMuerta(cabeza)){
			pantalla();
			inicializaSerpiente(&serpiente);
			direccion=KEY_RIGHT;
			comida=creaComida(serpiente);//Crea una nueva comida
			puntos=0;}//Antes de pegar la cabeza miramos si va estar en un mal sitio
     	else{				
			
			serpiente.push_back(cabeza);//Pegamos la nueva cabeza de la serpiente, un nuevo elemento
			imprimeSerpiente(serpiente);//Imprime el cuerpo de la serpiente			
			serpiente.erase(serpiente.begin());//Borra primer elemento del vector, la cola 
		}
		
		/*La serpiente ha encontrado comida */
		if (serpienteCome(cabeza,comida)){//La cabeza ha encontrado comida 
			puntos++;//Incrementa puntos
			comida=creaComida(serpiente);//Crea una nueva comida
			serpiente.push_back(cabeza);//La serpiente crece un elemento mas
		}
	}
	
	endwin();
	return 0;
}
