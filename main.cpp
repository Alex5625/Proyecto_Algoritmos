#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
/* COMPILA BIEN PERO LA FUNCION generar_matriz_secuencias GENERA UNA MATRIZ
4X4 Y NO 6X6 COMO ES EL LARGO DE LOS ARCHIVOS. (solucionado)*/


using namespace std;

/*
// devuelve puntaje
int alineamiento(){
    
}
*/


void imprimir_matriz(int** matriz, int fila, int columna){
	for (int i = 0; i < fila; ++i) {
		for (int j = 0; j < columna; ++j) {
			std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

}


//POR MEJORAR hay que ver como se leen bien los archivos.tex
int** generar_matriz_secuencias(const char* cad1, const char* cad2){
    int columna = strlen(cad1) + 1;
    int fila = strlen(cad2) + 1;


    int** matriz = new int*[fila];
    for (int i = 0; i <= fila; ++i) {
        matriz[i] = new int[columna];
    }

    //rellenar la matriz con 0
    int valor = 0;

    for (int i = 0; i < fila; i++){
        for (int j = 0; j < columna; j++){
            matriz[i][j] = valor;
        }

    }
    imprimir_matriz(matriz, fila, columna);
    return matriz;
}


int** generar_Funcion(string nombreArchivo){
	
	ifstream file(nombreArchivo); // archivo de puntajes

    int fila = 4, columna = 4; 

    int** matriz = new int*[fila];
    for (int i = 0; i < fila; ++i) {
        matriz[i] = new int[columna];
    }
    fila = 0;

    string linea;

    while(getline(file, linea) && fila < 4){
        stringstream ss(linea);
        string valor;
        int columna = 0;

        while(getline(ss, valor, ',') && columna < 4){
            matriz[fila][columna] = stoi(valor);
            columna++;
        }
        fila++;
    }

    file.close();
	return matriz;
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
	
	string cadena_columna;
	ifstream file1(argv[1]);
    file1 >> cadena_columna;
    file1.close();
    const char* cadena1 = cadena_columna.c_str();
    
    string cadena_fila;
    ifstream file2(argv[2]);
    file2 >> cadena_fila;
    file2.close();
    const char* cadena2 = cadena_fila.c_str();
    
    //MATRIZ DE EMPAREJAMIENTO
    int** similitud = generar_Funcion(argv[3]);
	imprimir_matriz(similitud,4,4);
    

    int** matriz_secuencia = generar_matriz_secuencias(cadena1, cadena2);

    alineamiento(similitud, matriz_secuencia, stoi(argv[4]));
}
