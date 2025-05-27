#ifndef RESERVAS_H
#define RESERVAS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip> //Para setw y setfill
#include <sstream> //Formato de ID

class ADMIN_AGG_apartamento {
public:

private:
 string datos = "apartamentos.txt"
 string UltimoID = "ultimoID.txt"


// Método para obtener y actualizar el próximo ultimoID
  int generarNuevoID ();
};





#endif // !RESERVAS_H

