
typedef struct tranking *pranking;
typedef struct tranking{

    tjugador dato;
    pranking izq;
    pranking der;

};

void recorrer_archivo(parchivo f, pranking &ranking);

//typedef FILE *parchivo;

void iniciar_arbol(pranking &a);
void crear_nodo(pranking &a, tjugador jug);
void cargar_arbol(pranking &a, pranking nuevo);

void preorden(pranking a);
void enorden(pranking a);
void posorden(pranking a);
void menu_ranking(int &opc);
void gestion_ranking2(parchivo j);
void mostrar_decreciente(pranking a);



void iniciar_arbol(pranking &a){

    a=NULL;

}


void gestion_ranking2(parchivo j) {
    int opc, opc2;
    bool orden;
    pranking arbol;

    iniciar_arbol(arbol);
    recorrer_archivo(j, arbol);

    do {
        system("cls");
        menu_ranking(opc);

        switch (opc) {
            case 1:
                cout << "Ranking de jugadores" << endl;
                cout << "Ingrese 0 para decreciente, 1 para creciente: ";

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


}

void recorrer_archivo(parchivo f, pranking &ranking){

    tjugador jug;
    pranking nuevo;

    int cont=0;
    f=fopen("jugadores.txt", "rb");

    while(!feof(f)){
        fread(&jug, sizeof(jug), 1, f);
        if(!feof(f)){
          cont++;
          crear_nodo(nuevo, jug);
          cargar_arbol(ranking, nuevo);
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

void preorden(pranking a) {
    if (a != NULL) {
        cout << a->dato.nombre << " pts: "<<a->dato.puntaje<<endl;
        preorden(a->izq);
        preorden(a->der);
    }
}

void enorden(pranking a) {
    if (a != NULL) {
        enorden(a->izq);
        cout << a->dato.nombre << " pts: "<<a->dato.puntaje<<endl;
        enorden(a->der);
    }
}

void posorden(pranking a) {
    if (a != NULL) {
        posorden(a->izq);
        posorden(a->der);
        cout << a->dato.nombre << " pts: "<<a->dato.puntaje<<endl;
    }
}


void mostrar_decreciente(pranking a){

	if(a!=NULL){

		mostrar_decreciente(a->der);
		cout << a->dato.nombre << " pts: "<<a->dato.puntaje<<endl;
		mostrar_decreciente(a->izq);

	}

}

void menu_ranking(int &opc){

    cout<<"1- mostrar ranking"<<endl;
    cout<<"5- Salir"<<endl;
    cin>>opc;

}
