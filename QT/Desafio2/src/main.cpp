#include <iostream>
#include "SistemaAutenticacion.h"

// Función para mostrar menú principal
void mostrarMenuPrincipal(SistemaAutenticacion& auth);

int main() {
    SistemaAutenticacion auth("usuarios.txt");

    // Crear usuarios por defecto si es necesario
    auth.crearUsuariosPorDefecto();

    std::cout << "=== SISTEMA DE AUTENTICACIÓN ===\n";
    std::cout << "Usuarios por defecto:\n";
    std::cout << "- admin/admin123 (Administrador)\n";
    std::cout << "- usuario/user123 (Usuario)\n\n";

    while (true) {
        if (!auth.estaAutenticado()) {
            std::string nombre, password;

            std::cout << "=== INICIAR SESIÓN ===\n";
            std::cout << "Usuario: ";
            std::cin >> nombre;
            std::cout << "Contraseña: ";
            std::cin >> password;

            if (auth.autenticar(nombre, password)) {
                mostrarMenuPrincipal(auth);
            } else {
                std::cout << "¿Deseas intentar de nuevo? (s/n): ";
                char respuesta;
                std::cin >> respuesta;
                if (respuesta != 's' && respuesta != 'S') {
                    break;
                }
            }
        }
    }

    return 0;
}

// Función para mostrar menú principal
void mostrarMenuPrincipal(SistemaAutenticacion& auth) {
    while (true) {
        std::cout << "\n=== MENÚ PRINCIPAL ===\n";
        std::cout << "Usuario actual: " << auth.obtenerNombreUsuario();
        std::cout << (auth.esAdministrador() ? " (Admin)" : " (Usuario)") << "\n";

        std::cout << "1. Área de usuario\n";
        if (auth.esAdministrador()) {
            std::cout << "2. Panel de administración\n";
        }
        std::cout << "3. Cerrar sesión\n";
        std::cout << "4. Salir\n";
        std::cout << "Selecciona una opción: ";

        int opcion;
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "\n--- ÁREA DE USUARIO ---\n";
                std::cout << "Aquí va la funcionalidad para usuarios...\n";
        //TODO:: Cambiar a la funcion (Aun por hacer) ver aptos / reservar.
                break;

            case 2:
                if (auth.esAdministrador()) {
                    std::cout << "\n--- PANEL DE ADMINISTRACIÓN ---\n";
                    auth.mostrarUsuarios();
                    std::cout << "Aquí va la funcionalidad para administradores...\n";
          // TODO:: Cambiar a la funcion (por hacer) Administrar aptos (SOlo para admins)
                } else {
                    std::cout << "Opción no válida.\n";
                }
                break;

            case 3:
                auth.cerrarSesion();
                return;

            case 4:
                std::cout << "¡Hasta luego!\n";
                exit(0);

            default:
                std::cout << "Opción no válida.\n";
                break;
        }
    }
}
