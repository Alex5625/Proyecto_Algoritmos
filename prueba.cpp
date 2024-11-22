#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

// devuelve puntaje
int alineamiento(int** puntuacion, int** matriz, int gap_score) {
    // Implementación pendiente
}

// invertir cadena
string invertirCadena(const string& original) {
    string inverse = "";
    for (int i = original.size() - 1; i >= 0; --i) {
        inverse += original[i];
    }
    return inverse;
}

void puntajeMaximo(int** matriz, const string& cad1, const string& cad2, int gap_score) {
    int n = cad1.size();
    int m = cad2.size();
    int i = n;
    int j = m;
    string alineamientoS = "";
    string alineamientoT = "";

    while (i > 0 || j > 0) {
        if (i > 0 && j == 0) {
            alineamientoS += cad1[i - 1];
            alineamientoT += "-";
            i--;
        } else if (i == 0 && j > 0) {
            alineamientoS += "-";
            alineamientoT += cad2[j - 1];
            j--;
        } else if (i > 0 && j > 0 && matriz[i][j] == matriz[i - 1][j] + gap_score) {
            alineamientoS += cad1[i - 1];
            alineamientoT += "-";
            i--;
        } else if (i > 0 && j > 0 && matriz[i][j] == matriz[i][j - 1] + gap_score) {
            alineamientoS += "-";
            alineamientoT += cad2[j - 1];
            j--;
        } else {
            alineamientoS += cad1[i - 1];
            alineamientoT += cad2[j - 1];
            i--;
            j--;
        }
    }
    alineamientoS = invertirCadena(alineamientoS);
    alineamientoT = invertirCadena(alineamientoT);
    
    cout << alineamientoS << endl << alineamientoT << endl;
}

void imprimir_matriz(int** matriz, int fila, int columna) {
    for (int i = 0; i < fila; ++i) {
        for (int j = 0; j < columna; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void imprimir_alineamiento(int** matriz, const string& cad1, const string& cad2) {
    int columna = cad1.size() + 1;
    int fila = cad2.size() + 1;

    cout << "   ";
    for (char c : cad1) {
        cout << c << " ";
    }
    cout << endl;

    for (int i = 0; i < fila; ++i) {
        if (i > 0)
            cout << cad2[i - 1] << " ";
        else
            cout << " " << " "; // Espacio vacío para la primera fila
        for (int j = 0; j < columna; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int valorPuntuacion(int** matriz,char a, char b){
    // char a pertenece a cad2 y char b pertenece a cad1
    int i = (a == 'A') ? 0 : (a == 'G') ? 1 : (a == 'C') ? 2 : (a == 'T') ? 3 : -1;
    int j = (b == 'A') ? 0 : (b == 'G') ? 1 : (b == 'C') ? 2 : (b == 'T') ? 3 : -1;

    return (i != -1 && j != -1) ? matriz[i][j] : 0; // Manejo de casos no válidos
}

int maximo(int a, int b, int c){
    return max(a, max(b, c));
}

int** matrizAlineamiento(const string& cad1, const string& cad2,
                        int** matriz, int** matriz_puntajes,
                        int gap_score){
    int columna = cad1.size() + 1;
    int fila = cad2.size() + 1;

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            if (i == 0 && j == 0) {
                matriz[i][j] = 0;
            } else if (i > 0 && j == 0) {
                matriz[i][j] = matriz[i-1][j] + gap_score;
            } else if (i == 0 && j > 0) {
                matriz[i][j] = matriz[i][j-1] + gap_score;
            } else if (i > 0 && j > 0) {
                matriz[i][j] = maximo(
                    matriz[i-1][j] + gap_score,
                    matriz[i][j-1] + gap_score,
                    matriz[i-1][j-1] + valorPuntuacion(matriz_puntajes, cad2[i-1], cad1[j-1])
                );
            }
        } 
    }    
}

// Generar la matriz de secuencias
int** generar_matriz_secuencias(const string& cad1, const string& cad2){
    int columna = cad1.size() + 1;
    int fila = cad2.size() + 1;

    int** matriz = new int*[fila];
    for (int i = 0; i < fila; ++i) {
        matriz[i] = new int[columna]{};
    }

    return matriz;
}

// Generar la función de puntuación
int** generar_Funcion(const string& nombreArchivo){
	
	ifstream file(nombreArchivo); // archivo de puntajes

	int fila = 4, columna = 4;

	int** matriz = new int*[fila];
	for (int i = 0; i < fila; ++i) {
		matriz[i] = new int[columna]{};
	}

	string linea;
	int rowIndex = 0;

	while(getline(file, linea) && rowIndex < fila){
		stringstream ss(linea);
		string valor;
		int colIndex = 0;

		while(getline(ss, valor, ',') && colIndex < columna){
			matriz[rowIndex][colIndex++] = stoi(valor);
		}
		rowIndex++;
	}

	file.close();
	return matriz;
}

// Liberar memoria de la matriz
void liberarMatriz(int** matriz, int filas) {
	for (int i = 0; i < filas; ++i) {
		delete[] matriz[i];
	}
	delete[] matriz;
}

// Función principal
int main(int argc, char **argv) {
	if (argc < 5) { // Se requiere al menos cinco argumentos
		cout << "No añadiste los archivos.\n";
		return EXIT_FAILURE;
	}
	
	string cadena_columna;
	ifstream file1(argv[1]);
	file1 >> cadena_columna;
	file1.close();
	
	string cadena_fila;
	ifstream file2(argv[2]);
	file2 >> cadena_fila;
	file2.close();
	
	// MATRIZ DE EMPAREJAMIENTO
	int** similitud = generar_Funcion(argv[3]);
	imprimir_matriz(similitud,4,4);
	
	int** matriz_secuencia = generar_matriz_secuencias(cadena_columna, cadena_fila);
	imprimir_alineamiento(matriz_secuencia,cadena_columna,cadena_fila);
	
	matrizAlineamiento(cadena_columna,cadena_fila,matriz_secuencia,similitud,stoi(argv[4]));
	imprimir_alineamiento(matriz_secuencia,cadena_columna,cadena_fila);
	
	puntajeMaximo(matriz_secuencia,cadena_columna,cadena_fila,stoi(argv[4]));

	liberarMatriz(similitud,4); // Para matriz de puntuación
	liberarMatriz(matriz_secuencia,cadena_fila.size() + 1); // Para la matriz basada en cadenas

	return EXIT_SUCCESS;
}
