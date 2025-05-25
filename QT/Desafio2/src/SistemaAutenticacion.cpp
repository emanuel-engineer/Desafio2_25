// ==================== SistemaAutenticacion.cpp ====================
#include "SistemaAutenticacion.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor de Usuario
Usuario::Usuario(const std::string& n, const std::string& p, TipoUsuario t)
    : nombre(n), password(p), tipo(t) {}

// Constructor de SistemaAutenticacion
SistemaAutenticacion::SistemaAutenticacion(const std::string& archivo)
    : archivoUsuarios(archivo), usuarioActual(nullptr) {
    cargarUsuarios();
}

// Cargar usuarios desde el archivo
bool SistemaAutenticacion::cargarUsuarios() {
    usuarios.clear();
    std::ifstream archivo(archivoUsuarios);

    if (!archivo.is_open()) {
        std::cout << "Archivo de usuarios no encontrado. Se creará uno nuevo.\n";
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string nombre, password, tipoStr;

        if (std::getline(iss, nombre, '|') &&
            std::getline(iss, password, '|') &&
            std::getline(iss, tipoStr)) {

            TipoUsuario tipo = (tipoStr == "admin") ?
                TipoUsuario::ADMINISTRADOR : TipoUsuario::USUARIO;

            usuarios.emplace_back(nombre, password, tipo);
        }
    }

    archivo.close();
    std::cout << "Se cargaron " << usuarios.size() << " usuarios.\n";
    return true;
}

// Guardar usuarios en el archivo
bool SistemaAutenticacion::guardarUsuarios() {
    std::ofstream archivo(archivoUsuarios);

    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo para guardar.\n";
        return false;
    }

    for (const auto& user : usuarios) {
        archivo << user.nombre << "|" << user.password << "|";
        archivo << (user.tipo == TipoUsuario::ADMINISTRADOR ? "admin" : "user");
        archivo << "\n";
    }

    archivo.close();
    return true;
}

// Verificar credenciales y autenticar usuario
bool SistemaAutenticacion::autenticar(const std::string& nombre, const std::string& password) {
    for (auto& user : usuarios) {
        if (user.nombre == nombre && user.password == password) {
            usuarioActual = &user;
            std::cout << "¡Autenticación exitosa!\n";
            std::cout << "Bienvenido, " << nombre;

            if (user.tipo == TipoUsuario::ADMINISTRADOR) {
                std::cout << " (Administrador)\n";
            } else {
                std::cout << " (Usuario)\n";
            }

            return true;
        }
    }

    std::cout << "Credenciales incorrectas.\n";
    usuarioActual = nullptr;
    return false;
}

// Verificar si hay un usuario autenticado
bool SistemaAutenticacion::estaAutenticado() const {
    return usuarioActual != nullptr;
}

// Verificar si el usuario actual es administrador
bool SistemaAutenticacion::esAdministrador() const {
    return estaAutenticado() &&
           usuarioActual->tipo == TipoUsuario::ADMINISTRADOR;
}

// Obtener el nombre del usuario actual
std::string SistemaAutenticacion::obtenerNombreUsuario() const {
    if (estaAutenticado()) {
        return usuarioActual->nombre;
    }
    return "";
}

// Cerrar sesión
void SistemaAutenticacion::cerrarSesion() {
    if (estaAutenticado()) {
        std::cout << "Sesión cerrada para: " << usuarioActual->nombre << "\n";
        usuarioActual = nullptr;
    }
}

// Agregar nuevo usuario (solo administradores)
bool SistemaAutenticacion::agregarUsuario(const std::string& nombre, const std::string& password, bool esAdmin) {
    // Verificar si el usuario ya existe
    for (const auto& user : usuarios) {
        if (user.nombre == nombre) {
            std::cout << "Error: El usuario ya existe.\n";
            return false;
        }
    }

    TipoUsuario tipo = esAdmin ? TipoUsuario::ADMINISTRADOR : TipoUsuario::USUARIO;
    usuarios.emplace_back(nombre, password, tipo);

    if (guardarUsuarios()) {
        std::cout << "Usuario agregado exitosamente.\n";
        return true;
    }

    return false;
}

// Mostrar todos los usuarios (solo para administradores)
void SistemaAutenticacion::mostrarUsuarios() const {
    if (!esAdministrador()) {
        std::cout << "Acceso denegado. Solo administradores.\n";
        return;
    }

    std::cout << "\n=== LISTA DE USUARIOS ===\n";
    for (const auto& user : usuarios) {
        std::cout << "Usuario: " << user.nombre;
        std::cout << " | Tipo: " << (user.tipo == TipoUsuario::ADMINISTRADOR ?
                                    "Administrador" : "Usuario") << "\n";
    }
    std::cout << "========================\n";
}

// Crear usuarios por defecto si el archivo no existe
void SistemaAutenticacion::crearUsuariosPorDefecto() {
    if (usuarios.empty()) {
        std::cout << "Creando usuarios por defecto...\n";
        agregarUsuario("admin", "admin123", true);
        agregarUsuario("usuario", "user123", false);
        std::cout << "Usuarios por defecto creados.\n";
    }
}
