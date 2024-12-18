#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip> // para que la matriz se vea mas bonita
#include <utility>


#ifdef _WIN32
#endif

using namespace std;


// debido a que el alineamiento se hace invertido, hay que volver
string invertirCadena(const string& original){
    string inverse="";
    for (int i=original.size() - 1; i>=0; --i){
        inverse += original[i];
    }
    return inverse;

}

pair<string,string> puntajeMaximo(int** matriz, const char* cad1, const char* cad2, int gap_score) {
    int n = strlen(cad2);
    int m = strlen(cad1);
    // se asignan 
    int i = n;
    int j = m;
    string alineamientoS = "";
    string alineamientoT = "";

    // debido a que se hace desde el final de la matriz
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
            //cout << "Se introduce " << cad1invertida[i] << " en cadena 1 porque " <<
            //j << " = 0 " << " y " << i << " > 0 " << endl;
            i--;
        } else if (i==0 && j>0){
            alineamientoS += "-";
            alineamientoT += cad2invertida[j];
            //cout << "Caso 2 \n";
            //cout << "Se introduce " << cad2invertida[j] << " en cadena 2 porque " <<
            //i << " = 0 " << " y " << j << " > 0 " << endl;
            
            j--;
        }else if (j>0 && matriz[i][j] == matriz[i - 1][j] + gap_score) {
            // Gap en cadena 2
            alineamientoS += cad1invertida[i - 1];  // Agregar el carácter de cad1 al final
            alineamientoT += "-";  // Agregar un gap en la secuencia 2
            cout << "Caso 3 \n";
            //cout << "Se introduce " << cad1invertida[i-1] << " en cadena 1 porque " <<
            //matriz[i][j] << " = " << matriz[i-1][j] << " + " << gap_score << endl;
            i--;

        } else if (i>0 &&matriz[i][j] == matriz[i][j - 1] + gap_score) {
            // Gap en cadena 1
            alineamientoS += "-";  // Agregar un gap en cad1
            alineamientoT += cad2invertida[j - 1];  // Agregar el carácter de cad2
            cout << "Caso 4 \n";
            //cout << "Se introduce " << cad2invertida[j-1] << " en cadena 2 porque " <<
            //matriz[i][j] << " = " << matriz[i][j-1] << " + " << gap_score << endl;

            j--;
        } else { 
            // Diagonal: match o mismatch
            alineamientoS += cad1invertida[i - 1];  // Agregar el carácter de cad1
            alineamientoT += cad2invertida[j - 1];  // Agregar el carácter de cad2
            cout << "Caso 5\n";
            //cout << "Se introduce " << cad1invertida[i-1] <<
            //" en cadena 1 y " << cad2invertida[j-1] << " en cadena 2"<< endl;;
            //cout << "Valor i,j: " << matriz[i][j] << endl;
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
    // volver al orden original de la cadena
    alineamientoS = invertirCadena(alineamientoS);
    alineamientoT = invertirCadena(alineamientoT);

    cout << "Resultado del alineamiento:\n";
    cout << alineamientoT << endl << alineamientoS << endl;
    string archivo_secuencia = alineamientoT + "\n" + alineamientoS;
    
    return make_pair(alineamientoT, alineamientoS);
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
    cout << setw(5) << "  ";
    for (int i=0;i<columna;++i){
        cout << setw(4) << " " << cad1[i];
    }
    cout << endl;

	for (int i = 0; i < fila; ++i) {
        cout << cad2[i-1] << "  ";
		for (int j = 0; j < columna; ++j) {
			std::cout << setw(4) << matriz[i][j] << " ";
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

// hace la matriz con el alineamiento
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
    cout << "El puntaje maximo es: " << matriz[fila][columna] << endl;
    //imprimir_alineamiento(matriz, cad1, cad2);
   
}


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


void escribirCSVDinamico(int** matriz, const string& cadena1, const string& cadena2 , 
                        const char* nombreArchivo) {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir.\n";
        return;
    }

    // Usar la longitud de las cadenas para determinar las dimensiones
    int filas = cadena1.size() + 1 ;  // Número de filas
    int columnas = cadena2.size() + 1   ;  // Número de columnas

    // Escribir la matriz en formato CSV
    for (int i = 0; i < columnas; ++i) {
        for (int j = 0; j < filas; ++j) {
            archivo << matriz[i][j];
            if (j < columnas - 1){            
                archivo << ",";
            }
        }
        archivo << "\n"; // Fin de la fila
    }


    archivo.close();
    std::cout << "Archivo CSV creado exitosamente: " << nombreArchivo << "\n";
}


// Liberar memoria de la matriz
void liberarMatriz(int** matriz, int filas) {
	for (int i = 0; i < filas; ++i) {
		delete[] matriz[i];
	}
	delete[] matriz;
}

// grafo de alineamiento
void generarGrafoDOT2(const std::string &alineamientoS, const std::string &alineamientoT) {

    int n = alineamientoS.size();
    int m = alineamientoT.size();

    // crear el archivo de salida
    std::ofstream fp("alineamiento.txt");

    // manejo errores
    if (!fp.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir el grafo.\n";
        return;
    }

    // escribir el grafo en formato DOT
    fp << "graph bonito {\n";


    fp << "rankdir=HR;\n";        // Orientación horizontal
    fp << "splines=false;\n";     // Fuerza líneas completamente rectas
    fp << "node [shape=circle];\n\n";

    
    //in beetween ----------------------------------------------------------------------------------------

    int contador_gaps = 0;

    
    //cadena 1 - S
    fp << "\n// Nodos para la primera cadena\n";

    int contador_bases_S = 0;

    for(int i = 0; i < n; i++){
        contador_bases_S++;
        fp << "S" << contador_bases_S << " [label = \"" << alineamientoS[i] << "\" ];\n";            
    }


    //cadena 2 - T
    fp << "\n// Nodos para la segunda cadena\n";

    int contador_bases_T = 0;

    for(int j = 0; j < n; j++){
        contador_bases_T++;
        fp << "T" << contador_bases_T << " [label = \"" << alineamientoT[j] << "\" ];\n";            
    }

    //----------------------------------------------------------------------------------------------------
    fp << "\n// Alineación horizontal por fila\n\n// cadena S\n";
    //cadena 1 - S
    string rank_s = "{rank=same; ";
    int contador_gaps_2 = 0;
    string gap_s = "";
    int contador_bases_S2 = 0;

    for(int i = 0; i < n; i++){

        contador_bases_S2++;
        string base_S = "S" + to_string(contador_bases_S2);

        rank_s = rank_s + base_S + "; ";    

    }
    fp <<rank_s<<" }\n";


    fp << "\n// cadena T\n";
    //cadena 2 - T
    string rank_t = "{rank=same; ";
    //int contador_gapt_2 = 0;
    string gap_t = "";
    int contador_bases_T2 = 0;

    for(int j = 0; j < n; j++){

        contador_bases_T2++;
        string base_T = "T" + to_string(contador_bases_T2);

        rank_t = rank_t + base_T + "; ";    
    
        
    }
    fp <<rank_t<<" }\n";

    //----------------------------------------------------------------------------------------------------
    fp << "\n// Conexiones dentro de cada cadena\n\n";
    
    //cadena 1 - S
    string conexion_s = "";
    int contador_gaps_3 = 0;
    string gap_s2 = "";
    int contador_bases_S3 = 0;

    for(int i = 0; i < n-1; i++){

        contador_bases_S3++;
        string base_S2 = "S" + to_string(contador_bases_S3);

        conexion_s = conexion_s + base_S2 + " -- ";    

    }

    for(int i = n-1; i < n; i++){

        contador_bases_S3++;
        string base_S2 = "S" + to_string(contador_bases_S3);

        conexion_s = conexion_s + base_S2 + ";";    

        
    }
    fp <<conexion_s + "\n";
    
    // --------------------------------------------------------------- 
    //cadena 2 - T
    string conexion_t = "";
    string gap_t2 = "";
    int contador_bases_T3 = 0;

    for(int i = 0; i < n-1; i++){

        contador_bases_T3++;
        string base_T2 = "T" + to_string(contador_bases_T3);

        conexion_t = conexion_t + base_T2 + " -- ";    

    }

    for(int i = n-1; i < n; i++){

        contador_bases_T3++;
        string base_T2 = "T" + to_string(contador_bases_T3);

        conexion_t = conexion_t + base_T2 + ";";    
    
    }
    fp <<conexion_t + "\n";

    
    //----------------------------------------------------------------------------------------------------
    fp << "\n// Conexiones entre cadenas (si esque las letras coinciden)\n";
    int kelly = 0;

    for (int i = 0; i < n; i++) {

        if(alineamientoS[i] == '-' || alineamientoT[i] == '-'){
            //fp<<"";
            string baseS = "S" + to_string(i + 1);
            string baseT = "T" + to_string(i + 1);
                                                //linea discontinua y negra
            fp << baseS << " -- " << baseT << " [style=dashed, penwidth=3, color=black];\n";

        }else{
            kelly++;
            //letras iguales
            if (alineamientoS[i] == alineamientoT[i]) {
                string baseS = "S" + to_string(i + 1);
                string baseT = "T" + to_string(i + 1);
                                                    //linea gruesa y azul
                fp << baseS << " -- " << baseT << " [style=bold, color=blue];\n";
            }else{
            //letras diferentes
                string baseS = "S" + to_string(i + 1);
                string baseT = "T" + to_string(i + 1);
                                                    //linea roja
                fp << baseS << " -- " << baseT << " [style=bold, color=red];\n";
            }
        }        
    }

    //in beetween ----------------------------------------------------------------------------------------

    fp << "}\n";

    fp.close();

    std::cout << "\nArchivo 'alineamiento.txt' generado correctamente.\n";
}



void abrirImagen() {
    const char* archivo_imagen = "archivo.png";
    
    //SI TU SISTEMA OPERATIVO NO POSEE GTK COMENTA ESTA FUNCION
    // cambiar python3 a py dependiendo del SO
    system("python3 gtk.py &");
    //-----------------------------------------------------------

    // Detectar el sistema operativo
    #ifdef _WIN32
        // En Windows usamos start
        system(("start " + std::string(archivo_imagen)).c_str());
    #elif defined(__APPLE__) || defined(__MACH__)
        // En macOS usamos el comando open
        system(("open " + std::string(archivo_imagen)).c_str());
    #elif defined(__linux__)
        // En Linux, primero detectamos el entorno de escritorio
        const char* entorno = std::getenv("XDG_CURRENT_DESKTOP");

        if (entorno) {
            if (strstr(entorno, "GNOME")) {
                system(("eog " + std::string(archivo_imagen)).c_str());  // GNOME
            }
            else if (strstr(entorno, "KDE") || strstr(entorno, "Plasma")) {
                system(("gwenview " + std::string(archivo_imagen)).c_str());  // KDE
            }
            else if (strstr(entorno, "XFCE")) {
                system(("ristretto " + std::string(archivo_imagen)).c_str());  // XFCE
            }
            else if (strstr(entorno, "MATE")) {
                system(("eom " + std::string(archivo_imagen)).c_str());  // MATE
            }
            else {
                std::cerr << "Entorno desconocido: " << entorno << ". Usando 'xdg-open'." << std::endl;
                system(("xdg-open " + std::string(archivo_imagen)).c_str());  // Genérico
            }
        } else {
            std::cerr << "No se pudo detectar el entorno de escritorio. Usando 'xdg-open'." << std::endl;
            system(("xdg-open " + std::string(archivo_imagen)).c_str());  // Genérico
        }


    #else
        std::cerr << "Sistema operativo no soportado." << std::endl;
    #endif
}

void comandos_sistema(){
    system("dot -Tpng alineamiento.txt -o archivo.png");
    abrirImagen();
}

//./programa cad1.tex cad2.tex matriz.csv -1
int main(int argc, char **argv) {
    if (argc < 5) {
        cout << "Para ejecutar: \n" <<
        " ./programa cad1.tex cad2.tex matriz_gtk.csv gap_score\n" <<
        "- cad1 y cad2 contienen las cadenas de nucleotidos, " <<
        "- matriz_gtk.csv es donde se guarda la matriz para graficar\n. "<<
        "- gap_score es un entero\n";
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
	//imprimir_matriz(similitud,4,4);
    
    int** matriz_secuencia = generar_matriz_secuencias(cadena1, cadena2);
    //imprimir_alineamiento(matriz_secuencia,cadena1,cadena2);

    matrizAlineamiento(cadena1,cadena2,matriz_secuencia,similitud,stoi(argv[4]));
    imprimir_alineamiento(matriz_secuencia,cadena1,cadena2);

    pair<string,string> alineamientos = puntajeMaximo(matriz_secuencia,cadena1,cadena2,stoi(argv[4]));
    string alineamientoT = alineamientos.first;
    string alineamientoS = alineamientos.second;

    escribirCSVDinamico(matriz_secuencia, cadena_columna, cadena_fila, "matriz_gtk.csv");
    generarGrafoDOT2(alineamientoT, alineamientoS);
    comandos_sistema();
}
