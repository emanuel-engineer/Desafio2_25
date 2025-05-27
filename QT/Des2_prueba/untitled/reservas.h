#ifndef RESERVAS_H
#define RESERVAS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Declarar el struct antes de la clase
struct Apartamento {
    std::string id;
    std::string nombre;
    double precio;
    std::string descripcion;
    std::string estado; // "disponible" o "reservado"
};

class Reservas {
private:
    std::string datosAPT;
    std::string archivoUltimoID;
    std::vector<Apartamento> apartamentos;

    int generarNuevoID();
    std::string formatearID(int id);
    bool cargarApartamentos();
    bool guardarApartamentos();

public:
    // Constructor
    Reservas(const std::string& archivo = "apartamentos.txt");

    // Métodos para administradores
    bool agregarApartamento(const std::string& nombre, double precio, const std::string& descripcion);
    bool eliminarApartamento(const std::string& id);
    bool modificarApartamento(const std::string& id, const std::string& nuevoNombre, double nuevoPrecio, const std::string& nuevaDescripcion);
    void mostrarTodosApartamentos() const;

    // Métodos para usuarios
    void mostrarApartamentosDisponibles() const;
    bool reservarApartamento(const std::string& id, const std::string& usuario);
    bool cancelarReserva(const std::string& id);

    // Métodos generales
    void mostrarReservas() const;
    bool existeApartamento(const std::string& id) const;
};

#endif // RESERVAS_H
