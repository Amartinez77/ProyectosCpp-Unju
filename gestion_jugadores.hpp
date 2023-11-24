//gestion de jugadores




typedef FILE *parchivo;
#include "colors.h"

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


// Menu de opciones de gestion de jugadores
void menu_gestion_jugador(int &opc){

    cout<< BLACK <<"****   gestion de jugadores   ****"<<endl;
    cout << endl;
    cout<<" 1 - Agregar jugador"<<endl;
    cout<<" 2 - Buscar jugador"<<endl;
    cout<<" 3 - Listar jugadores "<<endl;
    cout<<" 4 - modificar jugadores"<<endl;
    cout<<" 5 - eliminar jugador"<<endl;
    cout<<" 9 - Salir"<<endl;
    cin>>opc;


}

// Procedimiento principal de gestion de jugadores
void gestion_jugador(parchivo jugadores){

    int opc, aux;
    tcad buscado;
    bool resp;

    do{

        system("cls");
        system("title El Corazon de la reina !!!  - Menu de Jugadores");
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
    int auxpart=0, auxpunt=0;
    fflush(stdin);
    strcpy(aux1, j.nickname);
    auxpart = j.p_ganadas;
    auxpunt = j.puntaje;

    if (modificacion) {
        cout << "Ingrese su nombre: ";
        fflush(stdin);
        gets(j.nombre);

        // Validar que el nombre no este vacio
        while (strlen(j.nombre) == 0) {
            cout << "El nombre no puede estar vacio. Ingreselo nuevamente: ";
            fflush(stdin);
            gets(j.nombre);
        }

        cout << "Ingrese su apellido: ";
        fflush(stdin);
        gets(j.apellido);

        // Validar que el apellido no este vacio
        while (strlen(j.apellido) == 0) {
            cout << "El apellido no puede estar vacio. Ingreselo nuevamente: ";
            fflush(stdin);
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
            fflush(stdin);
            gets(j.nickname);
        }

        cout << "Ingrese su nombre: ";
        fflush(stdin);
        gets(j.nombre);

        // Validar que el nombre no est� vac�o
        while (strlen(j.nombre) == 0) {
            cout << "El nombre no puede estar vac�o. Ingr�selo nuevamente: ";
            fflush(stdin);
            gets(j.nombre);
        }

        cout << "Ingrese su apellido: ";
        fflush(stdin);
        gets(j.apellido);

        // Validar que el apellido no est� vac�o
        while (strlen(j.apellido) == 0) {
            cout << "El apellido no puede estar vac�o. Ingr�selo nuevamente: ";
            fflush(stdin);
            gets(j.apellido);
        }

        j.puntaje = 0;
        j.p_ganadas = 0;
    }
}


/*
Procedimiento que carga los registros de jugadores a un archivo(no agrega repetidos)
para esto llama a la funcion existe_jugador
*/ 
void agregar_jugador(parchivo jugadores){

    tjugador j;
    bool modificacion=false;

    char rta;

    jugadores=fopen("jugadores.txt", "ab+");

    do{

        carga_reg(j, modificacion);
        if (existe_jugador(jugadores, j.nickname)){
            cout<<RED<<"ya existe jugador! - Intente nuevamente"<<endl;
        }else{
            fwrite(&j, sizeof(j), 1, jugadores);
            cout << GREEN << " Jugador agregado correctamente !" << endl;
        }

        cout<<BLACK<<"Desea ingresar mas jugadores s/n "<<endl;
        cin>>rta;

    }while(rta!='N' && rta!='n');

    fclose(jugadores);

}




// Procedimiento para listar los juegares

void consulta_jugador(parchivo jugadores){

    tjugador a;

    jugadores=fopen("jugadores.txt","rb");
    if (jugadores==NULL)
        cout << RED << "Archivo Inexistente" << endl;
    else
    {
        cout << MAGENTA << " ---    Listado de Jugadores Registrados    --- " << endl;
        while (!feof(jugadores))
        {
            fread(&a,sizeof(a),1,jugadores);
            if (!feof(jugadores))
            {
                cout << GREEN << "Nickname: " << a.nickname << endl;
                cout << BLACK << "Nombre: " << a.nombre << endl;
                cout << BLACK << "Apellido: " << a.apellido << endl;
                if(a.puntaje==0){
                    cout << RED << "Puntaje: " << a.puntaje << endl;
                }else{
                    cout << BLUE << "Puntaje: " << a.puntaje << endl;
                }
                
            }
        }
    }
    fclose(jugadores);

}


//Procedimiento de busqueda de jugadores

void buscar_jugador(parchivo jugadores, tcad buscado){

    tjugador a;
    bool encontrado=false;
    jugadores=fopen("jugadores.txt", "rb");

    if(jugadores==NULL){
        cout << RED << "Archivo Inexistente" << endl;
    }else{

        while(!feof(jugadores) && encontrado==false){

            fread(&a,sizeof(a),1,jugadores);

            if(strcmp(a.nickname, buscado)==0){
                cout<< BLUE <<"nickname: "<<a.nickname<<endl;
                cout<< BLACK <<"nombre: "<<a.nombre<<endl;
                cout<<"apellido: "<<a.apellido<<endl;
                cout<<"partidas ganadas: "<<a.p_ganadas<<endl;
                
                if(a.puntaje==0){
                    cout << RED << "Puntaje: " << a.puntaje << endl;
                }else{
                    cout << BLUE << "Puntaje: " << a.puntaje << endl;
                    cout << BLACK << endl;
                }
                
                encontrado=true;
            }

        }

        if(!encontrado){
            cout<< RED <<"No se encontro el jugador"<<endl;
        }

    }



    fclose(jugadores);

}

/*
Procedimiento de modificacion, recorre el archivo comparando 1 por uno los registros con el valor buscado
si lo encuentra llama a la funcion de cargar el registro con la variable modificacion=true para
evitar modificar el nickname

*/

void modificar_jugador(parchivo f, tcad buscado) {
    tjugador p;
    bool encontrado = false;
    bool modificacion;

    f = fopen("jugadores.txt", "rb+");

    if (f == NULL) {
        cout << RED << "Archivo Inexistente" << endl;
    } else {
        // Buscar al jugador por su nickname
        while (fread(&p, sizeof(p), 1, f) && !encontrado) {
            if (strcmp(p.nickname, buscado) == 0) {
                encontrado = true;
            }
        }

        // Si se encontró al jugador, realizar la modificación
        if (encontrado) {
            modificacion = true;
            carga_reg(p, modificacion);

            // Volver a la posición correcta en el archivo antes de escribir el nuevo registro
            fseek(f, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, f);
        } else {
            cout << RED << "Registro no encontrado" << endl;
            cout << BLACK << endl;
        }
    }

    fclose(f);
}

// eliminacion de un registro del archivo

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
            cout << BLUE << "ELIMINADO EXITOSAMENTE" << endl;
            if (rename("temporal.txt","jugadores.txt")==0)
                cout << BLACK << "RENOMBRADO EXITOSAMENTE" << endl;
            else
                cout << RED << "ERROR AL RENOMBRAR" << endl;
                cout << BLACK << endl;
        }
        else
            cout << RED << "ERROR AL ELIMINAR" << endl;
            cout << BLACK << endl;
    }

}

// funcion que determina si un jugador(nickname) se encuentra en el archivo, devuelve true si es asi
bool existe_jugador(parchivo jugadores, tcad buscado){

    tjugador a;
    bool encontrado=false;
    jugadores=fopen("jugadores.txt", "rb");

    if(jugadores==NULL){
        cout << RED << "Archivo Inexistente" << endl;
        cout << BLACK << endl;
        return false;
    }

        while(!feof(jugadores) && encontrado==false){

            fread(&a,sizeof(a),1,jugadores);

            if(strcmp(a.nickname, buscado)==0){
                encontrado=true;
            }
        }




    fclose(jugadores);
    return encontrado;
}

/*
funcion que determina la cantidad de jugadores en el archivo, recorre el archivo
y cuenta los registros, en el caso de que no hayan registros devuelve un valor -1
*/ 
int cantidad_jugadores(parchivo f) {
    tjugador letra;
    int cont = 0;

    f = fopen("jugadores.txt", "rb");

    if (f == NULL) {
        cout << RED << "Error al abrir el archivo." << endl;
        cout << BLACK << endl;
        return -1;  // Si falla devuelve -1
    }

    while (fread(&letra, sizeof(letra), 1, f) == 1) {
        cont++;
    }

    fclose(f);

    return cont;
}

