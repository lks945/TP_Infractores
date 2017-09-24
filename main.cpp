#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VACIO 0
#define TAM 1000
// Macro para detectar el sistema operativo ejecutando el programa
#ifdef __linux__
#define OS "linux"
#else
#define OS "noLinux"
#endif
/////////////////////
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

string strint(int num);
void verInfractores(Conductor infractores[]);
void pausa(void);
void limpiar(void);
void generarConducores(void);
void generarInfracciones(void);
void cargarArchivo(Conductor conductorParaCargar[]);
void inicializar(Conductor infractores[]);
void eliminar(string nombreDelArchivo);
void seleccionarFecha(unsigned int &fecha);
void mostrarDatos(const Conductor infractor);
bool buscarXid(const Conductor infractores[], unsigned int &idBuscado);
bool buscarXcorreo(const Conductor infractores[], unsigned int &indice);
Conductor cargarConductor(void);
void comenzarJornada(Conductor infractores[]);
void guardarConductor(Conductor infreactores[]);
unsigned int conductoresTotales(Conductor infractores[]);
bool registrar(Conductor infractor);
bool fechaValida(unsigned int fecha);
void desactivarConductor(Conductor infractores[], unsigned int conductorID);

int main(void){
    string const mes[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    string  const provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    unsigned int select, conductorID, opcion = 0, ultimo = 0, buscado;
    Conductor infractores[TAM];
    inicializar(infractores);
    generarConducores();

    while(true){
        switch(opcion){
            case 0:
                limpiar();
                cout << "[1] Comenzar jornada" << endl;
                cout << "[2] Ver infractores " << endl;
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
                //comenzarJornada(infractor);
                cout << "Comenzo la jornada" << endl;
                pausa();
                opcion = 0;
                break;
            case 2:
                verInfractores(infractores);
                opcion = 0;
                break;
            case 3:
                ultimo = conductoresTotales(infractores);
                if(ultimo <= TAM){
                    infractores[ultimo] = cargarConductor();
                } else {
                    cout << "ERROR: No se pueden agregar mas conductores hasta finalizar la jornada " << endl;
                }
                pausa();
                opcion = 0;
                break;
            case 4:
                cout << "Ingrese el ID del conductor a desactivar:   ";
                cin >> conductorID;
                desactivarConductor(infractores, conductorID);
                pausa();
                opcion = 0;
                break;
            case 5:
                do{
                    cout << "[1] Buscar por ID" << endl;
                    cout << "[2] Buscar por E-mail" << endl;
                    cout << "Seleccione una opcion:  " << endl;
                    cin >> select;
                    limpiar();
               }while(select>2);
               if(select==1){
                   cout << "ingrese el ID del conductor:  ";
                   cin >> buscado;
                   if(buscarXid(infractores, buscado))
                       cout << "DATOS DEL CONDUCTOR"<< endl;
                       mostrarDatos(infractores[buscado]);
                } else {
                    if(buscarXcorreo(infractores, buscado))
                          cout << "DATOS DEL CONDUCTOR"<< endl;
                          mostrarDatos(infractores[buscado]);
                }
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
                do{
                    cout << "[0] Buenos Aires" << endl;
                    cout << "[1] Catamarca" << endl;
                    cout << "[2] Chaco" << endl;
                    cout << "[3] Chubut" << endl;
                    cout << "[4] Corrientes" << endl;
                    cout << "[5] Cordoba" << endl;
                    cout << "[6] Entre Rios" << endl;
                    cout << "[7] Formosa" << endl;
                    cout << "[8] Jujuy" << endl;
                    cout << "[9] Neuquen" << endl;
                    cout << "[10] Mendoza" << endl;
                    cout << "[11] Misiones" << endl;
                    cout << "[12] La Pampa" << endl;
                    cout << "[13] La Rioja" << endl;
                    cout << "[14] Rio Negro" << endl;
                    cout << "[15] Salta" << endl;
                    cout << "[16] San Juan" << endl;
                    cout << "[17] San Luis" << endl;
                    cout << "[18] Santa Cruz" << endl;
                    cout << "[19] Santa Fe" << endl;
                    cout << "[20] Santiago del Estero" << endl;
                    cout << "[21] Tierra del Fuego" << endl;
                    cout << "[22] Tucuman" << endl;
                    cout << "SELECCIONES UNA PROVINCIA: " << endl;
                    cin >> select;
                    limpiar();
                } while(22 < select);
                opcion = 0;
                //infraccionesXprovicia(provincia[select]);
                pausa();
                break;
            case 9:
                //finalizarJornada()
                opcion = 0;
                break;
            case 10:
                cout << "Gracias por utilizar este programa";
                return 0;
                break;
            default:
                opcion = 0;
                break;
        }
    }
}

void generarInfracciones(){}

void generarConducores(){
    FILE *archivo;
    Conductor prueba[20];
    for(int i=0 ; i<20 ; i++){
        prueba[i].ConductorID = i;
        prueba[i].FechaVencimiento = (i+1)*1000000+(82020); // 'i' de agosto de 2020
        prueba[i].Activo = (i%2 == 0)? true : false;
        prueba[i].Infracciones = i%3;
    }
    archivo = fopen("conductores.bin","wb");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fwrite(prueba, sizeof(Conductor),20, archivo);
    fclose(archivo);
}

void comenzarJornada(Conductor infractores[]) {
    FILE *conductores;
    conductores = fopen("conductores.bin", "rb");
    if(!conductores){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fread(infractores, sizeof(Conductor), 1000, conductores);
    fclose(conductores);
}

void inicializar(Conductor cond1[]){
    for(unsigned int i=0; i<TAM ; i++) {
            cond1[i].ConductorID = VACIO;
    }
}

Conductor cargarConductor() {
    Conductor infractor;
    bool datosCorrectos, registrado = false;
    do{
        limpiar();
        cout << "Ingrese el ID del conductor: ";
        cin >> infractor.ConductorID;
        seleccionarFecha(infractor.FechaVencimiento);

        cout << "Ingrese el ID del conductor: " <<  infractor.ConductorID << endl;
        cout << "Fecha de vencimiento (formato AAAAMMDD): "<< infractor.FechaVencimiento << endl;
        cout << "Ingrese el Total de infracciones del conductor: ";
        cin >> infractor.Infracciones;
        if(infractor.Infracciones>=3){
            infractor.Activo = false;
            cout << "conductor inactivo, mas de 3 infracciones cometidas" << endl;
        } else {
            cout << "Conductor activo (ingrese 1) o conductor inactivo (ingrese 0): ";
            cin >> infractor.Activo;
        }
        cout << "Ingrese el mail del conductor (max 50 caracteres):  ";
        cin.ignore();
        cin.getline(infractor.Email, 50);

        cout << endl << "Los datos son correctos? 0=NO, 1=SI" << endl;
        cin >> datosCorrectos;
    }while(!datosCorrectos);
    limpiar();
    //registrado = registrar(infractor);    Esta funcion tiene que encargarse de buscar si un conductor ya se habia registrado
    if(registrado == false){
        cout << "Conductor registrado con exito" << endl;
    } else {
        infractor.ConductorID = VACIO;
        cout << "ERROR: El conductor ya se encuentra registrado" << endl;
    }
    return infractor;
}

void guardarConductor(Conductor infractor[]) {
    FILE* archivo;
    Conductor actual;
    long int tamanio, posicion;
    archivo = fopen("conductores.bin","ab");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fread(&actual ,sizeof(Conductor), 1, archivo);
    fseek(archivo ,0 ,SEEK_END);
    tamanio = ftell(archivo)/sizeof(Conductor);
    fseek(archivo ,0 ,SEEK_SET);
    for(posicion=0 ; (posicion<tamanio) ; posicion++){

    }
    fclose(archivo);
}

void cargarArchivo(Conductor x[]) {
    FILE* archivo;
    archivo = fopen("conductores.bin", "rb");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fseek(archivo ,0 ,SEEK_END);                //se para en el final
    int tam = ftell(archivo)/sizeof(Conductor); //tam = pesoDelArchivo/pesoDeCadaConductor
    fseek(archivo ,0 ,SEEK_SET);                //se para en el inicio
    fread(x ,sizeof(Conductor) ,tam,archivo);   //lee 'tam' conductores de archivo y guarda en x
    fclose(archivo);
    cout << "El archivo ha sido cargado exitosamente" <<endl;
}

unsigned int conductoresTotales(Conductor infractores[]){
    unsigned int i;
    for(i=0 ; infractores[i].ConductorID!=VACIO && i<TAM ; i++)
    return i;
}

void limpiar() {
    if(OS == "linux"){
        system("clear");    //Limpia la consola si el SO es GNU/Linux
    } else {
        system("cls");      //Limpia la consola si el SO es Windows
    }
}

void pausa(){
    char seguir[1];
    cout << "Presione ENTER para continuar";
    cin.ignore();
    cin.getline(seguir,0);
    limpiar();
}

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

bool fechaValida(unsigned int fecha){
    bool validez;
    unsigned const short diasDelMes[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int dd, mm;
    dd = fecha - (fecha/100)*100;
    mm =(fecha/100) - (fecha/10000)*100;
    //anio = fecha/10000;
    validez = ((dd>diasDelMes[mm-1] || dd<1) && (mm<1 || mm>12))? false : true;
    return validez;
}

void desactivarConductor(Conductor infractores[], unsigned int id){
    bool desactivar;

    if(!buscarXid(infractores, id)){
        return;
    }
    limpiar();
    cout << "DATOS DEL CONDUCTOR" << endl;
    mostrarDatos(infractores[id]);
    cout << endl << "Esta seguro de que quiere desactivar a este conductor? 0=NO, 1=SI:   ";
    cin >> desactivar;
    if (desactivar)
        infractores[id].Activo=false;
        cout << "Conductor Desactivado" << endl;
}

void verInfractores(Conductor infractores[]){
    for(int i=0 ; i<TAM ; i++){
        if(infractores[i].Infracciones>=1)
          mostrarDatos(infractores[i]);
    }
    pausa();
}

bool buscarXcorreo(const Conductor infractor[], unsigned int &indice){
    indice = 0;
    char email[50];
    cout << "Introduzca el email del conductor a buscar: ";
    cin.ignore();
    cin.getline(email, 50);
    limpiar();
    for(int i=0;i<=TAM;i++){
        if(strcmp(email, infractor[i].Email) == 0)
            indice = i;
            return true;
    }
    cout << "El conductor con Email \"" <<email<<"\" no ha sido encontrado"<<endl;
    return false;
}

bool buscarXid(const Conductor infractor[], unsigned int &buscado){
    unsigned int id = buscado;
    for(int i=0;i<=TAM;i++){
        if (infractor[i].ConductorID == id)
            buscado = i;
            return true;
    }
    cout << "El conductor con ID \"" <<id<< "\" no ha sido encontrado" <<  endl;
    return false;
}

void mostrarDatos(const Conductor infractor){
    string estado = (infractor.Activo!=0) ? "Activo" : "Inactivo";
    cout <<"Id: " <<infractor.ConductorID <<endl;
    cout <<"Fecha de vencimiento: "<<infractor.FechaVencimiento<<endl;
    cout <<"Estado: " << estado << endl;
    cout <<"Total de infracciones: "<<infractor.Infracciones<<endl;
    cout <<"Email: "<<infractor.Email<<endl;
}

string strint(int num){
    string strnum;
    stringstream convert;
    convert << num;
    strnum = convert.str();
    return strnum;
}

void eliminar(string nombreDelArchivo){
    string comando;
    comando = (OS == "linux") ? "rm " : "del ";
    comando.append(nombreDelArchivo);
    system(comando.c_str());
}
