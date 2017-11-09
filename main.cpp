#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 unsigned int FechaVencimiento;
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

void verInfracciones(Conductor conductores[], Infraccion infracciones[]);
void cargarInfraccion();
bool infraccionesPorProvincia ( char provincia[], Conductor conductores[], Infraccion infracciones[] );
void infraccionesPorConductor( unsigned int IDbuscado, Infraccion infracciones[] );
void mostrarInfraccion(Infraccion actual);
void operacionesConLotes(Conductor conductores[], Infraccion infracciones[]);
bool cargarLoteDeConductores(Conductor conductores[], string nombre);
bool cargarLoteDeInfracciones(Infraccion infracciones[], string nombre);
bool guardarInfraccionesEnLote(Infraccion Infracciones[], string nombre);
bool guardarConductoresEnLote(Conductor conductores[], string nombre);
void archivarConductor(Conductor infractor);
void verConductores(Conductor conductores[]);
void verTodos(const Conductor conductores[]);   //linea
void verTodas(const Infraccion infracciones[]);
void verMasDeTresInfracciones(Conductor conductores[]);
void verInactivos(Conductor conductores[]);
void verActivos(Conductor conductores[]);
void buscarConductor(Conductor conductores[]);
void generarConducores();   //linea
void generarInfracciones();   //linea
void inicializar(Conductor conductores[], Infraccion infracciones[]);   //linea
void mostrarDatos(const Conductor infractor);   //linea
bool buscarPorID(const Conductor conductores[], unsigned int &idBuscado);   //linea
bool buscarXcorreo(const Conductor conductores[], unsigned int &indice);   //linea
bool guardarArchivoDeConductores(Conductor conductores[], unsigned int cantidad);
bool guardarArchivoDeProcesados(Infraccion infracciones[], unsigned int cantidad);
Conductor nuevoConductor(const Conductor conductores[]);   //linea
unsigned int conductoresTotales(Conductor conductores[]);   //linea
void desactivarConductor(Conductor conductores[], unsigned int conductorID);   //linea
void seleccionarFecha(unsigned int &fecha);   //linea
void pausa(void);   //linea
void limpiar(void);   //linea
void eliminar(string nombreDelArchivo);   //linea
string seleccionarProvincia();   //linea

// ---------------------------- FUNCION PRINCIPAL ---------------------------- //

int main(){
    unsigned int conductorID, opcion, ultimo;
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
                    archivarConductor( conductores[ultimo] );
                } else {
                    cout << "ERROR: No se pueden agregar conductores" <<endl << endl;
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
                cargarInfraccion();
                opcion = MENU;
                break;
            case 8:
                //buscarInfraccion( infracciones );
                pausa();
                opcion = MENU;
                break;
            case 9:
                operacionesConLotes(conductores, infracciones);
                opcion = MENU;
                break;
            case 10:
                ultimo = conductoresTotales( conductores );
                guardarArchivoDeConductores( conductores, ultimo );
                guardarArchivoDeProcesados( infracciones, ultimo );
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

// ---------------------------- CONDUCTORES DE PRUEBA ---------------------------- //

void generarConducores(){
    FILE *archivo;
    Conductor prueba[20];
    for(int i=0 ; i<20 ; i++){
        prueba[i].ConductorID = i+1;
        prueba[i].FechaVencimiento = (i < 30) ? (i+1)+20200800 : (i%30+1)*20200800; // 'i+1' de agosto de 2020
        prueba[i].Activo = (i%2 == 0) ? true : false;
        prueba[i].Infracciones = i%3;
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
    Infraccion prueba[23];
    for(int i=0 ; i<20 ; i++){
        prueba[i].InfraccionID = i+1;
        prueba[i].ConductorID = i+1;
        //prueba[i].FechaHora = (i < 30) ? (i+1)+20200800 : (i%30+1)*20200800; // 'i+1' de agosto de 2020
        prueba[i].Monto = i*100;
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

bool guardarArchivoDeConductores(Conductor conductores[], unsigned int cantidad){
    FILE *archivo;
    archivo = fopen("conductores.bin","wb");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return false;
    } else {
        fwrite( conductores, sizeof(Conductor),cantidad ,archivo );
        fclose( archivo );
        return true;
    }
}

// ---------------------------- ARCHIVAR EN PROCESADOS.BIN ---------------------------- //

bool guardarArchivoDeProcesados(Infraccion infracciones[], unsigned int cantidad){
    FILE *archivo;
    archivo = fopen("procesados.bin" ,"wb" );
    if( !archivo ){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return false;
    } else {
        fwrite( infracciones, sizeof(Infraccion) ,cantidad ,archivo );
        fclose( archivo );
        return true;
    }
}

// ---------------------------- DESACTIVAR UN CONDUCTOR ---------------------------- //

void desactivarConductor(Conductor conductores[], unsigned int id){
    bool desactivar;
    if(!buscarPorID(conductores, id)){
        return;
    }
    limpiar();
    cout << "DATOS DEL CONDUCTOR" << endl;
    mostrarDatos(conductores[id]);
    if(conductores[id].Activo == true){
        cout << endl << "Esta seguro de que quiere desactivar a este conductor? 0=NO, 1=SI:   ";
        cin >> desactivar;
        conductores[id].Activo = !desactivar;
        cout << "Conductor Desactivado" << endl << endl;
    } else {
        cout << "El conductor ya se encuentra inactivo" << endl <<endl;
    }
}

// ---------------------------- AGREGAR CONDUCTOR ---------------------------- //

Conductor nuevoConductor(const Conductor conductores[]) {
    Conductor infractor;
    bool datosCorrectos;
    do{
        do{
            limpiar();
            cout << "Ingrese el ID del conductor: ";
            cin >> infractor.ConductorID;
            if(buscarPorID(conductores, infractor.ConductorID)){
                    cout << "ERROR: El ID ya se encuentra registrado" << endl;
                    infractor.ConductorID = VACIO;
                    pausa();
            }
        }while(infractor.ConductorID < 1);
        seleccionarFecha(infractor.FechaVencimiento);
        cout << "Ingrese el ID del conductor: " <<  infractor.ConductorID << endl;
        cout << "Fecha de vencimiento (formato AAAAMMDD): "<< infractor.FechaVencimiento << endl;
        cout << "Ingrese el Total de infracciones del conductor: ";
        cin >> infractor.Infracciones;
        if( infractor.Infracciones >= 3 ){
            infractor.Activo = false;
            cout << "conductor inactivo, mas de 3 infracciones cometidas" << endl;
        } else {
            cout << "Conductor activo (ingrese 1) o conductor inactivo (ingrese 0): ";
            cin >> infractor.Activo;
        }
        cout << "Ingrese el mail del conductor (max 50 caracteres):  ";
        cin.ignore();
        cin.getline( infractor.Email, 50 );

        cout << endl << "Los datos son correctos? 0=NO, 1=SI" << endl;
        cin >> datosCorrectos;
    }while( !datosCorrectos );
    limpiar();
    return infractor;
}

// ---------------------------- ARCHIVAR UN CONDUCTOR---------------------------- //

void archivarConductor(Conductor infractor) {
    FILE* archivoDeConductores;
    archivoDeConductores= fopen("conductores.bin", "ab");
    if(!archivoDeConductores){
        cout << "ERROR: No se pudo abrir el archivo de conductores" << endl;
        return;
    } else {
        fwrite(&infractor, sizeof(Conductor), 1, archivoDeConductores);
        fclose(archivoDeConductores);
    }
}

// ---------------------------- CONTAR CONDUCTORES ---------------------------- //

unsigned int conductoresTotales(Conductor conductores[]){
    unsigned int i;
    for(i=0 ; conductores[i].ConductorID!=VACIO && i<TAM ; i++){}
    return i;
}

// ---------------------------- INICIALIZAR VECTORES ---------------------------- //

void inicializar(Conductor conductores[], Infraccion infracciones[]){
    for(unsigned int i=0; i<TAM ; i++) {
            conductores[i].ConductorID = VACIO;
            infracciones[i].InfraccionID = VACIO;
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

// ---------------------------- SELECCIONAR UNA FECHA VALIDA ---------------------------- //

void seleccionarFecha( unsigned int &fecha ){
    unsigned const short diasDelMes[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int dd, mm, aaaa;
    limpiar();
    do{
        cout << "SELECCIONE EL MES" << endl;
        cout << "[1] Enero" << '\t' << "[5] Mayo" << '\t' << "[9] Septiembre" << endl;
        cout << "[2] Febrero" << '\t' << "[6] Junio" << '\t' << "[10] Octubre" << endl;
        cout << "[3] Marzo" << '\t' << "[7] Julio" << '\t' << "[11] Noviembre" << endl;
        cout << "[4] Abril" << '\t' << "[8] Agosto" << '\t' << "[12] Diciembre" << endl;
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
}

// ---------------------------- BUSCAR CONDUCTOR POR EMAIL ---------------------------- //

bool buscarXcorreo(const Conductor infractor[], unsigned int &indice){
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

// ---------------------------- BUSCAR CONDUCTOR POR ID ---------------------------- //

bool buscarPorID(const Conductor conductores[], unsigned int &buscado){
    unsigned int id = buscado;
    for(int i=0 ; i<TAM ; i++){
        if ( conductores[i].ConductorID == id ){
            buscado = i;
            return true;
        }
    }
    cout << "El conductor con ID \"" <<id<< "\" no ha sido encontrado" <<  endl;
    return false;
}

// ---------------------------- VER DATOS DE UN CONDUCTOR ---------------------------- //

void mostrarDatos(const Conductor infractor){
    string estado = ( infractor.Activo != 0) ? "Activo" : "Inactivo";
    cout <<"Conductor ID: " <<infractor.ConductorID <<endl;
    cout <<"Fecha de vencimiento (formato AAAAMMDD): "<<infractor.FechaVencimiento<<endl;
    cout <<"Estado: " << estado << endl;
    cout <<"Total de infracciones: "<<infractor.Infracciones<<endl;
    cout <<"Email: "<<infractor.Email<<endl<<endl;
}

// ---------------------------- CREAR UN LOTE ---------------------------- //

void CrearLote(){
    string nombreLote;
    char elegir = 's';
    FILE *archivo;
    Infraccion infra;
    cout << "Ingrese el nombre del lote:    ";
    cin >> nombreLote;
    nombreLote = nombreLote + ".bin";
    archivo = fopen( nombreLote.c_str(), "wb" );
    if ( !archivo ) {
        cout << "ERROR: No se pudo crear el lote." << endl;
        return;
    } else {
        do{
            limpiar();
            if ( elegir == 's' || elegir == 'S' ) {
                cout<<"ingrese la id de la infracción:   ";
                cin >> infra.InfraccionID;
                cout<<"ingrese la fecha y hora de la infracción (use el formato AAAAMMDDHH:MM):   ";
                cin >> infra.FechaHora;
                cout << "ingrese el monto de la infracción:   ";
                cin >> infra.Monto;
                cout << "ingrese el id del conductor:   ";
                cin >> infra.ConductorID;
                strcpy( infra.Provincia, seleccionarProvincia().c_str() );
                fwrite(&infra , sizeof(Infraccion) ,1 , archivo);
                limpiar();
            }
            cout << "Desea ingresar otra infraccion al lote? S/N"<< endl;
            cin.ignore();
            cin.getline( &elegir, 1 );
        } while ( elegir != 'n' || elegir != 'N' );
        fclose(archivo);
    }
}

// ---------------------------- ELEGIR PROVINCA ---------------------------- //

string seleccionarProvincia(){
    unsigned int seleccion;
    const string provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    do{
        limpiar();
        cout << "[0] Buenos Aires\t[8] Jujuy\t\t[16] San Juan" << endl;
        cout << "[1] Catamarca\t\t[9] Neuquen\t\t[17] San Luis" << endl;
        cout << "[2] Chaco\t\t[10] Mendoza\t\t[18] Santa Cruz" << endl;
        cout << "[3] Chubut\t\t[11] Misiones\t\t[19] Santa Fe" << endl;
        cout << "[4] Corrientes\t\t[12] La Pampa\t\t[20] Santiago del Estero" << endl;
        cout << "[5] Cordoba\t\t[13] La Rioja\t\t[21] Tierra del Fuego" << endl;
        cout << "[6] Entre Rios\t\t[14] Rio Negro\t\t[22] Tucuman"  << endl;
        cout << "[7] Formosa\t\t[15] Salta" << endl;
        cout << endl << "SELECCIONES UNA PROVINCIA:  ";
        cin >> seleccion;
    }while( seleccion > 23);
    return provincia[seleccion];
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
            cout << "|\t\t[5] Voler atras \t\t\t\t|" << endl;
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

// ---------------------------- VER TODOS LOS CONDUCTORES ---------------------------- //

void verTodos(const Conductor conductores[]){
    for(int i=0 ; i<TAM && conductores[i].ConductorID != VACIO ; i++){
        mostrarDatos( conductores[i] );
    }
}

// ---------------------------- VER TODAS LAS INFRACCIONES ---------------------------- //

void verTodas(const Infraccion infracciones[]){
    for(int i=0 ; i<TAM && infracciones[i].InfraccionID != VACIO ; i++){
        mostrarInfraccion( infracciones[i] );
    }
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
                if(buscarPorID( conductores, buscado ) ){
                    cout << endl <<"DATOS DEL CONDUCTOR"<< endl;
                    mostrarDatos( conductores[buscado] );
                }
                pausa();
                seleccion = EXIT;
                break;
            case 2:
                if(buscarXcorreo( conductores, buscado ) ){
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

// ---------------------------- VER INFRACCIONES---------------------------- //

void verInfracciones(Conductor conductores[], Infraccion infracciones[]){
    char provincia[23];
    unsigned int seleccion = MENU;
    unsigned int buscado;
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
            if(  buscarPorID( conductores, buscado ) ){
                cout << endl <<"DATOS DEL CONDUCTOR"<< endl;
                mostrarDatos( conductores[buscado] );
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

// ---------------------------- INFRACCIONES EN 'X' PROVINCIA---------------------------- //

bool infraccionesPorProvincia ( char provincia[], Conductor conductores[], Infraccion infracciones[]){
    bool encontrado=false;
    unsigned int buscado, i;
    limpiar();
    for( i=0 ; i<TAM ; i++ ){
        if ( strcmp( provincia, infracciones[i].Provincia ) == 0 ){
            buscado = infracciones[i].ConductorID;
            encontrado = buscarPorID( conductores , buscado );
            if( encontrado ){
                mostrarDatos( conductores[ buscado ]);
                cout << endl;
                mostrarInfraccion( infracciones[i] );
                cout << "======================================" << endl;
            }
        }
    }
    if ( encontrado==false ){
        cout << "No hay registros de infracciones en esta provincia";
    }
    return encontrado;
}

// ---------------------------- INFRACCIONES DE UN CONDUCTOR---------------------------- //

void infraccionesPorConductor( unsigned int IDbuscado, Infraccion infracciones[] ){
    for(int i=0 ; i<TAM && infracciones[i].InfraccionID != VACIO ; i++){
        if( infracciones[i].ConductorID == IDbuscado ){
            mostrarInfraccion( infracciones[i] );
        }
    }
}

// ---------------------------- MOSTRAR UNA INFRACCION ---------------------------- //

void mostrarInfraccion(Infraccion actual){
    char fecha[8], hora[5];
    unsigned int i;
    for( i=0 ; i < 8 ; i++){
        fecha[i] = actual.FechaHora[i];
    }
    for( i=0 ; i < 5 ; i++){
        hora[i] = actual.FechaHora[i+8];
    }
    cout << "Infraccion ID: " << actual.InfraccionID << endl;
    cout << "Conductor ID: " << actual.ConductorID << endl;
    cout << "Fecha: ";
    puts( fecha );
    cout << endl;
    cout << "Hora: ";
    puts( hora );
    cout << endl;
    cout << "Monto: " << actual.Monto << endl;
    cout << "Provincia: ";
    puts( actual.Provincia );
    cout << endl;
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
            break;
        case 1:
            cout << "Ingrese el nombre del lote (con su extension) :   ";
            cin >> nombre;
            cargarLoteDeConductores( conductores, nombre );
            limpiar();
            pausa();
            opcion = EXIT;
            break;
        case 2:
            cout << "Ingrese el nombre del lote (con su extension) :   ";
            cin >> nombre;
            cargarLoteDeInfracciones( infracciones, nombre );
            limpiar();
            pausa();
            opcion = EXIT;
            break;
        case 3:
            guardarConductoresEnLote( conductores, "Conductores.bin" );
            limpiar();
            pausa();
            opcion = EXIT;
            break;
        case 4:
            guardarInfraccionesEnLote( infracciones, "Procesados.bin");
            limpiar();
            pausa();
            opcion = EXIT;
            break;
        case 5:
            generarConducores();
            generarInfracciones();
            limpiar();
            pausa();
            opcion = EXIT;
            break;
        case 6:
            cargarLoteDeConductores( conductores, "PruebaDeConductores.bin" );
            cargarLoteDeInfracciones( infracciones, "PruebaDeInfracciones.bin" );
            limpiar();
            pausa();
            opcion = EXIT;
            break;
        case 7:
            CrearLote();
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
    archivo = fopen( nombre.c_str(), "rb" );
    if ( !archivo ) {
        cout << "ERROR: No se pudo abrir el lote." << endl;
        return false;
    } else {
        fseek( archivo ,0 ,SEEK_END);
        tam = ftell( archivo ) / sizeof(Conductor);
        fseek( archivo ,0 ,SEEK_SET );
        fread( conductores ,sizeof(Conductor), tam, archivo );
    }
    fclose( archivo );
    return true;
}

// ---------------------------- CARGAR LOTE (INFRACCIONES) ---------------------------- //

bool cargarLoteDeInfracciones( Infraccion infracciones[], string nombre ){
    FILE *archivo;
    unsigned int tam;
    archivo = fopen( nombre.c_str(), "rb" );
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
