#include "capa.h"
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define umbral  0.0001
using namespace std;


class redNeuronal
{
	private:
		double alpha,cambioAlpha;

		int nEntradas;
		int nSalidas;
		vector<Capa>red;

		/************testing************/
		vector<vector<double> > data;
		vector<vector<double> >Y;

		vector<vector<double> > testData;
		vector<vector<double> > yData;
		vector<vector<int> > Tabla;
		/*******************************/

	vector<double> separar(string cadena, char separador){//recorta datos
		vector<double> cont;
		cadena += ";";
		int tam = cadena.size();
		int atras = 0;
		for(int i=0; i<tam; i++){
			if(cadena[i]==separador){
				string cad = cadena.substr(atras,i-atras);
				cont.push_back(strtof((cad).c_str(),0));
				atras = i+1;
			}
			else if(cadena[i]==';'){
				string cad = cadena.substr(atras,i-atras);
				cont.push_back(strtof((cad).c_str(),0));
				atras = i+1;
			}
		}
		return cont;
	}

	void CopiarPesos(layer &Copia, int iCapa){//copia en dimensionalidad###
		int tamNeurona = red[iCapa].neurona.size();//numero de neuronas en la capa icapa
		int tamPesos = red[iCapa].neurona[0].size();//numero de pesos

		for(int i=0; i<tamNeurona;i++){
			Copia.push_back(vector< double >(tamPesos,0));

			////////////////////////////////////////
			for(int j=0;j<tamPesos;j++){
				Copia[i][j] = red[iCapa].neurona[i][j];
			}
		}
	}
	
	public:
		redNeuronal(int Entradas, int Salidas){
			alpha = 0.1;
			cambioAlpha = 0.0;

			nEntradas = Entradas;
			nSalidas = Salidas;

			for(int i=0; i<nSalidas;i++){//res
				Tabla.push_back(vector<int>(nSalidas));
			}
			

		}

		void readData(string nameData,char delimitador){
			ifstream read(nameData.c_str());
			while(!read.eof()){
				char C[200];
				read.getline(C,200);
				string caracteristicas(C);

				if(caracteristicas!=""){
					vector<double> A = separar(caracteristicas,delimitador);
					vector<double> R;
					for(int i=nEntradas; i<nSalidas+nEntradas; i++){
						R.push_back(A[i]);
					}
					Y.push_back(R);
					A.erase(A.begin()+nEntradas,A.begin()+nEntradas+nSalidas);//aqui se debe agregar +1 al inicio
				
					data.push_back(A);
				}
			}
			read.close();
		}

		void readTest(string nameData,char delimitador){
			ifstream read(nameData.c_str());
			while(!read.eof()){
				char C[200];
				read.getline(C,200);
				string caracteristicas(C);

				if(caracteristicas!=""){
					vector<double> A = separar(caracteristicas,delimitador);
					vector<double> R;
					for(int i=nEntradas; i<nSalidas+nEntradas; i++){
						R.push_back(A[i]);
					}
					yData.push_back(R);
					A.erase(A.begin()+nEntradas,A.begin()+nEntradas+nSalidas);
				
					testData.push_back(A);
				}
			}
			read.close();
		}

		vector<double> getResultados(){//copia resultado final del forward
			vector<double>Result;
			int tamRes = red[red.size()-1].salida.size();

			for(int i=0;i<tamRes;i++){
				Result.push_back(red[red.size()-1].salida[i]);
			}
			return Result;
		}

		/**********************testing*******************/
		void hacerPruebas(){//tabla de confusion

			ofstream write("resultados.csv");
			
			int tam = testData.size();
			for(int i=0 ; i<tam; i++){
				//cout<<i<<endl;
				CalcularResultado(testData[i]);
				vector<double>R = getResultados();
				Tabla[compararResultados(yData[i])][compararResultados(R)]++;
				string Res;
				int j;
				for(j=0;j<R.size()-1;j++){
					Res +=to_string(R[j]);
					Res +=",";
				}
				Res+=to_string(R[j]);
				write<<Res<<endl;
				//cout<<"hola"<<endl;
			}

			write.close();
			cout<<"*****************************************************************"<<endl;
			getTablaResultados();
			cout<<"*****************************************************************"<<endl;
			vector<int>Cantidad(tam);
			int n = Tabla.size();
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++)
					Cantidad[i]+=Tabla[i][j];
			}

			double sumaPorcentajes=0.0;
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					Tabla[i][j] = (Tabla[i][j]*100)/Cantidad[i];
					if(i==j)sumaPorcentajes+=Tabla[i][j];
				}
			}
			cout<<endl;
			cout<<"*****************************************************************"<<endl;
			cout<<"Porcentajes(%):"<<endl;
			getTablaResultados();
			cout<<"*****************************************************************"<<endl;
			cout<<"Eficiencia de la red Neuronal: "<<sumaPorcentajes/n<<"%"<<endl;
		}

		void getTablaResultados(){
			int tam = Tabla.size();

			string cabecera="              ";
			for(int i=0;i<tam;i++){
				cabecera+="Caracteristica"+to_string(i+1)+"   ";
			}
			cout<<cabecera<<endl;

			for(int i=0;i<tam;i++){
				string resTabla="Caracteristica";
				resTabla+= to_string(i+1)+": ";
				for(int j=0;j<Tabla[0].size();j++){
					resTabla+=to_string(Tabla[i][j]);
					resTabla+="               ";
				}
				cout<<resTabla<<endl;
			}
		}

		int compararResultados(vector<double>&v){
			int tam = v.size();

			for(int i=0;i<tam;i++){
				if(round(v[i])==1){
					return i;
				}
			}
		}

		/*****************************************************************************/


		void crearRed(vector<int>&infoCapa){// Para en este caso se usara 1 capa oculta
			int tam = infoCapa.size();
			red.push_back(Capa(infoCapa[0],nEntradas));

			int i;
			for(i=1; i<tam; i++){
  				red.push_back(Capa(infoCapa[i],infoCapa[i-1]));
  			}
  			i--;
  			red.push_back(Capa(nSalidas,infoCapa[i]));

		}

		void rellenarPesos(string filename){
			ifstream read(filename.c_str());
			int i=0;
			int cantNeurona = 0;

			while(!read.eof()){
				char C[200];
				read.getline(C,200);
				string caracteristicas(C);

				if(caracteristicas!=""){
					vector<double> A = separar(caracteristicas,',');
					for(int k=0;k<red[i].numCaracteristicas;k++)//ingresa los pesos a las neuronas
					{
						red[i].neurona[cantNeurona][k] = A[k];
					}
					cantNeurona++;

					if(cantNeurona == red[i].numNeuronas){
						i++;
						if(i<red.size()){
							cantNeurona = 0;
						}
					}
				}
			}
			read.close();
		}

		void CalcularResultado(vector<double>&I){//calcula el resultado de la red neuronal
			red[0].generarResultados(I);
			int tam = red.size();
			for(int i=1;i<tam;i++){
				red[i].generarResultados(red[i-1].salida);
			}
		}

		double calcularError(int M){
			int tam = red[red.size()-1].salida.size();
			double suma = 0.0;
			for(int i=0;i<tam;i++){
				suma += pow(red[red.size()-1].salida[i]-Y[M][i],2);
			}
			return (suma)/2.0;
		}

		double BackPropagation(){//se limitara a dos capas,,cada llamada se cambiara los pesos
			int cantData = data.size();
			double ErrorSuma=0.0;
			for(int m=0;m<cantData;m++){
				CalcularResultado(data[m]); //Despues de realizar esta funcion los resultados estaran registrados en cada capa de la red
				layer CapaTemporal;

				int capaActual = red.size()-1;
				CopiarPesos(CapaTemporal,capaActual);

				/******************PARA LA CAPA OUTPUT*************/
				int cantNeuronas = red[capaActual].numNeuronas;
				int cantCarateristicas = red[capaActual].numCaracteristicas;

				for(int i=0;i<cantNeuronas;i++){
					for(int j=0; j<cantCarateristicas;j++){
						double res = (red[capaActual].salida[i] - Y[m][i])*(1.0-red[capaActual].salida[i])*red[capaActual].salida[i];
						red[capaActual].valorDelta[i] = res;
						if(j!=0){
							red[capaActual].neurona[i][j]+= -alpha*res*red[capaActual-1].salida[j-1];
						}
						else{
							red[capaActual].neurona[i][j]+= -alpha*res;
						}
					}
				}
				/*******************PARA LA CAPA HIDDEN****************/
				capaActual = red.size()-2;
				cantNeuronas = red[capaActual].numNeuronas;
				cantCarateristicas = red[capaActual].numCaracteristicas;

				for(int i=0; i<cantNeuronas ;i++){
					double sum = 0.0;
					for(int k=0;k<red[capaActual+1].numNeuronas;k++){
						sum += red[capaActual+1].valorDelta[k]*CapaTemporal[k][i+1];//red[capaActual+1].neurona[k][i+1];
					}
					for(int j=0; j<cantCarateristicas;j++){
						double res = sum*(1.0-red[capaActual].salida[i])*red[capaActual].salida[i];
						red[capaActual].valorDelta[i]=res;
						if(j!=0){
							red[capaActual].neurona[i][j] += -alpha*res*data[m][j-1];
						}
						else{
							red[capaActual].neurona[i][j] += -alpha*res;
						}
					}
				}
				//calcular error para cada entrada
				ErrorSuma+=calcularError(m);
			}
			//suma total
			cout<<ErrorSuma/(double)cantData<<endl;
			return ErrorSuma/(double)cantData;
		}

		void Ajustar(){
			double tiempo = 0.0;
			ofstream write("errorData.csv");
			time_t first,second;

			first = clock();
			
			double error=BackPropagation();
			second = clock();
			tiempo +=(double)(second-first)/CLOCKS_PER_SEC;

			write<<tiempo<<","<<error<<endl;

			while(error>=umbral){
				first = clock();
				error = BackPropagation();
				second = clock();
				tiempo +=(double)(second-first)/CLOCKS_PER_SEC;
				write<<tiempo<<","<<error<<endl;
				alpha-=cambioAlpha;
			}

			write.close();

			return;
		}

		void guardarPesos(){
			int tam = red.size();
			ofstream write("dataPesosXOR.csv");
			for(int i=0; i<tam;i++){
				for(int j=0;j<red[i].numNeuronas;j++){
					int k;
					string pesos;
					for(k=0;k<red[i].numCaracteristicas-1;k++){
						pesos+=to_string(red[i].neurona[j][k]);
						pesos+=",";
					}
					pesos+=to_string(red[i].neurona[j][k]);
					write<<pesos<<endl;
				}
			}
		}

		void graficarError(){
			system("python graficarError.py");
		}

		void printRed(){
			int tam = red.size();
			for(int i = 0; i<tam; i++){
				cout<<"Capa: "<<i<<endl;
				red[i].imprimir();
			}
		}

		void printDataBase(){
			int tamx = data.size();
			int tamy = data[0].size();
			cout<<"ENTRADAS"<<endl;
			for(int i=0; i<tamx; i++){
				for(int j=0; j<tamy; j++){
					cout<<data[i][j]<<" ";
				}
				cout<<endl;
			}

			cout<<"SALIDAS"<<endl;
			tamx = Y.size();
			tamy = Y[0].size();
			for(int i=0; i<tamx; i++){
				for(int j=0; j<tamy; j++){
					cout<<Y[i][j]<<" ";
				}
				cout<<endl;
			}

		}
  
		//~redNeuronal();
	
};
