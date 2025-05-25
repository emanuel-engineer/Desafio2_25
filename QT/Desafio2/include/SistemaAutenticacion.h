// ==================== SistemaAutenticacion.h ====================
#ifndef SISTEMA_AUTENTICACION_H
#define SISTEMA_AUTENTICACION_H

#include <string>
#include <vector>

enum class TipoUsuario {
    USUARIO,
    ADMINISTRADOR,
    NO_ENCONTRADO
};

struct Usuario {
    std::string nombre;
    std::string password;
    TipoUsuario tipo;

    Usuario(const std::string& n, const std::string& p, TipoUsuario t);
};

class SistemaAutenticacion {
private:
    std::vector<Usuario> usuarios;
    std::string archivoUsuarios;
    Usuario* usuarioActual;

public:
    // Constructor
    SistemaAutenticacion(const std::string& archivo = "usuarios.txt");

    // Métodos públicos
    bool cargarUsuarios();
    bool guardarUsuarios();
    bool autenticar(const std::string& nombre, const std::string& password);
    bool estaAutenticado() const;
    bool esAdministrador() const;
    std::string obtenerNombreUsuario() const;
    void cerrarSesion();
    bool agregarUsuario(const std::string& nombre, const std::string& password, bool esAdmin = false);
    void mostrarUsuarios() const;
    void crearUsuariosPorDefecto();
};

#endif // SISTEMA_AUTENTICACION_H
