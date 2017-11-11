#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#define VACIO 0
#define MENU 0
#define EXIT 11
#define TAM 1000
// Macro para detectar el sistema operativo ejecutando el programa
#ifdef __linux__
#define OS "linux"
#else
#define OS "noLinux"
#endif

using namespace std;

// ---------------------------- ESTRUCTURAS ---------------------------- //

struct Conductor {
 unsigned int ConductorID;
 char FechaVencimiento[9];
 bool Activo;
 int Infracciones;
 char Email[50];
};

struct Infraccion {
    unsigned int InfraccionID;
    unsigned int ConductorID;
    char FechaHora[14];
    float Monto;
    char Provincia[23];
};

// ---------------------------- PROTOTIPOS DE FUNCIONES ---------------------------- //

/*LINEA 182*/ void limpiar(void);
/*LINEA 190*/ void pausa(void);
/*LINEA 200*/ void inicializar(Conductor conductores[], Infraccion infracciones[]);
/*LINEA 210*/ unsigned int conductoresTotales(Conductor conductores[]);
/*LINEA 218*/ unsigned int infraccionesTotales(Infraccion infracciones[]);
/*LINEA 226*/ string seleccionarFecha();
/*LINEA 260*/ string seleccionarProvincia();
/*LINEA 281*/ Conductor nuevoConductor(const Conductor conductores[]);
/*LINEA 317*/ Infraccion nuevaInfraccion(const Infraccion infracciones[], Conductor conductores[]);
/*LINEA 353*/ void desactivarConductor(Conductor conductores[], unsigned int conductorID);
/*LINEA 374*/ void verConductores(Conductor conductores[]);
/*LINEA 441*/ void mostrarDatos(const Conductor infractor);
/*LINEA 454*/ void verTodos(const Conductor conductores[]);
/*LINEA 462*/ void verMasDeTresInfracciones(Conductor conductores[]);
/*LINEA 472*/ void verInactivos(Conductor conductores[]);
/*LINEA 482*/ void verActivos(Conductor conductores[]);
/*LINEA 492*/ void verVencidos(Conductor conductores[]);
/*LINEA 505*/ void verInfracciones(Conductor conductores[], Infraccion infracciones[]);
/*LINEA 572*/ void mostrarInfraccion(Infraccion actual);
/*LINEA 593*/ void verTodas(const Infraccion infracciones[]);
/*LINEA 601*/ bool infraccionesPorProvincia ( char provincia[], Conductor conductores[], Infraccion infracciones[] );
/*LINEA 625*/ void infraccionesPorConductor( unsigned int IDbuscado, Infraccion infracciones[] );
/*LINEA 641*/ void buscarConductor(Conductor conductores[]);
/*LINEA 699*/ bool buscarConductorPorID(const Conductor conductores[], unsigned int &idBuscado);
/*LINEA 712*/ bool buscarConductorPorEmail(const Conductor conductores[], unsigned int &indice);
/*LINEA 731*/ bool buscarInfraccionPorID(const Infraccion infracciones[], unsigned int &buscado);
/*LINEA 744*/ void operacionesConLotes(Conductor conductores[], Infraccion infracciones[]);
/*LINEA 831*/ bool cargarLoteDeConductores(Conductor conductores[], string nombre);
/*LINEA 850*/ bool cargarLoteDeInfracciones(Infraccion infracciones[], string nombre);
/*LINEA 869*/ bool guardarConductoresEnLote(Conductor conductores[], string nombre);
/*LINEA 884*/ bool guardarInfraccionesEnLote(Infraccion Infracciones[], string nombre);
/*LINEA 899*/ void crearLote();
/*LINEA 928*/ void generarConducores();
/*LINEA 957*/ void generarInfracciones();
/*LINEA 979*/ bool guardarArchivoDeConductores(Conductor conductores[]);
/*LINEA 1001*/ bool guardarArchivoDeProcesados(Infraccion infracciones[]);
/*LINEA 1019*/ string tiempoActual(string modo);
/*LINEA 1039*/ void actualizarVencidos(Conductor conductores[]);

// ---------------------------- FUNCION PRINCIPAL ---------------------------- //

int main(){
    unsigned int conductorID, opcion, ultimo, buscado;
    Conductor conductores[TAM];
    Infraccion infracciones[TAM];
    inicializar( conductores, infracciones);
    ultimo = opcion = MENU;

    while( true ){
        switch( opcion ){
            case MENU:
                limpiar();
                cout << " =============================================================== "<<endl;
                cout << "|\t[1] Comenzar jornada \t\t\t\t\t|" << endl;
                cout << "|\t[2] Ver conductores \t\t\t\t\t|" << endl;
                cout << "|\t[3] Cargar conductor \t\t\t\t\t|" << endl;
                cout << "|\t[4] Desactivar conductor \t\t\t\t|" << endl;
                cout << "|\t[5] Buscar conductor \t\t\t\t\t|" << endl;
                cout << "|\t[6] Ver infracciones \t\t\t\t\t|" << endl;
                cout << "|\t[7] cargar infraccion \t\t\t\t\t|" << endl;
                cout << "|\t[8] Buscar infraccion \t\t\t\t\t|" << endl;
                cout << "|\t[9] Guardar/Cargar un Lote \t\t\t\t|" << endl;
                cout << "|\t[10] Finalizar jornada \t\t\t\t\t|" << endl;
                cout << "|\t[11] Salir del programa \t\t\t\t|" << endl;
                cout << " =============================================================== "<< endl;
                cout << "SELECCIONE UNA DE LAS OPCIONES:    ";
                cin >> opcion;
                limpiar();
                break;
            case 1:
                cargarLoteDeConductores( conductores, "Conductores.bin" );
                cargarLoteDeInfracciones( infracciones, "Procesados.bin" );
                pausa();
                opcion = MENU;
                break;
            case 2:
                verConductores(conductores);
                opcion = MENU;
                break;
            case 3:
                ultimo = conductoresTotales( conductores );
                if(ultimo < TAM){
                    conductores[ultimo] = nuevoConductor( conductores );
                } else {
                    cout << "ERROR: No se pueden agregar conductor" <<endl << endl;
                    pausa();
                }
                opcion = MENU;
                break;
            case 4:
                cout << "Ingrese el ID del conductor a desactivar:   ";
                cin >> conductorID;
                desactivarConductor( conductores, conductorID );
                pausa();
                opcion = MENU;
                break;
            case 5:
                buscarConductor( conductores );
                opcion = MENU;
                break;
            case 6:
                verInfracciones( conductores, infracciones );
                opcion = MENU;
                break;
            case 7:
                ultimo = infraccionesTotales( infracciones );
                if(ultimo < TAM){
                    infracciones[ultimo] = nuevaInfraccion(infracciones, conductores);
                } else {
                    cout << "ERROR: No se pueden agregar infraccion" <<endl << endl;
                    pausa();
                }
                opcion = MENU;
                break;
            case 8:
                cout << "ingrese el ID de la infraccion:  ";
                cin >> buscado;
                if( buscarInfraccionPorID( infracciones, buscado ) ){
                    limpiar();
                    cout << endl <<"DATOS DE LA INFRACCION"<< endl << endl;
                    mostrarInfraccion( infracciones[buscado] );
                }
                pausa();
                opcion = MENU;
                break;
            case 9:
                operacionesConLotes( conductores, infracciones );
                opcion = MENU;
                break;
            case 10:
                guardarArchivoDeConductores( conductores );
                guardarArchivoDeProcesados( infracciones );
                opcion = MENU;
                break;
            case EXIT:
                cout << "Gracias por utilizar este programa" << endl<< endl;
                return 0;
            default:
                opcion = MENU;
                break;
        }
    }
}

// ---------------------------- LIMPIAR PANTALLA ---------------------------- //

void limpiar() {
    string orden;
    orden = (strcmp(OS, "linux")==0)? "clear" : "cls";
    system(orden.c_str());
}

// ---------------------------- UNA PEQUEÑA PAUSA ---------------------------- //

void pausa(){
    char seguir[1];
    cout << "PRESIONE ENTER PARA CONTINUAR...";
    cin.ignore();
    cin.getline(seguir,0);
    limpiar();
}

// ---------------------------- INICIALIZAR VECTORES ---------------------------- //

void inicializar(Conductor conductores[], Infraccion infracciones[]){
    for(unsigned int i=0; i<TAM ; i++) {
            conductores[i].ConductorID = VACIO;
            infracciones[i].InfraccionID = VACIO;
    }
}


// ---------------------------- CONTAR CONDUCTORES ---------------------------- //

unsigned int conductoresTotales(Conductor conductores[]){
    unsigned int i;
    for(i=0 ; conductores[i].ConductorID!=VACIO && i<TAM ; i++){}
    return i;
}

// ---------------------------- CONTAR INFRACCIONES ---------------------------- //

unsigned int infraccionesTotales(Infraccion infracciones[]){
    unsigned int i;
    for(i=0 ; infracciones[i].InfraccionID!=VACIO && i<TAM ; i++){}
    return i;
}

// ---------------------------- SELECCIONAR UNA FECHA ---------------------------- //

string seleccionarFecha(){
    unsigned const short diasDelMes[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int dd, mm, aaaa;
    unsigned int fecha;
    char fecha_str[9];

    limpiar();
    do{
        cout << "SELECCIONE EL MES" << endl;
        cout << "[1] Enero \t [5] Mayo \t [9] Septiembre" << endl;
        cout << "[2] Febrero \t [6] Junio \t [10] Octubre" << endl;
        cout << "[3] Marzo \t [7] Julio \t [11] Noviembre" << endl;
        cout << "[4] Abril \t [8] Agosto \t [12] Diciembre" << endl;
        cin >> mm;
        limpiar();
    }while( mm<1 || mm>12 );
    do{
        cout << "MES:  " << mm << endl;
        cout << "SELECCIONE EL DIA:     ";
        cin >> dd;
        limpiar();
    }while ( dd>diasDelMes[mm-1] || dd<1 );
    cout << "MES:   " << mm << endl;
    cout << "DIA:  " << dd << endl;
    cout << "SELECCIONE EL ANIO:   ";
    cin >> aaaa;
    limpiar();
    fecha = aaaa*10000 + mm*100 + dd;
    sprintf(fecha_str, "%d", fecha);
    return fecha_str;
}

// ---------------------------- ELEGIR PROVINCA ---------------------------- //

string seleccionarProvincia(){
    unsigned int seleccion;
    const string provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    do{
        limpiar();
        cout << "[0] Buenos Aires \t [8] Jujuy \t\t [16] San Juan" << endl;
        cout << "[1] Catamarca \t\t [9] Neuquen \t\t [17] San Luis" << endl;
        cout << "[2] Chaco \t\t [10] Mendoza \t\t [18] Santa Cruz" << endl;
        cout << "[3] Chubut \t\t [11] Misiones \t\t [19] Santa Fe" << endl;
        cout << "[4] Corrientes \t\t [12] La Pampa \t\t [20] Santiago del Estero" << endl;
        cout << "[5] Cordoba \t\t [13] La Rioja \t\t [21] Tierra del Fuego" << endl;
        cout << "[6] Entre Rios \t\t [14] Rio Negro \t\t [22] Tucuman"  << endl;
        cout << "[7] Formosa \t\t [15] Salta" << endl;
        cout << endl << "SELECCIONES UNA PROVINCIA:  ";
        cin >> seleccion;
    }while( seleccion > 23);
    return provincia[seleccion];
}

// ---------------------------- NUEVO CONDUCTOR ---------------------------- //

Conductor nuevoConductor(const Conductor conductores[]) {
    Conductor nuevo;
    bool datosCorrectos;
    unsigned int buscar;
    char f[9];
    do{
        do{
            limpiar();
            cout << "Ingrese el ID del conductor: ";
            cin >> nuevo.ConductorID;
            buscar = nuevo.ConductorID;
            if( buscarConductorPorID(conductores, buscar) ){
                    cout << "ERROR: El ID ya se encuentra registrado" << endl;
                    nuevo.ConductorID = VACIO;
                    pausa();
            }
        }while(nuevo.ConductorID < 1);
        strcpy( nuevo.FechaVencimiento, seleccionarFecha().c_str() );
        strcpy(f, nuevo.FechaVencimiento);
        cout << "Ingrese el ID del conductor: " <<  nuevo.ConductorID << endl;
        cout << "Fecha de vencimiento: " << f[6] << f[7] << "/" << f[4] << f[5] << "/" << f[0] << f[1] << f[2] << f[3] << endl;
        nuevo.Infracciones = 0;
        nuevo.Activo= ( strcmp( nuevo.FechaVencimiento, tiempoActual("fecha").c_str()) > 0) ? true : false;
        cout << "Ingrese el mail del conductor (max 50 caracteres):  ";
        cin.ignore();
        cin.getline( nuevo.Email, 50 );

        cout << endl << "Los datos son correctos? 0=NO, 1=SI" << endl;
        cin >> datosCorrectos;
    }while( !datosCorrectos );
    limpiar();
    return nuevo;
}

// ---------------------------- NUEVA INFRACCION---------------------------- //

Infraccion nuevaInfraccion(const Infraccion infracciones[], Conductor conductores[]){
    Infraccion nueva;
    bool datosCorrectos;
    unsigned int buscar;
    do{
        do{
            limpiar();
            cout << "Ingrese el ID de la Infraccion: ";
            cin >> nueva.InfraccionID;
            buscar = nueva.InfraccionID;
            if( buscarInfraccionPorID( infracciones, buscar) ){
                    cout << "ERROR: El ID ya se encuentra registrado" << endl;
                    nueva.InfraccionID = VACIO;
                    pausa();
            }
        }while(nueva.InfraccionID < 1);
        cout<<"Ingrese el ID del Conductor:  ";
        cin >> nueva.ConductorID;
        cout << "Fecha y hora de la infracción (formato AAAAMMDDHH:MM):   ";
        cin >> nueva.FechaHora;
        cout << "ingrese el monto de la infracción:   ";
        cin >> nueva.Monto;
        strcpy( nueva.Provincia, seleccionarProvincia().c_str() );

        cout << endl << "Los datos son correctos? 0=NO, 1=SI" << endl;
        cin >> datosCorrectos;
    }while( !datosCorrectos );
    buscar = nueva.ConductorID;
    if( buscarConductorPorID(conductores, buscar) ){
        conductores[buscar].Infracciones++;
    }
    limpiar();
    return nueva;
}

// ---------------------------- DESACTIVAR UN CONDUCTOR ---------------------------- //

void desactivarConductor(Conductor conductores[], unsigned int id){
    bool desactivar;
    if(!buscarConductorPorID(conductores, id)){
        return;
    }
    limpiar();
    cout << "DATOS DEL CONDUCTOR" << endl << endl;
    mostrarDatos(conductores[id]);
    if(conductores[id].Activo == true){
        cout << endl << "Esta seguro de que quiere desactivar a este conductor? 0=NO, 1=SI:   ";
        cin >> desactivar;
        conductores[id].Activo = !desactivar;
        limpiar();
        cout << "Conductor Desactivado" << endl << endl;
    } else {
        cout << "El conductor ya se encuentra inactivo" << endl <<endl;
    }
}

// ---------------------------- VER CONDUCTORES ---------------------------- //

void verConductores(Conductor conductores[]){
    unsigned int seleccion = 0;
    limpiar();
    do{
    switch (seleccion){
        case MENU:
            cout << " =============================================================== "<<endl;
            cout << "|\t[*] Comenzar jornada \t\t\t\t\t|" << endl;
            cout << "|\t[+] Ver conductores \t\t\t\t\t|" << endl;
            cout << "|\t\t[1] Ver todos los conductores \t\t\t|" << endl;
            cout << "|\t\t[2] Ver con mas de 3 infracciones \t\t|" <<endl;
            cout << "|\t\t[3] Ver conductores activos \t\t\t|" << endl;
            cout << "|\t\t[4] Ver conductores inactivos \t\t\t|" << endl;
            cout << "|\t\t[5] Ver conductores vencidos \t\t\t|" << endl;
            cout << "|\t\t[6] Voler atras \t\t\t\t|" << endl;
            cout << "|\t[*] Cargar conductor \t\t\t\t\t|" << endl;
            cout << "|\t[*] Desactivar conductor \t\t\t\t|" << endl;
            cout << "|\t[*] Buscar conductor \t\t\t\t\t|" << endl;
            cout << "|\t[*] Ver infracciones \t\t\t\t\t|" << endl;
            cout << "|\t[*] cargar infraccion \t\t\t\t\t|" << endl;
            cout << "|\t[*] Buscar infraccion \t\t\t\t\t|" << endl;
            cout << "|\t[*] Guardar/Cargar un Lote \t\t\t\t|" << endl;
            cout << "|\t[*] Finalizar jornada \t\t\t\t\t|" << endl;
            cout << "|\t[*] Salir del programa \t\t\t\t\t|" << endl;
            cout << " =============================================================== "<< endl;
            cout << endl << "SELECCIONE UNA DE LAS OPCIONES:    ";
            cin >> seleccion;
            limpiar();
            break;
        case 1:
            verTodos( conductores );
            pausa();
            seleccion = EXIT;
            break;
        case 2:
            verMasDeTresInfracciones( conductores );
            pausa();
            seleccion = EXIT;
            break;
        case 3:
            verActivos( conductores );
            pausa();
            seleccion = EXIT;
            break;
        case 4:
            verInactivos( conductores );
            pausa();
            seleccion = EXIT;
            break;
        case 5:
            verVencidos( conductores );
            pausa();
            seleccion = EXIT;
        case 6:
            seleccion = EXIT;
            break;
        case EXIT:
            return;
        default:
            seleccion = MENU;
            break;
        }
    }while(seleccion != EXIT);
}

// ---------------------------- VER DATOS DE UN CONDUCTOR ---------------------------- //

void mostrarDatos(const Conductor infractor){
    char f[9];
    strcpy(f, infractor.FechaVencimiento);
    string estado = ( infractor.Activo != 0) ? "Activo" : "Inactivo";
    cout <<"Conductor ID: " <<infractor.ConductorID <<endl;
    cout << "Fecha de vencimiento: " << f[6] << f[7] << "/" << f[4] << f[5] << "/" << f[0] << f[1] << f[2] << f[3] << endl;
    cout <<"Estado: " << estado << endl;
    cout <<"Total de infracciones: "<<infractor.Infracciones<<endl;
    cout <<"Email: "<<infractor.Email<<endl<<endl;
}

// ---------------------------- VER TODOS LOS CONDUCTORES ---------------------------- //

void verTodos(const Conductor conductores[]){
    for(int i=0 ; i<TAM && conductores[i].ConductorID != VACIO ; i++){
        mostrarDatos( conductores[i] );
    }
}

// ---------------------------- VER CONDUCTORES MAS DE 3 INFR ---------------------------- //

void verMasDeTresInfracciones(Conductor conductores[]){
    for(int i=0 ; i<TAM ; i++){
        if( (conductores[i].Infracciones >= 3) && (conductores[i].ConductorID != VACIO) ){
            mostrarDatos( conductores[i] );
        }
    }
}

// ---------------------------- VER CONDUCTORES INACTIVOS ---------------------------- //

void verInactivos(Conductor conductores[]){
    for(int i=0 ; i<TAM ; i++){
        if( (conductores[i].Activo == false) && (conductores[i].ConductorID != VACIO) ){
            mostrarDatos( conductores[i] );
        }
    }
}

// ---------------------------- VER CONDUCTORES ACTIVOS ---------------------------- //

void verActivos(Conductor conductores[]){
    for(int i=0 ; i<TAM ; i++){
        if( (conductores[i].Activo == true) && (conductores[i].ConductorID != VACIO) ){
            mostrarDatos( conductores[i] );
        }
    }
}

// ---------------------------- VER CONDUCTORES VENCIDOS ---------------------------- //

void verVencidos(Conductor conductores[]){
    unsigned int i;
    char fechaActual[9];
    strcpy( fechaActual, tiempoActual("fecha").c_str());
    for( i=0 ; i<TAM && conductores[i].ConductorID!=VACIO ; i++ ){
        if( strcmp(fechaActual, conductores[i].FechaVencimiento) > 0 ){
            mostrarDatos(conductores[i]);
        }
    }
}

// ---------------------------- VER INFRACCIONES---------------------------- //

void verInfracciones(Conductor conductores[], Infraccion infracciones[]){
    char provincia[23];
    unsigned int seleccion = MENU;
    unsigned int buscado, aux;
    limpiar();
    do{
    switch (seleccion){
        case MENU:
            cout << " =============================================================== "<<endl;
            cout << "|\t[*] Comenzar jornada \t\t\t\t\t|" << endl;
            cout << "|\t[*] Ver conductores \t\t\t\t\t|" << endl;
            cout << "|\t[*] Cargar conductor \t\t\t\t\t|" << endl;
            cout << "|\t[*] Desactivar conductor \t\t\t\t|" << endl;
            cout << "|\t[*] Buscar conductor \t\t\t\t\t|" << endl;
            cout << "|\t[+] Ver infracciones \t\t\t\t\t|" << endl;
            cout << "|\t\t[1] Ver todas las infracciones \t\t\t| " <<endl;
            cout << "|\t\t[2] Ver infracciones por provincia \t\t|" <<endl;
            cout << "|\t\t[3] Ver infracciones de un conductor \t\t|" <<endl;
            cout << "|\t\t[4] Voler atras \t\t\t\t|" << endl;
            cout << "|\t[*] cargar infraccion \t\t\t\t\t|" << endl;
            cout << "|\t[*] Buscar infraccion \t\t\t\t\t|" << endl;
            cout << "|\t[*] Guardar/Cargar un Lote \t\t\t\t|" << endl;
            cout << "|\t[*] Finalizar jornada \t\t\t\t\t|" << endl;
            cout << "|\t[*] Salir del programa \t\t\t\t\t|" << endl;
            cout << " =============================================================== "<< endl;
            cout << endl << "SELECCIONE UNA DE LAS OPCIONES:    ";
            cin >> seleccion;
            limpiar();
            break;
        case 1:
            verTodas( infracciones );
            pausa();
            seleccion = EXIT;
            break;
        case 2:
            strcpy( provincia, seleccionarProvincia().c_str() );
            infraccionesPorProvincia( provincia, conductores, infracciones );
            pausa();
            seleccion = EXIT;
            break;
        case 3:
            cout << "ingrese el ID del conductor:  ";
            cin >> buscado;
            aux = buscado;
            if(  buscarConductorPorID( conductores, buscado ) ){
                cout << endl <<"DATOS DEL CONDUCTOR"<< endl;
                mostrarDatos( conductores[buscado] );
                buscado = aux;
                infraccionesPorConductor( buscado , infracciones );
            }
            pausa();
            seleccion = EXIT;
            break;
        case 4:
            seleccion = EXIT;
            break;
        case EXIT:
            return;
        default:
            seleccion = MENU;
            break;
        }
    }while( seleccion != EXIT );
}

// ---------------------------- MOSTRAR UNA INFRACCION ---------------------------- //

void mostrarInfraccion(Infraccion actual){
    char fecha[9], hora[6];
    fecha[8] = hora[5] = '\0';
    unsigned int i;
    for( i=0 ; i < 8 ; i++){
        fecha[i] = actual.FechaHora[i];
    }
    for( i=0 ; i < 5 ; i++){
        hora[i] = actual.FechaHora[i+8];
    }
    cout << "Infraccion ID: " << actual.InfraccionID << endl;
    cout << "Conductor ID: " << actual.ConductorID << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "Monto: $" << actual.Monto << endl;
    cout << "Provincia: "<<  actual.Provincia << endl;
    cout << endl;
}

// ---------------------------- VER TODAS LAS INFRACCIONES ---------------------------- //

void verTodas(const Infraccion infracciones[]){
    for(int i=0 ; i<TAM && infracciones[i].InfraccionID != VACIO ; i++){
        mostrarInfraccion( infracciones[i] );
    }
}

// ---------------------------- INFRACCIONES EN 'X' PROVINCIA---------------------------- //

bool infraccionesPorProvincia ( char provincia[], Conductor conductores[], Infraccion infracciones[]){
    bool encontrado=false;
    unsigned int buscado, i;
    limpiar();
    for( i=0 ; i<TAM ; i++ ){
        if ( strcmp( provincia, infracciones[i].Provincia ) == 0 ){
            buscado = infracciones[i].ConductorID;
            encontrado = buscarConductorPorID( conductores , buscado );
            if( encontrado ){
                mostrarDatos( conductores[ buscado ]);
                cout << endl;
                mostrarInfraccion( infracciones[i] );
                cout << "======================================" << endl;
            }
        }
    }
    if ( encontrado==false ){
        cout << "No hay registros de infracciones en esta provincia" << endl;
    }
    return encontrado;
}

// ---------------------------- INFRACCIONES DE UN CONDUCTOR---------------------------- //

void infraccionesPorConductor( unsigned int IDbuscado, Infraccion infracciones[] ){
    unsigned int montoTotal = 0;
    for(int i=0 ; i<TAM && infracciones[i].InfraccionID != VACIO ; i++){
        if( infracciones[i].ConductorID == IDbuscado ){
            mostrarInfraccion( infracciones[i] );
            montoTotal = montoTotal + infracciones[i].Monto;
        }
    }
    cout << "======================================" << endl;
    cout << "TOTAL A PAGAR:  $" << montoTotal << endl;
    cout << "======================================" <<endl << endl;

}

// ---------------------------- BUSCAR CONDUCTOR ---------------------------- //

void buscarConductor(Conductor conductores[]){
    unsigned int seleccion = 0, buscado;
    limpiar();
    do{
        switch(seleccion){
            case 0:
                cout << " =============================================================== "<<endl;
                cout << "|\t[*] Comenzar jornada \t\t\t\t\t|" << endl;
                cout << "|\t[*] Ver conductores \t\t\t\t\t|" << endl;
                cout << "|\t[*] Cargar conductor \t\t\t\t\t|" << endl;
                cout << "|\t[*] Desactivar conductor \t\t\t\t|" << endl;
                cout << "|\t[+] Buscar conductor \t\t\t\t\t|" << endl;
                cout << "|\t\t[1] Buscar por Conductor ID \t\t\t|" << endl;
                cout << "|\t\t[2] Buscar por E-mail \t\t\t\t|" << endl;
                cout << "|\t\t[3] Voler atras \t\t\t\t|" << endl;
                cout << "|\t[*] Ver infracciones \t\t\t\t\t|" << endl;
                cout << "|\t[*] cargar infraccion \t\t\t\t\t|" << endl;
                cout << "|\t[*] Buscar infraccion \t\t\t\t\t|" << endl;
                cout << "|\t[*] Guardar/Cargar un Lote \t\t\t\t|" << endl;
                cout << "|\t[*] Finalizar jornada \t\t\t\t\t|" << endl;
                cout << "|\t[*] Salir del programa \t\t\t\t\t|" << endl;
                cout << " =============================================================== "<< endl;
                cout << endl << "SELECCIONE UNA DE LAS OPCIONES:    ";
                cin >> seleccion;
                limpiar();
                break;
            case 1:
                cout << "ingrese el ID del conductor:  ";
                cin >> buscado;
                if(buscarConductorPorID( conductores, buscado ) ){
                    cout << endl <<"DATOS DEL CONDUCTOR"<< endl;
                    mostrarDatos( conductores[buscado] );
                }
                pausa();
                seleccion = EXIT;
                break;
            case 2:
                if(buscarConductorPorEmail( conductores, buscado ) ){
                    cout << "DATOS DEL CONDUCTOR"<< endl << endl;
                    mostrarDatos( conductores[buscado] );
                }
                pausa();
                seleccion = EXIT;
                break;
            case 3:
                seleccion = EXIT;
                break;
            case EXIT:
                return;
            default:
                seleccion = 0;
                break;
        }
    }while(seleccion != EXIT);
}

// ---------------------------- BUSCAR CONDUCTOR POR ID ---------------------------- //

bool buscarConductorPorID(const Conductor conductores[], unsigned int &buscado){
    unsigned int id = buscado;
    for(int i=0 ; i<TAM ; i++){
        if ( conductores[i].ConductorID == id ){
            buscado = i;
            return true;
        }
    }
    return false;
}

// ---------------------------- BUSCAR CONDUCTOR POR EMAIL ---------------------------- //

bool buscarConductorPorEmail(const Conductor infractor[], unsigned int &indice){
    indice = 0;
    char email[50];
    cout << "Introduzca el email del conductor a buscar: ";
    cin.ignore();
    cin.getline( email, 50 );
    limpiar();
    for( int i=0 ; i<TAM ; i++ ){
        if( strcmp( email, infractor[i].Email ) == 0){
            indice = i;
            return true;
        }
    }
    cout << "El conductor con Email \"" <<email<<"\" no ha sido encontrado"<<endl;
    return false;
}

// ---------------------------- BUSCAR INFRACCION POR ID ---------------------------- //

bool buscarInfraccionPorID(const Infraccion infracciones[], unsigned int &buscado){
    unsigned int id = buscado;
    for(int i=0 ; i<TAM ; i++){
        if ( infracciones[i].InfraccionID == id ){
            buscado = i;
            return true;
        }
    }
    return false;
}

// ---------------------------- OPERACIONES CON LOTES  ---------------------------- //

void operacionesConLotes(Conductor conductores[], Infraccion infracciones[]){
    unsigned int opcion = MENU;
    string nombre;
    while( true ){
        switch( opcion ){
            case MENU:
            cout << " =============================================================== "<<endl;
            cout << "|\t[*] Comenzar jornada \t\t\t\t\t|" << endl;
            cout << "|\t[*] Ver conductores \t\t\t\t\t|" << endl;
            cout << "|\t[*] Cargar conductor \t\t\t\t\t|" << endl;
            cout << "|\t[*] Desactivar conductor \t\t\t\t|" << endl;
            cout << "|\t[*] Buscar conductor \t\t\t\t\t|" << endl;
            cout << "|\t[*] Ver infracciones \t\t\t\t\t|" << endl;
            cout << "|\t[*] cargar infraccion \t\t\t\t\t|" << endl;
            cout << "|\t[*] Buscar infraccion \t\t\t\t\t|" << endl;
            cout << "|\t[+] Guardar/Cargar un Lote \t\t\t\t|" << endl;
            cout << "|\t\t[1] Cargar Lote de Conductores \t\t\t| " << endl;
            cout << "|\t\t[2] Cargar Lote de Infracciones \t\t|" << endl;
            cout << "|\t\t[3] Guardar Conductores en un Lote \t\t|" << endl;
            cout << "|\t\t[4] Guardar Infracciones en un Lote \t\t|" << endl;
            cout << "|\t\t[5] Generar Lotes de prueba \t\t\t|" << endl;
            cout << "|\t\t[6] Cargar Lotes de prueba \t\t\t|" << endl;
            cout << "|\t\t[7] Crear un Lote \t\t\t\t|" << endl;
            cout << "|\t\t[8] Voler atras \t\t\t\t|" << endl;
            cout << "|\t[*] Finalizar jornada \t\t\t\t\t|" << endl;
            cout << "|\t[*] Salir del programa \t\t\t\t\t|" << endl;
            cout << " =============================================================== "<< endl;
            cout << endl << "SELECCIONE UNA DE LAS OPCIONES:    ";
            cin >> opcion;
            limpiar();
            break;
        case 1:
            cout << "Ingrese el nombre del lote (con su extension) :   ";
            cin >> nombre;
            cargarLoteDeConductores( conductores, nombre );
            pausa();
            limpiar();
            opcion = EXIT;
            break;
        case 2:
            cout << "Ingrese el nombre del lote (con su extension) :   ";
            cin >> nombre;
            cargarLoteDeInfracciones( infracciones, nombre );
            guardarArchivoDeProcesados( infracciones );
            pausa();
            limpiar();
            opcion = EXIT;
            break;
        case 3:
            cout << "Ingrese el nombre del nuevo lote (con su extension) :   ";
            cin >> nombre;
            guardarConductoresEnLote( conductores, nombre );
            opcion = EXIT;
            break;
        case 4:
            cout << "Ingrese el nombre del nuevo lote (con su extension) :   ";
            cin >> nombre;
            guardarInfraccionesEnLote( infracciones, nombre);
            opcion = EXIT;
            break;
        case 5:
            generarConducores();
            generarInfracciones();
            opcion = EXIT;
            break;
        case 6:
            cargarLoteDeConductores( conductores, "PruebaDeConductores.bin" );
            cargarLoteDeInfracciones( infracciones, "PruebaDeInfracciones.bin" );
            opcion = EXIT;
            break;
        case 7:
            crearLote();
            opcion = EXIT;
            break;
        case 8:
            opcion = EXIT;
            break;
        case EXIT:
            return;
        default:
            opcion = MENU;
            break;
        }
    }
}

// ---------------------------- CARGAR LOTE (CONDUCTORES) ---------------------------- //

bool cargarLoteDeConductores( Conductor conductores[], string nombre ){
    FILE *archivo;
    unsigned int tam;
    if( strcmp(nombre.c_str(), "Conductores.bin")==0){
        archivo = fopen( nombre.c_str(), "ab+" );
    } else {
        archivo = fopen( nombre.c_str(), "rb" );
    }
    if ( !archivo ) {
        cout << "ERROR: No se pudo abrir el lote." << endl;
        return false;
    } else {
        fseek( archivo ,0 ,SEEK_END);
        tam = ftell( archivo ) / sizeof(Conductor);
        fseek( archivo ,0 ,SEEK_SET );
        fread( conductores ,sizeof(Conductor), tam, archivo );
    }
    actualizarVencidos( conductores );
    fclose( archivo );
    return true;
}

// ---------------------------- CARGAR LOTE (INFRACCIONES) ---------------------------- //

bool cargarLoteDeInfracciones( Infraccion infracciones[], string nombre ){
    FILE *archivo;
    unsigned int tam;
    bool flag=true;
    if( strcmp(nombre.c_str(), "Procesados.bin")==0){
        archivo = fopen( nombre.c_str(), "ab+" );
        flag=false;
    } else {
        archivo = fopen( nombre.c_str(), "rb" );
    }
    if ( !archivo ) {
        cout << "ERROR: No se pudo abrir el lote." << endl;
        return false;
    } else {
        fseek( archivo ,0 ,SEEK_END );
        tam = ftell(archivo) / sizeof(Infraccion);
        fseek( archivo ,0 ,SEEK_SET );
        fread( infracciones ,sizeof(Infraccion), tam, archivo );
    }
    fclose( archivo );
    if( flag ){
        archivo = fopen("Procesados.bin", "ab+");
        fwrite(infracciones, sizeof(Infraccion), tam, archivo );
        fclose(archivo);
    }
    return true;
}

// ---------------------------- GUARDAR EN LOTE (CONDUCTORES)---------------------------- //

bool guardarConductoresEnLote(Conductor conductores[], string nombre){
    FILE *archivo;
    archivo = fopen( nombre.c_str(), "wb" );
    if ( !archivo ) {
        cout << "ERROR: No se pudo crear el lote." << endl;
        return false;
    } else {
        fwrite( conductores, sizeof(Conductor),TAM ,archivo );
    }
    fclose( archivo );
    return true;
}

// ---------------------------- GUARDAR EN LOTE (INFRACCIONES)---------------------------- //

bool guardarInfraccionesEnLote( Infraccion infracciones[], string nombre ){
    FILE *archivo;
    archivo = fopen( nombre.c_str(), "wb" );
    if ( !archivo ) {
        cout << "ERROR: No se pudo crear el lote." << endl;
        return false;
    } else {
        fwrite( infracciones, sizeof(Infraccion),TAM ,archivo );
    }
    fclose( archivo );
    return true;
}

// ---------------------------- CREAR UN LOTE ---------------------------- //

void crearLote(){
    string nombreLote;
    bool opcion = true;
    FILE *archivo;
    Infraccion nueva, vacia[1];
    Conductor vacio[1];
    vacio[0].ConductorID = vacia[0].InfraccionID = VACIO;
    cout << "Ingrese el nombre del lote:    ";
    cin >> nombreLote;
    nombreLote = nombreLote + ".bin";
    archivo = fopen( nombreLote.c_str(), "wb" );
    if ( !archivo ) {
        cout << "ERROR: No se pudo crear el lote." << endl;
        return;
    } else {
        limpiar();
        do{
            nueva = nuevaInfraccion( vacia, vacio);
            fwrite(&nueva , sizeof(Infraccion) ,1 , archivo);
            limpiar();
            cout << "Desea ingresar otra infraccion al lote? NO=0 , SI=1"<< endl;
            cin >> opcion;
        } while ( opcion == true );
        fclose(archivo);
    }
}

// ---------------------------- CONDUCTORES DE PRUEBA ---------------------------- //

void generarConducores(){
    FILE *archivo;
    Conductor prueba[20];
    char num[1];
    char fecha[9] = {'2','0','2','0','0','8','1','7','\0'};
    string correo;
    for(int i=0 ; i<20 ; i++){
        prueba[i].ConductorID = i+1;
        strcpy( prueba[i].FechaVencimiento, fecha );
        prueba[i].Activo = true;
        prueba[i].Infracciones = 0;
        num[0] = ((i+11)%10)+48;
        correo = "conductorID_";
        strcpy(prueba[i].Email, correo.c_str() );
        strcat(prueba[i].Email, num);
        correo = "@mail.com";
        strcat(prueba[i].Email, correo.c_str() );
    }
    archivo = fopen("PruebaDeConductores.bin","wb");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
    } else {
        fwrite(prueba, sizeof(Conductor),20, archivo);
        fclose(archivo);
    }
}

// ---------------------------- INFRACCIONES DE PRUEBA ---------------------------- //

void generarInfracciones(){
    const string provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    FILE *archivo;
    Infraccion prueba[30];
    for(int i=0 ; i<30 ; i++){
        prueba[i].InfraccionID = i+1;
        prueba[i].ConductorID = i+1;
        strcpy(prueba[i].FechaHora, tiempoActual("fechaHora").c_str() );
        prueba[i].Monto = (i+1)*100;
        strcpy(prueba[i].Provincia, provincia[(i+23)%23].c_str());
    }
    archivo = fopen("PruebaDeInfracciones.bin","wb");
    if( !archivo ){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
    } else {
        fwrite( prueba, sizeof(Infraccion),23, archivo );
        fclose( archivo );
    }
}

// ---------------------------- ARCHIVAR EN CONDUCTORES.BIN ---------------------------- //

bool guardarArchivoDeConductores(Conductor conductores[]){
    FILE *archivo;
    unsigned int i;
    archivo = fopen("Conductores.bin","wb+");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return false;
    } else {
        actualizarVencidos(conductores);
        fseek(archivo, 0, SEEK_SET);
        for( i=0 ; i<TAM && conductores[i].ConductorID!=VACIO ; i++ ){
            if (conductores[i].Activo == true){
                fwrite( conductores, sizeof(Conductor),1 ,archivo );
            }
        }
        fclose( archivo );
        return true;
    }
}

// ---------------------------- ARCHIVAR EN PROCESADOS.BIN ---------------------------- //

bool guardarArchivoDeProcesados(Infraccion infracciones[]){
    FILE *archivo;
    unsigned int i;
    archivo = fopen("Procesados.bin" ,"ab+" );
    if( !archivo ){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return false;
    } else {
        for( i=0 ; i<TAM && infracciones[i].InfraccionID!=VACIO ; i++ ) {
            fwrite( infracciones, sizeof(Infraccion) ,1 ,archivo );
        }
        fclose( archivo );
        return true;
    }
}

// ---------------------------- HORA DEL SISTEMA ---------------------------- //

string tiempoActual(string modo) {
        time_t tiempo = time( NULL );
        tm *tiempoLocal = localtime( &tiempo );
        char horaDelSistema[14];
        if( strcmp(modo.c_str(), "fechaHora") == 0 ){
            strftime( horaDelSistema, 14, "%Y%m%d%H:%M", tiempoLocal);
        }
        else if( strcmp(modo.c_str(), "fecha") == 0 ){
            strftime( horaDelSistema, 14, "%Y%m%d", tiempoLocal);
        }
        else if( strcmp( modo.c_str(), "hora" ) == 0 ){
            strftime( horaDelSistema, 14, "%H:%M", tiempoLocal);
        } else{
            horaDelSistema[0] = '\0';
        }
        return horaDelSistema;
}

// ---------------------------- ACTUALIZAR VENCIDOS---------------------------- //

void actualizarVencidos(Conductor conductores[]){
    unsigned int i;
    char fechaActual[9];
    strcpy( fechaActual, tiempoActual("fecha").c_str());
    for( i=0 ; i<TAM && conductores[i].ConductorID!=VACIO ; i++ ){
        if( strcmp( fechaActual, conductores[i].FechaVencimiento ) > 0 ){
            conductores[i].Activo = false;
        }
    }
}
