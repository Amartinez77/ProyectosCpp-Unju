


typedef tjugador tjugcontenedor[MAX_JUG];
typedef struct tjugselec{
    tjugcontenedor jugadores;
    int ocup;
};


void menu_juego();
void gestion_juego(mazo_aux mazo, parchivo jugadores, tcola &cola, bool mazo_nuevo);
void listar_jugadores(parchivo jugadores, tjugselec &js);
bool seleccion_de_jug(parchivo jugadores, int num, tjugselec &js);
void reiniciar_selec_jug(tjugselec &js);

void repartir_cartas(tjugselec &js, tcola &cola);

void mostrar_jug_seleccionados(tjugselec js);

void mostrar_mazo_de_listas(tcola cola);

void mostrar_barajas(tjugselec js);
void pasar_al_ultimo(tcola &lis);


/** ------------ operaciones listas dobles de la baraja del jugador ------------ */
void iniciar_baraja(tblista &lista);
void crear_nodo_doble(pbaraja &nuevo, tcarta valor);
void agregar_a_la_baraja(tblista &lista, tcarta carta);
bool ver_baraja(tblista &lista, tcola &cola);
void elegir_carta(tblista &lista, tpila &pila, tcola &cola, bool extraer);
tcarta quitar_a_la_baraja(tblista &lista, int cartabuscada);

/** operaciones de pila (pila donde se extraen las cartas de un jugador) */
void iniciar_pila(tpila &pila);
bool pila_vacia(tpila pila);
bool pila_llena(tpila pila);
void agregar_pila(tpila &pila, tcarta nuevo);
tcarta quitar_pila(tpila &pila);
void mostrar_pilas(tjugselec &js);
void mostrar_una_pila(tjugador j);

int contar_puntos(tjugador &jugador);

void actualizar_jugador(parchivo jugadores, tjugador jug_buscado, int puntosGanados);


void menu_juego() {
    cout<<"*** MENU DE JUEGO ***"<<endl;
    cout<<"1 - Elegir jugadores"<<endl;
    cout<<"2 - Repartir cartas"<<endl;
    cout<<"3 - Iniciar la partida"<<endl;
    cout<<"4 - (testeo) mostrar jugadores seleccionados (array)"<<endl;
    cout<<"5 - (testeo) mostrar mazo (lista simple)"<<endl;
    cout<<"6 - (testeo) mostrar baraja de cada jugador (listas dobles)"<<endl;
    cout<<"7 - (testeo) mostrar pila de cada jugador (tpila)"<<endl;
    cout<<"9 - Volver al menu principal"<<endl;
}

void gestion_juego(mazo_aux mazo, parchivo jugadores, tcola &cola, bool mazo_nuevo) {

    tjugselec js;
    tjugador jug_aux;
    int opcion;
    int i, j, m, pts, maxpts;
    int cant_jug;

    bool pextraer; // puede extraer
    bool nueva_partida=false;
    bool cartas_repartidas=false;
    bool jugadores_elegidos=false;
    bool jug_con_cartas, juego_continua, empate, encontrado=false;

    do {
        system("cls");
        menu_juego();
        cin>>opcion;
        switch (opcion) {

            case 1: cout<<"funcion listar_jugadores()"<<endl;
                    listar_jugadores(jugadores, js);
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
                        cout<<"Primero debe repartir las cartas"<<endl;
                    } else {
                        cout<<"\n*** COMIENZA LA PARTIDA ***\n\n"<<endl;
                        cartas_repartidas=false;
                        jugadores_elegidos=false;
                        mazo_nuevo=false;
                        system("pause");
                        cant_jug = js.ocup;

                        if (nueva_partida==true) {
                            for (i=0; i<=cant_jug; i++) {
                                iniciar_pila(js.jugadores[i].pila);
                                js.jugadores[i].pts_partida=0;
                            }
                            nueva_partida=false;
                            empate=false;
                        }


                        juego_continua=true;
                        jug_con_cartas=true;
                        while (jug_con_cartas==true || juego_continua==true) {
                            m=cola.cont;
                            juego_continua=false;
                            jug_con_cartas=false;

                            /**recorrido de los jugadores que estan jugando la partida*/
                            for (i=0; i<=cant_jug; i++) {
                                system("cls");
                                //si aun tiene cartas en la baraja toma su turno
                                if (js.jugadores[i].baraja.contador>0) {
                                    jug_con_cartas=true;
                                    juego_continua=true;
                                    cout<<"ES EL TURNO DE: "<<js.jugadores[i].nickname<<endl;

                                    pextraer = ver_baraja(js.jugadores[i].baraja, cola);
                                    elegir_carta(js.jugadores[i].baraja, js.jugadores[i].pila, cola, pextraer);

                                    if (js.jugadores[i].baraja.contador==0) {
                                        cout<<"Te acabas de quedar sin cartas!!"<<endl;
                                        //jug_con_cartas=false;
                                    }

                                    cout<<"Pasando al siguiente turno..."<<endl;
                                    system("pause");
                                } else {
                                    cout<<"*** El jugador: "<<js.jugadores[i].nickname<<" ya no tiene cartas en su baraja ***"<<endl;
                                    system("pause");
                                }

                                if (js.jugadores[i].baraja.contador==0) {
                                    pts=0;
                                    pts=contar_puntos(js.jugadores[i]);
                                    js.jugadores[i].pts_partida = pts;
                                    //system("pause");
                                }
                            }

                            //si ninguno modifica el cont del mazo(cola) es xq ninguno pudo estraer y pasa al ultimo
                            if (m==cola.cont && jug_con_cartas==true) {
                                juego_continua=true;
                                cout<<"\n*** NINGUNO DE LOS JUGADORES PUDO SACAR DEL MAZO ***"<<endl;
                                cout<<"** Pasando carta al final del mazo **"<<endl;
                                pasar_al_ultimo(cola);
                                system("pause");
                            }
                        }

                        system("cls");
                        /** al momento que finaliza la partida */
                        cout<<"PUNTOS ALCANZADOS POR LOS JUGADORES"<<endl;
                        maxpts=-1;
                        for (i=0; i<=cant_jug; i++) {
                            pts = js.jugadores[i].pts_partida;
                            cout<<js.jugadores[i].nickname<<": "<<pts<<"pts."<<endl;
                            mostrar_una_pila(js.jugadores[i]);
                            cout<<"-----------------------"<<endl;
                            if (maxpts < pts) {
                                maxpts = pts;
                                jug_aux = js.jugadores[i];
                            }
                        }

                        //buscar si hubo empate
                        empate=false;
                        for (i=0; i<=cant_jug && !empate; i++) {
                            //cout<<js.jugadores[i].pts_partida<<endl;
                            if (strcmp(jug_aux.nickname,js.jugadores[i].nickname)!=0 && jug_aux.pts_partida==js.jugadores[i].pts_partida) {
                                cout<<"\nHubo un empate entre "<<jug_aux.nickname<<" y "<<js.jugadores[i].nickname<<" de "<<maxpts<<"pts."<<endl;
                                empate=true;
                                system("pause");
                            }
                        }

                        encontrado=false;
                        if (empate==true) {
                            i--;
                            cout<<"\nLOS GANADORES SON "<<jug_aux.nickname<<" Y "<<js.jugadores[i].nickname<<endl;
                            js.jugadores[i].puntaje = js.jugadores[i].puntaje + maxpts;

                            for (j=0; j<=cant_jug && !encontrado; j++) {
                                if ( strcmp(jug_aux.nickname, js.jugadores[j].nickname)==0 ) {
                                    encontrado=true;
                                    js.jugadores[j].puntaje = js.jugadores[j].puntaje + maxpts;
                                }
                            }
                            j--;
                            actualizar_jugador(jugadores, js.jugadores[i], maxpts);
                            actualizar_jugador(jugadores, js.jugadores[j], maxpts);
                            //cout<<"**(debug) se le asigno los puntos a "<<js.jugadores[i].nickname<<" y "<<js.jugadores[j].nickname<<" "<<maxpts<<"pts."<<endl;

                        } else {
                            cout<<"\nEL GANADOR ES "<<jug_aux.nickname<<" CON "<<maxpts<<"pts."<<endl;
                            for(i=0; i<=cant_jug; i++) {
                                if ( strcmp(jug_aux.nickname, js.jugadores[i].nickname)==0 ) {
                                    js.jugadores[i].puntaje = js.jugadores[i].puntaje + maxpts;
                                    actualizar_jugador(jugadores, js.jugadores[i], maxpts);
                                    //cout<<"**(debug) se le asigno los puntos a "<<js.jugadores[i].nickname<<" "<<maxpts<<"pts."<<endl;
                                }
                            }
                        }
                    }
                    break;

            case 4: mostrar_jug_seleccionados(js);
                    break;

            case 5: mostrar_mazo_de_listas(cola);
                    break;

            //testeo
            case 6: mostrar_barajas(js);
                    break;

            //testeo
            case 7: mostrar_pilas(js);
                    break;

            case 9: cout<<"Volviendo al menu principal"<<endl;
                    break;
        }
        if (opcion!=9)
            system("pause");
    } while (opcion!=9);
}

void listar_jugadores(parchivo jugadores, tjugselec &js) {

    tjugador a;
    char resp='s';
    int cont=0, jugSeleccionado, contJugSel=0;
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
                //cout<<cont<<" -> "<<a.nickname<<endl;
                cout<<cont<<" -> "<<a.nickname<<" pts: "<<a.puntaje<<endl;
            }
        }
    }
    reiniciar_selec_jug(js); //reinicio ocup=-1;
    if (hayJugadores==true) {
        cout<<"SELECCIONE UN JUGADOR POR SU NUMERO:"<<endl;
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

bool seleccion_de_jug(parchivo jugadores, int num, tjugselec &js) {

    bool valido=true;
    int k=0, i;
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
                    /** valida si en el array ya se encuentra este jugador
                        en caso de encontrar es xq ya se selecciono */
                    for (i=0; i<=js.ocup; i++) {
                        if ( strcmp(js.jugadores[i].nickname, jugador.nickname)==0 ) {
                            return false;
                        }
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

void reiniciar_selec_jug(tjugselec &js) {
    js.ocup=-1;
}

void mostrar_jug_seleccionados(tjugselec js) {
    int i;
    cout<<"\n\nJugadores seleccionados:"<<endl;
    for (i=0; i<=js.ocup; i++)
        cout<<"Jugador"<<i+1<<" -> "<<js.jugadores[i].nickname<<endl;

    cout<<"\n****************************"<<endl;
}

void mostrar_mazo_de_listas(tcola cola) {
    pnodo i;
    int n=0;
    for (i=cola.inicio; i!=NULL; i=i->sig) {
        n++;
        mostrar_carta(i->datos, n);
    }
}

/** ejecuta agregar_a_la_baraja() */
void repartir_cartas(tjugselec &js, tcola &cola) {

    int i, j, aux=js.ocup;

    for (j=0; j<=aux; j++) {
        iniciar_baraja(js.jugadores[j].baraja);
    }

    for (i=0; i<MAX_BARAJA; i++) {
        for (j=0; j<=aux; j++) {
            //js.jugadores[j].baraja[i] = quitar_cola(cola);
            agregar_a_la_baraja( js.jugadores[j].baraja, quitar_cola(cola) );
        }
    }
}

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

/** ------------ operaciones listas dobles de la baraja del jugador ------------ */

void iniciar_baraja(tblista &lista) {
    lista.inicio=NULL;
    lista.fin=NULL;
    lista.contador=0;
}

/** Creaci�n de un nodo de lista doble */
void crear_nodo_doble(pbaraja &nuevo, tcarta valor) {
    nuevo=new tbaraja;
    if (nuevo!=NULL) {
        nuevo->dato=valor;
        nuevo->sig=NULL;
        nuevo->ant=NULL;
    }
}

void agregar_a_la_baraja(tblista &lista, tcarta carta) {
    pbaraja nuevo;
    if (lista.contador==MAX_BARAJA) {
        cout<<"BARAJA DE JUGADOR LLENA"<<endl;
    } else {
        crear_nodo_doble(nuevo, carta);
        if (lista.contador==0) {
            lista.inicio=nuevo;
            lista.fin=nuevo;
            lista.contador++;
        } else {
            lista.fin->sig=nuevo;
            nuevo->ant=lista.fin;
            lista.fin=nuevo;
            lista.contador++;
        }
    }
}

/**
 * ver baraja del jugador
 * ver la primera carta del mazo
 * valida si tienes una carta >= al del mazo
 */
bool ver_baraja(tblista &lista, tcola &cola) {

    bool poderExtraer=false; //validar si tienes una carta >= al del mazo

    pbaraja i;
    int k=0;

    tcarta primera_carta = obtener_primera_carta(cola);

    int nro_pcdm = primera_carta.nro; // nro de primera carta del mazo
    int aux, nro_carta;

    cout<<"\nCARTA DE MAZO:"<<endl;
    mostrar_carta(primera_carta, 1);
    cout<<endl;

    if (lista.contador>0) {
        cout<<"TU BARAJA:"<<endl;
        for (i=lista.inicio; i!=NULL; i=i->sig) {
            k++;
            mostrar_carta(i->dato, k);
            aux = i->dato.nro;
            if ( (aux>=nro_pcdm)==true || (aux>=1 && aux<=3)==true ) {
                poderExtraer=true;
            }
        }
    } else {
        cout<<"Te quedaste sin cartas en tu baraja"<<endl;
    }

    return poderExtraer;

}


/**
 * da a elegir al jugador que carta usar para extraer del mazo
 * ejecuta funcion quitar_a_la_baraja() a la baraja del jugador
 */
void elegir_carta(tblista &lista, tpila &pila, tcola &cola, bool extraer) {

    tcarta primera_carta = obtener_primera_carta(cola);
    //tcarta primera_carta = quitar_cola(cola);

    int nro_pcdm = primera_carta.nro; // nro de primera carta del mazo
    tcarta carta_extraida;

    int nro_carta_elegida;
    int cant_cartas=0;
    int k, aux;
    bool band=false;

    pbaraja i;
    for (i=lista.inicio; i!=NULL; i=i->sig) {
        cant_cartas++;
    }

    if (cant_cartas==0) {
        cout<<"Te quedaste sin cartas en tu baraja"<<endl;
    } else {
        if (extraer==false) {
            cout<<"\nNO TIENE NINGUNA CARTA MAYOR O IGUAL AL DEL MAZO"<<endl;

        } else {

            cout<<"\nPUEDES EXTRAER UNA CARTA DEL MAZO!!!"<<endl;

            do {
                cout<<"SELECCIONA UNA CARTA: ";
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

                        agregar_pila(pila, carta_extraida);
                        agregar_pila(pila, primera_carta);

                        band=true;
                    } else {
                        cout<<"ESTA CARTA ES MENOR A LA DEL MAZO, PRUEBA OTRA"<<endl;
                        band=false;
                    }

                } else {
                    cout<<"ERROR: Seleccione un numero de carta valido..."<<endl;
                    band=false;
                }
            } while (band==false);
        }
    }
}

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
            //cout<<"llegue a pasar hasta despues de ext==lista.inicio && ext==lista.fin"<<endl;
            lista.inicio=NULL;
            lista.fin=NULL;
            lista.contador--;
        } else {
            if (ext==lista.inicio) {
                //cout<<"llegue a pasar hasta despues de ext==lista.inicio"<<endl;
                lista.inicio=lista.inicio->sig;
                lista.inicio->ant=NULL;
                ext->sig=NULL;
                lista.contador--;
            } else {
                if (ext==lista.fin) {
                    //cout<<"llegue a pasar hasta despues de ext==lista.fin"<<endl;
                    lista.fin=lista.fin->ant;
                    lista.fin->sig=NULL;
                    ext->ant=NULL;
                    lista.contador--;
                } else {
                    //cout<<"llegue a pasar hasta despues de ELSE"<<endl;
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

/** operaciones de pila (pila donde se extraen las cartas de un jugador) */

void iniciar_pila(tpila &pila) {
    pila.cima=-1;
}

bool pila_vacia(tpila pila) {
    return pila.cima==-1;
}

bool pila_llena(tpila pila) {
    return pila.cima==MAX_PILA-1;
}

void agregar_pila(tpila &pila, tcarta nuevo) {
    if (pila_llena(pila)) {
        cout<<"Pila llena"<<endl;
    } else {
        pila.cima++;
        pila.contenedor[pila.cima]=nuevo;
    }
}

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

void mostrar_pilas(tjugselec &js) {

    int i, j, k, m=js.ocup, p;
    for(i=0; i<=m; i++) {
        cout<<"\nCartas del jugador: "<<js.jugadores[i].nickname<<endl;
        k=0;
        p=js.jugadores[i].pila.cima;
        for (j=0; j<=p; j++) {
            k++;
            mostrar_carta(js.jugadores[i].pila.contenedor[j], k);
        }
    }
}

void mostrar_una_pila(tjugador j) {
    int i, k=0, cima=j.pila.cima;
    for (i=0; i<=cima; i++) {
        k++;
        mostrar_carta(j.pila.contenedor[i], k);
    }

}

void pasar_al_ultimo(tcola &lis) {
    pnodo aux;
    tcarta valor;
    //aux = obtener_primera_carta(lis);
    valor = quitar_cola(lis);
    crear(aux, valor);

    lis.fin->sig=aux;
    lis.fin=aux;
    aux=NULL;
    lis.cont++; //mantener el mismo conteo que le resto el quitar_cola()
    //delete(aux);

    //testeo
    cout<<"*** LA CARTA FUE PASADO AL ULTIMO DEL MAZO ***"<<endl;
}

int contar_puntos(tjugador &jugador) {
    int puntos=0, i, cima=jugador.pila.cima;
    for (i=0; i<=cima; i++) {
        puntos = puntos+jugador.pila.contenedor[i].puntos;
    }
    //cout<<"(debug)Puntos alcanzados por "<<jugador.nickname<<": "<<puntos<<"pts."<<endl;
    return puntos;
}

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

