/*
 * Antonio Villanueva Segura
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
 * instalar ncurses  sudo apt-get install libncurses5-dev libncursesw5-dev
 * compile and link: gcc <program file> -lncurses
 */
#include <iostream>
#include <string>
#include <cstring> //c_str() conversion a una cadena de texto a lo C
#include <ncurses.h> //Libreria grafica basica
#include <random> //numeros aleatorios
#include <ctime> //hora para generar numeros aleatorios
#include <unistd.h> //usleep retardos

#include <vector>//Creamos el cuerpo de la serpiente con un vector de ptos. 

using namespace std;

struct punto {int y;int x;}; //Definimos un punto una coordenada 

void pantalla(){
	//Crea los bordes del juego
	//clear();
	box(stdscr,'*','*');//Crea borde 			
	//refresh();
}

punto crea_comida(vector <punto> &serpiente){
	/*Crea la comida de la serpiente mirando de no caer en la serpiente o el borde */	
	punto pto;
	do {
		pto={2+ rand() % (LINES-3),2+ rand() % (COLS-3) };//Crea una comida aleatoria
	}
		while (mvinch(pto.y, pto.x)& A_CHARTEXT!=32);

	mvwprintw (stdscr,pto.y,pto.x,"$");//Crea una comida *

	return pto;
}

bool come(punto &cabeza,punto &comida){//Ha comido ? 
	if (cabeza.y==comida.y && cabeza.x==comida.x ){
		return true;
	}
	return false;
}

bool muerta(punto &cabeza){
	//Choca con ella misma o los limites del juego
	//Mira la cabeza
	//Ha colisionado con los extremos ?
	
	//La cabeza esta en un sitio que no es espacio o comida ???
	//Hay que preveer 
	
	char objeto=mvinch(cabeza.y, cabeza.x)& A_CHARTEXT;//Cabeza
	if ( objeto!=' ' && objeto !='$'){
		return true;
	}
	
	
	
	/*
	if (serpiente.back().x==0 ||serpiente.back().x==COLS ||
		serpiente.back().y==0 ||serpiente.back().y==LINES){
		return true;//Colision bordes
	}
	//Se muerde ella misma ?
	for (auto elemento=serpiente.begin();elemento!=serpiente.end();elemento++){
		if ((*elemento).x ==serpiente.back().x && (*elemento).y ==serpiente.back().y ){
			return true;//Se muerde ella mista
		}
	}
	*/
	return false;
}
void imprimeSerpiente(vector <punto> serpiente){
	//Imprime el vector serpiente exceptuando la cola que es vacio	
	
	while (!serpiente.empty()){
		mvwprintw (stdscr,serpiente.back().y,serpiente.back().x, serpiente.size()>1 ?"#":" ");
		serpiente.pop_back();
	}
	//refresh();
}

int main(){	
	srand (time(NULL));//Inicializa numeros aleatorios para crear comida 
	vector  <punto> serpiente;
	int direccion(KEY_RIGHT);//Direccion inicial de la serpiente derecha
	int key(KEY_RIGHT) ;//Lectura de teclas
	int puntos(1);
	punto cabeza;//Un punto y,x que contiene la cabeza de la serpiente
	punto comida;//donde esta la comida
	
	initscr();//Inicio de ncurses , el entorno grafico
	//configuraciones varias de ncurses 
	nodelay(stdscr,true);//Evita bloquear en wgetch ,lectura de una tecla
	noecho();//No aparaece tecla pulsada
	keypad(stdscr,true);//Activa teclas especiales ,flechas F1..F2
	curs_set(0);//Elimina cursor ncurses en la pantalla 

	//Crea la serpiente con 3 elementos y le da una direccion

	serpiente.push_back({LINES/2,COLS/2+1});//Elemento 1
	serpiente.push_back({LINES/2,COLS/2});//Elemento 2
	serpiente.push_back({LINES/2,COLS/2-1});//Elemento 3	
	

	pantalla();//Imprime los bordes de la pantalla
	comida=crea_comida (serpiente);
	while (true){//Bucle principal del juego 
		
		usleep(200000);//Retardo del movimiento de la serpiente
		key = wgetch(stdscr);//Lectura de teclas 

		//Solo acepta flechas en el cambio de direccion de la serpiente
        if (key ==KEY_RIGHT || key ==KEY_LEFT || key ==KEY_DOWN || key ==KEY_UP){
			direccion = key;}
           
		//mvwprintw(stdscr,2,2,(to_string(direccion)).c_str());//DEBUG TECLA PULSADA
      	//mvwprintw( stdscr , 2 , 2 , ( to_string (mvinch(1, 1)& A_CHARTEXT)).c_str() );//DEBUG lectura un punto 
     
      	
      	mvwprintw( stdscr , 0, 2 , ( to_string (puntos).c_str() ));//MUESTRA PUNTOS CONSEGUIDOS comidas    
		cabeza=serpiente.back();//Recupera la cabeza de la serpiente
		
		switch (direccion){	//Direccion y manipulacion de la cabeza			
			case KEY_RIGHT:cabeza={cabeza.y,cabeza.x+1}; break;//valor direccion 261
			case KEY_LEFT:cabeza={cabeza.y,cabeza.x-1}; break;//valor direccion 260
			case KEY_DOWN:cabeza={cabeza.y+1,cabeza.x}; break;//valor direccion 258
			case KEY_UP:cabeza={cabeza.y-1,cabeza.x}; break;//valor direccion 259									
		}
		
		
		mvwprintw (stdscr,comida.y,comida.x,"$");//Visualiza comida	
		
		if (muerta(cabeza)){//Antes de pegar la cabeza miramos si va estar en un mal sitio
			puntos=0;
		}
     				
		
			
		serpiente.push_back(cabeza);//Pegamos la nueva cabeza , un nuevo elemento
		imprimeSerpiente(serpiente);//Imprime la serpiente			
		serpiente.erase(serpiente.begin());//Borra primer elemento del vector, la cola 
		

		
		if (come(cabeza,comida)){
			puntos++;//Incrementa puntos
			comida=crea_comida(serpiente);//Crea una nueva comida
			serpiente.push_back(cabeza);//La serpiente crece un elemento mas
		}


		//pantalla();//Imprime la pantalla
	}
	

	
	endwin();
	return 0;
}
