/**
 * ******** GESTION DE BARAJA ********
 */

typedef FILE *parchivo2;

/** ESTRUCTURA DE CARTA (lo pase al archivo principal)
 *  1 - ORO
 *  2 - ESPADA
 *  3 - COPA
 *  4 - BASTO

typedef struct tcarta{
    int nro;
    int palo;
    bool comodin;
    int puntos;
};
*/

/** ESTRUCTURA DE ARRAY DE MAZO AUX */
typedef tcarta mazo_aux[MAX_CARTAS];

/** ESTRUCTURA DE LISTA SIMPLE DEL MAZO */
typedef struct tnodo *pnodo;
typedef struct tnodo{
    tcarta datos;
    pnodo sig;
};

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
void consulta_baraja(parchivo2 baraja);
void vector_mezcla(parchivo2 baraja, mazo_aux &m);
void mostrar_mazo_aux(mazo_aux m);
void mezclar_cartas(mazo_aux &mazo);
void recorrer_mazo_y_cargar_lista(mazo_aux m, tcola &cola);
void mostrar_carta(tcarta carta, int n);


/** FUNCIONES DE LISTAS SIMPLES (del mazo) */
void iniciar_cola(tcola &lis);
void crear(pnodo &nuevo, tcarta valor);
bool cola_llena(tcola lis);
void agregar_cola(tcola &lis, tcarta valor);
bool cola_vacia(tcola lis);
tcarta quitar_cola(tcola &lis);
tcarta obtener_primera_carta(tcola lis);
tcarta obtener_ultima_carta(tcola lis);

void mostrar_mazo_de_listas(tcola cola);


void menu_gestion_baraja(int &opc){
    cout<<"*** GESTION DE BARAJA ***"<<endl;
    cout<<"1 - Generar Una Baraja"<<endl;
    cout<<"2 - Crear Mazo Aleatorio"<<endl;
    cout<<"3 - Mostrar Mazo"<<endl;
    cout<<"4 - (testeo)mostrar primera y ultima carta del mazo(cola)"<<endl;
    cout<<"9 - Salir al Menu Principal"<<endl;
    cin>>opc;
}

/** SWITCH DE GESTION DE BARAJA */
void gestion_baraja(parchivo2 baraja, tcola &cola, bool &mazo_nuevo) {

    int opc;
    mazo_aux mazo;
    //tcola cola;
    bool mazo_creado=false;

    do{
        system("cls");
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
                        iniciar_cola(cola); //para generar un nuevo mazo aleatorio y no salga un error de q la cola esta llena
                        vector_mezcla(baraja, mazo); // carga un vector con las 48 cartas
                        mezclar_cartas(mazo); // mezcla las cartas del vector
                        recorrer_mazo_y_cargar_lista(mazo, cola); // pasa el vector a una cola de listas
                        mazo_creado=true;
                        mazo_nuevo=true;
                        cout<<"*** MAZO CREADO CON EXITO ***"<<endl;
                    }
                    fclose(baraja);
                    break;

            case 3: if (mazo_creado==true || cola.cont>0) {
                        cout<<"\nMOSTRANDO MAZO..."<<endl;
                        //mostrar_mazo_aux(mazo);
                        mostrar_mazo_de_listas(cola);
                    } else
                        cout<<"\nERROR: PRIMERO DEBE CREAR UN MAZO\n"<<endl;
                    break;

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

/** PROCEDIMIENTO PARA GENERAR UNA BARAJA */
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
        cout<<"BARAJA CREADA CON EXITO"<<endl;
    }
}

void consulta_baraja(parchivo2 baraja){

    tcarta a;

    baraja=fopen("baraja.txt","rb");
    if (baraja==NULL)
        cout << "Archivo Inexistente" << endl;
    else
    {
        while (!feof(baraja))
        {
            fread(&a,sizeof(a),1,baraja);
            if (!feof(baraja))
            {
                cout << "carta: "<<a.nro << " palo: "<< a.palo << " puntos: " << a.puntos << " comodin? : "<<a.comodin<<endl;
            }
        }
    }
    fclose(baraja);
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


/** RECORRIDO DEL MAZO Y CARGAR LISTA */
void recorrer_mazo_y_cargar_lista(mazo_aux m, tcola &cola){
    int i;
    for(i=0; i<MAX_CARTAS; i++)
        agregar_cola(cola, m[i]);
}

/** MUESTRA UNA CARTA CON SUS ATRIBUTOS */
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
        cout<<"[carta"<<n<<"] Nro: "<<carta.nro<<" "<<tipo_palo<<" "<<carta.puntos<<" pts. (comodin)"<<endl;
    } else {
        cout<<"[carta"<<n<<"] Nro: "<<carta.nro<<" "<<tipo_palo<<" "<<carta.puntos<<" pts."<<endl;
    }
}


/******************** OPERACIONES DE COLAS ***************************/

void iniciar_cola(tcola &lis)
{
    lis.inicio=NULL;
    lis.fin=NULL;
    lis.cont=0;
}

/** Creación de un nodo */
void crear(pnodo &nuevo, tcarta valor) {
    nuevo=new tnodo;
    if (nuevo!=NULL) {
        nuevo->datos=valor;
        nuevo->sig=NULL;
    }
}

bool cola_llena(tcola lis) {
	return lis.cont==MAX_CARTAS;
}

/** Agrega elemento al final de la cola (agregar final) */
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

bool cola_vacia(tcola lis) {
    return lis.cont==0;
}

/** Quita el primer elemento de la cola (quitar frente) */
tcarta quitar_cola(tcola &lis) {
    pnodo aux;
    tcarta carta;
	if (cola_vacia(lis)) {
        aux=NULL;
	} else {
		aux=lis.inicio;
		lis.inicio=lis.inicio->sig;
		aux->sig=NULL;
		lis.cont--;
	}
	carta=aux->datos;
	delete(aux);
	return carta;
}


tcarta obtener_primera_carta(tcola lis) {
    tcarta carta_vacia;  // Carta por defecto si la cola está vacía
    carta_vacia.nro = -1; // Valor que indica una carta vacía o no válida

    if (!cola_vacia(lis)) {
        return lis.inicio->datos;
    } else {
        return carta_vacia;
    }
}


tcarta obtener_ultima_carta(tcola lis) {
    tcarta carta_vacia;  // Carta por defecto si la cola está vacía
    carta_vacia.nro = -1; // Valor que indica una carta vacía o no válida

    if (!cola_vacia(lis)) {
        return lis.fin->datos;
    } else {
        return carta_vacia;
    }
}



