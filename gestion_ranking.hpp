/****************************
 *  Generacion del Ranking *
 ****************************/


// Estrucutura del Arbol
typedef struct tranking *pranking;
typedef struct tranking{

    tjugador dato;
    pranking izq;
    pranking der;

};

// Prototipos

void recorrer_archivo(parchivo f, pranking &ranking);

void iniciar_arbol(pranking &a);
void crear_nodo(pranking &a, tjugador jug);
void cargar_arbol(pranking &a, pranking nuevo);

void preorden(pranking a);
void enorden(pranking a);
void posorden(pranking a);
void menu_ranking(int &opc);
void gestion_ranking2(parchivo j);
void mostrar_decreciente(pranking a);
void liberar_arbol(pranking a);

// Inicio arbol
void iniciar_arbol(pranking &a){
    a=NULL;
}

// Procedimiento de manejo de opciones principales del menu de gestion de ranking

void gestion_ranking2(parchivo j) {
    int opc, opc2;
    bool orden;
    pranking arbol;

    iniciar_arbol(arbol);
    recorrer_archivo(j, arbol);


    do {
        system("cls");
        system("title El Corazon de la reina !!!  - Ranking");
        menu_ranking(opc);

        switch (opc) {
            case 1:
                
                    cout << BLUE << "Ranking de jugadores" << endl;
                    cout << BLACK << endl;
                    cout << "Ingrese 0 para mostrar en orden decreciente y  1 para creciente: ";
                    cin >> opc2;
                    if(opc2==0){
                        mostrar_decreciente(arbol);
                    }else{
                        enorden(arbol);
                    }
                    
                break;

            case 5:
                cout << "Salir" << endl;
                break;

            default:
                cout << "Opcion no valida" << endl;
                break;
        }

        system("pause");

    } while (opc != 5);

    liberar_arbol(arbol);
}


/* 
Procedimiento que recorre el archivo y copia los registros al arbol
(crea el nodo y inserta en el arbol) siempre y cuando el puntaje sea mayor a 0

*/
void recorrer_archivo(parchivo f, pranking &ranking){

    tjugador jug;
    pranking nuevo;

    int cont=0;
    f=fopen("jugadores.txt", "rb");

    while(!feof(f)){
        fread(&jug, sizeof(jug), 1, f);
        if(!feof(f)){
            if (jug.puntaje > 0) {
                cont++;
                crear_nodo(nuevo, jug);
                cargar_arbol(ranking, nuevo);
            }
          
        }

    }

    cout<<endl;
    fclose(f);

}

void crear_nodo(pranking &nuevo, tjugador valor){

    nuevo=new tranking;

    if(nuevo!=NULL){
        nuevo->dato=valor;
        nuevo->izq=NULL;
        nuevo->der=NULL;
    }else{

        cout<<"NO HAY MEMORIA"<<endl;

    }

}

//ealiza la carga del arbol insertando los valores inferiores a la izquierda

void cargar_arbol(pranking &a, pranking nuevo) {
    if (a == NULL) {
        a = nuevo;
    } else {
        if (nuevo->dato.puntaje < a->dato.puntaje) {
            cargar_arbol(a->izq, nuevo);
        } else {
            cargar_arbol(a->der, nuevo);
        }
    }
}


// El recorrido enOrden muestra los elementos de forma creciente
void enorden(pranking a) {
    if (a != NULL) {
        enorden(a->izq);
        cout << a->dato.nombre << " pts: "<<a->dato.puntaje<<endl;
        enorden(a->der);
    }
}



/*
Muestra los elementos del arbol en forma decreciente. es una modificacion
del recorrido enOrden, inviertiendo el orden empezando por el lado
derecho
*/
void mostrar_decreciente(pranking a){

	if(a!=NULL){

		mostrar_decreciente(a->der);
		cout << a->dato.nombre << " pts: "<<a->dato.puntaje<<endl;
		mostrar_decreciente(a->izq);

	}

}

// menu simple

void menu_ranking(int &opc){

    cout<<"1- mostrar ranking"<<endl;
    cout<<"5- Salir"<<endl;
    cin>>opc;

}

// funcion para liberar nodos
void liberar_arbol(pranking a) {
    if (a != NULL) {
        liberar_arbol(a->izq);
        liberar_arbol(a->der);
        delete a;
    }
}