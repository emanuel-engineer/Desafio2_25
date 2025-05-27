#include "reservas.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

// Constructor
Reservas::Reservas(const string& archivo) : datosAPT(archivo), archivoUltimoID("ultimoID.txt") {
    cargarApartamentos();
}

// Generar nuevo ID
int Reservas::generarNuevoID() {
    int ultimoID = 0;

    ifstream fileIn(archivoUltimoID);
    if (fileIn.is_open()) {
        fileIn >> ultimoID;
        fileIn.close();
    }

    int nuevoID = ultimoID + 1;

    if (nuevoID > 999999) {
        nuevoID = 1;
    }

    ofstream fileOut(archivoUltimoID);
    if (fileOut.is_open()) {
        fileOut << nuevoID;
        fileOut.close();
    }

    return nuevoID;
}

// Formatear ID con ceros a la izquierda
string Reservas::formatearID(int id) {
    ostringstream oss;
    oss << setw(6) << setfill('0') << id;
    return oss.str();
}

// Cargar apartamentos desde archivo
bool Reservas::cargarApartamentos() {
    apartamentos.clear();
    ifstream file(datosAPT);

    if (!file.is_open()) {
        cout << "Archivo de apartamentos no encontrado. Se creará uno nuevo.\n";
        return false;
    }

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        string id, nombre, precioStr, descripcion, estado;

        if (getline(iss, id, '|') &&
            getline(iss, nombre, '|') &&
            getline(iss, precioStr, '|') &&
            getline(iss, descripcion, '|') &&
            getline(iss, estado, '|')) {

            // Limpiar espacios
            id.erase(0, id.find_first_not_of(" \t"));
            id.erase(id.find_last_not_of(" \t") + 1);
            nombre.erase(0, nombre.find_first_not_of(" \t"));
            nombre.erase(nombre.find_last_not_of(" \t") + 1);
            descripcion.erase(0, descripcion.find_first_not_of(" \t"));
            descripcion.erase(descripcion.find_last_not_of(" \t") + 1);
            estado.erase(0, estado.find_first_not_of(" \t"));
            estado.erase(estado.find_last_not_of(" \t") + 1);

            double precio = stod(precioStr);
            apartamentos.push_back({id, nombre, precio, descripcion, estado});
        }
    }

    file.close();
    return true;
}

// Guardar apartamentos en archivo
bool Reservas::guardarApartamentos() {
    ofstream file(datosAPT);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo para guardar.\n";
        return false;
    }

    for (const auto& apt : apartamentos) {
        file << apt.id << " | " << apt.nombre << " | " << apt.precio << " | "
             << apt.descripcion << " | " << apt.estado << " |\n";
    }

    file.close();
    return true;
}

// Agregar apartamento (solo administradores)
bool Reservas::agregarApartamento(const string& nombre, double precio, const string& descripcion) {
    int nuevoID = generarNuevoID();
    string idFormateado = formatearID(nuevoID);

    apartamentos.push_back({idFormateado, nombre, precio, descripcion, "disponible"});

    if (guardarApartamentos()) {
        cout << "Apartamento agregado correctamente. ID asignado: " << idFormateado << endl;
        return true;
    }

    return false;
}

// Eliminar apartamento
bool Reservas::eliminarApartamento(const string& id) {
    auto it = find_if(apartamentos.begin(), apartamentos.end(),
                      [&id](const Apartamento& apt) { return apt.id == id; });

    if (it != apartamentos.end()) {
        apartamentos.erase(it);
        guardarApartamentos();
        cout << "Apartamento eliminado correctamente.\n";
        return true;
    }

    cout << "Apartamento no encontrado.\n";
    return false;
}

// Modificar apartamento
bool Reservas::modificarApartamento(const string& id, const string& nuevoNombre, double nuevoPrecio, const string& nuevaDescripcion) {
    auto it = find_if(apartamentos.begin(), apartamentos.end(),
                      [&id](const Apartamento& apt) { return apt.id == id; });

    if (it != apartamentos.end()) {
        it->nombre = nuevoNombre;
        it->precio = nuevoPrecio;
        it->descripcion = nuevaDescripcion;
        guardarApartamentos();
        cout << "Apartamento modificado correctamente.\n";
        return true;
    }

    cout << "Apartamento no encontrado.\n";
    return false;
}

// Mostrar todos los apartamentos (para administradores)
void Reservas::mostrarTodosApartamentos() const {
    cout << "\n=== TODOS LOS APARTAMENTOS ===\n";
    cout << left << setw(8) << "ID" << setw(20) << "Nombre" << setw(10) << "Precio"
         << setw(15) << "Estado" << "Descripción\n";
    cout << string(70, '-') << "\n";

    for (const auto& apt : apartamentos) {
        cout << left << setw(8) << apt.id << setw(20) << apt.nombre
             << setw(10) << apt.precio << setw(15) << apt.estado << apt.descripcion << "\n";
    }
    cout << "==============================\n";
}

// Mostrar apartamentos disponibles (para usuarios)
void Reservas::mostrarApartamentosDisponibles() const {
    cout << "\n=== APARTAMENTOS DISPONIBLES ===\n";
    cout << left << setw(8) << "ID" << setw(20) << "Nombre" << setw(10) << "Precio" << "Descripción\n";
    cout << string(60, '-') << "\n";

    for (const auto& apt : apartamentos) {
        if (apt.estado == "disponible") {
            cout << left << setw(8) << apt.id << setw(20) << apt.nombre
                 << setw(10) << apt.precio << apt.descripcion << "\n";
        }
    }
    cout << "================================\n";
}

// Reservar apartamento
bool Reservas::reservarApartamento(const string& id, const string& usuario) {
    auto it = find_if(apartamentos.begin(), apartamentos.end(),
                      [&id](const Apartamento& apt) { return apt.id == id; });

    if (it != apartamentos.end() && it->estado == "disponible") {
        it->estado = "reservado";
        guardarApartamentos();
        cout << "Apartamento reservado correctamente para " << usuario << ".\n";
        return true;
    }

    cout << "Apartamento no disponible o no encontrado.\n";
    return false;
}

// Cancelar reserva
bool Reservas::cancelarReserva(const string& id) {
    auto it = find_if(apartamentos.begin(), apartamentos.end(),
                      [&id](const Apartamento& apt) { return apt.id == id; });

    if (it != apartamentos.end() && it->estado == "reservado") {
        it->estado = "disponible";
        guardarApartamentos();
        cout << "Reserva cancelada correctamente.\n";
        return true;
    }

    cout << "Reserva no encontrada o apartamento ya disponible.\n";
    return false;
}

// Mostrar reservas
void Reservas::mostrarReservas() const {
    cout << "\n=== APARTAMENTOS RESERVADOS ===\n";
    cout << left << setw(8) << "ID" << setw(20) << "Nombre" << setw(10) << "Precio" << "Descripción\n";
    cout << string(60, '-') << "\n";

    bool hayReservas = false;
    for (const auto& apt : apartamentos) {
        if (apt.estado == "reservado") {
            cout << left << setw(8) << apt.id << setw(20) << apt.nombre
                 << setw(10) << apt.precio << apt.descripcion << "\n";
            hayReservas = true;
        }
    }

    if (!hayReservas) {
        cout << "No hay apartamentos reservados.\n";
    }
    cout << "===============================\n";
}

// Verificar si existe apartamento
bool Reservas::existeApartamento(const string& id) const {
    return find_if(apartamentos.begin(), apartamentos.end(),
                   [&id](const Apartamento& apt) { return apt.id == id; }) != apartamentos.end();
}
