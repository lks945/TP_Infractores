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
    int codProvicia;
};

void inicializar(Conductor cond1[]);
unsigned int tamVector(Conductor cond1[]);
void guardarConductor(Conductor cond1[]);
void cargarConductor(Conductor cond1[]);
void cargarArchivo(Conductor x[]);

int main(void){
    string provincia[23] = { "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Corrientes", "Cordoba", "Entre Rios", "Formosa", "Jujuy", "Neuquen", "Mendoza", "Misiones", "La Pampa", "La Rioja", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe","Santiago del Estero", "Tierra del Fuego", "Tucuman"};
    unsigned int select, conductorID;
    Conductor cond1[TAM];
    inicializar(cond1);
    unsigned int opcion = 0;
    char provincia[20];
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
                //comenzarJornada()
                opcion = 0;
                break;
            case 2:
                //verInfractores()
                opcion = 0;
                break;
            case 3:
                cargarConductor(cond1);
                opcion = 0;
                break;
            case 4:
                cout << "Escriba el ID del conductor a desactivar: " << endl;
                cin >> conductorID;
                //desactivarConductor(conductorID);
                opcion = 0;
                break;
            case 5:
                cout << "[0] Buscar por ID" << endl;
                cout << "[1] Buscar por E-mail" << endl;
                cout << "Seleccione una opcion:  " << endl
                cin >> select;
                /*cond1 = (select == 0)? buscarXid() : buscarXemail();
                if(cond1.conductorID == VACIO){
                    cout << "No se encontro al conductor";
                } else {
                    //mostrarDatos(cond1);
                }*/
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
                    //infraccionesXprovicia(provincia[select]);
                } while((select < 0) || (22 < select));
                break;
            case 9:
                //finalizarJornada()
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

void inicializar(Conductor cond1[]){
    for(unsigned int i=0; i<TAM ; i++) {
            cond1[i].ConductorID=VACIO;
    }
}
unsigned int tamVector(Conductor cond1[]) {
    unsigned int i;
    for( i ; cond1[i].ConductorID!=VACIO ; i++ );
    return (i+1);
}

void guardarConductor(Conductor cond1[]) {
    FILE* archivo;
    archivo =fopen("conductores.bin","wb");
    fwrite(cond1, sizeof(Conductor),1, archivo);
    fclose(archivo);
}

void cargarConductor(Conductor cond1[]) {
    int i=tamVector(cond1);
    cout << "Ingrese el ID del conductor"<<endl;
    cin >> cond1[i].ConductorID;
    cout << "Ingrese la fecha de vencimiento de la licencia del conductor en formato AAAAMMDD"<<endl;
    cin >> cond1[i].FechaVencimiento;
    cout << "Ingrese 1 si el estado de el conductor es activo, de lo contrario ingrese 0"<<endl;
    cin >> cond1[i].Activo;
    cout << "Ingrese el Total de infracciones del conductor"<<endl;
    cin >> cond1[i].Infracciones;
    cout << "Ingrese el mail del conductor"<<endl;
    cin >> cond1[i].Email;
    guardarConductor(cond1);
}

void cargarArchivo(Conductor x[]) {
    FILE* archivo;
    f=fopen("conductores.bin", "rb");
    fseek(archivo ,0 ,SEEK_END);
    int tam = ftell(archivo)/sizeof(Conductor);
    fseek(archivo ,0 ,SEEK_SET);
    fread(x ,sizeof(Conductor) ,tam,archivo);
    fclose(archivo);
    cout << "El archivo ha sido cargado exitosamente" <<endl;
}

void limpiar() {
    if(OS == "linux"){
        system("clear");    //Limpia la consola si el SO es GNU/Linux
    } else {
        system("cls");      //Limpia la consola si el SO es Windows
    }
}
