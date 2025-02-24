#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Definimos la estructura de un aula con los datos especificados
struct Aula {
    string codigo_aula;
    float largo;
    float ancho;
    int capacidad;
    string color;
    short int tipo_aula;
};

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
    cout << "Codigo del aula: ";
    cin >> aula.codigo_aula;
    cout << "Largo: ";
    cin >> aula.largo;
    cout << "Ancho: ";
    cin >> aula.ancho;
    cout << "Capacidad: ";
    cin >> aula.capacidad;
    cout << "Color: ";
    cin >> aula.color;
    cout << "Tipo de Aula: ";
    cin >> aula.tipo_aula;
    
    // Guardamos los datos en el archivo
    file << aula.codigo_aula << "|" << aula.largo << "|" << aula.ancho << "|"
         << aula.capacidad << "|" << aula.color << "|" << aula.tipo_aula << "\n";
    file.close();
    cout << "Aula agregada correctamente!" << endl;
}

// Función para listar todas las aulas del archivo
void listarAulas(const string& archivo) {
    Aula aula;

    ifstream file(archivo);
    if (!file) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    cout << "\nListado de Aulas:\n";
    string linea;
    while (getline(file, linea)) {
        size_t pos = 0;
        string datos[6];
        int i = 0;
        while ((pos = linea.find("|")) != string::npos) {
            datos[i++] = linea.substr(0, pos);
            linea.erase(0, pos + 1);
        }
        datos[i] = linea;

        // Asignamos los datos a la estructura
        aula.codigo_aula = datos[0];
        aula.largo = stof(datos[1]);
        aula.ancho = stof(datos[2]);
        aula.capacidad = stoi(datos[3]);
        aula.color = datos[4];
        aula.tipo_aula = stoi(datos[5]);

        cout << "Codigo: " << aula.codigo_aula << " | Largo: " << aula.largo << " | Ancho: " << aula.ancho
             << " | Capacidad: " << aula.capacidad << " | Color: " << aula.color
             << " | Tipo: " << aula.tipo_aula << endl;
    }
    file.close();
}

// Función para editar un aula por su código
void editarAula(const string& archivo) {
    string codigo;
    cout << "Ingrese el codigo del aula a editar: ";
    cin >> codigo;
    ifstream file(archivo);
    ofstream temp("temp.txt");
    string linea;
    bool encontrado = false;
    while (getline(file, linea)) {
        if (linea.substr(0, linea.find("|")) == codigo) {
            Aula aula;
            cout << "Nuevo Largo: "; cin >> aula.largo;
            cout << "Nuevo Ancho: "; cin >> aula.ancho;
            cout << "Nueva Capacidad: "; cin >> aula.capacidad;
            cout << "Nuevo Color: "; cin >> aula.color;
            cout << "Nuevo Tipo de Aula: "; cin >> aula.tipo_aula;
            temp << codigo << "|" << aula.largo << "|" << aula.ancho << "|"
                 << aula.capacidad << "|" << aula.color << "|" << aula.tipo_aula << "\n";
            encontrado = true;
        } else {
            temp << linea << "\n";
        }
    }
    file.close();
    temp.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (encontrado) cout << "Aula actualizada correctamente!" << endl;
    else cout << "Aula no encontrada." << endl;
}

// Función para eliminar un aula por su código
void eliminarAula(const string& archivo) {
    string codigo;
    cout << "Ingrese el codigo del aula a eliminar: ";
    cin >> codigo;
    ifstream file(archivo);
    ofstream temp("temp.txt");
    string linea;
    bool eliminado = false;
    while (getline(file, linea)) {
        if (linea.substr(0, linea.find("|")) != codigo) {
            temp << linea << "\n";
        } else {
            eliminado = true;
        }
    }
    file.close();
    temp.close();
    remove(archivo.c_str());
    rename("temp.txt", archivo.c_str());
    if (eliminado) cout << "Aula eliminada correctamente!" << endl;
    else cout << "Aula no encontrada." << endl;
}

// Función principal con menú
int main() {
    string archivo = "/workspaces/Fake_DB/aulas.txt";
    int opcion;
    // do {
        cout << "\n1. Agregar Aula";
        cout << "\n2. Listar Aulas";
        cout << "\n3. Editar Aula";
        cout << "\n4. Eliminar Aula";
        cout << "\n5. Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        
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
            default:
                cout << "Opción inválida." << endl;
        }
    // } while (opcion != 5);
    
    return 0;
}
