#ifndef INGRESO_PLATAFORMA_H
#define INGRESO_PLATAFORMA_H


class Ingreso_Plataforma
{
public:
    Ingreso_Plataforma();
    void leer_uduarios();
    void verificar_datos();
    //verifica los datos del usuario, y dependiendo si es admin o usuario carga las reservas y opciones
    //correspondientes.
    int tipo_cuenta;
private:
    char16_t nombre_usuario; //char16_t es para poder tener 16 bits de memoria, en caso de nombres o contraseñas largas.
    char16_t contrasena;
};

#endif // INGRESO_PLATAFORMA_H
