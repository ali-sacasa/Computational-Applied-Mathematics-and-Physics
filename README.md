# Computational & Applied Mathematics
### Subjects, development, and resources for industrial and academic purposes.

This repository hosts advanced computational solutions, research reports, and numerical experiments. It focuses on the intersection of programming science, theoretical physics, high-performance computing (HPC), and applied mathematics.

---

## Featured Research & Technical Reports

These reports include my own implementations, rigorous stability analysis, and performance benchmarking for each topic:

### 1. [Parallel Computing: Discrete Fourier Transform & Vector Products]
* **Core Development:** Parallelization of scientific algorithms using **OpenMP** (Shared Memory) and **MPI** (Distributed Memory).
* **Key Contributions:** Race condition analysis, scalability testing in multi-core architectures, and implementation of parallel internal products and DFT.

### 2. [Numerical Analysis: Matrix Algebra & RK4 Integrators]
* **Core Development:** Custom C++ `Matrix` class and 4th Order Runge-Kutta (RK4) solvers.
* **Key Contributions:** Analysis of numerical stability, memory efficiency in OOP, and graphical results of dynamical systems convergence.

### 3. [Data Science & Shell Scripting: A Topological Approach]
* **Core Development:** Large-scale data processing using the Bash declarative paradigm (awk, sed, grep).
* **Key Contributions:** Theoretical framework based on **Discrete Topological Spaces** applied to data streams and automated workflow generation.

---

## Key Features of this Repository
* **Custom Implementations:** Beyond course exercises, including optimized C++ classes and parallel scripts.
* **Graphical Analysis:** Every module includes visual representations of numerical results and performance scaling (Speedup/Efficiency).
* **Rigorous Documentation:** Full LaTeX-compiled reports with academic citations.

--- 
High-Performance Tools
For parallel execution, ensure you have an MPI implementation (like OpenMPI or MPICH) and a GCC compiler with OpenMP support:
# Example Compilation for Parallel DFT
g++ -fopenmp -O2 fourier.cpp -o fourier.x
mpicxx -O2 dot_product.cpp -o dot_product.x

---

# Academic Credits & Acknowledgments
## This repository is built upon the foundational materials of the Computational Physics (FS0432) course from the University of Costa Rica (UCR).

### Original Course Design: * Dr. Federico Muñoz Rojas and Dr. Marlon Brenes Porras

### Extended Development, Graphics & Reports: Sebastián Alí Sacasa Céspedes.

### Reference Source: [mbrenesn/FisicaComputacional](https://github.com/mbrenesn/FisicaComputacional)

---

## Environment Setup

### Cloning the Repository
```powershell
git clone [https://github.com/ali-sacasa/Computational-Applied-Mathematics.git](https://github.com/ali-sacasa/Computational-Applied-Mathematics.git)
cd Computational-Applied-Mathematics
```
