#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"	

/*
Entrada: Nombre de un archivo con formato bmp.
Salida: Cantidad de bytes que contiene dicho archivo.
Descripcion: Funcion que devuelve la cantidad total de bytes contenidos en una imagen con formato bmp.
*/
long calcularTamano(char* nombreArchivo){
 	long largo;
 	int x;
 	FILE *archivoEntrada;
 	archivoEntrada = fopen(nombreArchivo, "rb");
 	unsigned char *bytesTamano = (unsigned char*) malloc(sizeof(unsigned char)*5);
 	for(x=0;x<6;x++){
 		if(!feof(archivoEntrada)){
 			bytesTamano[x]=fgetc(archivoEntrada);
 			}
 		else{
 			return 0;
 			}
 		}
 	largo=(bytesTamano[5]*16777216)+(bytesTamano[4]*65536)+(bytesTamano[3]*256)+(bytesTamano[2]);
 	fclose(archivoEntrada);

 	free(bytesTamano);
 	return largo;
 }

/*
Entrada: Nombre de la imagen que se quiere leer en formato en bmp.
Salida: un arreglo con todos los bytes de la imagen.
Descripcion: Funcion encargada de leer los bytes de la imagen y guardalos en un arreglo. En caso de que no exista la imagen, se muestra
una imagen por pantalla.
*/
Estructura* leerImagen(char* nombreArchivo){
	int x;
	int j=0;
	long largo = calcularTamano(nombreArchivo);
	Estructura* arr = (Estructura*)malloc(sizeof(Estructura));
	FILE *archivoEntrada;
	archivoEntrada = fopen(nombreArchivo, "rb");
	if (archivoEntrada == NULL)
	{
		printf("No se ha encontrado imagen. \n");
		exit(1);
	}
	unsigned char auxInt;	
	char **par = (char **) malloc(sizeof(char *)*largo*4);
	for(x=0;x<largo*4;x++){
        par[x]=(char *) malloc(sizeof(char)*2);
	}
    arr->par = par;	
	char* auxStr=(char*)malloc(2*sizeof(char));
	while (!feof(archivoEntrada)) {
    	auxInt = fgetc(archivoEntrada);
    	sprintf(auxStr,"%02x",auxInt);	
    	strcpy(par[j], auxStr);
    	par[j][2]= '\0';
    	j++;
	}	
	par[j-1]='\0';
	arr->cantidadDePares = j-1;
	fclose(archivoEntrada);
	arr->largo = largo;

	free(auxStr);
	return arr;
}

/*
Entrada: Estructura que guarda todos los arreglos necesarios para el procesamiento.
Salida: Misma estructura que entra pero con un arreglo adicional que que elimina su cabecera.
Descripcion: Funcion que le quita la cabecera a un arreglo de imagen bmp.
*/
Estructura* cortarArreglo(Estructura* estr){
	int a=0;
	int i,x;
	char **arregloBytes = (char **) malloc(sizeof(char *)*estr->largo);
	for(x=0;x<estr->largo;x++){
        arregloBytes[x]=(char *) malloc(sizeof(char)*2);
	}
	for (i = 138; i < estr->cantidadDePares; ++i)
	{
		strcpy(arregloBytes[a], estr->par[i]);
		a++;
	}
	estr->cantidadDePares = estr->cantidadDePares - 138;
	estr->arregloBytes = arregloBytes;
	return estr;
}

/*
Entrada: Estructura que guarda todos los arreglos necesarios para el procesamiento.
Salida: Misma estructura que entra pero con un arreglo adicional que contiene los pixeles invertidos.
Descripcion: Funcion que recorre e invierte el orden de los pixeles en un nuevo arreglo.
*/
Estructura* invertirArreglo(Estructura* estr){
	int j=0;
	int i;
	char **arregloBytesOrdenado = (char **) malloc(sizeof(char *)*estr->cantidadDePares);
	for (i = estr->cantidadDePares-1 ; i >= 0; i--)
	{
		arregloBytesOrdenado[j]=(char *) malloc(sizeof(char)*2);
		strcpy(arregloBytesOrdenado[j], estr->arregloBytes[i]);
		j++;
	}
	estr->arregloBytesOrdenado=arregloBytesOrdenado;


	for (i = 0; i <estr->cantidadDePares-138; ++i)
	{
		free(estr->arregloBytes[i]);
	}
	free(estr->arregloBytes);
	return estr;
}

/*
Entrada: Numero hexadecimal en formato de string.
Salida: Numero convertido a entero.
Descripcion: Convierte de hexadecimal a entero.
*/
int stringAHexadecimal(char* stringEntrada){
	int numeroHexa=0;
	int i;
	for(i=0;i<2;i++){
		if(stringEntrada[i]==48){
		}
		else if(stringEntrada[i]==49){
			if(i==0){
				numeroHexa=numeroHexa+16;
			}
			else{
				numeroHexa=numeroHexa+1;
			}
		}
		else if(stringEntrada[i]==50){
			if(i==0){
				numeroHexa=numeroHexa+32;
			}
			else{
				numeroHexa=numeroHexa+2;
			}
		}
		else if(stringEntrada[i]==51){
			if(i==0){
				numeroHexa=numeroHexa+48;
			}
			else{
				numeroHexa=numeroHexa+3;
			}
		}
		else if(stringEntrada[i]==52){
			if(i==0){
				numeroHexa=numeroHexa+64;
			}
			else{
				numeroHexa=numeroHexa+4;
			}
		}
		else if(stringEntrada[i]==53){
			if(i==0){
				numeroHexa=numeroHexa+80;
			}
			else{
				numeroHexa=numeroHexa+5;
			}
		}
		else if(stringEntrada[i]==54){
			if(i==0){
				numeroHexa=numeroHexa+96;
			}
			else{
				numeroHexa=numeroHexa+6;
			}
		}
		else if(stringEntrada[i]==55){
			if(i==0){
				numeroHexa=numeroHexa+112;
			}
			else{
				numeroHexa=numeroHexa+7;
			}
		}
		else if(stringEntrada[i]==56){
			if(i==0){
				numeroHexa=numeroHexa+128;
			}
			else{
				numeroHexa=numeroHexa+8;
			}
		}
		else if(stringEntrada[i]==57){
			if(i==0){
				numeroHexa=numeroHexa+144;
			}
			else{
				numeroHexa=numeroHexa+9;
			}
		}
		else if(stringEntrada[i]==97){
			if(i==0){
				numeroHexa=numeroHexa+160;
			}
			else{
				numeroHexa=numeroHexa+10;
			}
		}
		else if(stringEntrada[i]==98){
			if(i==0){
				numeroHexa=numeroHexa+176;
			}
			else{
				numeroHexa=numeroHexa+11;
			}
		}
		else if(stringEntrada[i]==99){
			if(i==0){
				numeroHexa=numeroHexa+192;
			}
			else{
				numeroHexa=numeroHexa+12;
			}
		}
		else if(stringEntrada[i]==100){
			if(i==0){
				numeroHexa=numeroHexa+208;
			}
			else{
				numeroHexa=numeroHexa+13;
			}
		}
		else if(stringEntrada[i]==101){
			if(i==0){
				numeroHexa=numeroHexa+224;
			}
			else{
				numeroHexa=numeroHexa+14;
			}
		}
		else if(stringEntrada[i]==102){
			if(i==0){
				numeroHexa=numeroHexa+240;
			}
			else{
				numeroHexa=numeroHexa+15;
			}
		}
	}
	return numeroHexa;
}

/*
Entrada: Arreglo con todos los pixeles de la imagen en hexadecimal y un entero que indica cuantos pixeles hay.
Salida: Arreglo con todos los pixeles convertidos a entero.
Descripcion: Funcion que de todos los datos de la imagen crea un arreglo de pixeles.
*/
Pixel* crearArregloPixeles(char** punteroStr,int cantidadPixeles){
	int i;
	Pixel* punteroPixel=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
	for(i=0;i<cantidadPixeles;i++){
		punteroPixel[i].red=stringAHexadecimal(punteroStr[i*4+1]);
		punteroPixel[i].green=stringAHexadecimal(punteroStr[i*4+2]);
		punteroPixel[i].blue=stringAHexadecimal(punteroStr[i*4+3]);
		punteroPixel[i].v=stringAHexadecimal(punteroStr[i*4]);
	}
	return punteroPixel;
}

/*
argv[1] => nombre de la imagen.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	unsigned char* cabeza_imagen=(unsigned char*)malloc(sizeof(unsigned char)*138);
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Estructura* es=leerImagen("imagen_1.bmp");
	es = cortarArreglo(es);
	es = invertirArreglo(es);
	for(int i=0;i<138;i++){
		mp->cabeza_imagen[i]=stringAHexadecimal(es->par[i]);
		//printf("iteracion:%i dentro:%i\n", i,cabeza_imagen[i]);
	}
	//mp->cabeza_imagen = *cabeza_imagen;
	mp->cantidadDePares=es->cantidadDePares;
	int o;
	Pixel* pixeles=crearArregloPixeles(es->arregloBytesOrdenado,es->cantidadDePares/4);
	//mp->pixeles=(Pixel)malloc((mp->cantidadDePares/4)*sizeof(Pixel));
	
	for(o=0;o<es->cantidadDePares/4;o++){
		free(es->arregloBytesOrdenado[o]);
	}
	free(es->arregloBytesOrdenado);
	for (int j = 0; j < 10; j++){
		//printf("%i\n", pixeles[j].red);
		printf("%i\n", mp->cabeza_imagen[j]);
	}
	for(int i=0;i<mp->cantidadDePares/4;i++){
		//mp->pixeles[i]=pixeles[i];
	}
	write(mp->pipefd[1], mp,sizeof(MensajePipe));
	printf("lector_de_imagen\n");
}