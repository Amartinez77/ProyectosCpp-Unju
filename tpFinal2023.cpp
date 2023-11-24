#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
using namespace std;

/** CONSTANTES */
const int MAX_CARTAS=48;
const int MAX_BARAJA=5;
const int MAX_PILA=10; //MAX_BARAJA*2
const int MAX_JUG=4;
const int MAX=30;

typedef char tcad[MAX];


/** ESTRUCTURA DE CARTA */
typedef struct tcarta{
    int nro;
    int palo;
    bool comodin;
    int puntos;
};


/** ESTRUCTURA DE BARAJA DE CARTAS */
typedef struct tbaraja *pbaraja;
typedef struct tbaraja{
    tcarta dato;
    pbaraja sig;
    pbaraja ant;
};

typedef struct tblista{
    pbaraja inicio;
    pbaraja fin;
    int contador;
};


/** ESTRUCTURA DE PILA (cartas extraidas de un jugador) */
typedef tcarta tcontenedor[MAX_PILA];
typedef struct tpila{
    tcontenedor contenedor;
    int cima;
};


/** ESTRUCTURA DE UN JUGADOR */
typedef struct tjugador{
    tcad nickname;
    tcad apellido;
    tcad nombre;
    int puntaje;
    int p_ganadas;
    tblista baraja; //(tblista)
    tpila pila;
    int pts_partida; //puntos de una partida
};


/** PROCEDIMIENTOS PRINCIPALES */
#include "gestion_jugadores.hpp"
#include "gestion_baraja.hpp"
#include "funcionalidad_juego.hpp"
#include "gestion_ranking.hpp"
#include "colors.h"

void menu_principal(int &opc);
void bienvenida();
void despedida();

main() {

    system("color f0");

    parchivo jugadores;
    parchivo2 baraja;
    mazo_aux mazo;
    pranking arbol;

    tcola cola;

    int opc;
    bool mazo_nuevo=false;

    srand(time(NULL));
    system("title BIENVENIDO !!!!");
    bienvenida();
    do{
        system("cls");
        system("title El Corazon de la reina !!!  - Menu Principal");
        menu_principal(opc);
        switch(opc){
            case 1: cout<<"gestion de jugadores"<<endl;
                    gestion_jugador(jugadores);
                    break;

            case 2: cout<<"gestion de baraja"<<endl;
                    gestion_baraja(baraja, cola, mazo_nuevo);
                    break;


            case 3:
                    //control de ingreso 2 jugadores minimo
                    if(cantidad_jugadores(jugadores)<2){
                        cout<<"debe registrar al menos 2 jugadores"<<endl;
                    }else{
                        if(!mazo_nuevo){
                            cout<<"Primero debe generar un mazo aleatorio."<<endl;
                        }else{
                            cout<<"dentro de gestion de juego"<<endl;
                        gestion_juego(mazo, jugadores, cola, mazo_nuevo);
                        }

                    }

                    break;



            case 4: cout<<"ranking"<<endl;
                    gestion_ranking2(jugadores);
     
                    break;

            case 9: cout<<"\n*** HAS SALIDO DEL JUEGO ***"<<endl;

                    break;

            default: cout<<"Opcion no valida"<<endl;

                    break;
        }
        if (opc!=9)
            system("pause");
    } while (opc!=9);
    despedida();
}


void menu_principal(int &opc){
    cout<<"************************************"<<endl;
    cout<<"********** MENU PRINCIPAL **********"<<endl;
    cout<<"**                                **"<<endl;
    cout<<"**   1 - Gestion de Jugadores     **"<<endl;
    cout<<"**   2 - Gestion de Baraja        **"<<endl;
    cout<<"**   3 - Jugar                    **"<<endl;
    cout<<"**   4 - Ranking de Jugadores     **"<<endl;
    cout<<"**   9 - Salir del Juego          **"<<endl;
    cout<<"**                                **"<<endl;
    cout<<"************************************"<<endl;
    cout<<"************************************"<<endl;
    cin>>opc;
}


void bienvenida(){
    
    cout << "  ----                             BIENVENIDOS                 ----" << endl;
    cout << endl;
    cout << MAGENTA << "       -------------        EL CORAZON DE LA REINA      --------------" << endl;
    cout << ORANGE << endl;
    cout << ".------..------..------.     .------..------..------.     .------..------..------." << endl;
    cout << "|7.--. ||3.--. ||9.--. |.-.  |1.--. ||4.--. ||0.--. |.-.  |6.--. ||3.--. ||5.--. |" << endl;
    cout << "| :(): || :(): || :/\: ((5)) | :/\: || :/\: || :/\: ((5)) | (\/) || :(): || :/\: |" << endl;
    cout << "| ()() || ()() || (__) |'-.-.| (__) || :\/: || :\/: |'-.-.| :\/: || ()() || (__) |" << endl;
    cout << "| '--'7|| '--'3|| '--'9| ((1)) '--'1|| '--'4|| '--'0| ((1)) '--'6|| '--'3|| '--'5|" << endl;
    cout << "`------'`------'`------'  '-'`------'`------'`------'  '-'`------'`------'`------'" << endl;
    cout << endl;
    cout << endl;
    cout << BLACK << "           pon a prueba tu habilidad en el mejor juego de cartas!" << endl;
    cout << endl;
    
    cout << endl;
    cout << endl;
    cout << "presiona una tecla para continuar...." << endl;
    _getch();
}

void despedida(){

    system("cls");
    system("title El Corazon de la reina !!!  - Gracias!!!");
    cout << "        -----------------      EL CORAZON DE LA REINA      --------------" << endl;
    cout << ".------..------..------.     .------..------..------.     .------..------..------." << endl;
    cout << "|7.--. ||3.--. ||9.--. |.-.  |1.--. ||4.--. ||0.--. |.-.  |6.--. ||3.--. ||5.--. |" << endl;
    cout << "| :(): || :(): || :/\: ((5)) | :/\: || :/\: || :/\: ((5)) | (\/) || :(): || :/\: |" << endl;
    cout << "| ()() || ()() || (__) |'-.-.| (__) || :\/: || :\/: |'-.-.| :\/: || ()() || (__) |" << endl;
    cout << "| '--'7|| '--'3|| '--'9| ((1)) '--'1|| '--'4|| '--'0| ((1)) '--'6|| '--'3|| '--'5|" << endl;
    cout << "`------'`------'`------'  '-'`------'`------'`------'  '-'`------'`------'`------'" << endl;
    cout << endl;
    cout << endl;
    cout << "Gracias por Jugar!" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "integrantes: Martinez Roberto Ariel Jesus - Yufra Marcelo Alejandro" << endl;
    cout << "Profesores:  Ing. Marcelo Perez Ibarra - Ing. Veronica Torres" << endl;
    cout << endl;
    cout << endl;
    cout << "Catedra: Estructura de Datos" << endl;
    cout << endl;
    cout << "2023"<<endl;
    cout << endl;
    //_getch();
}