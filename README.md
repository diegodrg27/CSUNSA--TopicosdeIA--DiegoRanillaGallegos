# CSUNSA--TopicosdeIA--DiegoRanillaGallegos
RED NEURONAL BACKPROPAGATION

/*****************************/
Caracteristicas:

- Esta red esta conformada por dos capas de neuronas
- Para poder modificar la cantidad de neuronas tanto como la primera como
  la segunda capa se tiene que realizar lo siguiente:


	--Linea 18: ->  redNeuronal Cabeza(2,1);  
	  El primer parametro es la cantidad de entradas de la red (capa de entrada), es la longitud de la entrada de la data.
          El segundo parametro es la cantidad de salidas que tendra la red (capa de salida). 					
			

	--Linea 22: ->  v.push_back(2)
	  Aqui se va añadir la cantidad de neuronas que habrá en la capa oculta en este caso tiene dos neuronas

	  
/********************************************/
Compilación y Ejecucion

Para compilar el programa se tiene que ejecutar el siguiente comando:
g++ -std=c++11 main.cpp -o main

Para ejecutarlo: ./main

/*********************************/
ALGO MAS

1. Cuando se ejecute va a entrenar la red neuronal hasta llegar a un valor minimo
2. Luego se mostrará los pesos obtenidos por el entrenamiento por cada capa

/********************************/
PRUEBAS

Se usaron los datos del XOR para el entrenamiento, después de mostrar los resultados del entrenamiento la consola le solicitará ingresar dos valores para poder hacer el respectivo testing, como el siguiente:

Ingresar Valores

Valor 1:1

Valor 2:0

Resultado
 0.986549

* Eso se repetirá de manera indefinida por lo que para detener el programa emplee ctrl+c
