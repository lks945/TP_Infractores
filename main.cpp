#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VACIO 0
#define EXIT 100
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
    int InfraccionID;
    char FechaHora[14];
    float Monto;
    int ConductorID;
    char Provincia[23];
};

// ---------------------------- PROTOTIPOS DE FUNCIONES ---------------------------- //

bool InfraccionesXProvincia ( char provincia[], Conductor conductores[] );
void mostrarInfraccion(Infraccion actual);
void archivarConductor(Conductor infractor);
void verInfractores(Conductor conductores[]);
void verTodos(const Conductor conductores[]);   //linea
void verInactivos(Conductor conductores[]);
void verActivos(Conductor conductores[]);
void buscarConductor(Conductor conductores[]);
void generarConducores();   //linea
void generarInfracciones();   //linea
void inicializar(Conductor conductores[]);   //linea
void mostrarDatos(const Conductor infractor);   //linea
bool buscarXid(const Conductor conductores[], unsigned int &idBuscado);   //linea
bool buscarXcorreo(const Conductor conductores[], unsigned int &indice);   //linea
void cargarArchivoDeConductores(Conductor conductores[]);   //linea
void cargarArchivoDeProcesados(Infraccion infracciones[]);   //linea
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
    char provincia[23];
    unsigned int conductorID, opcion, ultimo = 0;
    Conductor conductores[TAM];
    Infraccion infracciones[TAM];
    inicializar( conductores );
    cout << "Desea generar un archivos de prueba?  0=NO, 1=SI  "<< endl;
    cin >> opcion;
    if( opcion ){
        generarConducores();
        generarInfracciones();
    }
    opcion = 0;

    while(true){
        switch(opcion){
            case 0:
                limpiar();
                cout << "[1] Comenzar jornada" << endl;
                cout << "[2] Ver conductores" << endl;
                cout << "[3] Cargar conductor" << endl;
                cout << "[4] Desactivar conductor" << endl;
                cout << "[5] Buscar conductor" << endl;
                cout << "[6] Procesar Lote de infracciones" << endl;
                cout << "[7] Ver infracciones" << endl;
                //cargar infraccion;
                cout << "[8] Listar conductores con infracciones por provicia" << endl;
                cout << "[9] Finalizar jornada" << endl;
                cout << "[10] Salir del programa" << endl;
                cout << endl << "SELECCIONE UNA DE LAS OPCIONES:    ";
                cin >> opcion;
                limpiar();
                break;
            case 1:
                cargarArchivoDeConductores( conductores );
                cargarArchivoDeProcesados( infracciones );
                cout << "Los archivos han sido cargados exitosamente" <<endl<<endl;
                pausa();
                opcion = 0;
                break;
            case 2:
                verInfractores(conductores);
                pausa();
                opcion = 0;
                break;
            case 3:
                ultimo = conductoresTotales( conductores );
                if(ultimo < TAM){
                    conductores[ultimo] = nuevoConductor( conductores );
                    archivarConductor( conductores[ultimo] );
                } else {
                    cout << "ERROR: No se pueden agregar conductores" <<endl<< endl;
                    pausa();
                }
                opcion = 0;
                break;
            case 4:
                cout << "Ingrese el ID del conductor a desactivar:   ";
                cin >> conductorID;
                desactivarConductor( conductores, conductorID );
                pausa();
                opcion = 0;
                break;
            case 5:
                buscarConductor( conductores );
                pausa();
                opcion = 0;
                break;
            case 6:
                //procesarLote()
                opcion = 0;
                break;
            case 7:
                //listarInfracciones()
                opcion = 0;
                break;
            case 8:
                strcpy( provincia, seleccionarProvincia().c_str() );
                limpiar();
                //infraccionesXprovicia( provincia );
                pausa();
                opcion = 0;
                break;
            case 9:
                ultimo = conductoresTotales( conductores );
                //finalizarJornada()
                guardarArchivoDeConductores( conductores, ultimo );
                guardarArchivoDeProcesados( infracciones, ultimo );
                opcion = 0;
                break;
            case 10:
                cout << "Gracias por utilizar este programa" << endl<< endl;
                return 0;
            default:
                opcion = 0;
                break;
        }
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
    archivo = fopen("procesados.bin","wb");
    if( !archivo ){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
    } else {
        fwrite( prueba, sizeof(Infraccion),23, archivo );
        fclose( archivo );
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
    archivo = fopen("conductores.bin","wb");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
    } else {
        fwrite(prueba, sizeof(Conductor),20, archivo);
        fclose(archivo);
    }
}

// ---------------------------- DESACTIVAR UN CONDUCTOR ---------------------------- //

void desactivarConductor(Conductor conductores[], unsigned int id){
    bool desactivar;
    if(!buscarXid(conductores, id)){
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
            if(buscarXid(conductores, infractor.ConductorID)){
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

// ---------------------------- CARGAR CONDUCTORES.BIN ---------------------------- //

void cargarArchivoDeConductores(Conductor conductores[]) {
    FILE* archivoDeConductores;
    unsigned long tam;
    archivoDeConductores = fopen("conductores.bin", "rb");
    if(!archivoDeConductores){
        cout << "ERROR: No se pudo abrir el archivo de conductores" << endl;
        return;
    } else {
        fseek(archivoDeConductores ,0 ,SEEK_END);                //se para en el final del archivo
        tam = ftell(archivoDeConductores)/sizeof(Conductor); //tam = pesoDelArchivo/pesoDeCadaConductor
        fseek(archivoDeConductores ,0 ,SEEK_SET);                //se para en el inicio del archivo
        fread(conductores ,sizeof(Conductor), tam, archivoDeConductores);   //lee 'tam' conductores de archivo y guarda en conductores
        fclose(archivoDeConductores);
    }
}

// ---------------------------- CARGAR PROCESADOS.BIN ---------------------------- //

void cargarArchivoDeProcesados(Infraccion infracciones[]) {
    FILE* archivoDeProcesados;
    unsigned long tam;
    archivoDeProcesados = fopen("procesados.bin", "rb");
    if(!archivoDeProcesados){
        cout << "ERROR: No se pudo abrir el archivo de conductores" << endl;
        return;
    } else {
        fseek( archivoDeProcesados ,0 ,SEEK_END);                //se para en el final del archivo
        tam = ftell( archivoDeProcesados )/sizeof( Infraccion ); //tam = pesoDelArchivo/pesoDeCadaConductor
        fseek( archivoDeProcesados ,0 ,SEEK_SET );                //se para en el inicio del archivo
        fread( infracciones ,sizeof( Infraccion ), tam, archivoDeProcesados );   //lee 'tam' conductores de archivo y guarda en conductores
        fclose( archivoDeProcesados );
    }
}

// ---------------------------- CONTAR CONDUCTORES ---------------------------- //

unsigned int conductoresTotales(Conductor conductores[]){
    unsigned int i;
    for(i=0 ; conductores[i].ConductorID!=VACIO && i<TAM ; i++){}
    return i;
}

// ---------------------------- INICIALIZAR CONDUCTORES ---------------------------- //

void inicializar(Conductor conductores[]){
    for(unsigned int i=0; i<TAM ; i++) {
            conductores[i].ConductorID = VACIO;
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

void seleccionarFecha(unsigned int &fecha){
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
    }while(mm<1 || mm>12);
    do{
        cout << "MES:  " << mm << endl;
        cout << "SELECCIONE EL DIA:     ";
        cin >> dd;
        limpiar();
    }while (dd>diasDelMes[mm-1] || dd<1);
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
    cin.getline(email, 50);
    limpiar();
    for(int i=0 ; i<TAM ; i++){
        if(strcmp(email, infractor[i].Email) == 0){
            indice = i;
            return true;
        }
    }
    cout << "El conductor con Email \"" <<email<<"\" no ha sido encontrado"<<endl;
    return false;
}

// ---------------------------- BUSCAR CONDUCTOR POR ID ---------------------------- //

bool buscarXid(const Conductor infractor[], unsigned int &buscado){
    unsigned int id = buscado;
    for(int i=0 ; i<TAM ; i++){
        if (infractor[i].ConductorID == id){
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
    string  const provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    char opcion;
    string nombreLote;
    FILE *archivo;
    Infraccion infra;
    cout << "Ingrese el nombre del lote:    ";
    cin >> nombreLote;
    nombreLote = nombreLote + ".bin";
    archivo = fopen( nombreLote.c_str(), "wb" );
    if (!archivo) {
        cout << "ERROR: No se pudo crear el lote." << endl;
        return;
    } else {
        switch ( opcion ) {
        case 0:
            limpiar();
            cout << "[1] Ingresar datos manualmente" << endl;
            cout << "[2] Datos aleatorios"<< endl;
            cin >>opcion;
            break;
        case 1:
            do{
                limpiar();
                if ( opcion == 's' || opcion == 'S' ) {
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
                cin.getline( &opcion, 1 );
            } while ( opcion != 'n' || opcion != 'N' );
            break;
        case 2:
            //loteAleatorio();
            break;
        default:
            opcion = 0;
            break;
        }
        fclose(archivo);
    }
}

// ---------------------------- ELIMINAR UN LOTE ---------------------------- //

void eliminarLote(){
    string nombre;
    cout << "Escriba el nombre completo del archivo que quiere eliminar:    ";
    cin >> nombre;
    eliminar(nombre);
}

void eliminar(string nombreDelArchivo){
    string comando;
    comando = (strcmp(OS, "linux")==0) ? "rm " : "del ";
    comando.append(nombreDelArchivo);
    system(comando.c_str());
}

// ---------------------------- ELEGIR PROVINCA ---------------------------- //

string seleccionarProvincia(){
    unsigned int seleccion;
    const string provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    do{
        limpiar();
        cout << "[0] Buenos Aires"<< '\t' << "[8] Jujuy" << '\t'  << '\t' << "[16] San Juan" << endl;
        cout << "[1] Catamarca" << '\t' << '\t' << "[9] Neuquen" << '\t' << '\t' << "[17] San Luis" << endl;
        cout << "[2] Chaco" << '\t' << '\t' <<"[10] Mendoza" << '\t' << '\t' << "[18] Santa Cruz" << endl;
        cout << "[3] Chubut" << '\t' << '\t' <<"[11] Misiones" << '\t' << '\t' << "[19] Santa Fe" << endl;
        cout << "[4] Corrientes" << '\t' << '\t' << "[12] La Pampa" << '\t' << '\t' << "[20] Santiago del Estero" << endl;
        cout << "[5] Cordoba" << '\t'  << '\t' << "[13] La Rioja" << '\t' << '\t' << "[21] Tierra del Fuego" << endl;
        cout << "[6] Entre Rios" << '\t'  << '\t' << "[14] Rio Negro"<< '\t' << '\t' <<"[22] Tucuman"  << endl;
        cout << "[7] Formosa"  << '\t' << '\t' << "[15] Salta" << endl;
        cout << endl << "SELECCIONES UNA PROVINCIA:  ";
        cin >> seleccion;
    }while( seleccion > 23);
    return provincia[seleccion];
}

// ---------------------------- VER INFRACTORES ---------------------------- //

void verInfractores(Conductor conductores[]){
    unsigned int seleccion = 0;
    limpiar();
    do{
    switch (seleccion){
        case 0 :
            cout << "[*] Ver infractores" << endl;
            cout << '\t' << "[1] Ver todos los conductores " <<endl;
            cout << '\t' << "[2] Ver conductores morosos" <<endl;
            cout << '\t' << "[3] Ver conductores vencidos" <<endl;
            cout << '\t' << "[4] Ver conductores con mas de 3 infracciones" <<endl;
            cout << '\t' << "[5] Ver conductores activos" <<endl;
            cout << '\t' << "[6] Ver conductores inactivos" <<endl;
            cin >> seleccion;
            limpiar();
            break;
        case 1:
            verTodos( conductores );
            seleccion = EXIT;
            break;
        case 2:
            //verMorosos( conductores );
            seleccion = EXIT;
            break;
        case 3:
            //verVencidos( conductores );
            seleccion = EXIT;
            break;
        case 4:
            //verMasDeTresInfracciones( conductores );
            seleccion = EXIT;
            break;
        case 5:
            verActivos( conductores );
            seleccion = EXIT;
            break;
        case 6:
            verInactivos( conductores );
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
    for(int i=0 ; i<TAM ; i++){
        if( (conductores[i].Infracciones >= 1) && (conductores[i].ConductorID != VACIO) ){
            mostrarDatos( conductores[i] );
        }
    }
}

// ---------------------------- BUSCAR CONDUCTOR ---------------------------- //

void buscarConductor(Conductor conductores[]){
    unsigned int seleccion = 0, buscado;
    limpiar();
    do{
        switch(seleccion){
            case 0:
                cout << "[*] Buscar conductor" << endl;
                cout << '\t' << "[1] Buscar por Conductor ID" << endl;
                cout << '\t' << "[2] Buscar por E-mail" << endl;
                // cout << "[3] Buscar por infraccion ID" << endl;
                cout << "Seleccione una opcion:  " << endl;
                cin >> seleccion;
                limpiar();
                break;
            case 1:
                cout << "ingrese el ID del conductor:  ";
                cin >> buscado;
                if(buscarXid( conductores, buscado ) ){
                    cout << endl <<"DATOS DEL CONDUCTOR"<< endl;
                    mostrarDatos( conductores[buscado] );
                }
                seleccion = EXIT;
                break;
            case 2:
                if(buscarXcorreo( conductores, buscado ) ){
                    cout << "DATOS DEL CONDUCTOR"<< endl << endl;
                    mostrarDatos( conductores[buscado] );
                }
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

// ---------------------------- INFRACCIONES EN 'X' PROVINCIA---------------------------- //

bool InfraccionesXProvincia ( char provincia[], Conductor conductores[] ){
    FILE* archivoDeConductores;
    FILE* archivoDeProcesados;
    //Conductor conductorActual;
    Infraccion infraccionActual;
    bool encontrado;
    unsigned int buscado;

    archivoDeProcesados = fopen( "procesados.bin" , "rb" );
    archivoDeConductores = fopen( "conductores.bin", "rb" );
    if ( (archivoDeProcesados == NULL) || (archivoDeConductores == NULL) ){
        cout << "ERROR: No se pudieron abrir los registros" << endl;
        return false;
    } else {
        while ( !feof( archivoDeProcesados ) ){
            fread( &infraccionActual, sizeof( Infraccion ),1, archivoDeProcesados );
            if ( strcmp( provincia, infraccionActual.Provincia ) == 0 ){
                limpiar();
                buscado = infraccionActual.ConductorID;
                encontrado = buscarXid( conductores , buscado );
                if( encontrado ){
                    mostrarDatos( conductores[ buscado ]);
                    cout << endl;
                    mostrarInfraccion( infraccionActual );
                    cout << "======================================" << endl;
                }
            }
        }
        if ( encontrado==false ){
            cout << "No hay registros de infracciones en esta provincia";
        }
    }
    fclose(archivoDeProcesados);
    fclose(archivoDeConductores);
    return encontrado;
}

// ---------------------------- MOSTRAR UNA INFRACCION ---------------------------- //

void mostrarInfraccion(Infraccion actual){
    char fecha[8], hora[5];
    int i;
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
