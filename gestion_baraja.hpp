/***************************
 **** GESTION DE BARAJA ****
 ***************************/

typedef FILE *parchivo2;


/** ESTRUCTURA DE ARRAY DE MAZO AUX */
typedef tcarta mazo_aux[MAX_CARTAS];

/** ESTRUCTURA DE LISTA SIMPLE DEL MAZO */
typedef struct tnodo *pnodo;
typedef struct tnodo{
    tcarta datos;
    pnodo sig;
};

/** ESTRUCTURA DE COLA PARA EL MAZO DE CARTAS */
typedef struct tcola{
    pnodo inicio;
    pnodo fin;
    int cont;
};


/** PROCEDIMIENTOS Y FUNCIONES */
void menu_gestion_baraja(int &opc);
void gestion_baraja(parchivo2 baraja, tcola &cola, bool &mazo_nuevo);
void generar_baraja(parchivo2 baraja);
void crear_carta(tcarta &c, int palo, int nro);
//void consulta_baraja(parchivo2 baraja);
void vector_mezcla(parchivo2 baraja, mazo_aux &m);
void mostrar_mazo_aux(mazo_aux m);
void mezclar_cartas(mazo_aux &mazo);
void recorrer_mazo_y_cargar_lista(mazo_aux m, tcola &cola);
void mostrar_carta(tcarta carta, int n);
void mostrar_carta_mazo(tcarta carta, int n);


/** FUNCIONES DE LISTAS SIMPLES (del mazo) */
void iniciar_cola(tcola &lis);
void crear(pnodo &nuevo, tcarta valor);
bool cola_llena(tcola lis);
void agregar_cola(tcola &lis, tcarta valor);
bool cola_vacia(tcola lis);
tcarta quitar_cola(tcola &lis);
tcarta obtener_primera_carta(tcola lis);
tcarta obtener_ultima_carta(tcola lis);
void mostrar_mazo_de_listas(tcola &cola);
void liberar_cola(tcola &lis);

void menu_gestion_baraja(int &opc){
    cout<< BLACK <<" ***    GESTION DE BARAJA    *** "<<endl;
    cout<<" 1 - Generar Una Baraja"<<endl;
    cout<<" 2 - Crear Mazo Aleatorio"<<endl;
    cout<<" 3 - Mostrar Mazo"<<endl;
    //cout<<"4 - (testeo)mostrar primera y ultima carta del mazo(cola)"<<endl;
    cout<<" 9 - Salir al Menu Principal"<<endl;
    cin>>opc;
}

/** SWITCH DE GESTION DE BARAJA */
void gestion_baraja(parchivo2 baraja, tcola &cola, bool &mazo_nuevo) {

    int opc;
    mazo_aux mazo;
    bool mazo_creado=false;

    do{
        system("cls");
        system("title El Corazon de la reina !!!  - Gestion de Cartas");
        menu_gestion_baraja(opc);
        switch(opc) {

            case 1: baraja=fopen("baraja.txt","rb");
                    if (baraja==NULL) {
                        generar_baraja(baraja);
                    } else
                        cout<<"*** YA EXISTE UNA BARAJA ***"<<endl;
                    fclose(baraja);
                    break;


            case 2: baraja=fopen("baraja.txt","rb");
                    if (baraja==NULL) {
                        cout<<"\nERROR: PRIMERO DEBE GENERAR UNA BARAJA\n"<<endl;
                    } else {
                        iniciar_cola(cola);
                        vector_mezcla(baraja, mazo); // carga un vector con las 48 cartas
                        mezclar_cartas(mazo); // mezcla las cartas del vector
                        recorrer_mazo_y_cargar_lista(mazo, cola); // pasa el vector a una cola de listas
                        mazo_creado=true;
                        mazo_nuevo=true;
                        cout<<"*** MAZO CREADO CON EXITO ***"<<endl;
                    }
                    fclose(baraja);
                    break;


            case 3: if (mazo_creado) {
                        cout<<"\nMOSTRANDO MAZO..."<<endl;
                        mostrar_mazo_de_listas(cola);
                    } else
                        cout<<"\nERROR: PRIMERO DEBE CREAR UN MAZO\n"<<endl;
                    break;

            //TEST
            case 4: cout<<"\nMostrar primera y ultima carta (tcola)"<<endl;
                    cout<<"Primera carta:"<<endl;
                    mostrar_carta(obtener_primera_carta(cola), 1);
                    cout<<"Ultima carta:"<<endl;
                    mostrar_carta(obtener_ultima_carta(cola), 48);
                    break;

            case 9: cout<<"VOLVIENDO AL MENU PRINCIPAL..."<<endl;
                    break;

            default: cout<<"Opcion no valida"<<endl;
                    break;
        }
        if (opc!=9)
            system("pause");
            
    } while (opc!=9);
}


/**
 * CREACION DE UNA CARTA CON SU RESPECTIVO NUMERO, PUNTAJE Y PALO
 */
void crear_carta(tcarta &c, int palo, int nro){
    c.nro=nro;
    c.palo=palo;
    if (palo>=1 && palo<=4) {
        if (nro<=3) {
            c.comodin=true;
            if (nro==1)
                c.puntos=50;
            else
                c.puntos=25;
        } else {
            c.comodin=false;
            if (nro==7 && (palo==1 || palo==2) )
                c.puntos=15;
            else
                if(nro<=9)
                    c.puntos=5;
                else
                    c.puntos=10;
        }
    }
}

/** PROCEDIMIENTO PARA GENERAR ARCHIVO DE BARAJA */
void generar_baraja(parchivo2 baraja){
    tcarta carta;
    int i,j;
    if (baraja==NULL){
        baraja=fopen("baraja.txt", "ab+");
        for(i=1; i<=4; i++){
            for(j=1; j<=12; j++){
                crear_carta(carta, i, j);
                fwrite(&carta, sizeof(carta), 1, baraja);
            }
        }
        fclose(baraja);
        cout<< GREEN <<"*** BARAJA CREADA CON EXITO ***"<<endl;
        cout << BLACK << endl;
    }
}


/** PROCEDIMIENTO DE LLEVAR LOS REGISTROS A UN ARRAY */
void vector_mezcla(parchivo2 baraja, mazo_aux &m) {
    tcarta carta;
    int pos=0;
    baraja=fopen("baraja.txt","rb");
    if (baraja==NULL)
        cout << "Primero debe generar una baraja" << endl;
    else {
        while (!feof(baraja)) {
            fread(&carta, sizeof(carta), 1, baraja);
            if (!feof(baraja)) {
                 m[pos]=carta;
                 pos++;
            }
        }
    }
    fclose(baraja);
}

/** PROCEDIMIENTO DE MEZCLAR LAS CARTAS DEL ARRAY */
void mezclar_cartas(mazo_aux &mazo){
    for (int i=MAX_CARTAS-1; i>0; i--) {
        int j = std::rand() % (i+1);
        tcarta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

/** MOSTRAR MAZO */
void mostrar_mazo_aux(mazo_aux m) {
    int i, n=0;
    for(i=0; i<MAX_CARTAS; i++) {
        n++;
        mostrar_carta(m[i], n);
    }
}


/** RECORRIDO DEL MAZO(array) Y CARGAR EL MAZO(de listas) */
void recorrer_mazo_y_cargar_lista(mazo_aux m, tcola &cola){
    int i;
    for(i=0; i<MAX_CARTAS; i++)
        agregar_cola(cola, m[i]);
}

/** MUESTRA UNA CARTA CON SUS ATRIBUTOS PARA LA BARAJA DEL JUGADOR */
void mostrar_carta(tcarta carta, int n) {
    tcad tipo_palo, escomodin;
    switch (carta.palo) {
        case 1: strcpy(tipo_palo, "Oro"); break;
        case 2: strcpy(tipo_palo, "Espada"); break;
        case 3: strcpy(tipo_palo, "Copa"); break;
        case 4: strcpy(tipo_palo, "Basto"); break;
    }
    if (carta.comodin) {
        strcpy(escomodin, "Si");
        cout<< ORANGE <<"[carta"<<n<<"] Numero: "<<carta.nro<<" "<<tipo_palo<<" "<<carta.puntos<<" pts. (comodin)"<<endl;
    } else {
        cout<< BLACK <<"[carta"<<n<<"] Numero: "<<carta.nro<<" "<<tipo_palo<<" "<<carta.puntos<<" pts."<<endl;
    }
}

/** MUESTRA UNA CARTA CON SUS ATRIBUTOS PARA LA PRIMERA CARTA EL MAZO */
void mostrar_carta_mazo(tcarta carta) {
    tcad tipo_palo;
    switch (carta.palo) {
        case 1: strcpy(tipo_palo, "Oro"); break;
        case 2: strcpy(tipo_palo, "Espada"); break;
        case 3: strcpy(tipo_palo, "Copa"); break;
        case 4: strcpy(tipo_palo, "Basto"); break;
    }
    cout<< BLACK <<"Numero "<<carta.nro<<" "<<tipo_palo<<" "<<carta.puntos<<" pts."<<endl;
}



/** ---------------------------- OPERACIONES DE COLAS ----------------------------- */
/** -------------- UTILIZADO PARA EL MAZO DE CARTAS (LISTA SIMPLE) ----------------*/


/** INICIAR MAZO */
void iniciar_cola(tcola &lis)
{
    lis.inicio=NULL;
    lis.fin=NULL;
    lis.cont=0;
}


/** CREACION DE UN NODO DE LISTA SIMPLE */
void crear(pnodo &nuevo, tcarta valor) {
    nuevo=new tnodo;
    if (nuevo!=NULL) {
        nuevo->datos=valor;
        nuevo->sig=NULL;
    }
}


/** MAZO LLENA */
bool cola_llena(tcola lis) {
	return lis.cont==MAX_CARTAS;
}


/** AGREGA UN ELEMENTO AL FINAL DEL MAZO */
void agregar_cola(tcola &lis, tcarta valor) {
    pnodo nuevo;
    if(cola_llena(lis))
        cout<<"Cola de mazo llena!"<<endl;
    else {
        crear(nuevo,valor);
        if (lis.inicio==NULL) {
            lis.inicio=nuevo;
            lis.fin=nuevo;
            lis.cont++;
        } else {
            lis.fin->sig=nuevo;
            lis.fin=lis.fin->sig;
            lis.cont++;
        }
    }
}


/** MAZO VACIO */
bool cola_vacia(tcola lis) {
    return lis.cont==0;
}


/** QUITA EL PRIMER ELEMENTO DEL MAZO */
tcarta quitar_cola(tcola &lis) {
    pnodo aux;
	if (cola_vacia(lis)) {
        aux=NULL;
	} else {
		aux=lis.inicio;
		lis.inicio=lis.inicio->sig;
		aux->sig=NULL;
		lis.cont--;
	}
	return aux->datos;
}




/*********************************************************************/

/** OBTENER EL FRENTE DEL MAZO */
tcarta obtener_primera_carta(tcola lis) {
    tcarta carta_vacia;  // Carta por defecto si la cola esta vacia
    carta_vacia.nro = -1; // Valor que indica una carta vacia o no valida
    if (!cola_vacia(lis))
        return lis.inicio->datos;
    else
        return carta_vacia;
}


/** OBTENER EL FINAL DEL MAZO */
tcarta obtener_ultima_carta(tcola lis) {
    tcarta carta_vacia;  // Carta por defecto si la cola esta vacia
    carta_vacia.nro = -1; // Valor que indica una carta vacia o no valida
    if (!cola_vacia(lis))
        return lis.fin->datos;
    else
        return carta_vacia;
}


void liberar_cola(tcola &lis) {
    pnodo actual = lis.inicio;
    pnodo siguiente;

    while (actual != NULL) {
        siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }

    lis.inicio = NULL;
    lis.fin = NULL;
    lis.cont = 0;
}
