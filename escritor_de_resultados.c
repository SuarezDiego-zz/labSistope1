#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"


/*
Entrada: Arreglo con la imagen en escala de gris y la imagen binarizada, nombre que tendra el archivo que se escribe.
Salida: Ninguna.
Descripcion: Funcion que permite escribir las nuevas imagenes. Una en escala de grises y la otra binarizada segun el umbral
entregado por el usuario. Por otra parte, esta funcion tambien calcula las dimensiones que debe tener el archivo de salida a
traves de la cabecera de la imagen original.
*/
void escribirImagen(Pixel* punteroPixeles, unsigned char* header, char* nombreArchivo, int cantidadDePares){
	int i;
	unsigned long x;
	int j=138;
	unsigned char* punteroFormatoSalida=(unsigned char*)malloc(sizeof(unsigned char)*(cantidadDePares+138));
	FILE *archivoSalida;
	archivoSalida = fopen(nombreArchivo, "wb");
	
	for(i=0;i<138;i++){
		punteroFormatoSalida[i]=header[i];
	}
	for (i = (cantidadDePares/4)-1 ; i >= 0; i--){
		punteroFormatoSalida[j+3]= punteroPixeles[i].v;
		punteroFormatoSalida[j+2]=punteroPixeles[i].red;
		punteroFormatoSalida[j+1]=punteroPixeles[i].green;
		punteroFormatoSalida[j]=punteroPixeles[i].blue;
		j=j+4;
	}

	x=(punteroFormatoSalida[5]*16777216)+(punteroFormatoSalida[4]*65536)+(punteroFormatoSalida[3]*256)+(punteroFormatoSalida[2]);
	fwrite(punteroFormatoSalida,x,1,archivoSalida);
	fclose(archivoSalida);
}

void liberarEstructura(Estructura* estr){
	int i;
	for(i=0;i<estr->cantidadDePares;i++){
		free(estr->par[i]);
	}
	free(estr->par);
	free(estr);
}

void main(int argc, char *argv[]){
	printf("escritor_de_resultados\n");
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	printf("proc 5\n");
}