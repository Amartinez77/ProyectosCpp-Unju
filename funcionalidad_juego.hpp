/****************************
 *  FUNCIONALIDAD DEL JUEGO *
 ****************************/


/**
 * ESTRUCTURA DE JUGADORES SELECCIONADOS PARA UNA PARTIDA
 */
typedef tjugador tjugcontenedor[MAX_JUG];
typedef struct tjugselec{
    tjugcontenedor jugadores;
    int ocup;
};


/** PROCEDIMIENTOS Y FUNCIONES */
void menu_juego();
void gestion_juego(mazo_aux mazo, parchivo jugadores, tcola &cola, bool mazo_nuevo);
void listar_jugadores(parchivo jugadores, tjugselec &js);
bool seleccion_de_jug(parchivo jugadores, int num, tjugselec &js);
void reiniciar_selec_jug(tjugselec &js);
void repartir_cartas(tjugselec &js, tcola &cola);
void mostrar_jug_seleccionados(tjugselec js); //PARA TESTEAR
int contar_puntos(tjugador &jugador);
void actualizar_jugador(parchivo jugadores, tjugador jug_buscado, int puntosGanados);

void mostrar_mazo_de_listas(tcola &cola); //PARA TESTEAR
void pasar_al_ultimo(tcola &lis);

void iniciar_baraja(tblista &lista);
void crear_nodo_doble(pbaraja &nuevo, tcarta valor);
void agregar_a_la_baraja(tblista &lista, tcarta carta);
bool ver_baraja(tblista &lista, tcola &cola);
void elegir_carta(tblista &lista, tpila &pila, tcola &cola, bool extraer);
tcarta quitar_a_la_baraja(tblista &lista, int cartabuscada);
void mostrar_barajas(tjugselec js); //PARA TESTEAR

void iniciar_pila(tpila &pila);
bool pila_vacia(tpila pila);
bool pila_llena(tpila pila);
tcarta tope_pila(tpila pila);
void agregar_pila(tpila &pila, tcarta nuevo);
tcarta quitar_pila(tpila &pila);
void mostrar_una_pila(tjugador j);
void mostrar_pilas(tjugselec &js); // PRARA TESTEAR



void menu_juego() {
    cout<<"*** MENU DE JUEGO ***"<<endl;
    cout<<"1 - Elegir jugadores"<<endl;
    cout<<"2 - Repartir cartas"<<endl;
    cout<<"3 - Iniciar la partida"<<endl;
    cout<<"4 - (testeo) mostrar jugadores seleccionados (array) (dsp de selec jugadores)"<<endl;
    cout<<"5 - (testeo) mostrar mazo (lista simple)"<<endl;
    cout<<"6 - (testeo) mostrar baraja de cada jugador (listas dobles) (despues de repartir las cartas)"<<endl;
    cout<<"7 - (testeo) mostrar pila de cada jugador (tpila) (despues de una partida)"<<endl;
    cout<<"9 - Volver al menu principal"<<endl;
}


void gestion_juego(mazo_aux mazo, parchivo jugadores, tcola &cola, bool mazo_nuevo) {

    tjugselec js;
    tjugador jug_aux;

    int opcion;
    int i, j, m, pts, maxpts;
    int cant_jug;

    bool puede_extraer;
    bool nueva_partida=false;
    bool cartas_repartidas=false;
    bool jugadores_elegidos=false;
    bool encontrado;
    bool jug_con_cartas, juego_continua, empate;

    do {
        system("cls");
        menu_juego();
        cin>>opcion;
        switch (opcion) {

            case 1: listar_jugadores(jugadores, js);
                    jugadores_elegidos=true;
                    break;


            case 2: if (jugadores_elegidos==false) {
                        cout<<"Primero debe elegir al menos 2 jugadores."<<endl;
                    } else {
                        if (mazo_nuevo==false) {
                            cout<<"Primero debes crear un mazo aleatorio nuevo."<<endl;
                        } else {
                            repartir_cartas(js, cola);
                            nueva_partida=true;
                            cartas_repartidas=true;
                            cout<<"*** LAS CARTAS FUERON REPARTIDAS ***"<<endl;
                        }
                    }
                    break;


            case 3: if (cartas_repartidas==false) {
                        cout<<"* Primero debe repartir las cartas *"<<endl;
                    } else {
                        cout<<"\n*** COMIENZA LA PARTIDA ***\n\n"<<endl;
                        cartas_repartidas=false;
                        jugadores_elegidos=false;
                        mazo_nuevo=false;
                        cant_jug = js.ocup;
                        system("pause");

                        if (nueva_partida==true) {
                            for (i=0; i<=cant_jug; i++) {
                                iniciar_pila(js.jugadores[i].pila);
                                js.jugadores[i].pts_partida=0;
                            }
                            nueva_partida=false;
                        }

                        juego_continua=true;
                        jug_con_cartas=true;

                        while (jug_con_cartas==true || juego_continua==true) {
                            m=cola.cont; // GUARDA LA CANTIDAD DE CARTAS DEL MAZO ANTES DE CADA RONDA
                            juego_continua=false;
                            jug_con_cartas=false;

                            // RECORRIDO DE LOS JUGADORES QUE ESTAN JUGANDO LA PARTIDA
                            for (i=0; i<=cant_jug; i++) {
                                system("cls");

                                if (js.jugadores[i].baraja.contador>0) {
                                    jug_con_cartas=true;
                                    juego_continua=true;
                                    cout<<"ES EL TURNO DE: "<<js.jugadores[i].nickname<<endl;
                                    puede_extraer = ver_baraja(js.jugadores[i].baraja, cola);
                                    elegir_carta(js.jugadores[i].baraja, js.jugadores[i].pila, cola, puede_extraer);
                                    if (js.jugadores[i].baraja.contador==0) {
                                        cout<<"\n*** OH!! TE ACABAS DE QUEDAR SIN CARTAS!! ***\n"<<endl;
                                    }
                                    cout<<"\n*** PASANDO AL SIGUIENTE TURNO... ***\n"<<endl;
                                    system("pause");

                                } else {
                                    cout<<"*******************************************************************"<<endl;
                                    cout<<"*** EL JUGADOR: "<<js.jugadores[i].nickname<<" YA NO TIENE CARTAS EN SU BARAJA ***"<<endl;
                                    cout<<"*******************************************************************\n"<<endl;
                                    system("pause");
                                }

                                if (js.jugadores[i].baraja.contador==0) {
                                    pts=contar_puntos(js.jugadores[i]);
                                    js.jugadores[i].pts_partida = pts;
                                }
                            }

                            // SI m SIGUE IGUAL AL DEL CONTADOR ES PORQUE QUE NINGUNO PUDO EXTRAER DEL MAZO
                            if (m==cola.cont && jug_con_cartas==true) {
                                juego_continua=true;
                                cout<<"\n*** NINGUNO DE LOS JUGADORES PUDO SACAR DEL MAZO ***"<<endl;
                                cout<<"** PASANDO CARTA AL FINAL DEL MAZO... **"<<endl;
                                pasar_al_ultimo(cola);
                                system("pause");
                            }
                        }
                        system("cls");

                        // AL MOMENTO QUE FINALIZA LA PARTIDA
                        cout<<"PUNTOS ALCANZADOS POR LOS JUGADORES\n"<<endl;
                        maxpts=-1;
                        for (i=0; i<=cant_jug; i++) {
                            pts = js.jugadores[i].pts_partida;
                            cout<<js.jugadores[i].nickname<<": "<<pts<<"pts."<<endl;
                            mostrar_una_pila(js.jugadores[i]);
                            cout<<"---------------------------------"<<endl;
                            if (maxpts < pts) {
                                maxpts = pts;
                                jug_aux = js.jugadores[i];
                            }
                        }

                        // BUSCAR SI HUBO ALGUN EMPATE
                        empate=false;
                        for (i=0; i<=cant_jug && !empate; i++) {
                            if (strcmp(jug_aux.nickname,js.jugadores[i].nickname)!=0 && jug_aux.pts_partida==js.jugadores[i].pts_partida) {
                                cout<<"\nHubo empate entre "<<jug_aux.nickname<<" y "<<js.jugadores[i].nickname<<" de "<<maxpts<<"pts."<<endl;
                                empate=true;
                                system("pause");
                            }
                        }
                        encontrado=false;
                        if (empate) {
                            i--;
                            cout<<"\nLOS GANADORES SON "<<jug_aux.nickname<<" Y "<<js.jugadores[i].nickname<<endl;
                            js.jugadores[i].puntaje = js.jugadores[i].puntaje + maxpts;
                            for (j=0; j<=cant_jug && !encontrado; j++) {
                                if (strcmp(jug_aux.nickname, js.jugadores[j].nickname)==0) {
                                    encontrado=true;
                                    js.jugadores[j].puntaje = js.jugadores[j].puntaje + maxpts;
                                }
                            }
                            j--;
                            actualizar_jugador(jugadores, js.jugadores[i], maxpts);
                            actualizar_jugador(jugadores, js.jugadores[j], maxpts);

                        } else {
                            cout<<"\nEL GANADOR ES "<<jug_aux.nickname<<" CON "<<maxpts<<"pts."<<endl;
                            for(i=0; i<=cant_jug; i++) {
                                if ( strcmp(jug_aux.nickname, js.jugadores[i].nickname)==0 ) {
                                    js.jugadores[i].puntaje = js.jugadores[i].puntaje + maxpts;
                                    actualizar_jugador(jugadores, js.jugadores[i], maxpts);
                                }
                            }
                        }
                    }
                    break;

            //TEST
            case 4: mostrar_jug_seleccionados(js);
                    break;
            //TEST
            case 5: mostrar_mazo_de_listas(cola);
                    break;
            //TEST
            case 6: mostrar_barajas(js);
                    break;
            //TEST
            case 7: mostrar_pilas(js);
                    break;

            case 9: cout<<"VOLVIENDO AL MENU PRINCIPAL..."<<endl;
                    break;
        }
        if (opcion!=9)
            system("pause");
    } while (opcion!=9);
}



/**
 * LISTA LOS JUGADORES REGISTRADOS PARA ELEGIR UNO
 *
 * jugadores -> archivos de los jugadores registrados
 * js -> registro con un array de jug donde se guardaran los jugadores seleccionados
 */
void listar_jugadores(parchivo jugadores, tjugselec &js) {

    tjugador a;
    char resp='s';
    int jugSeleccionado, cont=0, contJugSel=0;
    bool hayJugadores=false, selValida; //seleccion de jugador valida

    jugadores=fopen("jugadores.txt","rb");
    if (jugadores==NULL) {
        cout << "Archivo de jugadores Inexistente" << endl;
    } else {
        cout << "JUGADORES:"<<endl;
        while (!feof(jugadores)) {
            fread(&a,sizeof(a),1,jugadores);
            if (!feof(jugadores)) {
                cont++;
                hayJugadores=true;
                cout<<"["<<cont<<"]"<<" -> "<<a.nickname<<endl;
            }
        }
    }
    reiniciar_selec_jug(js); //reinicio ocup=-1;
    if (hayJugadores) {
        cout<<"INGRESE UN NUMERO PARA SELECCIONAR UN JUGADOR:"<<endl;
        do {
            cin>>jugSeleccionado;
            if (jugSeleccionado>0 && jugSeleccionado<=cont) {
                selValida = seleccion_de_jug(jugadores, jugSeleccionado, js);
                if (selValida==true) {
                    contJugSel++;
                } else {
                    cout<<"ERROR: Este jugador ya fue seleccionado, elija otro."<<endl;
                    resp='s';
                }
            } else {
                cout<<"Numero invalido"<<endl;
            }
            if (contJugSel>=2 && selValida==true && contJugSel<MAX_JUG) {
                cout<<"Desea seleccionar mas jugadores? s/n"<<endl;
                cin>>resp;
            }
        } while (contJugSel<MAX_JUG && (resp=='s' || resp=='S'));
    } else {
        cout<<"No hay jugadores para mostrar."<<endl;
    }
    fclose(jugadores);
}


/** SELECCION DE JUGADOR
 *
 *  despues de mostrar la lista de jugadores el usuario elige uno ingresando un numero
 *  jugadores -> archivos de los jugadores registrados
 *  num -> numero ingresado por el usuario para elegir jugador
 *  js -> registro con un array de jugadores seleccionados
 *  usamos js para agregar un jugador y/o verificar si no se selecciono antes
 *  Retorna un booleano validando si el jugador se puede seleccionar o si ya fue seleccionado
 */
bool seleccion_de_jug(parchivo jugadores, int num, tjugselec &js) {
    int k=0, i;
    bool valido=true;
    tjugador jugador;
    jugadores=fopen("jugadores.txt", "rb");
    if (jugadores==NULL) {
        cout<<"Archivo de jugadores no existe"<<endl;
    } else {
        while (!feof(jugadores) && k<num) {
            fread(&jugador, sizeof(jugador), 1, jugadores);
            if (!feof(jugadores)) {
                k++;
                if (k==num) {
                    // valida si en el array ya se encuentra este jugador en caso de encontrar es porque ya se selecciono
                    for (i=0; i<=js.ocup; i++) {
                        if ( strcmp(js.jugadores[i].nickname, jugador.nickname)==0 )
                            return false;
                    }
                    if (valido==true) {
                        cout<<"Has seleccionado a "<<jugador.nickname<<endl;
                        js.ocup++;
                        js.jugadores[js.ocup]=jugador;
                    }
                }
            }
        }
    }
    fclose(jugadores);
    return valido;
}


/** INICIA EL ARREGLO DEL REGISTRO DE JUGADORES SELECCIONADOS */
void reiniciar_selec_jug(tjugselec &js) {
    js.ocup=-1;
}


/** REPARTIR CARTAS
 *  Reparte las cartas a los jugadores seleccionados para la partida
 *  js -> registro de jugadores seleccionados
 *  cola -> mazo de cartas
 */
void repartir_cartas(tjugselec &js, tcola &cola) {
    int i, j, aux=js.ocup;
    for (j=0; j<=aux; j++)
        iniciar_baraja(js.jugadores[j].baraja);

    for (i=0; i<MAX_BARAJA; i++) {
        for (j=0; j<=aux; j++)
            agregar_a_la_baraja(js.jugadores[j].baraja, quitar_cola(cola));
    }
}

/** PASA LA PRIMERA CARTA AL ULTIMO DEL MAZO */
void pasar_al_ultimo(tcola &lis) {
    tcarta carta = quitar_cola(lis);
    agregar_cola(lis, carta);
}




/** ---------------------- OPERACIONES DE LISTAS DOBLES ------------------------ */
/** --------------- LISTAS DOBLES PARA LA BARAJA DE CADA JUGADOR --------------- */


/** INICIAR BARAJA DE JUGADOR*/
void iniciar_baraja(tblista &lista) {
    lista.inicio=NULL;
    lista.fin=NULL;
    lista.contador=0;
}


/** CREACION DE UN NODO DE LISTAS DOBLES */
void crear_nodo_doble(pbaraja &nuevo, tcarta valor) {
    nuevo=new tbaraja;
    if (nuevo!=NULL) {
        nuevo->dato=valor;
        nuevo->sig=NULL;
        nuevo->ant=NULL;
    }
}


/** AGREGA AL FINAL DE LA LISTA UNA CARTA PARA LA BARAJA DEL JUGADOR */
void agregar_a_la_baraja(tblista &lista, tcarta carta) {
    pbaraja nuevo;
    if (lista.contador==MAX_BARAJA) {
        cout<<"BARAJA DE JUGADOR LLENA"<<endl;
    } else {
        crear_nodo_doble(nuevo, carta);
        if (lista.contador==0) {
            lista.inicio=nuevo;
            lista.fin=nuevo;
        } else {
            lista.fin->sig=nuevo;
            nuevo->ant=lista.fin;
            lista.fin=nuevo;
        }
        lista.contador++;
    }
}


/**
 *  VER BARAJA DE UN JUGADOR
 *
 *  lista de tipo tblista -> lista(baraja) de un jugador
 *  cola -> mazo de cartas
 *  Ve la primera carta del mazo
 *  Valida si la carta seleccionada es >= al de mazo
 */
bool ver_baraja(tblista &lista, tcola &cola) {

    bool poderExtraer=false;
    pbaraja i;
    int k=0;
    tcarta primera_carta = obtener_primera_carta(cola);
    int nro_pcdm = primera_carta.nro; // nro de primera carta del mazo
    int aux, nro_carta;

    cout<<"\nCARTA DE MAZO:";
    mostrar_carta_mazo(primera_carta);

    if (lista.contador>0) {
        cout<<"\nTU BARAJA:"<<endl;
        for (i=lista.inicio; i!=NULL; i=i->sig) {
            k++;
            mostrar_carta(i->dato, k);
            aux = i->dato.nro;
            if ( (aux>=nro_pcdm)==true || (aux>=1 && aux<=3)==true ) {
                poderExtraer=true;
            }
        }
    }
    return poderExtraer;
}


/** ELEGIR CARTA
 *
 *  verifica si existe alguna carta >= o comodin al del primero del mazo
 *  da a elegir al jugador que carta usar para extraer del mazo
 *  controla que el usuario elija entre las cartas que tiene
 *  ejecuta funcion quitar_a_la_baraja() a la baraja del jugador
 *  agrega a la pila de un jugador las cartas extraidas
 */
void elegir_carta(tblista &lista, tpila &pila, tcola &cola, bool extraer) {

    tcarta primera_carta = obtener_primera_carta(cola);

    int nro_pcdm = primera_carta.nro; // numero de primera carta del mazo
    tcarta carta_extraida;

    int nro_carta_elegida;
    int cant_cartas=0;
    int k, aux;
    bool band=false;

    pbaraja i;
    for (i=lista.inicio; i!=NULL; i=i->sig)
        cant_cartas++;

    if (cant_cartas==0) {
        cout<<"---Te quedaste sin cartas en tu baraja---"<<endl;
    } else {
        if (extraer==false) {
            cout<<"\n\n\n\nNO TIENES NINGUNA CARTA PARA EXTRAER DEL MAZO!!!"<<endl;
        } else {
            cout<<"\n\n\n\nPUEDES EXTRAER UNA CARTA DEL MAZO!!!"<<endl;
            do {
                cout<<"\nINGRESA UN NUMERO PARA SELECCIONAR UNA CARTA: ";
                cin>>nro_carta_elegida;

                if (nro_carta_elegida>=1 && nro_carta_elegida<=cant_cartas) {
                    k=1;
                    i=lista.inicio;
                    while (k<nro_carta_elegida) {
                        i=i->sig;
                        k++;
                    }
                    aux = i->dato.nro;
                    if ( (aux>=nro_pcdm) || (aux>=1 && aux<=3) ) {
                        carta_extraida = quitar_a_la_baraja(lista, nro_carta_elegida); //quita de la baraja del jugador
                        primera_carta = quitar_cola(cola); //quita del mazo

                        agregar_pila(pila, carta_extraida); //agrega a la pila del jugador la carta de la baraja extraida
                        agregar_pila(pila, primera_carta); // agrega a la pila del jugador la carta del mazo extraida

                        band=true;
                    } else {
                        cout<<"\nESTA CARTA ES MENOR A LA DEL MAZO, PRUEBA OTRA!!!"<<endl;
                        band=false;
                    }

                } else {
                    cout<<"ERROR: INGRESE UN NUMERO VALIDO PARA LA SELECCION..."<<endl;
                    band=false;
                }
            } while (band==false);
        }
    }
}


/** QUITAR UNA CARTA DE LA BARAJA (LISTA DOBLE)
 *  lista -> registro de punteros de la baraja de un jugador
 *  cartabuscada -> numero de carta seleccionada anteriormente para buscar y extraer
 */
tcarta quitar_a_la_baraja(tblista &lista, int cartabuscada) {

    pbaraja ext, i;
    tcarta cartaExtraida;
    int k;

    if (lista.contador==0) {
        cout<<"NO SE PUEDE EXTRAER, LA BARAJA DEL JUG ESTA VACIA"<<endl;
    } else {
        k=1;
        i=lista.inicio;
        while (k<cartabuscada) {
            i=i->sig;
            k++;
        }
        ext=i;
        if (ext==lista.inicio && ext==lista.fin) {
            lista.inicio=NULL;
            lista.fin=NULL;
            lista.contador--;
        } else {
            if (ext==lista.inicio) {
                lista.inicio=lista.inicio->sig;
                lista.inicio->ant=NULL;
                ext->sig=NULL;
                lista.contador--;
            } else {
                if (ext==lista.fin) {
                    lista.fin=lista.fin->ant;
                    lista.fin->sig=NULL;
                    ext->ant=NULL;
                    lista.contador--;
                } else {
                    (ext->sig)->ant = ext->ant;
                    (ext->ant)->sig = ext->sig;
                    ext->sig=NULL;
                    ext->ant=NULL;
                    lista.contador--;
                }
            }
        }
    }
    cartaExtraida = ext->dato;
    delete(ext);
    return cartaExtraida;
}


/** ACTUALIZA EN EL ARCHIVO DE JUGADORES EL GANADOR DE LA PARTIDA CON SUS PUNTOS GANADOS
 *
 *  jugadores -> archivo de los jugadores registrados
 *  jug_buscado -> jugador al que se buscara para sumarle sus puntos
 *  puntosGanados -> puntos ganados en la partida
 */
void actualizar_jugador(parchivo jugadores, tjugador jug_buscado, int puntosGanados) {

    bool encontrado=false;
    tjugador j;

    jugadores=fopen("jugadores.txt", "rb+");
    while (!feof(jugadores) && !encontrado) {
        fread(&j, sizeof(j), 1, jugadores);
        if (strcmp(j.nickname, jug_buscado.nickname)==0) {
            encontrado=true;
        }
    }
    if (!encontrado) {
        cout<<"Error al actualizar: El jugador no existe en el archivo"<<endl;
    } else {
        j.puntaje = j.puntaje + puntosGanados;
        fseek(jugadores, -sizeof(j), SEEK_CUR);
        fwrite(&j, sizeof(j), 1, jugadores);
    }
    fclose(jugadores);
}




/** --------------------- OPERACIONES DE PILA -----------------------*/
/** ESTA PILA ES USADA DONDE SE EXTRAERA LAS CARTAS DE LOS JUGADORES */


/** INICIAR PILA */
void iniciar_pila(tpila &pila) {
    pila.cima=-1;
}

/** PILA VACIA */
bool pila_vacia(tpila pila) {
    return pila.cima==-1;
}

/** PILA LLENA */
bool pila_llena(tpila pila) {
    return pila.cima==MAX_PILA-1;
}

/** AGREGAR LA PILA */
void agregar_pila(tpila &pila, tcarta nuevo) {
    if (pila_llena(pila)) {
        cout<<"Pila llena"<<endl;
    } else {
        pila.cima++;
        pila.contenedor[pila.cima]=nuevo;
    }
}

/** QUITAR A LA PILA */
tcarta quitar_pila(tpila &pila) {
    tcarta ext;
    if (pila_vacia(pila)) {
        cout<<"Pila vacia"<<endl;
    } else {
        ext=pila.contenedor[pila.cima];
        pila.cima--;
    }
    return ext;
}


/** MOSTRAR UNA PILA DE UN JUGADOR EN PANTALLA */
void mostrar_una_pila(tjugador j) {
    int n=0;
    tcarta aux;
    tpila pila_aux;
    iniciar_pila(pila_aux);
    while (!pila_vacia(j.pila)) {
        aux=quitar_pila(j.pila);
        agregar_pila(pila_aux, aux);
        n++;
        mostrar_carta(tope_pila(pila_aux), n);
    }
}

/** TOPE DE PILA */
tcarta tope_pila(tpila pila) {
    tcarta aux;
    aux.nro = -1;
    if (pila_vacia(pila))
        cout<<"Sin tope, pila vacia"<<endl;
    else
        aux=pila.contenedor[pila.cima];
    return aux;
}


/** CUENTA LOS PUNTOS EN TOTAL DE LAS CARTAS DENTRO DE LA PILA DE UN JUGADOR */
int contar_puntos(tjugador &jugador) {
    int i, puntos=0, cima=jugador.pila.cima;
    for (i=0; i<=cima; i++) {
        puntos = puntos+jugador.pila.contenedor[i].puntos;
    }
    return puntos;
}





/*********************************** MODULOS DE PRUEBA ***********************************/

/** MUESTRA LOS JUGADORES QUE FUERON SELECCIONADOS (dsp de selec jugadores) */
void mostrar_jug_seleccionados(tjugselec js) {
    int i;
    cout<<"\n\nJugadores seleccionados:"<<endl;
    for (i=0; i<=js.ocup; i++)
        cout<<"Jugador"<<i+1<<" -> "<<js.jugadores[i].nickname<<endl;

    cout<<"\n****************************"<<endl;
}

/** MUESTRA LAS BARAJAS DE LOS JUGADORES (dsp de repartir cartas) */
void mostrar_barajas(tjugselec js) {
    int i, k, aux=js.ocup;
    pbaraja j;

    cout<<"\nBARAJAS DE LOS JUGADORES"<<endl;
    for (i=0; i<=aux; i++) {

        cout<<"Jugador"<<i+1<<": "<<js.jugadores[i].nickname<<endl;
        k=0;
        for (j=js.jugadores[i].baraja.inicio; j!=NULL; j=j->sig) {
            k++;
            mostrar_carta(j->dato, k);
        }
        cout<<endl;
    }
}

/** MOSTRAR EL MAZO DE LISTAS SIMPLES */
void mostrar_mazo_de_listas(tcola &cola) {
    int n=0;
    pnodo i;
    tcarta aux;
    tcola cola_aux;
    iniciar_cola(cola_aux);
    while (!cola_vacia(cola)) {
        aux = quitar_cola(cola);
        agregar_cola(cola_aux, aux);
        n++;
        mostrar_carta(obtener_ultima_carta(cola_aux), n);
    }
    while (!cola_vacia(cola_aux)) {
        aux = quitar_cola(cola_aux);
        agregar_cola(cola, aux);
    }
}

/** MOSTRAR PILAS DE LOS JUGADORES SELECCIONADOS (usar dsp de jugar una partida) */
void mostrar_pilas(tjugselec &js) {
    int i, m=js.ocup;
    for(i=0; i<=m; i++) {
        cout<<"\nCartas del jugador: "<<js.jugadores[i].nickname<<endl;
        mostrar_una_pila(js.jugadores[i]);
    }
}
