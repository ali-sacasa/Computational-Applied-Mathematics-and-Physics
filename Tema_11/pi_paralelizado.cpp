// Sebastián Alí Sacasa Céspedes, C4J546
#include <iostream>
#include <mpi.h>
#include <cmath> // Agrego esta librería para verificar el error absoluto de pi con respecto al valor exacto

int main(int argc, char* argv[]) {
    // Número de iteraciones se lee como entrada de la aplicación
    // Se desea que el número de argumentos sean dos:
    // El nombre del programa y el número de iteraciones
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " --n [iterations]" << std::endl;
        return 1; // Cambio exit(1) por return 1 para mantener la consistencia
    }
    /* Aquí cambié el código para manejar errores de entrada ahorrándome una línea de código
    para añadir una verificación adicional*/
    // Ahora leemos el número de iteraciones
    int n = atoi(argv[2]);
    if (n <= 0) {
        std::cerr << "Existe un error, puesto que el número n de iteraciones debe ser positivo" << std::endl;
        return 1;
    }

    // Inicialización del ambiente MPI
    MPI_Init(&argc, &argv);
    /* acá reescribí el código u orden de las cosas para poder practicar 
    y no sólo copiar el código del repositorio con las instrucciones de la clase
    cumpliendo al final con lo solicitado*/
    int size, rank;
    // Tamaño y rango
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double time_1 = MPI_Wtime();

    // Subdivisión del rango de trabajo
    // Las siguientes operaciones se encargan de balancear la carga
    // en caso de que "n" no sea un múltiplo de del número de procesos
    // Su código aquí 
    int nlocal = n / size;
    int rest = n % size;

    // Ahora, si existe un resto y el rango es *menor* que el resto,
    // le sumamos uno a nlocal:
    // Su código aquí
    int start, end;
    if (rank < rest) {/* Si el rango es menor que el resto implicará que este proceso recibe una iteración extra
    en consecuencia se suma uno a nlocal*/
        nlocal++;
    // Definimos un punto de comienzo y le llamamos "start"

        start =rank*nlocal;


    } else {
        // Ahora, si existe un resto y el rango es *mayor o igual* que el resto,
        // le sumamos el resto a start. Esto se debe a que los rangos menores son los
        // los que recibieron un trozo mas grande
        start = rank*nlocal+rest;
    }
    // Ahora definimos un punto final
    end = start + nlocal;

    // Verificación de rangos (debug)
    if (end > n) {
        end = n; // Asegurar que no exceda n
    }
    // Cálculo de la integral
    // La suma local es local a cada rango
    double local_sum=0.0;
    double w = 1.0/(double)n;
    // Subdividimos el for loop en secciones más pequeñas que cada proceso realiza

    for (int i = start; i < end; ++i) {
        double x = w * ((double)i + 0.5); // ¿Por qué (i - 0.5)? Cambié a (i + 0.5) para centrar el rectángulo
    }   //Agregué un comentario para explicar el cambio puesto que es relevante ya que si se hubiera usado (i - 0.5) se estaría calculando un área fuera del intervalo [0,1]
        local_sum += 4.0 / (1.0 + (x * x));
    }

    // Reducción MPI aquí
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double time_2 = MPI_Wtime();

     // Ahora el rango 0 contiene la suma total, los otros procesos no contienen este valor!
    if (rank == 0) {
        double pi_approx = global_sum*w;
        double pi_exact = 3.14159265358979323846;
        double error = std::abs(pi_approx - pi_exact);
        
        std::cout.precision(15);
        std::cout << " Integración Numérica para Pi" << std::endl;
        std::cout << "Número de procesos: " << size << std::endl;
        std::cout << "Iteraciones totales: " << n << std::endl;
        std::cout << "Tiempo de ejecución: " << time_2 - time_1 << " segundos" << std::endl;
        std::cout << "Valor aproximado de pi: " << pi_approx << std::endl;
        std::cout << "Valor exacto de Pi:    " << pi_exact << std::endl;
        std::cout << "Error absoluto: " << error << std::endl;
        std::cout << "¿Cálculo correcto? " << (error < 1e-10 ? "Sí" : "No") << std::endl;
        
        // Verificación adicional para tolerancia o cota del error numérico.
        if (error > 1e-6) {
            std::cerr << " Error mayor al esperado" << std::endl;
        }
    }

    // Información de debug por proceso
    std::cout << "Proceso " << rank << ": start=" << start << ", end=" << end 
              << ", nlocal=" << nlocal << ", local_sum=" << local_sum << std::endl;

    MPI_Finalize();
    return 0;
}

// To run
// mpicc o bien mpicxx -o pi.cpp pi.c ó pi.x
// mpirun -np 4 ./pi.c ó bien ./pi.x
// Resercher sur MPI_LAND 
//
// 27/10/2025
// Investigar para la forma dinámica de la geometría.