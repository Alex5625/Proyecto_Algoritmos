#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
/* COMPILA BIEN PERO LA FUNCION generar_matriz_secuencias GENERA UNA MATRIZ
4X4 Y NO 6X6 COMO ES EL LARGO DE LOS ARCHIVOS. (solucionado)*/

/* -----------------------------------------------------------------------------------------------
22/11/2024
NO ES LA ALINEACION QUE PROPONE LOS ALGORITMOS, PROBLEMA DE PUNTUACION ??? ALINEACION???? IDK
--------------------------------------------------------------------------------------------------
*/
using namespace std;


// debido a que el alineamiento se hace invertido, hay que volver
string invertirCadena(const string& original){
    string inverse="";
    for (int i=original.size() - 1; i>=0; --i){
        inverse += original[i];
    }
    return inverse;

}

void puntajeMaximo(int** matriz, const char* cad1, const char* cad2, int gap_score) {
    int n = strlen(cad2);
    int m = strlen(cad1); // ATENTI AQUI ns pq funciona bien
    // se me hace que es pq va de atras para adelante y ahi se
    // invierten los indices?????????
    int i = n;
    int j = m;
    string alineamientoS = "";
    string alineamientoT = "";

    string cad1invertida = cad2;
    string cad2invertida = cad1;
    // Realizar el traceback
    while (i > 0 || j > 0) {
        cout << "PASADA: \n";
        cout << "j: " << j << ", i: " << i << endl;
        if (i>0 && j==0){
            alineamientoS += cad1invertida[i];
            alineamientoT += "-";
            cout << "Caso 1 \n";
            cout << "Se introduce " << cad1invertida[i] << " en cadena 1 porque " <<
            j << " = 0 " << " y " << i << " > 0 " << endl;
            i--;
        } else if (i==0 && j>0){
            alineamientoS += "-";
            alineamientoT += cad2invertida[j];
            cout << "Caso 2 \n";
            cout << "Se introduce " << cad2invertida[j] << " en cadena 2 porque " <<
            i << " = 0 " << " y " << j << " > 0 " << endl;
            
            j--;
        }else if (j>0 && matriz[i][j] == matriz[i - 1][j] + gap_score) {
            // Gap en cadena 2
            alineamientoS += cad1invertida[i - 1];  // Agregar el carácter de cad1 al final
            alineamientoT += "-";  // Agregar un gap en la secuencia 2
            cout << "Caso 3 \n";
            cout << "Se introduce " << cad1invertida[i-1] << " en cadena 1 porque " <<
            matriz[i][j] << " = " << matriz[i-1][j] << " + " << gap_score << endl;
            i--;

        } else if (i>0 &&matriz[i][j] == matriz[i][j - 1] + gap_score) {
            // Gap en cadena 1
            alineamientoS += "-";  // Agregar un gap en cad1
            alineamientoT += cad2invertida[j - 1];  // Agregar el carácter de cad2
            cout << "Caso 4 \n";
            cout << "Se introduce " << cad2invertida[j-1] << " en cadena 2 porque " <<
            matriz[i][j] << " = " << matriz[i][j-1] << " + " << gap_score << endl;

            j--;
        } else { 
            // Diagonal: match o mismatch
            alineamientoS += cad1invertida[i - 1];  // Agregar el carácter de cad1
            alineamientoT += cad2invertida[j - 1];  // Agregar el carácter de cad2
            cout << "Caso 5\n";
            cout << "Se introduce " << cad1invertida[i-1] <<
            " en cadena 1 y " << cad2invertida[j-1] << " en cadena 2"<< endl;;
            cout << "Valor i,j: " << matriz[i][j] << endl;
            i--;
            j--;
        }
        
    }

    // Agregar gaps al final si las cadenas tienen longitudes diferentes
    while (i > 0) {
        alineamientoS += cad1invertida[i - 1];  // Agregar el resto de los caracteres de cad1
        alineamientoT += "-";  // Agregar gaps en cad2
        i--;
    }

    while (j > 0) {
        alineamientoS += "-";  // Agregar gaps en cad1
        alineamientoT += cad2invertida[j - 1];  // Agregar el resto de los caracteres de cad2
        j--;
    }
    //alineamientoT = invertirCadena(alineamientoT);

    cout << "Resultado del alineamiento:\n";
    alineamientoS = invertirCadena(alineamientoS);
    alineamientoT = invertirCadena(alineamientoT);
    cout << alineamientoT << endl << alineamientoS << endl;
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

void matrizAlineamiento(const char* cad1, const char* cad2,
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
            /*cout << "Se asigna " << matriz[i][j] << " en " << cad1[i] <<
             " y " << cad2[j] << " fila " << i << " columna " << j << endl;*/
        } 
    }
    //imprimir_alineamiento(matriz, cad1, cad2);
   
}


//POR MEJORAR hay que ver como se leen bien los archivos.tex
int** generar_matriz_secuencias(const char* cad1, const char* cad2){
    int columna = strlen(cad1) + 1;
    int fila = strlen(cad2) + 1;

    int** matriz = new int*[fila];
    for (int i = 0; i < fila; ++i) { // Cambiado a "< fila"
        matriz[i] = new int[columna];
    }

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matriz[i][j] = 0; // Inicialización explícita
        }
    }
    //imprimir_matriz(matriz, fila, columna);
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

// Liberar memoria de la matriz
void liberarMatriz(int** matriz, int filas) {
	for (int i = 0; i < filas; ++i) {
		delete[] matriz[i];
	}
	delete[] matriz;
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
	cout << "CONTROL 1\n";

	string cadena_columna;
	ifstream file1(argv[1]);
    file1 >> cadena_columna;
    file1.close();
    const char* cadena1 = cadena_columna.c_str();
 
	cout << "CONTROL 2\n";

    string cadena_fila;
    ifstream file2(argv[2]);
    file2 >> cadena_fila;
    file2.close();
    const char* cadena2 = cadena_fila.c_str();
    
	cout << "CONTROL 3\n";

    //MATRIZ DE EMPAREJAMIENTO
    int** similitud = generar_Funcion(argv[3]);
	//imprimir_matriz(similitud,4,4);
    

    int** matriz_secuencia = generar_matriz_secuencias(cadena1, cadena2);
    //imprimir_alineamiento(matriz_secuencia,cadena1,cadena2);
    
	cout << "CONTROL 4\n";
    matrizAlineamiento(cadena1,cadena2,matriz_secuencia,similitud,stoi(argv[4]));
    imprimir_alineamiento(matriz_secuencia,cadena1,cadena2);
    
    // estoy probando aparte para organizarlo despues
    //alineamiento(similitud, matriz_secuencia, stoi(argv[4]));

	cout << "CONTROL 5\n";
    puntajeMaximo(matriz_secuencia,cadena1,cadena2,stoi(argv[4]));


}
