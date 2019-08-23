/*
 * Antonio Villanueva Segura
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
 * instalar ncurses  sudo apt-get install libncurses5-dev libncursesw5-dev
 * compile and link: gcc <program file> -lncurses
 */
#include <iostream>
#include <string>
 
#include <ncurses.h> //Libreria grafica basica
 
#include <random> //numeros aleatorios
#include <ctime> //hora para generar numeros aleatorios

#include <vector>

using namespace std;

struct punto {int y;int x;}; //Un punto

void pantalla(){

	//clear();
	box(stdscr,'*','*');//Crea borde 			
	refresh();
}

punto crea_comida(){
	/*Crea la comida de la serpiente */	
	return punto {0,0};
}

void imprimeSerpiente(vector <punto> serpiente){
	//Imprime el vector serpiente
	while (!serpiente.empty()){
		mvwprintw (stdscr,serpiente.back().y,serpiente.back().x,"#");
		serpiente.pop_back();
	}
}

int main(){	

	vector  <punto> serpiente;
	int direccion=KEY_RIGHT;//Direccion inicial de la serpiente
	int key ;
	punto cabeza;
	initscr(); 	
	//WINDOW *pantalla;
	nodelay(stdscr,true);
	noecho();

	//Crea la serpiente y le da una direccion

	serpiente.push_back({LINES/2,COLS/2+1});
	serpiente.push_back({LINES/2,COLS/2});
	serpiente.push_back({LINES/2,COLS/2-1});		

	while (true){

		key = getch();//Lee teclas

        if (key ==KEY_RIGHT or key ==KEY_LEFT or key ==KEY_DOWN or key ==KEY_UP){
      direccion = key;		
           }
           
		cabeza=serpiente.back();//Recupera la cabeza de la serpiente
		//Direccion de la cabeza
		switch (direccion){
			case KEY_RIGHT:cabeza={cabeza.y,cabeza.x+1}; break;
			case KEY_LEFT:cabeza={cabeza.y,cabeza.x-1}; break;
			case KEY_DOWN:cabeza={cabeza.y-1,cabeza.x}; break;
			case KEY_UP:cabeza={cabeza.y+1,cabeza.x}; break;									
		}
/*		
        # find next position of snake head
        head = snake[0]
        if direction == curses.KEY_RIGHT:
            new_head = [head[0], head[1]+1]
        elif direction == curses.KEY_LEFT:
            new_head = [head[0], head[1]-1]
        elif direction == curses.KEY_DOWN:
            new_head = [head[0]+1, head[1]]
        elif direction == curses.KEY_UP:
            new_head = [head[0]-1, head[1]]		
*/		
		
		
		
		
		
		imprimeSerpiente(serpiente);
		pantalla();
	}
	
	getch();

	
	endwin();
	return 0;
}
