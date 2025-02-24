#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

// Definimos la estructura de un aula con los datos especificados
struct Aula {
    char codigo_aula[10];
    float largo;
    float ancho;
    int capacidad;
    char color[20];
    char tipo_aula[25];
};

// Función para validar la longitud de la entrada
void validarEntrada(char *campo, int longitud, const string &mensaje) {
    string entrada;
    do {
        cout << mensaje;
        cin >> ws;
        getline(cin, entrada);
        if (entrada.length() >= longitud) {
            cout << "Error: La entrada es demasiado larga. Máximo " << longitud - 1 << " caracteres. Intente nuevamente." << endl;
        }
    } while (entrada.length() >= longitud);
    strncpy(campo, entrada.c_str(), longitud - 1);
    campo[longitud - 1] = '\0'; // Asegurar terminación nula
}

// Función para agregar un nuevo aula al archivo
void agregarAula(const string& archivo) {
    Aula aula;
    ofstream file(archivo, ios::app); // Abrimos en modo texto y agregar datos
    if (!file) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    // Solicitamos los datos del aula al usuario
    cout << "\nIngrese los datos del aula:\n";
    validarEntrada(aula.codigo_aula, 10, "Codigo del aula: ");
    cout << "Largo: ";
    cin >> aula.largo;
    cout << "Ancho: ";
    cin >> aula.ancho;
    cout << "Capacidad: ";
    cin >> aula.capacidad;
    validarEntrada(aula.color, 20, "Color: ");
    validarEntrada(aula.tipo_aula, 25, "Tipo de Aula: ");
    

    file << aula.codigo_aula << "|" << aula.largo << "|" << aula.ancho << "|"
         << aula.capacidad << "|" << aula.color << "|" << aula.tipo_aula << "\n";
    file.close();
    cout << "Aula agregada correctamente!" << endl;
}

// Función para listar todas las aulas del archivo
void listarAulas(const string& archivo) {
    ifstream file(archivo);
    if (!file) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    cout << "\nListado de Aulas:\n";
    string linea;
    while (getline(file, linea)) {
        if (linea.find("#ELIMINADO#") == string::npos) { // Ignorar eliminados
            cout << linea << endl;
        }
    }
    file.close();
}

// Función para editar un aula por su código
void editarAula(const string& archivo) {
    fstream file(archivo, ios::in | ios::out);
    if (!file) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    char codigo[10];
    string linea;
    validarEntrada(codigo, 10, "Ingrese el codigo del aula a editar: ");
    long pos = file.tellg();
    bool encontrado = false;

    while (getline(file, linea)) {
        if (linea.substr(0, linea.find("|")) == codigo) {
            Aula aula;
            strcpy(aula.codigo_aula, codigo);
            cout << "Nuevo Largo: "; cin >> aula.largo;
            cout << "Nuevo Ancho: "; cin >> aula.ancho;
            cout << "Nueva Capacidad: "; cin >> aula.capacidad;
            validarEntrada(aula.color, 20, "Nuevo Color: ");
            validarEntrada(aula.tipo_aula, 25, "Nuevo Tipo de Aula: ");

            file.seekp(pos, ios::beg);
            file << aula.codigo_aula << "|" << aula.largo << "|" << aula.ancho << "|"
                 << aula.capacidad << "|" << aula.color << "|" << aula.tipo_aula << "\n";
            encontrado = true;
            break;
        }
        pos = file.tellg();
    }

    file.close();
    if (encontrado) cout << "Aula actualizada correctamente!" << endl;
    else cout << "Aula no encontrada." << endl;
}

// Función para eliminar un aula por su código
void eliminarAula(const string& archivo) {
    fstream file(archivo, ios::in | ios::out);
    if (!file) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string codigo, linea;
    cout << "Ingrese el codigo del aula a eliminar: ";
    cin >> codigo;
    long pos = file.tellg();
    bool eliminado = false;

    while (getline(file, linea)) {
        if (linea.substr(0, linea.find("|")) == codigo) {
            file.seekp(pos, ios::beg);
            file << "#ELIMINADO#" << string(linea.length() - 10, ' ') << "\n";
            eliminado = true;
            break;
        }
        pos = file.tellg();
    }

    file.close();
    if (eliminado) cout << "Aula eliminada correctamente (marcado lógico)!" << endl;
    else cout << "Aula no encontrada." << endl;
}

// This function definition is removed to avoid redefinition error

void importarDesdeCSV(const string& archivoCSV, const string& archivo) {
    ifstream csvFile(archivoCSV);
    ofstream file(archivo, ios::app);
    if (!csvFile || !file) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(csvFile, linea)) {
        stringstream ss(linea);
        Aula aula;
        string temp;

        getline(ss, temp, ','); strncpy(aula.codigo_aula, temp.c_str(), 9);
        getline(ss, temp, ','); aula.largo = stof(temp);
        getline(ss, temp, ','); aula.ancho = stof(temp);
        getline(ss, temp, ','); aula.capacidad = stoi(temp);
        getline(ss, temp, ','); strncpy(aula.color, temp.c_str(), 19);
        getline(ss, temp, ','); strncpy(aula.tipo_aula, temp.c_str(), 24);

        file << aula.codigo_aula << "|" << aula.largo << "|" << aula.ancho << "|"
             << aula.capacidad << "|" << aula.color << "|" << aula.tipo_aula << "\n";
    }
    csvFile.close();
    file.close();
    cout << "Importación completada." << endl;
}

void exportarACSV(const string& archivo, const string& archivoCSV) {
    ifstream file(archivo);
    ofstream csvFile(archivoCSV);
    if (!file || !csvFile) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        if (linea.find("#ELIMINADO#") == string::npos) {
            replace(linea.begin(), linea.end(), '|', ',');
            csvFile << linea << "\n";
        }
    }
    file.close();
    csvFile.close();
    cout << "Exportación completada." << endl;
}

// Función principal con menú
int main() {
    string archivo = "/workspaces/Fake_DB/aulas.txt";
    
    int opcion;
    do {
        cout << "\n1. Agregar Aula";
        cout << "\n2. Listar Aulas";
        cout << "\n3. Editar Aula";
        cout << "\n4. Eliminar Aula";
        cout << "\n5. Salir";
        cout << "\n6. Importar desde CSV";
        cout << "\n7. Exportar a CSV";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        string archivoCSV;
        
        switch (opcion) {
            case 1:
                agregarAula(archivo);
                break;
            case 2:
                listarAulas(archivo);
                break;
            case 3:
                editarAula(archivo);
                break;
            case 4:
                eliminarAula(archivo);
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            case 6:
                cout << "Ingrese la ruta del archivo CSV: ";
                cin >> archivoCSV;
                importarDesdeCSV(archivoCSV, archivo);
                break;
            case 7:
                cout << "Ingrese la ruta del archivo CSV de destino: ";
                cin >> archivoCSV;
                exportarACSV(archivo, archivoCSV);
                break;
            default:
                cout << "Opción inválida." << endl;
        }
    } while (opcion != 5);
    
    return 0;
}
