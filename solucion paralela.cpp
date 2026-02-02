#include <iostream>
#include <omp.h>    // Librería OpenMP [cite: 17]
#include <cstdlib>  // Para generar números aleatorios [cite: 16]
#include <ctime>

using namespace std;

#define N 1000      // Cantidad de elementos definida en las instrucciones [cite: 16]
#define chunk 10    // Porción de datos para mostrar en pantalla [cite: 18]

int main() {
    cout << "Suma de arreglos en paralelo con OpenMP\n";

    float a[N], b[N], r[N];
    int i;

    // Inicialización de los arreglos con valores aleatorios [cite: 16]
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        a[i] = static_cast<float>(rand() % 100);
        b[i] = static_cast<float>(rand() % 100);
    }

    // Realizar un for paralelo a través de las funciones de OpenMP [cite: 17]
    // Se utiliza 'shared' para los arreglos que todos ven y 'private' para el índice
    #pragma omp parallel for \
        shared(a, b, r) private(i) \
        schedule(static, chunk)
    for (i = 0; i < N; i++) {
        r[i] = a[i] + b[i]; // Cada hilo se encarga de una parte de la suma [cite: 10]
    }

    // Imprimir parte de los arreglos para comprobar resultados [cite: 18]
    cout << "\nComprobando los primeros " << chunk << " resultados:\n";
    cout << "Arreglo A + Arreglo B = Arreglo R (Resultado)\n";
    for (i = 0; i < chunk; i++) {
        cout << a[i] << " + " << b[i] << " = " << r[i] << endl;
    }

    return 0;
}