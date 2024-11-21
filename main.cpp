#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
/* COMPILA BIEN PERO LA FUNCION generar_matriz_secuencias GENERA UNA MATRIZ
4X4 Y NO 6X6 COMO ES EL LARGO DE LOS ARCHIVOS. (solucionado)*/


using namespace std;


// devuelve puntaje
int alineamiento(int** puntuacion, int** matriz, int gap_score){
    /*
        recorrer matriz, revisar los valores de i,j:
            Si i se esta moviendo y j = 0, se hace el gap * la posicion (i)
            si i y j se estan moviendo se hace la puntuacion maxima de los 3 i-1 / j-1 / i-1 j-1
                aqui dentro se recorre la matriz de puntuacion para revisar los puntajes y eso.
            si i = 0 y j se esta moviendo se hace gap * la posicion (j)
    */
}

void imprimir_matriz(int** matriz, int fila, int columna){
	for (int i = 0; i < fila; ++i) {
		for (int j = 0; j < columna; ++j) {
			std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int valorPuntuacion(char a, char b){
    // usar con la matriz de puntuacion, ns como usarla
    if (a==b){
        return 2;
    } else {
        return -1;
    };
}

// maximo para recorrer las secuencias
int maximo(int a, int b, int c){ // uhh idk
    if (a > b && a > c){
        return a;
    } else if (b>a && b > c){
        return b;
    } else if (c>a && c>b){
        return c;
    } else if (c > a && b == c){
        return c; // valor sin gap
    } else if (c > b && c == a){
        return c;
    }
}

int** draftMatrizAlineada(const char* cad1, const char* cad2, int** matriz, int gap_score){
    int columna = strlen(cad1) + 1;
    int fila = strlen(cad2) + 1;

    for (int i = 0; i<=fila; i++){
        for (int j = 0;j<=columna;j++){
            if (i==0 && j==0){
                matriz[i][j] = 0;
            } else if (i>0 && j == 0){
                matriz[i][j] = matriz[i-1][j] + gap_score;
            } else if (i==0 && j>0){
                matriz[i][j] = matriz[i][j-1] + gap_score;
            } else if (i>0 && j>0) {
                matriz[i][j] = maximo(
                    matriz[i-1][j]+gap_score,
                    matriz[i][j-1]+gap_score,
                    matriz[i][j]+valorPuntuacion(cad1[i],cad2[j]));
            }
        } 
    }    
    imprimir_matriz(matriz,fila,columna);
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

// genera matriz 4x4 con los puntajes, donde 2 para match y -1 mismatch
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

//./programa cad.tex cad2.tex matriz.tex -1

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
    
    draftMatrizAlineada(cadena1,cadena2,matriz_secuencia,stoi(argv[4]));
    // estoy probando aparte para organizarlo despues
    //alineamiento(similitud, matriz_secuencia, stoi(argv[4]));
}
