#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define e 2.718281828459045
using namespace std;

typedef vector < vector < double > > layer;
typedef vector < double > resultados;
typedef vector < double > delta;

//el uso del bias se usará cuando se multiplique la salida con los pesos

class Capa
{		
	public:
		resultados salida;//Respuestas no contiendra un 1 para el bias
		layer neurona;//CapaNeurona Matriz de neurona x pesos
		delta valorDelta;// las entradas

		int numCaracteristicas;
		int numNeuronas;
		//el bias sera analizado mediante un if
		Capa(int numNeuronas , int numCaracteristicas){
			this->numNeuronas = numNeuronas;//Cantidad de Neuronas
			this->numCaracteristicas = numCaracteristicas+1;//+1 por el bias para el array de pesos

			for(int i=0 ; i < this->numNeuronas;i++){
				valorDelta.push_back(0.0);//inicializa los deltas
				salida.push_back(0.0);//inicializa las salidas

				neurona.push_back(vector< double >(this->numCaracteristicas));//genera la matriz de pesos
				for (int j = 0; j < this->numCaracteristicas; j++)
				{
					//srand (time(NULL));
					neurona[i][j] = (double)(rand()%100)/1000;//rand();
				}
			}

			/*for(int i=0;i < this->numNeuronas;i++){
				salida.push_back(0.0);
			}*/
		}
		//la cantidad de pesos en una neurona es la cantidad de salidas de una capa +1
		double multiplicacion(vector < double >&A, int Neurona){//resultados genera la neta
			int lim = A.size();//vector de salidas de la capa anterior (se incluye antes un 1 para el bias)
			double sum = neurona[Neurona][0];

			for(int i=0;i<lim;i++){
				sum += A[i] * neurona[Neurona][i+1];
			}

			return sum;
		}

		double sigmoide(double value){//funcion de activacion
			return 1/(1+pow(e,-value));
		}
		//Funcion a llamar principal
		double generarResultados(vector < double >&salidaAnterior){//funcion de calculo recive las salidas de la capa anterior
			for(int i = 0; i<this->numNeuronas; i++){
				salida[i] = sigmoide(multiplicacion(salidaAnterior,i));
			}
		}


		void imprimir(){
			//imprime neuronas

			for(int i=0; i<neurona.size(); i++){
				cout<<endl;
				cout<<"neurona: "<<i<<endl;
				for (int j=0; j < neurona[i].size(); j++)
				{
					cout<<neurona[i][j]<<" ";
				}
			}

			cout<<endl;

			resultados::iterator it;
			cout<<"Salidas"<<endl;
			for (it = salida.begin(); it != salida.end(); it++) {
				printf("%f\n", *it);
			}
			cout<<endl;
		}

		//~Capa();
	
};