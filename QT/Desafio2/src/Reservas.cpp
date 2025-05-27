#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip> //Para setw y setfill
#include <sstream> //Formato de ID
#include <Reservas.h>


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

