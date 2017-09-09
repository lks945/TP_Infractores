#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define VACIO 0
#define TAM 1000
// Macro para obtener el tamaño de un vector
#define length(vector) (sizeof(vector)/sizeof(*(vector)))
// Macro para detectar el sistema operativo ejecutando el programa
#ifdef __linux__
#define OS "linux"
#else
#define OS "noLinux"
#endif
/////////////////////
using namespace std;

struct Conductor {
 int ConductorID;
 int FechaVencimiento;
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

void limpiar();
void pausa();
void cargarArchivo(Conductor x[]);
void inicializar(Conductor infractores[]);
Conductor cargarConductor();
void comenzarJornada(Conductor infractores[]);
void guardarConductor(Conductor infreactores[]);
unsigned int conductoresTotales(Conductor infractores[]);
bool registrar(Conductor infractor);
void generarConducores();
void generarInfracciones();
bool fechaValida(unsigned int fecha);

int main(void){
    string const mes[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    string  const provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    unsigned int select, conductorID, opcion = 0, ultimo;
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
                //verInfractores()
                opcion = 0;
                break;
            case 3:
                ultimo = conductoresTotales(infractores);
                if(ultimo <= TAM){
                    infractores[ultimo] = cargarConductor();
                    cout << "Conductor agregado con exito" << endl;
                } else {
                    cout << "ERROR: No se pueden agregar mas conductores hasta finalizar la jornada " << endl;
                }
                pausa();
                opcion = 0;
                break;
            case 4:
                cout << "Escriba el ID del conductor a desactivar: " << endl;
                cin >> conductorID;
                //desactivarConductor(conductorID);
                pausa();
                opcion = 0;
                break;
            case 5:
                cout << "[0] Buscar por ID" << endl;
                cout << "[1] Buscar por E-mail" << endl;
                cout << "Seleccione una opcion:  " << endl;
                cin >> select;
                /*buscado = (select == 0)? buscarXid() : buscarXemail();
                if(buscado.conductorID == VACIO){
                    cout << "No se encontro al conductor";
                } else {
                    //mostrarDatos(buscado);
                }*/
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

void guardarConductor(Conductor cond1[]) {
    FILE* archivo;
    archivo = fopen("conductores.bin","ab");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fwrite(cond1, sizeof(Conductor),1, archivo);
    fclose(archivo);
}

Conductor cargarConductor() {
    Conductor infractor;
    bool registrado = false;
    cout << "Ingrese el ID del conductor"<<endl;
    cin >> infractor.ConductorID;
    cout << "Ingrese la fecha de vencimiento de la licencia del conductor en formato AAAAMMDD"<<endl;
    do{
        cin >> infractor.FechaVencimiento;
    }while(!fechaValida(infractor.FechaVencimiento));
    cout << "Ingrese el Total de infracciones del conductor"<<endl;
    cin >> infractor.Infracciones;
    if(infractor.Infracciones>=3){
        infractor.Activo = false;
    } else {
        cout << "Ingrese 1 si el estado de el conductor es activo, de lo contrario ingrese 0"<<endl;
        cin >> infractor.Activo;
    }
    cout << "Ingrese el mail del conductor (hasta 50 caracteres)"<<endl;
    cin >> infractor.Email;
    limpiar();
    //registrado = registrar(infractor);    Esta funcion tiene que encargarse de buscar si un conductor ya se habia registrado
    if(registrado == true){
        cout << "Conductor registrado con exito" << endl;
    } else {
        infractor.ConductorID = VACIO;
        cout << "ERROR: El conductor ya se encuentra registrado" << endl;
    }
    return infractor;
}

void cargarArchivo(Conductor x[]) {
    FILE* archivo;
    archivo = fopen("conductores.bin", "rb");
    if(!archivo){
        cout << "ERROR: No se pudo abrir el archivo" << endl;
        return;
    }
    fseek(archivo ,0 ,SEEK_END);
    int tam = ftell(archivo)/sizeof(Conductor);
    fseek(archivo ,0 ,SEEK_SET);
    fread(x ,sizeof(Conductor) ,tam,archivo);
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

bool fechaValida(unsigned int fecha){
    bool validez;
    unsigned const short diasDelMes[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unsigned int dd, mm;
    dd = fecha/1000000;
    mm =(fecha-dd)/10000;
    validez = ((dd>diasDelMes[mm-1] || dd<1) && (mm<1 || mm>12))? false : true;
    return validez;
}
