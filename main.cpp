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

// debido a que el alineamiento se hace invertido, hay que volver
string invertirCadena(string& original){
    string inverse="";
    for (int i=original.size() - 1; i>=0; --i){
        inverse += original[i];
    }
    return inverse;

}

void puntajeMaximo(int** matriz, const char* cad1, const char* cad2, int gap_score){
    // recordar S es cad1 y T es cad2
    int n = strlen(cad1);
    int m = strlen(cad2);
    int i = n;
    int j = m;
    string alineamientoS = "";
    string alineamientoT = "";

    while (i>0 || j>0){
        if (i>0 && j==0){
            alineamientoS += cad1[i-1];
            alineamientoT += "-";
            i=i-1;
        } else if (i==0 && j>0){
            alineamientoS += "-";
            alineamientoT += cad2[j-1];
            j=j-1;
        } else if (i>0 && j>0 && matriz[i][j]==matriz[i-1][j]+gap_score){
            alineamientoS +=cad1[i-1];
            alineamientoT += "-";  
            i=i-1;          
        } else if (i>0 && j>0 && matriz[i][j]==matriz[i][j-1]+gap_score){
            alineamientoS += "-";
            alineamientoT += cad2[j-1];
            j=j-1;
        } else {
            alineamientoS += cad1[i-1];
            alineamientoT += cad2[j-1];
            i=i-1;
            j=j-1;
        }
    }
    alineamientoS = invertirCadena(alineamientoS);
    alineamientoT = invertirCadena(alineamientoT);
    
    cout << alineamientoS << endl << alineamientoT << endl;
}


void imprimir_matriz(int** matriz, int fila, int columna){
	for (int i = 0; i < fila; ++i) {
		for (int j = 0; j < columna; ++j) {
			std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void imprimir_alineamiento(int** matriz, const char* cad1, const char* cad2){

    int columna = strlen(cad1) + 1;
    int fila = strlen(cad2) + 1;
    for (int i=0;i<fila;++i){
        cout << "  " << cad1[i];
    }
    cout << endl;

	for (int i = 0; i < fila; ++i) {
        cout << cad2[i-1] << "  ";
		for (int j = 0; j < columna; ++j) {
			std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int valorPuntuacion(int** matriz,char a, char b){
    // char a pertenece a cad2 y char b pertenece a cad1
    int i;
    int j;

    if(a == 'A'){
        i = 0;
    } else if (a=='G'){
        i = 1;
    } else if (a == 'C'){
        i = 2;
    } else if (a == 'T'){
        i = 3;
    }
    
    if(b == 'A'){
        j = 0;
    } else if (b=='G'){
        j = 1;
    } else if (b == 'C'){
        j = 2;
    } else if (b == 'T'){
        j = 3;
    }

    return matriz[i][j];
}

// maximo para recorrer las secuencias
int maximo(int a, int b, int c){ // uhh idk
    return max(a,max(b,c));
}

int** matrizAlineamiento(const char* cad1, const char* cad2,
                        int** matriz, int** matriz_puntajes,
                        int gap_score){
    int columna = strlen(cad1);
    int fila = strlen(cad2);

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
                    matriz[i-1][j-1]+valorPuntuacion(matriz_puntajes,cad2[i-1],cad1[j-1]));
            }
            cout << "Se asigna " << matriz[i][j] << " en " << cad1[i] <<
             " y " << cad2[j] << " fila " << i << " columna " << j << endl;
        } 
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
    const char* cadena1 = cadena_columna.c_str() + '\0' ;
    
    string cadena_fila;
    ifstream file2(argv[2]);
    file2 >> cadena_fila;
    file2.close();
    const char* cadena2 = cadena_fila.c_str() + '\0' ;
    
    //MATRIZ DE EMPAREJAMIENTO
    int** similitud = generar_Funcion(argv[3]);
	imprimir_matriz(similitud,4,4);
    

    int** matriz_secuencia = generar_matriz_secuencias(cadena1, cadena2);
    imprimir_alineamiento(matriz_secuencia,cadena1,cadena2);
    
    matrizAlineamiento(cadena1,cadena2,matriz_secuencia,similitud,stoi(argv[4]));
    imprimir_alineamiento(matriz_secuencia,cadena1,cadena2);
    // estoy probando aparte para organizarlo despues
    //alineamiento(similitud, matriz_secuencia, stoi(argv[4]));
    
    puntajeMaximo(matriz_secuencia,cadena1,cadena2,stoi(argv[4]));
}
