#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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

struct Conductor
{
 int ConductorID;
 int Fechavencimiento;
 bool Activo;
 int Totalinfracciones;
 char email[50];
};

struct Infraccion{
    int infraccionID;
    char fechahora[14];
    float monto;
    int conductorID;
    int codProvicia;
};

void inicializar(Conductor cond1[]);
unsigned int tamVector(Conductor cond1[]);
void guardarConductor(Conductor cond1[]);
void cargarConductor(Conductor cond1[]);
void cargarArchivo(Conductor x[]);

int main(void){
    Conductor cond1[TAM];
    inicializar(cond1);
    unsigned int opcion = 0;
    char provincia[20];
    while(true){
        switch(opcion){
            case 0:
                if(OS == "linux"){
                    system("clear");    //Limpia la consola si el SO es GNU/Linux
                } else {
                    system("cls");      //Limpia la consola si el SO es Windows
                }
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
                if(OS == "linux"){
                    system("clear");    //Limpia la consola si el SO es GNU/Linux
                } else {
                    system("cls");      //Limpia la consola si el SO es Windows
                }
                break;
            case 1:
                //comenzarJornada()
                opcion=0;
                break;
            case 2:
                //verInfractores()
                opcion=0;
                break;
            case 3:
                cargarConductor(cond1);
                opcion=0;
                break;
            case 4:
                //desactivarConductor()
                opcion=0;
                break;
            case 5:
                cout << "" << endl;
                cout << "" << endl;
                opcion=0;
                break;
            case 6:
                //procesarLote()
                opcion=0;
                break;
            case 7:
                //listarInfracciones()
                opcion=0;
                break;
            case 8:
                cout << "Provincia que desea ver:" << endl;
                cin.ignore();
                cin.getline(provincia, 20);
                //infraccionesXprovicia(provincia)
                opcion=0;
                break;
            case 9:
                //finalizarJornada()
                break;
            case 10:
                return 0;
                break;
            default:
                opcion = 0;
                break;
        }
    }
}

void inicializar(Conductor cond1[]){
    for(unsigned int i=0; i<TAM ; i++){
            cond1[i].ConductorID=VACIO;
        }
}
unsigned int tamVector(Conductor cond1[]){
    unsigned int i;
    for( i ; cond1[i].ConductorID!=VACIO ; i++ );
    return (i+1);
}

void guardarConductor(Conductor cond1[]){
    FILE*f;
    f=fopen("conductores.bin","wb");
    fwrite(cond1,sizeof(Conductor),1,f);
    fclose(f);
}

void cargarConductor(Conductor cond1[]){
    int i=tamVector(cond1);
    cout << "Ingrese el ID del conductor"<<endl;
    cin >> cond1[i].ConductorID;
    cout << "Ingrese la fecha de vencimiento de la licencia del conductor en formato AAAAMMDD"<<endl;
    cin >> cond1[i].Fechavencimiento;
    cout << "Ingrese 1 si el estado de el conductor es activo, de lo contrario ingrese 0"<<endl;
    cin >> cond1[i].Activo;
    cout << "Ingrese el Total de infracciones del conductor"<<endl;
    cin >> cond1[i].Totalinfracciones;
    cout << "Ingrese el mail del conductor"<<endl;
    cin >> cond1[i].email;
    guardarConductor(cond1);
}

void cargarArchivo(Conductor x[]){
    FILE*f;
    f=fopen("conductores.bin", "rb");
    fseek(f,0,SEEK_END);
    int tam=ftell(f)/sizeof(Conductor);
    fseek(f,0,SEEK_SET);
    fread(x,sizeof(Conductor),tam,f);
    fclose(f);
    cout << "El archivo ha sido cargado exitosamente" <<endl;
}
