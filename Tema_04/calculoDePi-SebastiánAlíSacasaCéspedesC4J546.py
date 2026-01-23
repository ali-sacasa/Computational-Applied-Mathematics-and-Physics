#!/usr/bin/env python3

#Sebastián Alí Sacasa Céspedes - C4J546
#Cálculo de Pi aprox.   

import math

def funcionIntegrar(variableIndependiente): #Función a integrar

    #Parámetros: variableIndependiente (tipo flotante): valor de t en el que se evalúa la función.

#Se retorna el valor de función en el punto t con el siguiente criterio.
    return 4/(1+variableIndependiente**2) 

def calcularPi(func, intervalos, limitSup, limitInf):
    # Determinamos la dirección de la integración y ajuste del diferencial discretizado.

    if limitSup>=limitInf:
        # Integración en dirección positiva
        direccion =1
        diferencialDiscreto= (limitSup-limitInf)/intervalos
        puntoInicio=limitInf #Es definido el punto de inicio con el límite inferior, como inicio de la trayectoria de integración.
        # Se podría quizás utilizar las funciones abs() o min().
    else:
        # Integración en dirección negativa (límites invertidos)
        # Se aplica el teorema de Fubini, tal que,

        direccion= -1

        diferencialDiscreto= (limitInf-limitSup)/intervalos
        puntoInicio= limitSup #Se define el punto de inicio con el límite inferior, se podría utilizar las funciones abs() o min() posiblemente.

    resultadoIntegralPi= 0.0 #Incia el resultado de la integral.

    for particion in range(intervalos): #Aproxima mediante el método del punto medio.

        # Suma el área del rectángulo con altura en el punto medio calculado en el subintervalo actual.
        resultadoIntegralPi+= func(puntoInicio+(particion+0.5)*diferencialDiscreto)*diferencialDiscreto
#Retorna el resultado de la integral, luego de completar el ciclo for ajustando la dirección de integración..
    return resultadoIntegralPi*direccion

#Se ajustan los parámetros de la integral y se invocan las funciones.
resultado = calcularPi(funcionIntegrar, 10000000, 1, 0)

#Se imprime el resultado.
print(f"{resultado} \n error: {abs(resultado -math.pi)*100}")
