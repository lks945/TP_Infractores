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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;

struct Conductor {
 unsigned int ConductorID;
 unsigned int FechaVencimiento;
 bool Activo;
 int Infracciones;
 char Email[50];
};
struct Infraccion {
    int infraccionID;
    char fechahora[14];
    float monto;
    int conductorID;
    char Provicia[23];
};
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void archivarConductor(Conductor infractor);
void verInfractores(Conductor infractores[]);
void verTodos(const Conductor infractores[]);   //linea
void verInactivos(Conductor infractores[]);
void verActivos(Conductor infractores[]);
void buscarConductor(Conductor infractores[]);
void generarConducores(void);   //linea
void generarInfracciones(void);   //linea
void inicializar(Conductor infractores[]);   //linea
void mostrarDatos(const Conductor infractor);   //linea
bool buscarXid(const Conductor infractores[], unsigned int &idBuscado);   //linea
bool buscarXcorreo(const Conductor infractores[], unsigned int &indice);   //linea
void cargarArchivoDeConductores(Conductor conductorParaCargar[]);   //linea
Conductor nuevoConductor(const Conductor infractores[]);   //linea
unsigned int conductoresTotales(Conductor infractores[]);   //linea
void desactivarConductor(Conductor infractores[], unsigned int conductorID);   //linea
void seleccionarFecha(unsigned int &fecha);   //linea
void pausa(void);   //linea
void limpiar(void);   //linea
void eliminar(string nombreDelArchivo);   //linea
string seleccionarProvincia();   //linea
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void){
    string const mes[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    char provincia[23];
    unsigned int conductorID, opcion = 0, ultimo = 0;
    Conductor infractores[TAM];
    inicializar(infractores);
    generarConducores();

    while(true){
        switch(opcion){
            case 0:
                limpiar();
                cout << "[1] Comenzar jornada" << endl;
                cout << "[2] Ver infractores" << endl;
                cout << "[3] Cargar conductor" << endl;
                cout << "[4] Desactivar conductor" << endl;
                cout << "[5] Buscar conductor" << endl;
                cout << "[6] Procesar Lote de infractores" << endl;
                cout << "[7] Listar infracciones" << endl;
                cout << "[8] Listar conductores con infracciones por provicia" << endl;
                cout << "[9] Finalizar jornada" << endl;
                cout << "[10] Salir del programa" << endl;
                cout << endl << "SELECCIONE UNA DE LAS OPCIONES:    ";
                cin >> opcion;
                limpiar();
                break;
            case 1:
                generarConducores();
                cargarArchivoDeConductores( infractores );
                pausa();
                opcion = 0;
                break;
            case 2:
                verInfractores(infractores);
                pausa();
                opcion = 0;
                break;
            case 3:
                ultimo = conductoresTotales( infractores );
                if(ultimo < TAM){
                    infractores[ultimo] = nuevoConductor( infractores );
                    archivarConductor( infractores[ultimo] );
                } else {
                    cout << "ERROR: No se pueden agregar conductores" <<endl<< endl;
                    pausa();
                }
                opcion = 0;
                break;
            case 4:
                cout << "Ingrese el ID del conductor a desactivar:   ";
                cin >> conductorID;
                desactivarConductor( infractores, conductorID );
                pausa();
                opcion = 0;
                break;
            case 5:
                buscarConductor( infractores );
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
                //finalizarJornada()
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void generarInfracciones(){}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void desactivarConductor(Conductor infractores[], unsigned int id){
    bool desactivar;
    if(!buscarXid(infractores, id)){
        return;
    }
    limpiar();
    cout << "DATOS DEL CONDUCTOR" << endl;
    mostrarDatos(infractores[id]);
    if(infractores[id].Activo == true){
        cout << endl << "Esta seguro de que quiere desactivar a este conductor? 0=NO, 1=SI:   ";
        cin >> desactivar;
        infractores[id].Activo = !desactivar;
        cout << "Conductor Desactivado" << endl << endl;
    } else {
        cout << "El conductor ya se encuentra inactivo" << endl <<endl;
    }
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
Conductor nuevoConductor(const Conductor infractores[]) {
    Conductor infractor;
    bool datosCorrectos;
    do{
        do{
            limpiar();
            cout << "Ingrese el ID del conductor: ";
            cin >> infractor.ConductorID;
            if(buscarXid(infractores, infractor.ConductorID)){
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void cargarArchivoDeConductores(Conductor infractores[]) {
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
        fread(infractores ,sizeof(Conductor), tam, archivoDeConductores);   //lee 'tam' conductores de archivo y guarda en infractores
        fclose(archivoDeConductores);
        cout << "El archivo ha sido cargado exitosamente" <<endl<<endl;
    }
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int conductoresTotales(Conductor infractores[]){
    unsigned int i;
    for(i=0 ; infractores[i].ConductorID!=VACIO && i<TAM ; i++){}
    return i;
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void inicializar(Conductor conductores[]){
    for(unsigned int i=0; i<TAM ; i++) {
            conductores[i].ConductorID = VACIO;
    }
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void limpiar() {
    string orden;
    orden = (strcmp(OS, "linux")==0)? "clear" : "cls";
    system(orden.c_str());
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void pausa(){
    char seguir[1];
    cout << "PRESIONE ENTER PARA CONTINUAR...";
    cin.ignore();
    cin.getline(seguir,0);
    limpiar();
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrarDatos(const Conductor infractor){
    string estado = ( infractor.Activo != 0) ? "Activo" : "Inactivo";
    cout <<"Conductor ID: " <<infractor.ConductorID <<endl;
    cout <<"Fecha de vencimiento (formato AAAAMMDD): "<<infractor.FechaVencimiento<<endl;
    cout <<"Estado: " << estado << endl;
    cout <<"Total de infracciones: "<<infractor.Infracciones<<endl;
    cout <<"Email: "<<infractor.Email<<endl<<endl;
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void eliminar(string nombreDelArchivo){
    string comando;
    comando = (strcmp(OS, "linux")==0) ? "rm " : "del ";
    comando.append(nombreDelArchivo);
    system(comando.c_str());
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
                    cin >> infra.infraccionID;
                    cout<<"ingrese la fecha y hora de la infracción (use el formato AAAAMMDDHH:MM):   ";
                    cin >> infra.fechahora;
                    cout << "ingrese el monto de la infracción:   ";
                    cin >> infra.monto;
                    cout << "ingrese el id del conductor:   ";
                    cin >> infra.conductorID;
                    strcpy( infra.Provicia, seleccionarProvincia().c_str() );
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void eliminarLote(){
    string nombre;
    cout << "Escriba el nombre completo del archivo que quiere eliminar:    ";
    cin >> nombre;
    eliminar(nombre);
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void verInfractores(Conductor infractores[]){
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
            verTodos( infractores );
            seleccion = EXIT;
            break;
        case 2:
            //verMorosos( infractores );
            seleccion = EXIT;
            break;
        case 3:
            //verVencidos( infractores );
            seleccion = EXIT;
            break;
        case 4:
            //verMasDeTresInfracciones( infractores );
            seleccion = EXIT;
            break;
        case 5:
            verActivos( infractores );
            seleccion = EXIT;
            break;
        case 6:
            verInactivos( infractores );
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
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void verInactivos(Conductor infractores[]){
    for(int i=0 ; i<TAM ; i++){
        if( (infractores[i].Activo == false) && (infractores[i].ConductorID != VACIO) ){
            mostrarDatos( infractores[i] );
        }
    }
    pausa();
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void verActivos(Conductor infractores[]){
    for(int i=0 ; i<TAM ; i++){
        if( (infractores[i].Activo == true) && (infractores[i].ConductorID != VACIO) ){
            mostrarDatos( infractores[i] );
        }
    }
    pausa();
}
// ///////////////////////////////////////////////////////////////////////////////////////////////////////
void verTodos(const Conductor infractores[]){
    for(int i=0 ; i<TAM ; i++){
        if( (infractores[i].Infracciones >= 1) && (infractores[i].ConductorID != VACIO) ){
            mostrarDatos( infractores[i] );
        }
    }
    pausa();
}

void buscarConductor(Conductor infractores[]){
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
                if(buscarXid( infractores, buscado ) ){
                    cout << endl <<"DATOS DEL CONDUCTOR"<< endl;
                    mostrarDatos( infractores[buscado] );
                }
                seleccion = EXIT;
                break;
            case 2:
                if(buscarXcorreo( infractores, buscado ) ){
                    cout << "DATOS DEL CONDUCTOR"<< endl << endl;
                    mostrarDatos( infractores[buscado] );
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
