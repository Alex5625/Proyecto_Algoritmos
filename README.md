# Needleman-Wunsch Algorithm Implementation

## Introducción
El algoritmo Needleman-Wunsch es un método ampliamente utilizado en bioinformática para realizar el alineamiento global de secuencias. Este enfoque permite identificar la mejor coincidencia posible entre dos secuencias biológicas (como ADN, ARN o proteínas), tomando en cuenta penalizaciones por desajustes y brechas.

Este repositorio contiene una implementación en C++ para alinear dos secuencias de diferentes longitudes, además de una visualización gráfica opcional mediante una API de GTK desarrollada en Python.

## Características
- **Compatibilidad con Linux y Windows**:
  - En Linux, todas las funcionalidades están garantizadas.
  - En Windows, la funcionalidad gráfica está limitada.
- **Visualización gráfica**:
  - Si las secuencias son del mismo tamaño, la matriz de puntuación se muestra en una ventana gráfica mediante GTK.
  - Si las secuencias son de distinto tamaño, la matriz de puntuación se imprimirá en la consola, ya que la ventana gráfica no funcionará en este caso.

## Archivos
- **`main.cpp`**:  
  Este archivo contiene todo el código necesario para ejecutar el alineamiento de secuencias.
- **Salida gráfica**:  
  Una vez ejecutado el programa, se genera una visualización del alineamiento como un archivo PNG utilizando Graphviz.

## Instrucciones de Uso
1. **Compilación**:  
   Para compilar el programa, utiliza el siguiente comando en bash:
   ```bash
   g++ -o nombre_ejecutable main.cpp
   ```
2. **Ejecución**:
    Ejecútalo con los siguientes argumentos:
    ```bash
    ./nombre_ejecutable -C1 cad1.tex -C2 cad2.tex -U martiz.csv -V valor_gap
    ```
    Donde:
    - **`-C1`**: Archivo que contiene la primera secuencia.  
    - **`-C2`**: Archivo que contiene la segunda secuencia.
    - **`-U`**: Archivo de ingreso en formato CSV con la matriz de puntuacion.
    - **`-V`**: Valor del gap (penalizacion por brechas).
3. **Visualización**:
    - El alineamiento se representará graficamente en dos formas:
    1. **Ventana GTK**: Se muestra la matriz de puntuacion (solo para secuencias del mismo tamaño).
    2. **Archivo PNG**: Se genera un archivo de imagen (formato PNG) en el directorio.
## Dependencias
- **Linux**:
    - GTK (para la visualizacion de la matriz de puntuacion)
    - Graphiz (para generar el gráfico del alineamiento)
- **Windows**:
    - Limitado a la funcionalidad basica sin soporte grafico. Solo se muestra en consola la matriz de puntuacion.
## Notas Importantes:
- Esta implementacion funciona completamente en Linux. En Windows, si bien el alineamiento se ejecuta, la visualizacion grafica podria no funcionar correctamente debido a las dependencias de GTK.
- Asegurate de que las secuencias de entrada tengan el formato adecuado.