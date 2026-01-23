#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
Función integrando para calcular pi mediante integración numérica.
La función a integrar es G(t) =4/(1+t**2), cuya integral definida de 0 a 1 es pi
 */
double calcular_integrando(double variable_independiente) {
    return 4.0/(1+variable_independiente*variable_independiente); // G(t) = 4/(1+t^2) se define aquí
}

// Se calcula la integral definida de una función en un intervalo [a, b] usando el método del punto medio,
// que es una variante de las sumas de Riemann.
// La función recibe como parámetros: un puntero a la función a integrar, el número de intervalos, y los límites de integración.
// de esa función, devolviendo el valor aproximado de la integral definida.
double integrar_metodo_punto_medio(double (*funcion)(double), // puntero a función
                                  unsigned long numero_intervalos,// número de intervalos con unsigned long para evitar overflow que puede ocurrir con int en rangos grandes de valores
                                  double limite_inferior, // límite inferior de integración
                                  double limite_superior) {// límite superior de integración
    
    // Validación de parámetros de entrada
    if (numero_intervalos == 0) {
        std::cerr << "El número de intervalos debe ser mayor que cero" << std::endl; // std::cerr es para imprimir mensajes de error
        return 0.0;
    }
    
    if (limite_superior==limite_inferior) {
        return 0.0;  // Integral sobre un intervalo nulo
    }
    
    // Determinación automática de la dirección de integración
    int direccion = 1;
    double a=limite_inferior; // se define el límite inferior
    double b=limite_superior;// se define el límite superior
    
    if (limite_superior<limite_inferior) {// de forma equivalente al caso anterior
        direccion = -1;
        a=limite_superior;
        b=limite_inferior;
    }
    
    // Se programa el cálculo del diferencial discreto
    const double diferencial=(b-a)/static_cast<double>(numero_intervalos); // static_cast es para la conversión de tipos de datos
    double suma_integral=0.0; // Inicialización de la suma de Riemann
    
    // Se implementa el algoritmo de integración por sumas de Riemann (punto medio)
    for (unsigned long p= 0; p < numero_intervalos; ++p) { //Se crea un bucle para recorrer los intervalos
        double punto_medio =a+(p+0.5)*diferencial; // Cálculo del punto medio del subintervalo
        suma_integral+=funcion(punto_medio)*diferencial;// Se acumula el área del rectángulo en la suma total
    }
    
    return suma_integral*direccion; // Se devuelve el valor aproximado de la integral definida multiplicado por la dirección
 }

// Se inicia la función principal del programa
int main() {
    // Parámetros del experimento numérico
    const unsigned long NUMERO_INTERVALOS = 1000000; // Más intervalos implica mayor precisión
    const double LIMITE_INFERIOR = 0.0; // Límite inferior de integración
    const double LIMITE_SUPERIOR = 1.0; // Límite superior de integración
    
    // Ejecución del cálculo numérico
    double pi_aproximado = integrar_metodo_punto_medio(calcular_integrando,
                                                      NUMERO_INTERVALOS,
                                                      LIMITE_INFERIOR,
                                                      LIMITE_SUPERIOR);
    
    //Se presenta el resultado del cálculo
    std::cout.precision(15);
    std::cout << "Cálculo de pi por integración numérica" << std::endl;// std::endl es para salto de línea
    std::cout << "Método usado es el de sumas de Riemann con punto medio" << std::endl; // std::count es para imprimir en consola
    std::cout << "Función integrada 4/(1 + t^2)" << std::endl;
    std::cout << "Límites de integración [" << LIMITE_INFERIOR // << es para concatenar cadenas
              << ", " << LIMITE_SUPERIOR << "]" << std::endl;
    std::cout << "Número de intervalos es " << NUMERO_INTERVALOS << std::endl;
    std::cout << "Valor aproximado es " << pi_aproximado << std::endl;
    std::cout << "Valor real es " << M_PI << std::endl;
    std::cout << "Error absoluto es " << std::abs(pi_aproximado - M_PI) << std::endl;
    std::cout << "Error relativo es " << std::abs(pi_aproximado - M_PI)/M_PI * 100 
              << "%" << std::endl;
    
    return 0;// Fin de la función principal, retornando 0
}