#include <iostream>
#include <string>                       //Libreria para los Strings
#include <time.h>                       //libreria para poder conocer el horario del sistema operativo

using namespace std;                    //ejecutar este programa en windows

//Constantes
const string ERROR_num = "ERROR: Ingrese un NUMERO valido. Intentelo de nuevo.";
const string ERROR_letra = "ERROR: Ingrese un CARACTER valido. Intentelo de nuevo.";
const string ERROR_excedido = "ERROR: Se ha ingresado mas de un digito o caracter. Solo se permite uno a la vez.\nIntentelo de nuevo.";
const string ERROR_campo_vacio = "ERROR: Este campo no puede estar vacio. Intentelo de nuevo.";
const int DF_PACIENTES = 2000;
const int DF_ESPECIALIDAD_MEDICA = 500;

//Structs
struct Paciente{
    string apellido;
    string nombre;
    string dni;
    string telefono;
};

struct Especialidad_Medica{
    int codigo;
    string nombre;
    string descripcion;
};

struct Turno{
    int codigo;
    int fecha;
    string hora;
    string paciente;
    int especialidad_medica;
    int estado;
};

struct Nodo_Turno{
    Turno dato;
    Nodo_Turno *siguiente;
};

struct Nodo{
    Nodo_Turno *dato;
    Nodo *siguiente;
};

//Prototipo de Funciones
void menu_principal(Paciente pacientes[], int dl_pacientes, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Nodo_Turno *&puntero_inicial_turnos);  //Menu Principal

int administrar_especialidades_medicas(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Nodo_Turno *puntero_inicial_turnos); //Submenu Administrar Especialidades Medicas
int administrar_pacientes(Paciente pacientes[], int dl_pacientes, Nodo_Turno *puntero_inicial_turnos); //Submenu Administrar Pacientes
Nodo_Turno *administrar_turnos(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Paciente pacientes[], int dl_pacientes);  //Submenu Administrar Turnos

//Apartado de Especialdedades Medicas
int alta_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);    //Opciones de Administracion de Especialidades Medicas
void modificacion_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);
int baja_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Nodo_Turno *puntero_inicial_turnos);
void listado_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);

void descripcion_especialidad_medica(Especialidad_Medica especialidades_medicas[], int i);
void mostrar_especialidad_medica(Especialidad_Medica especialidades_medicas[], int i);

//Apartado de Pacientes
int alta_paciente(Paciente pacientes[], int dl_pacientes);   //Opciones de Administracion de Pacientes
void modificacion_paciente(Paciente pacientes[], int dl_pacientes);
int baja_paciente(Paciente pacientes[], int dl_pacientes, Nodo_Turno *puntero_inicial_turnos);
void listado_paciente(Paciente pacientes[], int dl_pacientes);

void modificar_dato_paciente(Paciente pacientes[], int indice_paciente, string opcion);

//Apartado de Turnos
Nodo_Turno *alta_turno(Nodo_Turno *puntero_inicial_turnos, Paciente pacientes[], int dl_pacientes, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);  //Opciones de Administracion de Turnos
void modificacion_turno(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);
void baja_turno(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);
void listado_turnos(Nodo_Turno *puntero_inicial_turnos,Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);

void mostrar_turno(Nodo_Turno *puntero_turno, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);
void hora_turno(Nodo_Turno  *nuevo_turno);
void turno_seleccionado_para_cancelar(Nodo_Turno *puntero_turno, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas);
void busqueda_listado_turno(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[],int dl_especialidades_medicas);
bool turno_cancelable_por_fecha(int fecha_verificar);
Nodo *insertar_final_nodo(Nodo *puntero_inicial, Nodo *puntero_nuevo);
Nodo_Turno *insertar_final(Nodo_Turno *puntero_inicial, Nodo_Turno *puntero_nuevo);
void vaciar_lista_nodo(Nodo *puntero_inicial);

//Otras funciones
void pausa();   //Continua con la ejecucion del programa unicamente si el usuario presiona ENTER
void error(string mensaje);   //Muestra mensaje de Error si el usuario ha ingresado mas de un digito o caracter
string pedir_dni();             //pide al usuario un numero de DNI y lo devuelve con puntos

//Funcion Principal
int main() {
    Paciente pacientes[DF_PACIENTES]={};
    int dl_pacientes = 0;

    Nodo_Turno *puntero_inicial_turnos = nullptr;

    Especialidad_Medica especialidades_medicas[DF_ESPECIALIDAD_MEDICA]={};
    int dl_especialidades_medicas = 0;

    menu_principal(pacientes, dl_pacientes, especialidades_medicas, dl_especialidades_medicas, puntero_inicial_turnos);
    return 0;
}

//Definicion de Funciones

/*PROPOSITO: Mostrar el Menu Principal

  PARAMETROS: * pacientes[]: arreglo de tipo paciente y representa las disponibles en el sistema
              * dl_pacientes:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero tipo Nodo_Turno que almacena el primer nodo de la lista de turnos

  RETORNO: tipo void, no tiene valor de retorno */

void menu_principal(Paciente pacientes[], int dl_pacientes, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Nodo_Turno *&puntero_inicial_turnos){

    /* Inicia el programa con un Menu Principal con cuatro opciones
      siendo la ultima, la que permite finalizar el programa */

    string menu;
    do{
        //MENU: Menu principal
        cout <<"\n\t MENU PRINCIPAL\n"
               "1. Administrar Especialidades Medicas.\n"
               "2. Administrar Pacientes.\n"
               "3. Administrar Turnos.\n"
               "4. Salir." << endl;

        //Lee la opcion elegida por el usuario
        cout << "Opcion: ";
        cin >> menu;
        system("cls");

        //Si se ingresa mas de un caracter o digito, se muestra un mensaje de error
        if (menu.length()>1){
            error(ERROR_excedido);
            continue;
        }

        //Inicia Menu de Opciones
        switch (menu[0]) {

            //MENU: Administrar Especialidades Medicas
            case '1': {
                dl_especialidades_medicas = administrar_especialidades_medicas(especialidades_medicas, dl_especialidades_medicas, puntero_inicial_turnos);
                break;
            }

                //MENU: Administrar Pacientes
            case '2': {
                dl_pacientes = administrar_pacientes(pacientes, dl_pacientes, puntero_inicial_turnos);
                break;
            }

                //MENU: Administrar Turnos
            case '3': {
                puntero_inicial_turnos = administrar_turnos(puntero_inicial_turnos, especialidades_medicas, dl_especialidades_medicas, pacientes, dl_pacientes);  //guarda administrar_turnos en puntero_inicial_turnos
                break;
            }

                //MENU: Salir del programa
            case '4': {
                cout << "Saliste del Programa Principal con exito. \n";
                pausa();
                break;
            }

                //MENU: Aparece un mensaje de error si el digito o caracter ingresado no es valido
            default: {
                error(ERROR_num);
                break;
            }
        }
    }while(menu != "4");
}

/*PROPOSITO: Mostrar el Submenu Administrar Especialidades Medicas

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero tipo Nodo_Turno que almacena el primer nodo de la lista de turnos

  RETORNO: no tiene valor de retorno */

int administrar_especialidades_medicas(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Nodo_Turno *puntero_inicial_turnos){
    string submenu1;
    do{

        cout << "\n1. Administrar Especialidades Medicas: \n"
                "   a) Alta de Especialidades Medicas. \n"
                "   b) Modificacion de Especialidades Medicas. \n"
                "   c) Baja de Especialidades Medicas. \n"
                "   d) Listado de Especialidades Medicas. \n"
                "   e) Menu Principal. \n";

        cout <<"Opcion: ";
        cin >> submenu1;
        system("cls");

        if (submenu1.length()>1){
            error(ERROR_excedido);
            continue;
        }

        switch (submenu1[0]) {
            case 'a': {
                dl_especialidades_medicas = alta_especialidad_medica( especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'b': {
                modificacion_especialidad_medica(especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'c': {
                dl_especialidades_medicas = baja_especialidad_medica(especialidades_medicas, dl_especialidades_medicas, puntero_inicial_turnos);
                break;
            }
            case 'd': {
                listado_especialidad_medica(especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'e': {
                return dl_especialidades_medicas;
                break;
            }
            default: {
                error(ERROR_letra);
                break;
            }
        }
    }while(submenu1 != "e");
    return dl_especialidades_medicas;
}

/*PROPOSITO: Mostrar el Submenu Administrar Pacientes

  PARAMETROS: * pacientes[]: arreglo de tipo paciente y representa las disponibles en el sistema
              * dl_pacientes:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero tipo Nodo_Turno que almacena el primer nodo de la lista de turnos

  RETORNO: no tiene valor de retorno */

int administrar_pacientes(Paciente pacientes[], int dl_pacientes, Nodo_Turno *puntero_inicial_turnos){
    string submenu2;
    do {
        cout << "\n2. Administrar Pacientes: \n"
                "   a) Alta de Pacientes. \n"
                "   b) Modificacion de Pacientes. \n"
                "   c) Baja de Pacientes. \n"
                "   d) Listado de Pacientes. \n"
                "   e) Menu Principal. \n";
        cout <<"Opcion: ";
        cin >> submenu2;
        system("cls");

        if (submenu2.length() > 1) {    //comprueba que no se ingrese mas de un digito
            error(ERROR_excedido);
            continue;
        }

        switch (submenu2[0]) {
            case 'a': {
                dl_pacientes = alta_paciente(pacientes, dl_pacientes);
                break;
            }
            case 'b': {
                modificacion_paciente(pacientes, dl_pacientes);
                break;
            }
            case 'c': {
                dl_pacientes = baja_paciente(pacientes, dl_pacientes, puntero_inicial_turnos);
                break;
            }
            case 'd': {
                listado_paciente(pacientes, dl_pacientes);
                break;
            }
            case 'e': {
                return dl_pacientes;
                break;
            }
            default: {
                error(ERROR_letra);
                break;
            }
        }
    }while(submenu2 != "e");
    return dl_pacientes;
}

/*PROPOSITO: Mostrar el Submenu Administrar Turnos de tipo nodo_turno

  PARAMETROS: * puntero_inicial_turnos: puntero tipo Nodo_Turno que almacena el primer nodo de la lista de turnos
              * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * pacientes[]: arreglo de tipo paciente y representa las disponibles en el sistema
              * dl_pacientes:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: puntero_inicial_turnos */

Nodo_Turno *administrar_turnos(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Paciente pacientes[], int dl_pacientes){
    string submenu3;
    do { //menu
        cout << "\n3. Administrar Turnos: \n"
                "   a) Alta de Turnos. \n"
                "   b) Modificacion de Turnos. \n"
                "   c) Baja de Turnos. \n"
                "   d) Listado de Turnos. \n"
                "   e) Menu Principal. \n";

        cout <<"Opcion: ";
        cin >> submenu3;
        system("cls");

        if (submenu3.length() > 1) {        //si se ingresa mas de un caracter, muestra el error
            error(ERROR_excedido);
            continue;
        }

        switch (submenu3[0]) {
            case 'a': {
                puntero_inicial_turnos = alta_turno(puntero_inicial_turnos, pacientes, dl_pacientes, especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'b': {
                modificacion_turno(puntero_inicial_turnos, especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'c': {
                baja_turno(puntero_inicial_turnos, especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'd': {
                listado_turnos(puntero_inicial_turnos, especialidades_medicas, dl_especialidades_medicas);
                break;
            }
            case 'e': {
                return puntero_inicial_turnos;
            }
            default: {
                error(ERROR_letra);
                break;
            }
        }
    }while(submenu3 != "e");
    return puntero_inicial_turnos;
}

/*PROPOSITO: pausar el programa hasta que el usuario presione ENTER

  PARAMETROS: ninguno

  RETORNO: no tiene valor de retorno*/

void pausa(){
    /*Continua con la ejecucion del programa solo si el usuario presiona unicamente ENTER*/
    do{
        cout << "Presione ENTER para continuar...\n";
        cin.ignore();
    }while(cin.get() != '\n');
}

/*PROPOSITO: permitir al usuario el ingreso de un numero de dni

  PARAMETROS: ninguno

  RETORNO: retorna el dni modificado (con puntos) (xx.xxx.xx)*/

string pedir_dni(){
    /*Esta funcion pide al usuario un numero de DNI y luego lo retorna con puntos.
    El usuario solo puede ingresar un DNI valido de 8 y 7 digitos*/
    string dni;
    //Pide al usuario un DNI valido de 7 u 8 digitos
    do{
        cout << "\nIngrese el DNI (sin puntuaciones) del paciente: ";
        cin >> dni;
        if(dni.length() != 8 and dni.length() != 7){
            cout << "ERROR: El DNI ingresado no es valido.\n";
        }
    }while(dni.length() != 8 and dni.length() != 7);
    return dni;
}

/*PROPOSITO: agregar una especialidad medica al sistema

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: retorna el tipo de especialidad medica que se dio de alta y el codigo unico */

int alta_especialidad_medica (Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){

    /*Esta funcion agrega una especialidad medica con los datos requeridos:
     nombre de especialidad y la descripcion. A la misma se le asigna un codigo
     unico de identificacion.*/

    if (dl_especialidades_medicas < DF_ESPECIALIDAD_MEDICA){      //En caso de que la Dimension Logica sea menor que la Dimension Fisica, comienza la generacion de la Especialidad Medica
        cout << "\nSelecciono la opcion a por error? ingrese la letra s para volver al menu anterior.\n "       //Le pregunta al ususario si ha ingresado por error para que no se tenga que crear una Especialidad Medica si o si
                "Si no es asi, presione ENTER y se generaran y pediran datos para la Especialidad Medica.\n";

        cin.ignore();
        if(cin.get() == 's'){
            system("cls");
            return dl_especialidades_medicas;
        }
        system("cls");

        //Codigo Unico de la Especialidad Medica
        if(dl_especialidades_medicas == 0){
            especialidades_medicas[dl_especialidades_medicas].codigo = 0;
        }
        else{
            especialidades_medicas[dl_especialidades_medicas].codigo = especialidades_medicas[dl_especialidades_medicas - 1].codigo + 1;
        }
        system("cls");

        //Especialidad Medica
        cout <<"Escriba una especialidad medica: ";
        getline(cin>>ws,especialidades_medicas[dl_especialidades_medicas].nombre);
        system("cls");

        //Descripcion de la Especialidad Medica
        descripcion_especialidad_medica(especialidades_medicas, dl_especialidades_medicas);
        system("cls");

        //Mostrar Especialidad Medica
        cout << "La especialidad medica se dio de alta con exito.\n";
        mostrar_especialidad_medica(especialidades_medicas, dl_especialidades_medicas);

        pausa();
        system("cls");
        dl_especialidades_medicas++;
    }

    else{   //en caso de que se halla llenado el cupo de Especialidades Medicas (DF) sale menaje por pantalla y vuelve al Menu anterior
        cout << "Se ha alcanzado la maxima cantidad de Especialidades Medicas que puede almacenar el programa.\n";
        pausa();
        system("cls");
    }
    return dl_especialidades_medicas;
}

/*PROPOSITO: modificar una especialidad medica ya existente en el programa

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: en un principio no tiene valor de retorno*/

void modificacion_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){

    /* Busqueda de la especialidad médica ingresada anteriormente en el programa a modificar a través del código único de identificación. */

    int codigo_a_buscar;
    cout << "Ingrese el Codigo Unico de Identificacion de la Especialidad Medica de la cual quiere modificar los datos: ";
    cin >> codigo_a_buscar;
    while(codigo_a_buscar < 0) {
        cout << "ERROR: El Codigo Unico de Identificacion ingresado no es valido, reingrese\n";
        cin >> codigo_a_buscar;
    }

    bool codigo_encontrado = false;
    for( int i=0 ; i < dl_especialidades_medicas; i++ ){
        if(especialidades_medicas[i].codigo == codigo_a_buscar){
            codigo_encontrado = true;

            string opcion;

            do{
                cout << "\n\nCodigo Unico de Identificacion encontrado. \n";
                mostrar_especialidad_medica(especialidades_medicas, i);

                cout << "\nSeleccione una opcion a modificar: \n"
                        "   a. Modificar Nombre. \n"
                        "   b. Modificar Descripcion. \n"
                        "   c. Volver al Menu Anterior. \n";

                //Lee la opcion elegida por el usuario
                cout << "Opcion: ";
                cin >> opcion;
                system("cls");

                if (opcion.length() > 1) {
                    error(ERROR_excedido);
                    continue;
                }

                switch (opcion[0]) {
                    case 'a': {         //Modificar Nombre
                        cout <<"Escriba una especialidad medica";
                        getline(cin>>ws,especialidades_medicas[i].nombre);
                        break;
                    }
                    case 'b': {         //Modificar Descripcion
                        descripcion_especialidad_medica(especialidades_medicas, i);
                        break;
                    }
                    case 'c': {         //Volver al menu anterior.
                        /* En este caso en vez de hacer un break podrían hacer un return. De esta forma, se vuelve al lugar donde se la invocó a la función (el menu anterior)
                         * Si el for termina en forma natural, es decir que no se encontró nunca con este return, avisa que no encontro el código.*/
                        break; //return modificacion_especialidad_medica(especialidades_medicas, dl_especialidades_medicas);
                    }
                    default: {
                        error(ERROR_letra);
                        break;
                    }
                }
            }while(opcion[0] != 'c');

            cout << "La operacion de modificacion finalizo con exito.\n";
            pausa();
            system("cls");
        }
    }
    if(!codigo_encontrado){
        cout << "\nNo se encontro ninguna Especialidad Medica con el Codigo Unico de Identificacion igresado. Se regresara al menu anterior.\n";
        pausa();
        system("cls");
    }
    system("cls");
}

/*PROPOSITO: borrar una especialidad medica guardada en el sistema

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero inicial de la lista que contiene los turnos almacenados en el sistema

  RETORNO: en el caso de que se dé de baja una especialidad medica, retorna el valor con la dimension logica restada. */

int baja_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas, Nodo_Turno *puntero_inicial_turnos){
    /*Esta funcion permite dar de baja una especialidad medica existente
      mediante su codigo unico de identificacion.*/

    int codigo_a_buscar;
    do{
        cout << "Ingrese el Codigo Unico de Identificacion de la Especialidad Medica de la cual quiere dar de baja: ";
        cin >> codigo_a_buscar;

        if(codigo_a_buscar < 0){
            cout << "ERROR: El Codigo Unico de Identificacion ingresado no es valido.\n";
        }
    }while(codigo_a_buscar < 0);

    bool codigo_encontrado = false;
    for(int i=0 ; i < dl_especialidades_medicas; i++ ){
        if(especialidades_medicas[i].codigo == codigo_a_buscar){
            codigo_encontrado = true;

            string opcion;
            do{
                mostrar_especialidad_medica(especialidades_medicas, i);

                cout << "\nDesea eliminar esta especialidad Medica? \n"
                        "   a. Eliminar. \n"
                        "   b. Volver al Menu Anterior. \n";

                //Lee la opcion elegida por el usuario
                cout << "Opcion: ";
                cin >> opcion;
                system("cls");

                if (opcion.length() > 1) {
                    error(ERROR_excedido);
                    continue;
                }

                switch (opcion[0]) {
                    //Elimina la especialidad medica.
                    case 'a':{
                        bool turno_activo = false;
                        //Se busca un turno que este activo y este relacionado a la especialidad medica ingresada
                        for(Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente){
                            if(aux->dato.estado == 1 and aux->dato.especialidad_medica == codigo_a_buscar){
                                turno_activo = true;
                                break;
                            }
                        }
                        //Si no se encontro un turno, se ejecuta esto y se procede a la eliminacion
                        if(!turno_activo){
                            //Se encarga de realizar la eliminacion de la especialidad medica mediante el corrimiento de todos los elementos del arreglo especialidades_medicas
                            for(int k = i; k < dl_especialidades_medicas - 1; k++){
                                especialidades_medicas[k] = especialidades_medicas[k+1];
                            }
                            cout << "\nLa Especialidad Medica se ha eliminado con exito. Se regresara al menu anterior.\n";
                            pausa();
                            dl_especialidades_medicas--;
                            return dl_especialidades_medicas;
                        }
                            //En el caso de que se haya encontrado un turno activo relacionado a la especialidad medica, se indica en pantalla y se vuelve al menu anterior
                        else{
                            cout << "\nLa Especialidad Medica no puede eliminarse debido a que se encuentra presente en uno o mas turnos reservados.\n Se regresara al menu anterior.\n";
                            pausa();
                            system("cls");
                            return dl_especialidades_medicas;
                        }
                        break;
                    }
                    case 'b': {     //Volver al Menu Anterior.
                        break;
                    }
                    default: {
                        error(ERROR_letra);
                        break;
                    }
                }
            }while(opcion[0] != 'b');
            cout << "La operacion de modificacion finalizo con exito.\n";
            pausa();
            system("cls");
        }
    }
    if(!codigo_encontrado){
        cout << "\nNo se encontro ninguna Especialidad Medica con el Codigo ingresado. Se regresara al menu anterior.\n";
        pausa();
        system("cls");
    }
    return dl_especialidades_medicas;
}

/*PROPOSITO: buscar una especialidad medica existente o ver todas las almacenadas.

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: no tiene valor de retorno*/

void listado_especialidad_medica(Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){

    /*Esta funcion permite ver un listado completo de las especialidades
      medicas registradas o realizar una busqueda mediante un codigo unico
      de identificacion. */

    string submenu_listado;
    if(dl_especialidades_medicas == 0){
        cout << "No hay Especialidades Medicas registradas.\n";
        pausa();
        system("cls");
    }
    else{
        do {
            cout << "\nListado de Especialidades Medicas: \n"
                    "   a) Completo. \n"
                    "   b) Busqueda. \n"
                    "   c) Volver al Menu de Especialidades Medicas. \n";

            cout <<"Opcion: ";
            cin >> submenu_listado;
            system("cls");

            if (submenu_listado.length() > 1) {
                error(ERROR_excedido);
                continue;
            }

            switch (submenu_listado[0]) {
                case 'a': {     //Muestra listado completo de Especialidades Medicas de toda la Clinica
                    for (int i = 0; i < dl_especialidades_medicas; i++) {
                        mostrar_especialidad_medica(especialidades_medicas, i);
                    }
                    pausa();
                    system("cls");
                    break;
                }
                case 'b': {     //Muestra el listado de todas las Especialidades Medicas filtradas por el codigo unico
                    int codigo_a_buscar;
                    cout << "Ingrese el Codigo Unico de Identificacion de la Especialidad Medica de la cual quiere modificar los datos: ";
                    cin >> codigo_a_buscar;
                    while(codigo_a_buscar < 0) {
                        cout << "ERROR: El Codigo Unico de Identificacion ingresado no es valido, reingrese\n";
                        cin >> codigo_a_buscar;
                    }
                    bool codigo_encontrado = false;
                    for( int i=0 ; i < dl_especialidades_medicas; i++ ) {
                        if (especialidades_medicas[i].codigo == codigo_a_buscar) {
                            codigo_encontrado = true;

                            cout << "\n\nCodigo Unico de Identificacion encontrado. \n";
                            mostrar_especialidad_medica(especialidades_medicas, i);
                            pausa();
                        }
                    }
                    if(!codigo_encontrado){
                        cout << "\nNo se encontro ninguna Especialidad Medica con el Codigo Unico de Identificacion igresado. Se regresara al menu anterior.\n";
                        pausa();
                        system("cls");
                    }
                    system("cls");
                    break;
                }
                case 'c': {
                    break;
                }
                default: {
                    error(ERROR_letra);
                    break;
                }
            }
        }while(submenu_listado != "c");
    }
}

/*PROPOSITO: buscar una especialidad medica existente o ver todas las almacenadas.

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * int i: iterador que recorre el arreglo de especialidades medicas

  RETORNO: no tiene valor de retorno*/

void descripcion_especialidad_medica(Especialidad_Medica especialidades_medicas[], int i){
    string desc;

    do{
        cout << "Desea ponerle una descripcion a la Especialidad Medica?\n"
                "   a) Ingresar una descripcion. \n"
                "   b) Omitir. \n";

        //Lee la opcion elegida por el usuario
        cout << "Opcion: ";
        cin >> desc;
        system("cls");

        if (desc.length() > 1) {
            error(ERROR_excedido);
            continue;
        }

        switch (desc[0]) {
            case 'a':{
                cout << "Indique la descripcion a usar: ";
                getline(cin>>ws,especialidades_medicas[i].descripcion);
                break;
            }
            case 'b':{
                //La descripcion quedara vacia
                especialidades_medicas[i].descripcion = "";
                break;
            }
            default:{
                error(ERROR_letra);
                break;
            }
        }
    }while (desc != "a" && desc != "b");
}

/*PROPOSITO: Imprimir todos los datos de la Especialidad Medica

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * int i: iterador que recorre el struct de especialidades medicas

  RETORNO: No tiene valor de retorno */

void mostrar_especialidad_medica(Especialidad_Medica especialidades_medicas[], int i){

    /* Esta funcion imprime todos los datos relacionados con una Especialidad Medica. Esta misma a imprimir es indicada por el iterador i */

    cout << "\n\nLos datos de la especialidad medica indicada son: \n";
    cout << "     Codigo Unico de Identificacion: " << especialidades_medicas[i].codigo << endl;
    cout << "     Nombre: " << especialidades_medicas[i].nombre << endl;
    if(especialidades_medicas[i].descripcion == ""){
        cout << "     Descripcion: (Sin descripcion.)\n";
    } else{
        cout << "     Descripcion: " << especialidades_medicas[i].descripcion << endl;
    }
}

/*PROPOSITO: agregar un paciente al sistema.

  PARAMETROS: * pacientes[]: arreglo de tipo paciente y representa las disponibles en el sistema
              * dl_pacientes: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: retorna la dimension logica del arreglo pacientes*/

int alta_paciente(Paciente pacientes[], int dl_pacientes){

    /*Esta funcion agrega un paciente al sistema
    con todos los campos requeridos y obligatorios: apellido, nombre, dni y telefono. */

    //Se ejecuta solo si la dimension logica del arreglo pacientes es menor a su dimension fisica
    if(dl_pacientes < DF_PACIENTES)
    {
        /*Permite al usuario regreasar al menu anterior ingresando la letra s. Esto se hizo para evitar que se vea obligado a ingresar datos aleatorios si selecciono la opcion por error
        y afectar a lo almacenado en el arreglo de pacientes*/
        cout << "Se ingreso a la opcion de alta paciente.\nSelecciono la opcion a por error? ingrese la letra s para volver al menu anterior. Si no es asi, presione ENTER. ";
        cin.ignore();
        if(cin.get() == 's'){
            system("cls");
            return dl_pacientes;
        }

        cout << "\nA continuacion se le pediran los datos del Paciente que desea ingresar.\n\n";

        //permite al usuario ingresar el apellido del paciente
        modificar_dato_paciente(pacientes, dl_pacientes, "a");
        //permite al usuario ingresar el nombre del paciente
        modificar_dato_paciente(pacientes, dl_pacientes, "b");
        //permite al usuario ingresar el telefono del paciente, el cual debe tener
        modificar_dato_paciente(pacientes, dl_pacientes, "c");

        //permite al usuario ingresar el DNI del paciente, tomando solo DNIs de 8 o 7 digitos
        pacientes[dl_pacientes].dni = pedir_dni();

        //Verifica si el DNI que ingreso el usuario ya existe, en el caso de que exista, no se aumenta dl_pacientes, por lo que no se da de alta al paciente nuevamente
        for(int i = 0; i < dl_pacientes; i++){
            if(pacientes[i].dni == pacientes[dl_pacientes].dni){
                cout << "\nEl dni del paciente que quiere dar de alta ya esta registrado en el sistema. Se regresara al menu anterior.\n";
                pausa();
                system("cls");
                return dl_pacientes;
            }
        }
        system("cls");
        cout << "\nEl Paciente se dio de alta con exito.\n";
        pausa();
        system("cls");

        dl_pacientes++;
        return dl_pacientes;
    }
        //Se ejecuta si la dimension logica del arreglo pacientes es igual o mayor a la dimension fisica
    else{
        cout << "Se ha alcanzado la maxima cantidad de Pacientes que puede almacenar el programa.\n";
        pausa();
        system("cls");
        return dl_pacientes;
    }
}

/*PROPOSITO: modificar datos personales de un paciente

  PARAMETROS: * pacientes[]: un arreglo que contiene estructuras de tipo pacientes y representa las disponibles en el sistema
              * dl_pacientes: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: sin retorno*/

void modificacion_paciente(Paciente pacientes[], int dl_pacientes){

    /*Esta funcion permite modificar los datos personales de un paciente (apellido, nombre y/o telefono
     mediante su DNI. Si no esta almacenado el paciente, se indicara.*/
    cout << "A continuacion se le pediran los datos del Paciente que desea modificar.";

    //Pide al usuario ingresar un DNI de 8 o 7 digitos
    string dni_a_buscar = pedir_dni();

    bool paciente_encontrado = false;
    //Busca en el arreglo pacientes el dni ingresado por el usuario hasta encontrar o no una coincidencia
    for( int i=0 ; i < dl_pacientes; i++ ){
        /*Si encuentra una coincidencia, muestra los datos relacionados al DNI ingresado y, para evitar el ingreso de todos los datos nuevamente, pregunta cual quiere modificar
        Se repite hasta que el usuario no quiera modificar mas datos y seleccione la opcion para volver al menu anterior
        El dato que se modifique, se mostrara actualizado al ejecutarse el while nuevamente*/
        if(pacientes[i].dni == dni_a_buscar){
            paciente_encontrado = true;
            string opcion;
            do{
                cout << "\n\nLos datos del Paciente con DNI " << dni_a_buscar <<  " son:";
                cout << "\n     Apellido: " << pacientes[i].apellido;
                cout << "\n     Nombre: " << pacientes[i].nombre;
                cout << "\n     Telefono: " << pacientes[i].telefono;

                cout << "\n\nSeleccione una opcion: "
                        "\n   a. Modificar apellido."
                        "\n   b. Modificar nombre."
                        "\n   c. Modificar telefono."
                        "\n   d. Volver al menu anterior."
                        "\nOpcion: ";
                cin >> opcion;
                //Si el usuario ingresa mas de un caracter, indicara tal error y pedira nuevamente que seleccione una opcion
                if (opcion.length() > 1) {
                    error(ERROR_excedido);
                    continue;
                }
                //Solo se ejecuta si el usuario no quiere volver al menu principal y, dependiendo de que opcion seleccione, se le pedira ese dato.
                if(opcion[0] != 'd'){
                    modificar_dato_paciente(pacientes, i, opcion);
                }
                system("cls");
            }while(opcion[0] != 'd');
            cout << "La operacion de modificacion finalizo con exito.\n";
            pausa();
            system("cls");
        }
    }

    //En el caso de que no se haya encontrado ningun paciente con el dni indicado, se indicara en pantalla y se regresara al menu anterior
    if(!paciente_encontrado){
        cout << "\nNo se encontro ningun paciente con el numero de DNI indicado. Se regresara al menu anterior.\n";
        pausa();
        system("cls");
    }
}

/*PROPOSITO: borrar a un paciente del sistema

  PARAMETROS: * pacientes[]: un arreglo que contiene estructuras de tipo pacientes y representa las disponibles en el sistema
              * dl_pacientes: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero tipo Nodo_Turno que almacena el primer nodo de la lista de turnos

  RETORNO: en principio no tiene valor de retorno*/

int baja_paciente(Paciente pacientes[], int dl_pacientes, Nodo_Turno *puntero_inicial_turnos){

    /*Esta funcion permite borrar del sistema a un paciente ingresando su DNI.
     Si el paciente no esta almacenado, se indicara por pantalla.
     */

    cout << "A continuacion se le pediran los datos del Paciente que desea eliminar.\n";
    //Pedira al usuario que ingrese un DNI valido (8 o 7 digitos)
    string paciente_a_borrar = pedir_dni();

    //Comienza a buscar el DNI en el arreglo pacientes
    for(int i = 0; i < dl_pacientes; i++){
        //Si encuentra el DNI, se mostraran los datos relacionados al mismo y permitira eliminar o no al paciente
        if(pacientes[i].dni == paciente_a_borrar){
            string borrar_paciente;
            //Preguntara al usuario si quiere eliminar o no al paciente hasta que ingrese una opcion valida
            do{
                cout << "\n\nLos datos del paciente con DNI " << paciente_a_borrar <<  " son:";
                cout << "\n     Apellido: " << pacientes[i].apellido;
                cout << "\n     Nombre: " << pacientes[i].nombre;
                cout << "\n     Telefono: " << pacientes[i].telefono;

                cout << "\n\nIndique una opcion:"
                        "\n     1- Eliminar paciente."
                        "\n     2- No eliminar paciente."
                        "\nOpcion: ";
                cin >> borrar_paciente;

                if(borrar_paciente.length() > 1){
                    error(ERROR_excedido);
                    continue;
                }

                /*Se ejecuta si solo se ingreso un caracter y el usuario decidio no eliminar al paciente
                Detiene la ejecucion de la funcion al retornar dl_pacientes*/
                if(borrar_paciente[0] == '2'){
                    cout << "\n\nUsted decidio no eliminar del sistema al paciente.\n";
                    pausa();
                    system("cls");
                    return dl_pacientes;
                }
            }while((borrar_paciente[0] != '1' and borrar_paciente[0] != '2') or borrar_paciente.length() > 1);

            //Verifica si hay turnos relacionados al paciente y si estan activos, en el caso de que existan y esten activos, no se puede eliminar al paciente y lo indica en pantalla
            for(Nodo_Turno *aux = puntero_inicial_turnos; puntero_inicial_turnos != nullptr; aux = aux->siguiente){
                if(paciente_a_borrar == aux->dato.paciente and aux->dato.estado == 1){
                    cout << "\nEl paciente no puede eliminarse debido a que tiene uno o mas turnos reservados.\n";
                    pausa();
                    system("cls");
                    return dl_pacientes;
                }
            }

            //Se encarga de realizar la eliminacion del paciente mediante el corrimiento de todos los elementos del arreglo pacientes
            for(int j = i; j < dl_pacientes - 1; j++){
                pacientes[j] = pacientes[j + 1];
            }
            cout << "\nEl paciente se ha eliminado con exito.\n";
            pausa();
            system("cls");
            dl_pacientes--;
            return dl_pacientes;
        }
    }

    //Solo se ejecuta si el DNI ingresdo por el usuario no está registrado, entonces informa de la situacion
    cout << "\nNo se pudo encontrar ningun paciente con el DNI indicado.\n";
    pausa();
    system("cls");
    return dl_pacientes;
}

/*PROPOSITO: buscar a un paciente para ver sus datos o ver un listado de todos los pacientes junto a sus datos.

  PARAMETROS: * pacientes[]: un arreglo que contiene estructuras de tipo pacientes y representa las disponibles en el sistema
              * dl_pacientes: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: no tiene valor de retorno (solo es para mostrar datos)*/

void listado_paciente(Paciente pacientes[], int dl_pacientes){

    /*Esta funcion permite consultar los datos de todos los pacientes en conjunto
    o de uno solo a la vez.*/
    string submenu_listado;
    if(dl_pacientes == 0){
        cout << "No hay pacientes registrados.\n";
        pausa();
        system("cls");

    }
    else{
        do {
            cout << "\nIndique una opcion: \n"
                    "   a) Ver lista completa de pacientes. \n"
                    "   b) Busqueda de paciente por DNI. \n"
                    "   c) Volver al Menu de Administracion de Pacientes. \n";

            cout <<"Opcion: ";
            cin >> submenu_listado;
            system("cls");

            if (submenu_listado.length() > 1) {
                error(ERROR_excedido);
                continue;
            }

            switch (submenu_listado[0]) {
                case 'a': {
                    cout << "Los pacientes registrados actualmente y sus datos son: \n\n";
                    for(int i = 0; i < dl_pacientes; i++){
                        cout << "Apellido: " << pacientes[i].apellido << endl;
                        cout << "Nombre: " << pacientes[i].nombre << endl;
                        cout << "DNI: " << pacientes[i].dni << endl;
                        cout << "Telefono: " << pacientes[i].telefono << endl << endl;
                    }
                    pausa();
                    system("cls");
                    break;
                }
                case 'b': {
                    string dni_a_buscar = pedir_dni();
                    for(int i = 0; i < dl_pacientes; i++){
                        if(pacientes[i].dni == dni_a_buscar){
                            cout << "Los datos del paciente encontrado son: \n\n";
                            cout << "Apellido: " << pacientes[i].apellido << endl;
                            cout << "Nombre: " << pacientes[i].nombre << endl;
                            cout << "DNI: " << pacientes[i].dni << endl;
                            cout << "Telefono: " << pacientes[i].telefono << endl << endl;
                            break;
                        }
                        if((i+1 == dl_pacientes) and (pacientes[i].dni != dni_a_buscar)){
                            cout << "No se encontro ningun paciente con el DNI indicado.\n";
                        }
                    }
                    pausa();
                    system("cls");
                    break;
                }
                case 'c': {
                    break;
                }
                default: {
                    error(ERROR_letra);
                    break;
                }
            }
        }while((submenu_listado != "c") and (submenu_listado != "b") and (submenu_listado != "a"));}
}

/*PROPOSITO: modificar o agregar un dato especifico de un paciente

   PARAMETROS: * pacientes[]: un arreglo que contiene estructuras de tipo pacientes y representa las disponibles en el sistema
               * indice_paciente: indice donde se encuentra el dato del paciente a agregar/modificar
               * opcion: dato que se quiere modificar

  RETORNO: retorna la modificacion de un dato o el agregado de un paciente*/

void modificar_dato_paciente(Paciente pacientes[], int indice_paciente, string opcion){
    /*Esta funcion agrega o modifica un dato especifico de un paciente segun la letra que tenga como parametro
    Las opciones aceptadas son a) apellido, b) nombre, c) telefono*/
    switch(opcion[0]){
        case 'a':{
            /* Se utiliza un if con la misma condicion dentro del bucle do while para que cada vez que haya un error, se indique nuevamente al usuario que dato tiene que ingresar */
            do{
                cout << "Indique el apellido del Paciente: ";
                cin >> pacientes[indice_paciente].apellido;
                if((pacientes[indice_paciente].apellido).length() < 1){
                    error(ERROR_campo_vacio);
                }
            }while(pacientes[indice_paciente].apellido.length() < 1);
            break;
        }
        case 'b':{
            do{
                cout << "\nIndique el nombre del Paciente: ";
                cin >> pacientes[indice_paciente].nombre;
                if(pacientes[indice_paciente].nombre.length() < 1){
                    error(ERROR_campo_vacio);
                }
            }while(pacientes[indice_paciente].nombre.length() < 1);
            break;
        }
        case 'c':{
            do{
                cout << "\nIndique el numero de telefono del Paciente (sin guiones ni espacios): ";
                cin >> pacientes[indice_paciente].telefono;
                if(pacientes[indice_paciente].telefono.length() != 10){
                    cout << "ERROR: El numero de telefono ingresado no es valido. Vuelva a ingresarlo.\n";
                }
            }while(pacientes[indice_paciente].telefono.length() != 10);
            break;
        }
        default: {
            error(ERROR_letra);
            break;
        }
    }
}

/*PROPOSITO: VERIFICAR e INDICAR si una fecha tiene un formato valida (AAAAMMDD) y es igual o mayor al año actual

  PARAMETROS: * fecha: fecha a verificar

  RETORNO: retorna true si la fecha es valida y false si no lo es*/

bool validar_fecha(int fecha){
    int dia, mes, anio;
    int dias_de_meses_del_anio[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //Se utiliza la biblioteca time.h para conocer el anio actual del sistema
    time_t ahora = time(0);
    struct tm *tiempoactual = localtime(&ahora);
    int anio_actual = tiempoactual->tm_year + 1900;

    //Se desgloza la fecha ingresada en dia, mes y anio
    dia = fecha%100;
    mes = (fecha/100)%100;
    anio = fecha/10000;

    //Se verifica si la fecha ingresada tiene la cantidad de digitos que pide el formato
    if(fecha < 10000000 || fecha > 99999999){
        cout << "\nLa cantidad de digitos ingresados no es valida. Intentelo nuevamente.";
        pausa();
        system("cls");
        return false;
    }
    /*Verifica si:
     1) el dia ingresado se encuentra entre uno que pueda estar en un mes (1 y 31)
     2) el mes ingresado esta entre 1 y 12
     3) el anio es igual o mayor al actual*/
    if((dia >= 1 && dia <= dias_de_meses_del_anio[mes-1]) && (mes >= 1 && mes <=12) && (anio >= anio_actual)){
        return true;
    }
    else{
        cout << "\nLa fecha ingresada no es valida. Verifique el formato nuevamente.\n";
        pausa();
        system("cls");
        return false;
    }
}

/*PROPOSITO: insertar al final de la lista un nodo tipo Nodo_Turno

  PARAMETRO: * puntero_inicial: es donde inicia la lista
             * puntero_nuevo: es el puntero del elemento a insertar

  RETORNO: retorna el puntero inicial*/

Nodo_Turno *insertar_final(Nodo_Turno *puntero_inicial, Nodo_Turno *puntero_nuevo){
    if(puntero_inicial == nullptr){
        puntero_inicial = puntero_nuevo;
    }
    else{
        Nodo_Turno *aux = puntero_inicial;
        while(aux->siguiente != nullptr){
            aux = aux->siguiente;
        }
        aux->siguiente = puntero_nuevo;
    }
    return puntero_inicial;
}

/*PROPOSITO: borrar todos los elementos de una lista tipo Nodo

  PARAMETROS: puntero_inicial de la lista tipo Nodo

  RETORNO: no retorna nada*/

void vaciar_lista_nodo(Nodo *puntero_inicial){
    if(puntero_inicial != nullptr){
        if(puntero_inicial->siguiente == nullptr){
            delete puntero_inicial;
        }
        else{
            Nodo *borrar = nullptr;
            Nodo *aux = puntero_inicial;
            while(aux->siguiente != nullptr){
                borrar = aux;
                aux = aux->siguiente;
                delete borrar;
            }
            delete aux;
        }
    }
}

/*PROPOSITO: insertar al final de la lista un nodo tipo Nodo

  PARAMETRO: * puntero_inicial: es donde inicia la lista
             * puntero_nuevo: es el puntero del elemento a insertar

  RETORNO: retorna el puntero inicial
*/

Nodo *insertar_final_nodo(Nodo *puntero_inicial, Nodo *puntero_nuevo){
    if(puntero_inicial == nullptr){
        puntero_inicial = puntero_nuevo;
    }
    else{
        Nodo *aux = puntero_inicial;
        while(aux->siguiente != nullptr){
            aux = aux->siguiente;
        }
        aux->siguiente = puntero_nuevo;
    }
    return puntero_inicial;
}

/*PROPOSITO: reservar un turno para un paciente

 PARAMETROS: * puntero_inicial_turnos: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta
             * especialidades_medicas[]: arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
             * dl_especialidades_medicas: entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
             * pacintes[]: un arreglo que contiene estructuras de tipo pacientes y representa las disponibles en el sistema
             * dl_pacientes:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: se retora un valor a la dimension logica de turno*/

Nodo_Turno *alta_turno(Nodo_Turno *puntero_inicial_turnos, Paciente pacientes[], int dl_pacientes, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas) {  //aca

/*Esta funcion permite reservar un turno (el cual se diferenciara por un codigo) que contendra:
DNI del paciente, identificacion de la especialidad medica y estado del turno ("cancelado" o "activo")*/

    cout << "\nSelecciono la opcion a por error? ingrese la letra s para volver al menu anterior. Si no es asi, presione ENTER. ";
    cin.ignore();
    if (cin.get() == 's') {
        system("cls");
        return puntero_inicial_turnos;
    }
    system("cls");

    //Verifica que existan pacientes registrados. Si no es asi, no se pueden dar de alta turnos y se vuelve al menu anterior.
    if(dl_pacientes == 0){
        cout << "No hay pacientes registrados. No se pueden dar de alta nuevos turnos.\n";
        pausa();
        system("cls");
        return puntero_inicial_turnos;
    }
    if(dl_especialidades_medicas == 0){   //si la dimension logica de especialidades medicas es 0, no existe ninguna registrada
        cout << "No existen especialidades medicas registradas. No se pueden dar de alta turnos.";
        pausa();
        system("cls");
        return puntero_inicial_turnos;
    }

    cout << "\nA continuacion se generaran y pediran datos para su Turno.\n\n";
    string dni_a_buscar;
    int codigo_a_buscar;
    //paciente

    dni_a_buscar = pedir_dni();

    //Busca en el arreglo pacientes el dni ingresado por el usuario hasta encontrar o no una coincidencia
    for(int i=0 ; i < dl_pacientes; i++){
        if(pacientes[i].dni == dni_a_buscar){
            cout << "Se ha encontrado el Paciente solicitado.\n";
            pausa();
            system("cls");
            break;
        }
        //En el caso de que no se haya encontrado ningun paciente con el dni indicado, se indicara en pantalla y se regresara al menu anterior
        if(i+1 == dl_pacientes and pacientes[i].dni != dni_a_buscar){
            cout << "\nNo se encontro ningun paciente con el numero de DNI indicado. Se regresara al menu anterior.\n";
            pausa();
            system("cls");
            return puntero_inicial_turnos;
        }
    }


    Nodo_Turno *nuevo_nodo = new Nodo_Turno; //se está definiendo a nuevo_nodo como un puntero de tipo nodo_turno, new: se crea nuevo nodo reservando un espacio en la memoria para guardarlo

    nuevo_nodo->dato.paciente = dni_a_buscar;  //se almacena el dni y el estado(empieza en uno)
    nuevo_nodo->dato.estado = 1;
    nuevo_nodo->siguiente = nullptr; //se inicializa el puntero en nullptr

    //Pide una para el turno al usuario y verifica si es valido
    do{
        cout << "\nIngrese una fecha AAAAMMDD: ";
        cin >> nuevo_nodo->dato.fecha;
    }while(!validar_fecha(nuevo_nodo->dato.fecha));  //mientras que no exista la fecha se repetira
    system("cls");

    //hora
    hora_turno(nuevo_nodo);
    system("cls");


    //especialidad
    do {
        cout << "Ingrese el Codigo Unico de Identificacion de la Especialidad Medica para el turno a ingresar: ";
        cin >> codigo_a_buscar;
        if (codigo_a_buscar < 0) {
            cout << "ERROR: El Codigo Unico de Identificacion ingresado no es valido.\n";
        }
    }while (codigo_a_buscar < 0);

    /*Busca en el arreglo especialidades_medicas el Codigo Unico de Identificacion de la especialidad medica ingresado por el usuario hasta encontrar o no una coincidencia
    En el caso de que la encuentre, verifica si la especialidad medica esta relacionada al mismo paciente en algun turno*/
    for(int i=0 ; i < dl_especialidades_medicas; i++){
        if(especialidades_medicas[i].codigo == codigo_a_buscar){
            for(Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente){   //se declara un auxiliar para recorrer la lista;termina cuando aux es igual a nullptr; salta al siguiente en la lista
                if(aux->dato.especialidad_medica == codigo_a_buscar && aux->dato.paciente == dni_a_buscar){ //se detecta que el paciente ya tiene un turno con la especialidad medica elegida
                    cout << "\nEl paciente ya cuenta con un turno para esta especialidad medica. No puede tener mas de uno.\n"
                            "Se regresara al menu principal.\n";
                    pausa();
                    system("cls");
                    return puntero_inicial_turnos;
                }
            }
            nuevo_nodo->dato.especialidad_medica = codigo_a_buscar; //!
            cout << "Se ha encontrado la Especialidad Medica perteneciente al Codigo ingresado.\n";
            pausa();
            system("cls");
            break;
        }
        if(i+1 == dl_especialidades_medicas && especialidades_medicas[i].codigo != codigo_a_buscar){   //!
            cout << "\nNo se ha encontrado ninguna Especialidad Medica perteneciente al Codigo ingresado. Se regresara al menu anterior.\n";
            pausa();
            system("cls");
            delete nuevo_nodo;
            return puntero_inicial_turnos;
        }
    }

    if(puntero_inicial_turnos == nullptr){
        nuevo_nodo->dato.codigo = 0;
    }
    else {
        //Se usa un auxiliar y no el mismo puntero_inicial_turnos porque mas tarde se retorna //!
        Nodo_Turno *aux = puntero_inicial_turnos;
        while(aux->siguiente != nullptr){
            aux = aux->siguiente;
        }
        nuevo_nodo->dato.codigo = aux->dato.codigo + 1; //itera el valor del turno anterior ingresado
    }
    puntero_inicial_turnos = insertar_final(puntero_inicial_turnos, nuevo_nodo);

    //fin
    cout << "\nEl turno se dio de alta con exito.\n\n";
    pausa();
    system("cls");

    mostrar_turno(nuevo_nodo, especialidades_medicas, dl_especialidades_medicas);//muestra turno
    pausa();
    system("cls");

    return puntero_inicial_turnos;
}

/*PROPOSITO: mostrar un turno

  PARAMETROS: * puntero_turnos: puntero que contiene la struct tipo Turno con los datos a imprimir
              * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas ->: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: no tiene valor de retorno(solo muestra los turnos)*/

void mostrar_turno(Nodo_Turno *puntero_turno, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){
    /*Esta funcion imprime todos los datos de un turno, cuya struct con sus datos se encuentra en puntero_turno*/
    cout << "\nLos datos son: ";
    cout << "\n     Codigo Unico de Identificacion: " << puntero_turno->dato.codigo;
    cout << "\n     Fecha: " << puntero_turno->dato.fecha%100 << "/" << (puntero_turno->dato.fecha/100)%100 << "/" << puntero_turno->dato.fecha/10000; //imprime la fecha con barras
    cout << "\n     Hora: " << puntero_turno->dato.hora;
    cout << "\n     DNI del paciente: " << puntero_turno->dato.paciente;
    cout << "\n     Especialidad medica: ";
    for(int j = 0; j < dl_especialidades_medicas; j++){ //recorre la dl de especialidad medica
        if(puntero_turno->dato.especialidad_medica == especialidades_medicas[j].codigo){ //si coincide el codigo mostrara
            cout << especialidades_medicas[j].nombre << " (codigo " << puntero_turno->dato.especialidad_medica << ").";
            break;
        }
    }
    if(puntero_turno->dato.estado == 1){  //si el estado es 1 esta activo
        cout << "\n     Estado: activo\n";
    }
    else{ //si no, esta cancelado
        cout << "\n     Estado: cancelado\n";
    }
}

/*PROPOSITO: Muestra las horas posibles para reservar un turno

  PARAMETROS: * nuevo_turno: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta

  RETORNO: No tiene valor de retorno*/

void hora_turno(Nodo_Turno *nuevo_turno) {

    /*Esta funcion se encarga de mostrar todos los horarios posibles para reservar un turno*/

    string horarios[22]={"08:00 hs.","08:30 hs.","09:00 hs.","09:30 hs.", "10:00 hs.", "10:30 hs.", "11:00 hs.", "11:30 hs.", "12:00 hs.", "12:30 hs.", "13:00 hs.", "13:30 hs.", "14:00 hs.", "14:30 hs.", "15:00 hs.", "15:30 hs.", "16:00 hs.", "16:30 hs.", "17:00 hs.", "17:30 hs.", "18:00 hs.", "18:30 hs."};
    int submenu_hora;  //arreglo que guarda los horarios

//22 turnos
    do {
        cout << "\nSeleccione la hora deseada para su turno: \n";
        for(int i = 0; i<22 ; i++){
            cout<<i<<") "<<horarios[i]<<endl; //muestra los horarios
        }
        cout<<"Opcion: ";
        cin >> submenu_hora;
        system("cls");
        nuevo_turno->dato.hora = horarios[submenu_hora]; //le agrega el horario a la lista
    }while(submenu_hora < 0 || submenu_hora > 21);
}

/*PROPOSITO: modificar el turno de un paciente

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta

  RETORNO: no tiene valor de retorno*/

void modificacion_turno(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){
/* Permitira buscar un turno o turnos mediante el DNI del paciente a traves void paciente_turno y permitira modificar su fecha y hora.
 * Si no hay turnos registrados, se informara por pantalla.*/

    cout << "A continuacion se le pediran los datos del turno que desea modificar.";

    //Puntero inicial de la lista que contendra todos los turnos del paciente
    Nodo *puntero_inicial_turnos_del_paciente = nullptr;

    int codigo_unico;

    //Se pide al usuario que ingrese el dni del paciente para buscar sus turnos
    string dni_paciente = pedir_dni();

    //Busca los turnos relacionados al dni del paciente y guarda sus las direcciones en nodos de la lista que inicia en puntero_inicial_turnos_del_paciente
    for (Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente) {
        if (dni_paciente == aux->dato.paciente){
            Nodo *nuevo_nodo = new Nodo;
            nuevo_nodo->dato = aux;
            nuevo_nodo->siguiente = nullptr;
            puntero_inicial_turnos_del_paciente = insertar_final_nodo(puntero_inicial_turnos_del_paciente, nuevo_nodo);
        }
    }

    //En el caso de que no se encuentre ningun dni relacionado, se lo menciona al paciente y se vuelve al menu anterior
    if (puntero_inicial_turnos_del_paciente == nullptr) {
        cout << "No se ha encontrado ningun turno relacionado al DNI ingresado.\n";
        pausa();
    }

        //En el caso de que encuentre el dni ingresado, se muestran todos los turnos activos del paciente
    else{
        cout << "Turnos ACTIVOS del paciente: " << endl;
        for (Nodo *aux = puntero_inicial_turnos_del_paciente; aux != nullptr; aux = aux->siguiente){
            if(aux->dato->dato.estado == 1){
                mostrar_turno(aux->dato, especialidades_medicas, dl_especialidades_medicas);
                cout << endl;
            }
        }

        cout << "\nIngrese el codigo unico de identificacion del turno que desea modificar: ";
        cin >> codigo_unico;
        system("cls");

        for(Nodo *aux = puntero_inicial_turnos_del_paciente; aux != nullptr; aux = aux->siguiente){
            string opcion;
            if (aux->dato->dato.codigo == codigo_unico){
                do{
                    //muestra el turno del nodo con direccion aux->dato, el cual debera tener igual codigo unico al ingresado por el usuario
                    mostrar_turno(aux->dato, especialidades_medicas, dl_especialidades_medicas);

                    cout << endl;

                    cout << "Seleccione una opcion: \n"
                            "     a) Modificar fecha del turno.\n"
                            "     b) Modificar horario del turno.\n"
                            "     c) No modificar nada y regresar al menu anterior.\n";
                    cout << "Opcion: ";
                    cin >> opcion;
                    system("cls");

                    if(opcion.length() > 1){
                        error(ERROR_excedido);
                        continue;
                    }
                    switch(opcion[0]){
                        case 'a':{
                            do{
                                cout << "Ingrese una fecha en formato AAAAMMDD (sin barras): " << endl;
                                cin >> aux->dato->dato.fecha;
                                system("cls");
                            }while(!validar_fecha(aux->dato->dato.fecha));
                            break;
                        }
                        case 'b':{
                            hora_turno(aux->dato);
                            system("cls");
                            break;
                        }
                        case 'c':{
                            system("cls");
                            break;
                        }
                        default:
                            error(ERROR_letra);
                    }
                }while(opcion[0] != 'c' );
            }
        }
    }
    vaciar_lista_nodo(puntero_inicial_turnos_del_paciente);
}

/*PROPOSITO: verifica e indica si un turno esta dentro del plazo de dos dias para ser cancelado

  PARAMETROS: fecha: fecha del turno a verificar

  RETORNO: retorna false NO es cancelable y true si SI es cancelable*/

bool turno_cancelable_por_fecha(int fecha_verificar){
    //Arreglo que contiene la cantidad de dias de cada mes
    int dias_de_meses_del_anio[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dia_turno, mes_turno, anio_turno, dia_actual, mes_actual, anio_actual;

    //Se inicializan 3 variables para facilitar el manejo de la fecha del turno
    dia_turno = fecha_verificar%100;
    mes_turno = (fecha_verificar/100)%100;
    anio_turno = fecha_verificar/10000;

    //Estas dos lineas permiten verificar la fecha actual del sistema
    time_t ahora = time(0);
    struct tm *tiempoactual = localtime(&ahora);
    /*Aclaraciones con respecto a el uso de la libreria time.h:
     *tiempoactual->tm_year cuenta la cantidad de años que pasaron desde 1900, por eso se suma 1900 al año
     *tiempoactual->tm_mon retorna el mes actual del sistema operativo - 1, osea, desde 0 a 11
     *tiempoactual->tm_day retorna el dia actual del mes (puede ser desde 1 a 31)*/

    //Se inicializan 3 variables para facilitar el manejo de la fecha actual del sistema
    dia_actual = tiempoactual->tm_mday;
    mes_actual = tiempoactual->tm_mon + 1;
    anio_actual = tiempoactual->tm_year + 1900;

    /*CONDICIONAL IF: Compara el dia, mes y año actuales con los que estan indicados en el turno para verificar si es posible su cancelacion.
        Primera condicion: se cumple en el caso de que falten menos de dos dias para el turno, que sea el mismo mes que se indica en el sistema y que sea el mismo año.
        Segunda condicion (primer or): se cumple en el caso de que el turno seleccionado para cancelar sea el dia 1 de un mes, hoy sea el mes anterior a el mes del turno y el ultimo dia del mes,
        y que el año del sistema sea el mismo del turno.
        Tercera condicion (segundo or): se cumple en el caso de que la fecha del turno sea el dia 1 del mes, que el mes indicado en el sistema sea el ultimo del año y que el año
        actual del sistema sea el anterior al del turno.*/
    if((dia_turno-dia_actual < 2 && mes_turno == mes_actual && anio_turno == anio_actual) || (dia_turno == 1 && dias_de_meses_del_anio[mes_actual - 1] == dia_actual && anio_actual == anio_turno || (dia_turno == 1 && mes_actual == 12 && mes_turno == 1 && anio_actual+1 == anio_turno))){
        return false;
    }
    else{
        return true;
    }
}

/*PROPOSITO: se encarga de cancelar un turno

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta

  RETORNO: no tiene valor de retorno*/

void turno_seleccionado_para_cancelar(Nodo_Turno *puntero_turno, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){
    /*Esta funcion toma un turno para cancelar, verifica si es posible y le pregunta al usuario si quiere cancelarlo
    Si el turno fue cancelado anteriormente se lo indica al usuario
    Si el turno no se puede cancelar por no estar dentro de los 2 dias aceptados, se informa al usuario que no se puede cancelar y que puede haber una penalizacion para el paciente.*/

    string opcion_eliminar;
    do {
        //Muestra el turno a cancelar
        mostrar_turno(puntero_turno, especialidades_medicas, dl_especialidades_medicas);

        //verifica si la fecha del turno es valida para poder cancelarlo (2 dias)
        if (!turno_cancelable_por_fecha(puntero_turno->dato.fecha)){
            cout << "\n\nPor razones de agenda, el turno no puede ser cancelado."
                    "\nEn caso de que el cliente no asista al turno, recibira una penalizacion y se lo contactara telefonicamente.\n";
            pausa();
            break;
        }

        cout << "\n\n Indique una opcion: "
                "\n     1) cancelar turno"
                "\n     2) no cancelar turno"
                "\nOpcion: ";
        cin >> opcion_eliminar;

        //Verifica si la opcion ingresada tiene solo 1 digito, si no es asi, se advierte al usuario y se pide nuevamente el ingreso
        if (opcion_eliminar.length() > 1) {
            error(ERROR_excedido);
            continue;
        }

        switch(opcion_eliminar[0]){
            //Pone el estado 2 al turno, lo que significa "cancelado"
            case '1':{
                puntero_turno->dato.estado = 2;
                cout << "El turno fue cancelado con exito.\n";
                pausa();
                break;
            }
                //Se regresa al menu principal
            case '2':{
                break;
            }
                //Si la opcion ingresada es incorrecta, se advierte al usuario y se pide nuevamente el ingreso
            default:
                error(ERROR_num);
        }
    }while ((opcion_eliminar[0] != '1' && opcion_eliminar[0] != '2') || (opcion_eliminar.length() > 1));
    system("cls");
}

/*PROPOSITO: cancelar un turno.

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta

  RETORNO: no tiene valor de retorno*/

void baja_turno(Nodo_Turno *puntero_inicial_turnos, Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas){
    /*Permitira dar de baja un turno, buscandolo por DNI del paciente. Si no existe ningun turno,
    se informara por pantalla.*/

    //Puntero inicial de la lista que contendra todos los turnos relacionados al paciente
    Nodo *puntero_inicial_turnos_del_paciente = nullptr;

    //Se pide al usuario que ingrese el dni del paciente para buscar sus turnos
    string dni_paciente = pedir_dni();

    //Busca los turnos relacionados al dni del paciente y almacena sus direcciones en la lista que inicia con puntero_inicial_turnos_del_paciente
    for (Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente) {
        if (dni_paciente == aux->dato.paciente && aux->dato.estado == 1) {
            Nodo *nuevo_nodo = new Nodo;
            nuevo_nodo->dato = aux;
            nuevo_nodo->siguiente = nullptr;
            puntero_inicial_turnos_del_paciente = insertar_final_nodo(puntero_inicial_turnos_del_paciente, nuevo_nodo);
        }
    }

    //En el caso de que no se encuentre ningun turno relacionado al dni, se lo menciona al paciente y se vuelve al menu anterior
    if (puntero_inicial_turnos_del_paciente == nullptr) {
        cout << "No se ha encontrado ningun turno ACTIVO relacionado al DNI ingresado.\n";
        pausa();
        system("cls");
    }

    //Si solo hay un turno relacionado al DNI del paciente, se le muestran los datos del mismo y se pregunta si quiere cancelarlo
    if (puntero_inicial_turnos_del_paciente != nullptr && puntero_inicial_turnos_del_paciente->siguiente == nullptr) {
        cout << "Los datos del unico turno encontrado son:\n";
        turno_seleccionado_para_cancelar(puntero_inicial_turnos_del_paciente->dato, especialidades_medicas, dl_especialidades_medicas);
    }

    //Cuando haya mas de 1 turno, se mostraran todos junto a sus datos y se le pedira al usuario que indique el codigo unico del turno a dar de baja
    int codigo_unico;
    if (puntero_inicial_turnos_del_paciente != nullptr && puntero_inicial_turnos_del_paciente->siguiente != nullptr) {
        cout << "Los turnos relacionados al DNI ingresado son: \n\n";
        //Se muestran todos los turnos relacionados al DNI del paciente ingresado
        for (Nodo *aux = puntero_inicial_turnos_del_paciente; aux != nullptr; aux = aux->siguiente){
            mostrar_turno(aux->dato, especialidades_medicas, dl_especialidades_medicas);
            cout << endl;
        }
        //Se pide al usuario que ingrese el codigo unico del turno que quiere cancelar
        cout << "\nIngrese el codigo unico de identificacion del turno que desea cancelar: ";
        cin >> codigo_unico;
        for (Nodo *aux = puntero_inicial_turnos_del_paciente; aux != nullptr; aux = aux->siguiente) {
            if (aux->dato->dato.codigo == codigo_unico) {
                turno_seleccionado_para_cancelar(aux->dato, especialidades_medicas, dl_especialidades_medicas);
            }
        }
    }
    vaciar_lista_nodo(puntero_inicial_turnos_del_paciente);
}

/*PROPOSITO: ver un listado completo de turnos o buscar solo uno.

  PARAMETROS: * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas:un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo
              * puntero_inicial_turnos: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta

  RETORNO: no tiene valor de retorno*/

void listado_turnos(Nodo_Turno *puntero_inicial_turnos,Especialidad_Medica especialidades_medicas[], int dl_especialidades_medicas) {

    /*Permite buscar un conjunto de turnos (filtrados por fecha, paciente, especialidad medica o estado
    o ver un listado completo de todos los turnos activos.*/

    cout << "Se ingreso a la funcion listado_turnos(). \n";
    if(puntero_inicial_turnos == nullptr){
        cout << "No hay Turnos registrados.\n";
    }
    else{
        string submenu_listado;
        do {
            cout << "\nListado de Turnos: \n"
                    "   a) Completo. \n"
                    "   b) Busqueda. \n"
                    "   c) Volver al Menu de Administracion de Turnos. \n";

            cout << "Opcion: ";
            cin >> submenu_listado;
            system("cls");

            if (submenu_listado.length() > 1) {
                error(ERROR_excedido);
                continue;
            }

            switch (submenu_listado[0]) {
                case 'a': {
                    cout << "Los Turnos activos (pendientes de atencion) son: \n\n";
                    for (Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente) {
                        if (aux->dato.estado == 1) {
                            mostrar_turno(aux, especialidades_medicas, dl_especialidades_medicas);
                        }
                    }
                    pausa();
                    system("cls");

                    break;
                }
                case 'b': {                                                     //Muestra el listado de turnos
                    busqueda_listado_turno(puntero_inicial_turnos,especialidades_medicas,dl_especialidades_medicas);
                    break;
                }
                case 'c': {
                    break;
                }

                default: {
                    error(ERROR_letra);
                    break;
                }
            }
        } while (submenu_listado != "c");}
}

/*PROPOSITO: mostrar el menu de los diferentes filtros de busqueda para la administracion de turnos

  PARAMETROS: * puntero_inicial_turnos: puntero que almacena en la memoria la dirección del objeto (los turnos) que apunta
              * especialidades_medicas[]: un arreglo que contiene estructuras de tipo especialidades_medicas y representa las disponibles en el sistema
              * dl_especialidades_medicas: un entero que representa la dimensión lógica del arreglo anterior, es decir el espacio utilizado del arreglo

  RETORNO: tipo void, no tiene valor de retorno */

void busqueda_listado_turno(Nodo_Turno *puntero_inicial_turnos,Especialidad_Medica especialidades_medicas[],int dl_especialidades_medicas){

    /*Carga el submenu de listado de turnos por busqueda*/

    string submenu_busqueda_listado;
    do{
        cout << "\nFiltrar por: \n"
                "   a) Fecha. \n"
                "   b) Paciente. \n"
                "   c) Especialidad medica. \n"
                "   d) Estado. \n"
                "   e) Volver al Menu de Administracion de Turnos.\n\n";

        cout << "Opcion: ";
        cin >> submenu_busqueda_listado;
        system("cls");

        if (submenu_busqueda_listado.length() > 1) {
            error(ERROR_excedido);
            continue;
        }

        switch (submenu_busqueda_listado[0]) {
            case 'a': { //Opcion Fecha
                int fecha_ingresada;
                bool turno_encontrado = false;
                do{
                    cout<<"\nIngrese una fecha AAAAMMDD: "<<endl;
                    cin>>fecha_ingresada;
                }while(!validar_fecha(fecha_ingresada));
                for (Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente){
                    if (aux->dato.fecha == fecha_ingresada) {
                        mostrar_turno(aux, especialidades_medicas, dl_especialidades_medicas);
                        turno_encontrado = true;
                    }
                    if (!turno_encontrado) {
                        cout << "No se encontro un turno con la fecha ingresada .\n";
                    }
                }
                pausa();
                system("cls");
                break;
            }
            case 'b': {//Opcion Paciente

                string dni_a_buscar = pedir_dni();
                bool turno_encontrado = false;

                //Se va a iterar sobre la lista, y cuando se encuentre un turno, se va a mostrar en pantalla.
                for (Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente) {
                    if (aux->dato.paciente == dni_a_buscar){
                        mostrar_turno(aux, especialidades_medicas, dl_especialidades_medicas);
                        turno_encontrado = true;
                    }
                }
                //Si no se encontro ningun turno relacionado al paciente, se indica en pantalla
                if (!turno_encontrado){
                    cout << "No se encontro ningun turno relacionado al paciente.\n";
                }
                pausa();
                system("cls");
                break;
            }
            case 'c': {//Opcion Especialidad Medica
                int codigo_a_buscar;
                cout << "Ingrese el Codigo Unico de Identificacion de la Especialidad Medica para filtrar su turno: ";
                cin >> codigo_a_buscar;
                while(codigo_a_buscar < 0) {
                    cout << "ERROR: El Codigo Unico de Identificacion ingresado no es valido, ingreselo nuevamente\n";
                    cin >> codigo_a_buscar;
                }

                bool turno_encontrado = false;
                //Itera sobre el arreglo de especialidades medicas para verificar si el Codigo Unico de Identificacion (CUI) de la especialidad medica que ingresó el usuario existe
                for(int i=0 ; i < dl_especialidades_medicas; i++ ){
                    //En el caso de que se encuentre la especialidad medica, se comienza a iterar sobre la lista que contiene los turnos para buscar turnos relacionados a la especialidad medica
                    if (especialidades_medicas[i].codigo == codigo_a_buscar){
                        for(Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente){
                            //Si se encuentra un turno que tiene el CUI de la especialidad medica que ingreso el usuario, se muestra el turno. Asi hasta que se acaben los turnos registrados en el sistema.
                            if(aux->dato.especialidad_medica == codigo_a_buscar){
                                mostrar_turno(aux, especialidades_medicas, dl_especialidades_medicas);
                                turno_encontrado = true;
                            }
                            //En el caso de que no se haya encontrado ningun turno relacionado al CUI ingresado y no queden mas para verificar, se muestra este mensaje
                            if(!turno_encontrado and aux->siguiente == nullptr){
                                cout << "No se encontro ningun Turno con la especialidad medica ingresada. Se regresara al menu anterior.\n";
                                pausa();
                                system("cls");
                            }
                        }
                        break;
                    }
                    //En el caso de que no se encuentre una especialidad medica con el CUI ingresado por el usuario, se indica en pantalla.
                    if((i+1 == dl_especialidades_medicas) && (especialidades_medicas[i].codigo != codigo_a_buscar)){
                        cout << "\nNo se encontro una especialidad medica con el Codigo Unico de Identificacion ingresado.";
                        pausa();
                        system("cls");
                    }
                }
                break;
            }
            case 'd': {//Opcion Estado
                int estado_turno;
                do{
                    //Pide al usuario si quiere ver los turnos ACTIVOS (estado_turno = 1) o CANCELADOS (estado_turno = 2)
                    cout << "Ingrese el estado del turno que quiere filtrar (1- activo / 2-cancelado): ";
                    cin >> estado_turno;
                    //Si se selecciono una opcion valida, se comienzan a buscar los turnos por el estado ingresado y a mostrarlos en pantalla
                    if(estado_turno == 1 or estado_turno == 2){
                        cout << "Los turnos ";
                        if(estado_turno == 1){
                            cout << " ACTIVOS son los siguientes: \n\n";
                        }
                        else{
                            cout << " CANCELADOS son los siguientes: \n\n";
                        }
                        for(Nodo_Turno *aux = puntero_inicial_turnos; aux != nullptr; aux = aux->siguiente){
                            if(aux->dato.estado == estado_turno){
                                mostrar_turno(aux, especialidades_medicas, dl_especialidades_medicas);
                            }
                        }
                    }
                        //Si no se ingreso una opcion valida, se indica en pantalla y se pedira nuevamente que se ingrese el filtro de estado
                    else{
                        error(ERROR_num);
                    }
                }while ((estado_turno != 1) and (estado_turno != 2));
                pausa();
                system("cls");
                break;
            }
            case 'e': {         //Opcion Volver al Menu de Administracion de Turnos.
                break;
            }
            default: {
                error(ERROR_letra);
                break;
            }
        }
    }while (submenu_busqueda_listado != "e");
    pausa();
    system("cls");
}

/*PROPOSITO: Mostrar en pantalla un mensaje de error cuando ha ingresado mas de un digito o caracter

  PARAMETROS: mensaje: mensaje de tipo string para pasar por parametro cada constante de los errores

  RETORNO: no tiene valor de retorno */

void error(string mensaje) {

    /*Muestra en pantalla un mensaje de error cuando se ingresan caracteres erroneos*/
    cout << mensaje << "\n";
    pausa();
    system("cls");
}