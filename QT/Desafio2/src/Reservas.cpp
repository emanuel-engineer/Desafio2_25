#include <fstream>
#include <Reservas.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip> //Para setw y setfill
#include <sstream> //Formato de ID
using namespace std;

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
// Guardar el nuevo ID para próxima vez
        ofstream fileOut(archivoID);
        if (fileOut.is_open()) {
            fileOut << nuevoID;
            fileOut.close();
        }
        
        return nuevoID;
    }
    
    // Método para formatear el ID con ceros a la izquierda
    string formatearID(int id) {
        ostringstream oss;
        oss << setw(6) << setfill('0') << id;
        return oss.str();
    }
  

