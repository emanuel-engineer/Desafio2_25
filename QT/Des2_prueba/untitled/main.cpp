#include <iostream>
#include "sistemaautenticacion.h"
#include "reservas.h"

using namespace std;

// Función para mostrar menú principal
void mostrarMenuPrincipal(SistemaAutenticacion& auth);
void menuUsuario(SistemaAutenticacion& auth);
void menuAdministrador(SistemaAutenticacion& auth);

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
            menuUsuario(auth);
            break;

        case 2:
            if (auth.esAdministrador()) {
                menuAdministrador(auth);
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

void menuUsuario(SistemaAutenticacion& auth) {
    Reservas reservas;
    int opcionUsuario;

    do {
        std::cout << "\n=== ÁREA DE USUARIO ===\n";
        std::cout << "1. Ver apartamentos disponibles\n";
        std::cout << "2. Reservar apartamento\n";
        std::cout << "3. Cancelar reserva\n";
        std::cout << "4. Ver reservas\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Selecciona una opción: ";
        std::cin >> opcionUsuario;

        switch (opcionUsuario) {
        case 1:
            reservas.mostrarApartamentosDisponibles();
            break;
        case 2: {
            std::string id;
            reservas.mostrarApartamentosDisponibles();
            std::cout << "ID del apartamento a reservar: ";
            std::cin >> id;
            reservas.reservarApartamento(id, auth.obtenerNombreUsuario());
            break;
        }
        case 3: {
            std::string id;
            reservas.mostrarReservas();
            std::cout << "ID del apartamento para cancelar reserva: ";
            std::cin >> id;
            reservas.cancelarReserva(id);
            break;
        }
        case 4:
            reservas.mostrarReservas();
            break;
        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cout << "Opción no válida.\n";
            break;
        }
    } while (opcionUsuario != 0);
}

void menuAdministrador(SistemaAutenticacion& auth) {
    Reservas reservas;
    int opcionAdmin;

    do {
        std::cout << "\n=== PANEL DE ADMINISTRACIÓN ===\n";
        std::cout << "1. Agregar apartamento\n";
        std::cout << "2. Eliminar apartamento\n";
        std::cout << "3. Modificar apartamento\n";
        std::cout << "4. Ver todos los apartamentos\n";
        std::cout << "5. Ver reservas\n";
        std::cout << "6. Gestionar usuarios\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "Selecciona una opción: ";
        std::cin >> opcionAdmin;

        switch (opcionAdmin) {
        case 1: {
            std::string nombre, descripcion;
            double precio;

            std::cout << "\n--- AGREGAR APARTAMENTO ---\n";
            std::cout << "Nombre del apartamento: ";
            std::cin.ignore(); // Limpiar buffer
            std::getline(std::cin, nombre);
            std::cout << "Precio por noche: $";
            std::cin >> precio;
            std::cout << "Descripción: ";
            std::cin.ignore(); // Limpiar buffer
            std::getline(std::cin, descripcion);

            if (reservas.agregarApartamento(nombre, precio, descripcion)) {
                std::cout << "¡Apartamento agregado exitosamente!\n";
            } else {
                std::cout << "Error al agregar el apartamento.\n";
            }
            break;
        }
        case 2: {
            std::string id;
            std::cout << "\n--- ELIMINAR APARTAMENTO ---\n";
            reservas.mostrarTodosApartamentos();
            std::cout << "ID del apartamento a eliminar: ";
            std::cin >> id;

            if (reservas.eliminarApartamento(id)) {
                std::cout << "¡Apartamento eliminado exitosamente!\n";
            } else {
                std::cout << "Error al eliminar el apartamento.\n";
            }
            break;
        }
        case 3: {
            std::string id, nuevoNombre, nuevaDescripcion;
            double nuevoPrecio;

            std::cout << "\n--- MODIFICAR APARTAMENTO ---\n";
            reservas.mostrarTodosApartamentos();
            std::cout << "ID del apartamento a modificar: ";
            std::cin >> id;

            if (reservas.existeApartamento(id)) {
                std::cout << "Nuevo nombre: ";
                std::cin.ignore();
                std::getline(std::cin, nuevoNombre);
                std::cout << "Nuevo precio: $";
                std::cin >> nuevoPrecio;
                std::cout << "Nueva descripción: ";
                std::cin.ignore();
                std::getline(std::cin, nuevaDescripcion);

                if (reservas.modificarApartamento(id, nuevoNombre, nuevoPrecio, nuevaDescripcion)) {
                    std::cout << "¡Apartamento modificado exitosamente!\n";
                } else {
                    std::cout << "Error al modificar el apartamento.\n";
                }
            } else {
                std::cout << "Apartamento no encontrado.\n";
            }
            break;
        }
        case 4:
            std::cout << "\n--- TODOS LOS APARTAMENTOS ---\n";
            reservas.mostrarTodosApartamentos();
            break;
        case 5:
            std::cout << "\n--- RESERVAS ACTUALES ---\n";
            reservas.mostrarReservas();
            break;
        case 6:
            std::cout << "\n--- GESTIÓN DE USUARIOS ---\n";
            auth.mostrarUsuarios();
            break;
        case 0:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cout << "Opción no válida.\n";
            break;
        }
    } while (opcionAdmin != 0);
}
