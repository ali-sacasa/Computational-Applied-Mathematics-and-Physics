#include <iostream> // Para std::cout, std::endl, std::cerr
#include <vector> // Usaremos vectores de la STL para representar las matrices
// Sebastián Alí Sacasa Céspedes - C4J546


// Porqué pongo la firma de esta función al inicio? En razón de que
// la función main la usa, y el compilador lee el código de arriba hacia abajo
// Si no se pone la firma, el compilador no sabe que existe esta función
// hasta que la encuentra más abajo en el código.
// Alternativamente, podría definir la función antes de main.
void print_mat(std::vector<double> &mat, int &rows, int &cols);

int main(int argc, char* argv[]){

  std::cout << "Multiplicación de matrices!" << std::endl;
  std::cout << "La idea es calcular C = A * B" << std::endl;
  std::cout << "A y B son matrices con valores predefinidos." << std::endl;
  std::cout << "Para esta evaluación requerimos poner en práctica" << std::endl;
  std::cout << "el concepto de memoria contigua." << std::endl;
  std::cout << "En general, este algoritmo depende mucho de la estructura de datos" << std::endl;
  std::cout << "usada para representar las matrices." << std::endl;
  std::cout << "Fun fact: los algoritmos para mejorar la eficiencia de multiplicación" << std::endl;
  std::cout << "de matrices es un campo de investigación aún abierto, dado que" << std::endl;
  std::cout << "existe una infinidad de algoritmos que dependen de esta operación" << std::endl;

  // Definamos la dimensión de las matrices mediante argumentos de la terminal
  if(argc != 7){
    std::cerr << "Usage: " << argv[0] << " --l [filas de A] --m [columnas de B] --n [columnas de A/filas de B]" << std::endl;
    exit(1);
  }
  // Ahora leemos las dimensiones
  int l, m, n;
  l = atoi(argv[2]);
  m = atoi(argv[4]);
  n = atoi(argv[6]);

  // Definamos nuestras matrices de entrada
  std::vector<double> A(l * n, 0.0); // Inicialización a 0.0
  std::vector<double> B(n * m, 0.0);
  std::vector<double> C(l * m, 0.0);
  std::vector<double> D(n * l, 0.0); // Para almacenar el resultado de B*A

  // Inicialización de A
  for(int i = 0; i < l; ++i){
    for(int j = 0; j < n; ++j){
      A[(i * n) + j] = i;
    }
  }
  // Inicialización de B
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      B[(i * m) + j] = j;
    }
  }

  std::cout << "Matrix A = " << std::endl;
  print_mat(A, l, n);
  std::cout << "Matrix B = " << std::endl;
  print_mat(B, n, m);

  std::cout << "Calculando multiplicación..." << std::endl;
  // C ya se encuentra inicializada en 0!
  // Eso significa que podemos hacer la suma parcial en cada uno de sus elementos
  // LABORATORIO: COMPLETAR la multiplicación de las matrices
  for(int i = 0; i < l; ++i){
    for(int j = 0; j < m; ++j){
      for(int k = 0; k < n; ++k){
       // Código aquí
        C[(i*m)+j]+=A[(i*n)+k]*B[(k*m)+j];
      }
    }
  }   // B es n x m, A es l x n solo posible si m == l
  // Resultado D será n x l
  if(m != l){
    std::cout << "Atención: B*A no está definida (m != l)" << std::endl;
  } else {
    for(int i = 0; i < n; ++i){
      for(int j = 0; j < l; ++j){
        for(int k = 0; k < m; ++k){
          D[(i*l)+j] += B[(i*m)+k] * A[(k*n)+j];
        }
      }
    }
  }

  // Resultados
  std::cout << "Resultado C=A*B" << std::endl;
  print_mat(C, l, m);

  if(m == l){
    std::cout << "Resultado D=B*A" << std::endl;
    print_mat(D, n, l);
  }

  return 0;
}

// Función auxiliar
void print_mat(const std::vector<double> &mat, const int &rows, const int &cols){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      std::cout << mat[(i * cols) + j] << " ";
    }
    std::cout << std::endl;
  }
}

// Porqué la firma de esta función usa & para sus argumentos? Porque así evitamos hacer copias de los vectores y enteros, y en su lugar trabajamos con referencias a los datos originales. Esto es más eficiente
// en términos de memoria y velocidad. Además, los vectores son pasados como referencia para evitar copiar toda la estructura de datos, lo cual sería ineficiente.
// Los enteros también se pasan por referencia, aunque en este caso la ganancia en eficiencia es menor, pero es una buena práctica.
// los vectores se pasan como referencia no constante (no const) porque la función podría modificarlos (aunque en este caso no lo hace).
// Si se quisiera asegurar que la función no modifique los vectores, se podrían pasar como referencia constante (const std::vector<double> &mat).
