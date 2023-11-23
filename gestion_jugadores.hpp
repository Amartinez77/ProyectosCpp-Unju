//gestion de jugadores




typedef FILE *parchivo;


void menu_gestion_jugador(int &opc);
void gestion_jugador(parchivo jugadores);
void agregar_jugador(parchivo jugadores);
void carga_reg(tjugador &j, bool modificacion);
void consulta_jugador(parchivo jugadores);
void buscar_jugador(parchivo jugadores, tcad buscado);
void modificar_jugador(parchivo jugadores, tcad buscado);
void eliminar_jugador(parchivo jugadores, tcad buscado);
bool existe_jugador(parchivo jugadores, tcad buscado);
int cantidad_jugadores(parchivo f);

//void agregar_jugador_rank(parchivo jugadores);
//void carga_reg_rank(tjugador &j);


void menu_gestion_jugador(int &opc){

    cout<<"gestion de jugadores"<<endl;
    cout<<"1 - Agregar jugador"<<endl;
    cout<<"2 - Buscar jugador"<<endl;
    cout<<"3 - Listar jugadores "<<endl;
    cout<<"4 - modificar jugadores"<<endl;
    cout<<"5 - eliminar jugador"<<endl;
    cout<<"6 - cantidad de jugadores registrados(prueba)"<<endl;
    cout<<"7 - Agregar solo para el ranking dsps borrar"<<endl;
    cout<<"9 - Salir"<<endl;
    cin>>opc;


}

void gestion_jugador(parchivo jugadores){

    int opc, aux;
    tcad buscado;
    bool resp;

    do{

        system("cls");
        menu_gestion_jugador(opc);

        switch(opc){

        case 1: cout<<"Agregar Jugador"<<endl;

                agregar_jugador(jugadores);

            break;

        case 2: cout<<"Buscar Jugador"<<endl;
                cout<<"ingrese el nickname del jugador a buscar"<<endl;
                fflush(stdin);
                gets(buscado);
                buscar_jugador(jugadores, buscado);
            break;

        case 3: cout<<"Consultar Jugador"<<endl;
                consulta_jugador(jugadores);
            break;

        case 4: cout<<"modificar Jugador"<<endl;
                cout<<"ingrese el nickname del jugador a modificar"<<endl;
                fflush(stdin);
                gets(buscado);
                modificar_jugador(jugadores, buscado);

            break;

        case 5: cout<<"Eliminar Jugador"<<endl;
                fflush(stdin);
                gets(buscado);
                eliminar_jugador(jugadores, buscado);

            break;

        /* case 6: cout<<"cantidad"<<endl;
                aux=cantidad_jugadores(jugadores);
                cout<<"la cantidad de jugadores registrados es "<<aux<<endl;
            break;

        case 7: cout<<"Agregar Jugador (solo para probar ranking)"<<endl;
                cout<<"ingrese el nickname del jugador a modificar"<<endl;
                fflush(stdin);
                gets(buscado);
                agregar_jugador_rank(jugadores);

            break; */


        case 9: cout<<"Hasta luego"<<endl;
            break;

        default: cout<<"opcion incorrecta"<<endl;
            break;

        }

    system("pause");


    }while(opc!=9);


}



void carga_reg(tjugador &j, bool modificacion) {
    tcad aux1;
    int auxpart, auxpunt;

    strcpy(aux1, j.nickname);
    auxpart = j.p_ganadas;
    auxpunt = j.puntaje;

    if (modificacion) {
        cout << "Ingrese su nombre: ";
        fflush(stdin);
        gets(j.nombre);

        // Validar que el nombre no est� vac�o
        while (strlen(j.nombre) == 0) {
            cout << "El nombre no puede estar vacio. Ingreselo nuevamente: ";
            gets(j.nombre);
        }

        cout << "Ingrese su apellido: ";
        gets(j.apellido);

        // Validar que el apellido no est� vac�o
        while (strlen(j.apellido) == 0) {
            cout << "El apellido no puede estar vacio. Ingreselo nuevamente: ";
            gets(j.apellido);
        }

        strcpy(j.nickname, aux1);
        j.p_ganadas = auxpart;
        j.puntaje = auxpunt;
    } else {
        cout << "Ingrese Nickname: ";
        fflush(stdin);
        gets(j.nickname);

        // Validar que el nickname no est� vac�o
        while (strlen(j.nickname) == 0) {
            cout << "El nickname no puede estar vac�o. Ingr�selo nuevamente: ";
            gets(j.nickname);
        }

        cout << "Ingrese su nombre: ";
        gets(j.nombre);

        // Validar que el nombre no est� vac�o
        while (strlen(j.nombre) == 0) {
            cout << "El nombre no puede estar vac�o. Ingr�selo nuevamente: ";
            gets(j.nombre);
        }

        cout << "Ingrese su apellido: ";
        gets(j.apellido);

        // Validar que el apellido no est� vac�o
        while (strlen(j.apellido) == 0) {
            cout << "El apellido no puede estar vac�o. Ingr�selo nuevamente: ";
            gets(j.apellido);
        }

        j.puntaje = 0;
        j.p_ganadas = 0;
    }
}



void agregar_jugador(parchivo jugadores){

    tjugador j;
    bool modificacion=false;

    char rta;

    jugadores=fopen("jugadores.txt", "ab+");

    do{

        carga_reg(j, modificacion);
        if (existe_jugador(jugadores, j.nickname)){
            cout<<"ya existe jugador!"<<endl;
        }else{
            fwrite(&j, sizeof(j), 1, jugadores);
        }

        cout<<"desea ingresar mas jugadores s/n "<<endl;
        cin>>rta;

    }while(rta!='N' && rta!='n');

    fclose(jugadores);

}

void consulta_jugador(parchivo jugadores){

    tjugador a;

    jugadores=fopen("jugadores.txt","rb");
    if (jugadores==NULL)
        cout << "Archivo Inexistente" << endl;
    else
    {
        while (!feof(jugadores))
        {
            fread(&a,sizeof(a),1,jugadores);
            if (!feof(jugadores))
            {
                cout << "\nNickname: " << a.nickname << endl;
                cout << "Nombre: " << a.nombre << endl;
                cout << "Apellido: " << a.apellido << endl;
                cout << "Puntaje: " << a.puntaje << endl;
            }
        }
    }
    fclose(jugadores);

}

void buscar_jugador(parchivo jugadores, tcad buscado){

    tjugador a;
    bool encontrado=false;
    jugadores=fopen("jugadores.txt", "rb");

    if(jugadores==NULL){
        cout<<"archivo inexistente"<<endl;
    }else{

        while(!feof(jugadores) && encontrado==false){

            fread(&a,sizeof(a),1,jugadores);

            if(strcmp(a.nickname, buscado)==0){
                cout<<"nickname: "<<a.nickname<<endl;
                cout<<"nombre: "<<a.nombre<<endl;
                cout<<"apellido: "<<a.apellido<<endl;
                cout<<"partidas ganadas: "<<a.p_ganadas<<endl;
                cout<<"puntaje: "<<a.puntaje<<endl;
                encontrado=true;
            }

        }

        if(!encontrado){
            cout<<"No se encontro el jugador"<<endl;
        }

    }



    fclose(jugadores);

}

void modificar_jugador(parchivo f, tcad buscado){

    tjugador p;
    bool band=true, modificacion;

    f=fopen("jugadores.txt", "rb+");

    if(f==NULL){
        cout<<"Archivo inexistente"<<endl;
    }else{

        while(!feof(f) && !band){
            fread(&p, sizeof(p), 1, f);

            if(p.nickname==buscado){
                band=true;
            }
        }

        if (band==true)
        {
            modificacion=true;
            carga_reg(p, modificacion);
            //fseek(f,-sizeof(p),1);
            fseek(f,-sizeof(p),SEEK_CUR);
            fwrite(&p,sizeof(p),1,f);
        }
        else
            cout << "REGISTRO NO ENCONTRADO" << endl;

    }

    fclose(f);

}

void eliminar_jugador(parchivo f, tcad buscado){

    tjugador a;
    parchivo aux;
    bool band=false;
    f=fopen("jugadores.txt","rb");
    aux=fopen("temporal.txt","w");

    if (f!=NULL)
    {
        while (!feof(f))
        {
            fread(&a,sizeof(a),1,f);
            if (strcmp(a.nickname, buscado) != 0 && !feof(f))
                fwrite(&a,sizeof(a),1,aux);
        }
        fclose(aux);
        fclose(f);
        if (remove("jugadores.txt")==0)
        {
            cout << "ELIMINADO EXITOSAMENTE" << endl;
            if (rename("temporal.txt","jugadores.txt")==0)
                cout << "RENOMBRADO EXITOSAMENTE" << endl;
            else
                cout << "ERROR AL RENOMBRAR" << endl;
        }
        else
            cout << "ERROR AL ELIMINAR" << endl;
    }



}


bool existe_jugador(parchivo jugadores, tcad buscado){

    tjugador a;
    bool encontrado=false;
    jugadores=fopen("jugadores.txt", "rb");

    if(jugadores==NULL){
        cout<<"archivo inexistente"<<endl;
        return false;
    }

        while(!feof(jugadores) && encontrado==false){

            fread(&a,sizeof(a),1,jugadores);

            if(strcmp(a.nickname, buscado)==0){
                encontrado=true;
            }
        }




    fclose(jugadores);
    cout<<encontrado;
    return encontrado;
}

int cantidad_jugadores(parchivo f) {
    tjugador letra;
    int cont = 0;

    f = fopen("jugadores.txt", "rb");

    if (f == NULL) {
        cout << "Error al abrir el archivo." << endl;
        return -1;  // Si falla devuelve -1
    }

    while (fread(&letra, sizeof(letra), 1, f) == 1) {
        cont++;
    }

    fclose(f);

    return cont;
}

//*********************

/*
void agregar_jugador_rank(parchivo jugadores){

    tjugador j;
    bool modificacion=false;

    char rta;

    jugadores=fopen("jugadores.txt", "ab+");

    do{

        carga_reg_rank(j);
        if (existe_jugador(jugadores, j.nickname)){
            cout<<"ya existe jugador!"<<endl;
        }else{
            fwrite(&j, sizeof(j), 1, jugadores);
        }

        cout<<"desea ingresar mas jugadores s/n "<<endl;
        cin>>rta;

    }while(rta!='N' && rta!='n');

    fclose(jugadores);



}


void carga_reg_rank(tjugador &j){

    tcad aux1;
    int auxpart, auxpunt;

    //strcpy(aux1, j.nickname);
    //auxpart = j.p_ganadas;
    //auxpunt = j.puntaje;


        cout << "Ingrese Nickname: ";
        fflush(stdin);
        gets(j.nickname);

        // Validar que el nickname no esté vacío
        while (strlen(j.nickname) == 0) {
            cout << "El nickname no puede estar vacío. Ingréselo nuevamente: ";
            gets(j.nickname);
        }

        cout << "Ingrese su nombre: ";
        gets(j.nombre);

        // Validar que el nombre no esté vacío
        while (strlen(j.nombre) == 0) {
            cout << "El nombre no puede estar vacío. Ingréselo nuevamente: ";
            gets(j.nombre);
        }

        cout << "Ingrese su apellido: ";
        gets(j.apellido);

        // Validar que el apellido no esté vacío
        while (strlen(j.apellido) == 0) {
            cout << "El apellido no puede estar vacío. Ingréselo nuevamente: ";
            gets(j.apellido);
        }

        cout << "Ingrese su el puntaje: ";
        cin>>j.puntaje;

        // Validar que el apellido no esté vacío
        while (j.puntaje == 0) {
            cout << "El puntaje no puede estar vacío. Ingréselo nuevamente: ";
            cin>>j.puntaje;
        }

        cout << "Ingrese partidas ganadas: ";
        cin>>j.p_ganadas;

        // Validar que el apellido no esté vacío
        while (j.p_ganadas == 0) {
            cout << "Partidas ganadas no puede estar vacío. Ingréselo nuevamente: ";
            cin>>j.p_ganadas;
        }

} */
