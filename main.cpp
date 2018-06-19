//#include "capa.h"
#include <stdio.h>
#include <time.h>
#include <ctime>
#include "redNeuronal.h"

void imprimir(vector<double>& Respuesta){
	vector<double>::iterator it;
	for (it = Respuesta.begin(); it != Respuesta.end(); it++) {
		cout << *it <<" ";
	}
	cout<<endl;
}

int main(){
	
	/**************Dos neuronas de salida****************/
	redNeuronal Cabeza(2,1);//inputLayer-outputlayer
	//Cabeza.readData("irisN.csv",',');
	Cabeza.readData("dataXOR.txt",' ');
	vector<int> v;
	v.push_back(2);//una capa oculta

	Cabeza.crearRed(v);//Crear otra funcion que almacena los pesos de un archivo sobre esa red creada
	Cabeza.Ajustar();// Guardar pesos en un archivo por capa


	
	Cabeza.guardarPesos();
	Cabeza.rellenarPesos("dataPesosXOR.csv");
	Cabeza.printRed();

	//Cabeza.CalcularResultado();

	while(true){
		vector<double>I;
		double val1,val2;
		cout<<"Ingresar Valores"<<endl;
		cout<<"Valor 1:";
		cin>>val1;

		cout<<"Valor 2:";
		cin>>val2;

		I.push_back(val1);
		I.push_back(val2);
		Cabeza.CalcularResultado(I);

		cout<<"Resultado"<<endl;
		vector<double>R = Cabeza.getResultados();


		for (std::vector<double>::iterator it = R.begin() ; it != R.end(); ++it)
		    std::cout << ' ' << *it;
		std::cout << '\n';

	}

}
