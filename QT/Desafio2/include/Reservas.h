#ifndef RESERVAS_H
#define RESERVAS_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class apartamento {
public:

private:
 string datos = "apartamentos.txt"
 string UltimoID = "ultimoID.txt"


  // Método para obtener y actualizar el próximo ID
 int generarNuevoID() {
    int ultimoID = 0;
        
    // Leer el último ID usado
    ifstream fileIn(archivoID);
      if (fileIn.is_open()) {
        fileIn >> ultimoID;
        fileIn.close();
        }
        
    // Incrementar el ID
    int nuevoID = ultimoID + 1;
        
    // Asegurar que no exceda 6 dígitos (999999)
    if (nuevoID > 999999) {
       nuevoID = 1; // Reiniciar si llegamos al límite
    } 
 }
};





#endif // !RESERVAS_H

