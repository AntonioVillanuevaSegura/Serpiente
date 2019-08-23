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

	clear();
	box(stdscr,'*','*');//Crea borde 			
	refresh();
}

punto crea_comida(){
	/*Crea la comida de la serpiente */	
	return punto {0,0};
}

void imprimeSerpiente(vector <punto> serpiente){
	while (!serpiente.empty()){
		mvwprintw (stdscr,int (serpiente.back).y,int (serpiente.back.x),"#");
		serpiente.pop_back();
	}
}

int main(){	
	vector  <punto> serpiente;
	int direccion=1;//Direccion de la serpiente

	initscr(); 	
	//WINDOW *pantalla;


	//Crea la serpiente y le da una direccion
	//snake = [[sh//2, sw//2+1], [sh//2, sw//2], [sh//2, sw//2-1]]

	serpiente.push_back({LINES/2,COLS/2+1});
	serpiente.push_back({LINES/2,COLS/2});
	serpiente.push_back({LINES/2,COLS/2-1});		


	mvwprintw(stdscr,serpiente[0].y,serpiente[0].x,"#");
	
	
	
	//pantalla();
	getch();

	
	endwin();
	return 0;
}
