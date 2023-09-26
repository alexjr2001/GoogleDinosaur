/*
PROJECT: SIMULATION OF DINOSAUR GAME
AUTHOR: ALEXANDER GÓMEZ DEL CARPIO
DATE: 30/05/2021

[EN]
This project is the simulation of the Dinosaur Game in Google when we don't have internet connection, it is developed to 
show the field in the console. It's is really intuitive because you just press the up-arrow key, however, it is a little 
difficult to master it.
*/



#include <iostream>
#include <conio.h>
#include <windows.h> 
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int record = 0;

class tablerinho {              //FIELD class
private:
    char piso = '_';            //floor
    char obstaculo = '|';       //barrier
    string dino1 = "  )";       //Top part of the dinosaur
    char dino2 = ')';           //Bottom part of the dinosaur
    char tabla[10] = {};
    int random;
    bool noChoca = true;        //It is alive, don't crash
    int tecla = 0;
    bool apreto = false;        //Key pressed
    int score = 0;      
    bool newRecord = false;
    int dobleSalto = 1;         //In case we make two continual jumps


public:
    tablerinho() {              //We fill the field with floor barriers and a dinosaur
        random = 0;
        for (int i = 0; i < 10; i++) {
            tabla[i] = piso;
        }
        tabla[2] = dino2;
        cout << "constructor";
    }
    void imprimeScore() {               //Score in the last try
        cout << "\n\nSCORE: " << score;
    }
    void imprimeTablero() {                 //We print the field
        cout << "\n" << dino1 << "\n";
        for (int i = 0; i < 10; i++) {
            if (i == 2 && dobleSalto % 2 == 1) {
                tabla[i] = dino2;
            }
            cout << tabla[i];
        }
        imprimeScore();
        dobleSalto += 1;
        return;
    }
    void gameOver() {       //In case, it collides with a barrier
        if (tabla[3] == obstaculo && apreto == true && tabla[4] == piso) {      
            noChoca = false;
        }
        if (apreto == false && tabla[2] == obstaculo && tabla[1] == piso) {
            noChoca = false;
        }
        return;
    }
    void nuevoRecord() {        //Set new record
        if (score > record && noChoca == false) {
            newRecord = true;
            record = score;
            cout << "\nNEW RECORD!\n";
        }
        return;
    }
    int dificultadObstaculo() {     //Odds of an obstacle 20%=4
        int probabilidad=4;
        return probabilidad;
    }
    void poneObstaculo() {
        random = rand() % dificultadObstaculo();
        if (tabla[7] == piso && tabla[8] == piso && random == 0) {  //In case there were two floors we can add a barrier
            tabla[9] = obstaculo;
        }
        return;
    }
    void actualizaTablero() {           //Update field, we move everything one index down
        for (int i = 0; i < 9; i++) {
            if (i == 2) {
                if (tabla[i + 1] != piso) {
                    tabla[i] = tabla[i + 1];
                }
            }
            else if (tabla[i + 1] != dino2) {
                    tabla[i] = tabla[i + 1];
            }
            else {
                tabla[i] = piso;
            }
        }
        if (tabla[1] == obstaculo && tabla[2] == obstaculo) {
            tabla[2] = dino2;
        }

        tabla[9] = piso;
        return;
    }
    void teclas() {                 //Identify the key pressed
        if (noChoca == true) system("cls");         //When it collides
        if (_kbhit()) {
            tecla = _getch();
            if (tecla == KEY_UP) {          //Jumps
                std::cout << "\n" << dino1;
                if (tabla[2] == obstaculo) {        //For jump 100 points
                    tabla[2] = obstaculo;
                    score += 100;
                }
                else {               
                    tabla[2] = piso;
                }
                apreto = true;
            }
        }
        else {
            apreto = false;
            if (tabla[3] == obstaculo) noChoca = false;
            tabla[2] = dino2;
            dobleSalto = 0;
        }

        return;
    }
    int velocidad(int _score) {     //Speed of the game, as time goes and score increases. We speed up
        int speed = 300;
        speed -= _score / 10;       

        return speed;       //Time of sleep between frames
    }

    void playAgain() {
        cout << "\n\tGAME OVER\n\nQuieres jugar de nuevo? Si(1) o No(0): ";     
        cin >> noChoca;
        if (noChoca) {
            for (int i = 3; i < 10; i++) {
                tabla[i] = piso;
            }
            score = 0;
            play();
        }
    }
    void play() {
        while (noChoca) {
            imprimeTablero();       //Print field

            gameOver();

            poneObstaculo();        //New Barrier
            actualizaTablero();     //Update field
            Sleep(velocidad(score));        //Speed
            teclas();               //Identify key hits
        }
        if (tabla[3] != piso) {
            imprimeTablero();       //Print field
        }
        nuevoRecord();          //New record
        playAgain();

        return;
    }
};

//In case we don't want a class use we have a global function, but we can ignore it for now.
void tablero(){
	char piso = '_';
	char obstaculo = '|';
	string dino1 = "  )";       //Parte de arriba del dinosaurio
	char dino2 = ')';
	char tabla[10] = {};
	int random;
    bool noChoca = true;
    int tecla = 0;
    bool apreto = false;        //Se puede eliminar
    
    for (int i = 0; i < 10; i++) {
        tabla[i] = piso;
    }
    tabla[2] = dino2;

    while (noChoca) {
        cout << "\n" << dino1 << "\n";
        for (int i = 0; i < 10; i++) {
            cout << tabla[i];
        }

        if (tabla[3] == obstaculo && apreto == true && tabla[4] == piso) noChoca = false;
        if (apreto == false && tabla[2] == obstaculo) noChoca = false;
    
        cout << "\napreto: " << apreto << "\ntabla[3]:" << tabla[3] << "\ntabla[4]:" << tabla[4];
        Sleep(10000);
        
       

        random = rand() % 3;
        if (tabla[7] == piso && tabla[8] == piso && random == 0) {
            tabla[9] = obstaculo;
        }
	    
        for (int i = 0; i < 9; i++) {
            if (i == 2){
                if (tabla[i + 1] != piso) {
                    tabla[i] = tabla[i + 1];
                }
            }
            else if (tabla[i + 1] != dino2){
                tabla[i] = tabla[i + 1];
            }
            else {
                tabla[i] = piso;
            }
        }

        tabla[9] = piso;
        Sleep(200);
        if (noChoca==true) system("cls");
        if (_kbhit()) {
            tecla = _getch();
            apreto = false;
            if (tecla == KEY_UP) {
                std::cout << "\n"<< dino1;
                if (tabla[2] == obstaculo) {
                    tabla[2] = obstaculo;
                }
                else {
                    tabla[2] = piso;
                }
                apreto = true;
            }       
        }
        else {
            apreto = false;
            if (tabla[3] == obstaculo) noChoca = false;
            tabla[2] = dino2;
            continue;
        }

    }
	return;
}
//We can ignore this function


int main() {
	//tablero();
    tablerinho tablero1;
    tablero1.play();
	
	return 0;
}
