#include <stdlib.h>
#include <fcntl.h>
#include <fstream>
#include <pthread.h>
#include <sys/stat.h>
#include <iostream>
#include <string.h>
#include <ctime>
//gcc thread.c -pthread
//./a.out
using namespace std;

struct parametros{
	string mensaje;
	int cont;//veces que se repite el mensahje
	int num;//random
	int tam;//tamaño random		
};

void *escritura_ar(void *arg){

	ofstream escribir;//nombre del archivo
	escribir.open("Archivo_Escribir.txt", ios::out);//abrinedo archivo //crea archivo

	if(escribir.fail()){
		cout<<"No se Creo Archivo\n";
		exit(1);
	}
	cout<<"El hilo 1 escribio el mensaje en el archivo\n";
	escribir<<"Hola esto es un mensje con Hilos en un Texto";
	escribir.close();

}
void *lectura_ar(void *arg){

	ifstream leer;
	leer.open("Lectura.txt",ios::in);
	string texto;

	if(leer.fail()){
		cout<<"NO se pudo abrir archivo\n";
		exit(1);
	}
	while(!leer.eof()){
		getline(leer,texto);
		cout<<texto<<endl;
	
	leer.close();
	}	

}
void *hm(void *parameters){
	
	struct parametros* p = (struct parametros*) parameters;
	for(int i = 0;  i<p->cont; i++)
		cout<<"\n"<<p->mensaje<<endl;
	return NULL;
	
}
void *random_num(void *param){
	struct parametros* r = (struct parametros*) param;
	for(int i = 0; i<r->tam; i++)
		cout<<" "<<r->num;
	return NULL;


}
int main(){
	srand(time(NULL));
	pthread_t h1;//declarar hilo 1 ESCRITURA
	pthread_create(&h1, NULL, escritura_ar, NULL);//creamos hilos

	pthread_t h2;//declarar hilo 2 LECTURA
	pthread_create(&h2, NULL, lectura_ar, NULL);//creamos hilos*/

	pthread_t h3;//declarar hilo 3 HOLA MUNDO
	struct parametros h3_args;
	h3_args.mensaje = "HIlo 3:Hola Mundo";
	h3_args.cont = 1;
	pthread_create(&h3, NULL, hm, &h3_args);//creamos hilos

	pthread_t h4;//declarar hilo 4 NUmeros random
	struct parametros h4_args;
	h4_args.num = rand()%500;
	h4_args.tam = 7;
	pthread_create(&h4, NULL, random_num, &h4_args);
	
	pthread_join(h1,NULL);//hilo de escritura
	pthread_join(h2,NULL);//hilo de lectura
	pthread_join(h3,NULL);//hilo de lectura
	pthread_join(h4,NULL);//hilo de numeros

return 0;
}


