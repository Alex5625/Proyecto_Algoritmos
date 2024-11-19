#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


using namespace std;

// devuelve puntaje
int alineamiento(){
    
}


int** generar_matriz_secuencias(string cad1, string cad2, int V){
    int fila = strlen(cad1);
    int columnas = strlen(cad2);

    int** matriz = new int*[filas];

    for (int i = 0; i < filas; i++){
        matriz[i] = new int[columnas];
    }

    //rellenar la matriz con 9 pq es probable que te encuentres con 
    int valor = 9;

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            matriz[i][j] = valor

        }

    }
 
     
}

int** generar_Funcion(string archivo){
	
	ifstream file(archivo); // archivo de puntajes
	
    int rows = 4, cols = 4; 

    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
                    
            //SI NO SE PUEDE METER EL VALOR DE FILE EN I,J
            if (!(file >> matrix[i][j])) { // Leer un valor
                std::cerr << "Error al leer el archivo.\n";

                // Liberar memoria en caso de error
                for (int k = 0; k <= i; ++k) {
                    delete[] matrix[k];
                }
                delete[] matrix;
            }
        }
    }

    file.close();
	return matrix;
}

void imprimir_matriz(int similitud){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

}
//  0          1    2       3     4     5   6       7  8 
//./programa -C1 cad1.tex -C2 cad2.tex -U matriz.tex -V val

//  0              1            2             3        4
//./programa -C1 cad1.tex -C2 cad2.tex -U matriz.tex -V val
int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "no añadiste los archivos.\n";
        return 1;
    }
	
	string cadena1;
	ifstream file1(argv[1]);
    file1 >> cadena1;
    file1.close();
    
    string cadena2;
    ifstream file2(argv[2]);
    file2 >> cadena2;
    file2.close();
    
    //MATRIZ DE EMPAREJAMIENTO
    int** similitud = generar_Funcion(argv[3]);
	imprimir_matriz(similitud);
    

    generar_matriz_secuencias()
}



