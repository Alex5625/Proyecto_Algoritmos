#include <iostream>
#include <fstream>


include namespace std;


//./programa -C1 cad1.tex -C2 cad2.tex -U funU.tex -V val

int** generar_Funcion(string archivo){
	
	ifstream file(archivo);
	
    int rows = 4, cols = 4; 

    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) { // Leer un valor
                std::cerr << "Error al leer el archivo.\n";

                // Liberar memoria en caso de error
                for (int k = 0; k <= i; ++k) {
                    delete[] matrix[k];
                }
                delete[] matrix;
                return 1;
            }
        }
    }

    file.close();
	
}
void imprimir_matriz(similitud){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

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
    
    int** similitud = generar_Funcion(argv[3]);
	imprimir_matriz(similitud);
    return 0;
}



