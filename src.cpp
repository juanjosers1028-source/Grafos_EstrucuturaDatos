#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAX = 20;

char usuarios[MAX][30];


int grafo[MAX][MAX];

int cantidadUsuarios = 0;


int iguales(char a[], char b[]) {

    int i = 0;

    while (a[i] != '\0' || b[i] != '\0') {

        if (a[i] != b[i]) {

            return 0;
        }

        i++;
    }

    return 1;
}


void copiar(char destino[], char origen[]) {

    int i = 0;

    while (origen[i] != '\0') {

        destino[i] = origen[i];

        i++;
    }

    destino[i] = '\0';
}


int buscarUsuario(char nombre[]) {

    int i;

    for (i = 0; i < cantidadUsuarios; i++) {

        if (iguales(usuarios[i], nombre) == 1) {

            return i;
        }
    }

    return -1;
}


void agregarUsuario() {

    char nombre[30];

    cout << "Ingrese nombre del usuario: ";
    cin >> nombre;

    if (buscarUsuario(nombre) == -1) {

        copiar(usuarios[cantidadUsuarios], nombre);

        cantidadUsuarios++;

        cout << "Usuario agregado correctamente\n";
    }
    else {

        cout << "El usuario ya existe\n";
    }
}


void eliminarUsuario() {

    char nombre[30];

    cout << "Ingrese usuario a eliminar: ";
    cin >> nombre;

    int pos = buscarUsuario(nombre);

    if (pos == -1) {

        cout << "Usuario no encontrado\n";
    }
    else {

        int i;
        int j;

        
        for (i = pos; i < cantidadUsuarios - 1; i++) {

            copiar(usuarios[i], usuarios[i + 1]);
        }

        
        for (i = pos; i < cantidadUsuarios - 1; i++) {

            for (j = 0; j < cantidadUsuarios; j++) {

                grafo[i][j] = grafo[i + 1][j];
            }
        }

       
        for (j = pos; j < cantidadUsuarios - 1; j++) {

            for (i = 0; i < cantidadUsuarios; i++) {

                grafo[i][j] = grafo[i][j + 1];
            }
        }

        cantidadUsuarios--;

        cout << "Usuario eliminado correctamente\n";
    }
}


void agregarAmistad() {

    char nombre1[30];
    char nombre2[30];

    cout << "Ingrese usuario 1: ";
    cin >> nombre1;

    cout << "Ingrese usuario 2: ";
    cin >> nombre2;

    int pos1 = buscarUsuario(nombre1);
    int pos2 = buscarUsuario(nombre2);

    if (pos1 == -1 || pos2 == -1) {

        cout << "Uno de los usuarios no existe\n";
    }
    else {

        grafo[pos1][pos2] = 1;
        grafo[pos2][pos1] = 1;

        cout << "Amistad agregada correctamente\n";
    }
}


void eliminarAmistad() {

    char nombre1[30];
    char nombre2[30];

    cout << "Ingrese usuario 1: ";
    cin >> nombre1;

    cout << "Ingrese usuario 2: ";
    cin >> nombre2;

    int pos1 = buscarUsuario(nombre1);
    int pos2 = buscarUsuario(nombre2);

    if (pos1 == -1 || pos2 == -1) {

        cout << "Uno de los usuarios no existe\n";
    }
    else {

        grafo[pos1][pos2] = 0;
        grafo[pos2][pos1] = 0;

        cout << "Amistad eliminada correctamente\n";
    }
}


void listarAmigos() {

    char nombre[30];

    cout << "Ingrese usuario: ";
    cin >> nombre;

    int pos = buscarUsuario(nombre);

    if (pos == -1) {

        cout << "Usuario no encontrado\n";
    }
    else {

        int i;

        cout << "Amigos de " << nombre << ":\n";

        for (i = 0; i < cantidadUsuarios; i++) {

            if (grafo[pos][i] == 1) {

                cout << usuarios[i] << endl;
            }
        }
    }
}


void sugerirAmigos() {

    char nombre[30];

    cout << "Ingrese usuario: ";
    cin >> nombre;

    int pos = buscarUsuario(nombre);

    if (pos == -1) {

        cout << "Usuario no encontrado\n";
    }
    else {

        int i;
        int j;
        int comunes;

        cout << "Sugerencias de amistad:\n";

        for (i = 0; i < cantidadUsuarios; i++) {

            if (i != pos && grafo[pos][i] == 0) {

                comunes = 0;

                for (j = 0; j < cantidadUsuarios; j++) {

                    if (grafo[pos][j] == 1 && grafo[i][j] == 1) {

                        comunes++;
                    }
                }

                if (comunes > 0) {

                    cout << usuarios[i];
                    cout << " - Amigos en comun: ";
                    cout << comunes << endl;
                }
            }
        }
    }
}


void caminoMasCorto() {

    char inicio[30];
    char destino[30];

    cout << "Ingrese usuario inicial: ";
    cin >> inicio;

    cout << "Ingrese usuario destino: ";
    cin >> destino;

    int origen = buscarUsuario(inicio);
    int fin = buscarUsuario(destino);

    if (origen == -1 || fin == -1) {

        cout << "Uno de los usuarios no existe\n";
    }
    else {

        int cola[MAX];
        int visitado[MAX];
        int distancia[MAX];

        int i;

        for (i = 0; i < cantidadUsuarios; i++) {

            visitado[i] = 0;
            distancia[i] = -1;
        }

        int inicioCola = 0;
        int finCola = 0;

        cola[finCola] = origen;
        finCola++;

        visitado[origen] = 1;
        distancia[origen] = 0;

        while (inicioCola < finCola) {

            int actual = cola[inicioCola];

            inicioCola++;

            for (i = 0; i < cantidadUsuarios; i++) {

                if (grafo[actual][i] == 1 && visitado[i] == 0) {

                    visitado[i] = 1;

                    distancia[i] = distancia[actual] + 1;

                    cola[finCola] = i;

                    finCola++;
                }
            }
        }

        if (distancia[fin] == -1) {

            cout << "No existe camino\n";
        }
        else {

            cout << "La distancia minima es: ";
            cout << distancia[fin] << endl;
        }
    }
}


void mostrarMatriz() {

    int i;
    int j;

    cout << "\nMATRIZ DE AMISTADES\n\n";

    for (i = 0; i < cantidadUsuarios; i++) {

        cout << usuarios[i] << " ";
    }

    cout << endl;

    for (i = 0; i < cantidadUsuarios; i++) {

        for (j = 0; j < cantidadUsuarios; j++) {

            cout << grafo[i][j] << " ";
        }

        cout << endl;
    }
}


int main() {

    int opcion;

    int i;
    int j;

    for (i = 0; i < MAX; i++) {

        for (j = 0; j < MAX; j++) {

            grafo[i][j] = 0;
        }
    }

    do {

        cout << "\n====== MENU ======\n";

        cout << "1. Agregar usuario\n";
        cout << "2. Eliminar usuario\n";
        cout << "3. Agregar amistad\n";
        cout << "4. Eliminar amistad\n";
        cout << "5. Listar amigos\n";
        cout << "6. Sugerir amigos\n";
        cout << "7. Camino mas corto\n";
        cout << "8. Mostrar matriz\n";
        cout << "0. Salir\n";

        cout << "Seleccione opcion: ";
        cin >> opcion;

        if (opcion == 1) {

            agregarUsuario();
        }
        else if (opcion == 2) {

            eliminarUsuario();
        }
        else if (opcion == 3) {

            agregarAmistad();
        }
        else if (opcion == 4) {

            eliminarAmistad();
        }
        else if (opcion == 5) {

            listarAmigos();
        }
        else if (opcion == 6) {

            sugerirAmigos();
        }
        else if (opcion == 7) {

            caminoMasCorto();
        }
        else if (opcion == 8) {

            mostrarMatriz();
        }
        else if (opcion == 0) {

            cout << "Programa finalizado\n";
        }
        else {

            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);

    return 0;
}