#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
Entrada: Un pixel RGB.
Salida: Un pixel en escala de grises
Descripcion: Funcion que convierte un pixel RGB a escala de grises
*/
Pixel pixel_a_negro(Pixel pix){
	int ecucion_de_luminiscencia=pix.red*0.3+pix.green*0.59+pix.blue*0.11;
	Pixel pixel_negro;
	pixel_negro.red=ecucion_de_luminiscencia;
	pixel_negro.green=ecucion_de_luminiscencia;
	pixel_negro.blue=ecucion_de_luminiscencia;
	pixel_negro.v=pix.v;
	return pixel_negro;
}

/*
Entrada: Arreglo con pixeles y la cantidad de pixeles
Salida: Arreglo con todos los pixeles convertidos a escala de grises.
Descripcion: Funcion que transforma todos los pixeles de un arreglo a una escala de grises.
*/
Pixel* pixeles_blanco_y_negro(Pixel* punteroPix, int cantidadPixeles){
	int i;
	Pixel* punteroPixelesBlancoYNegro=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
	for(i=0;i<cantidadPixeles;i++){
		punteroPixelesBlancoYNegro[i]=pixel_a_negro(punteroPix[i]);
	}
	return punteroPixelesBlancoYNegro;
}

void main(int argc, char *argv[]){
	printf("conversor_a_gris\n");
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	printf("%i\n",mp->xd);
	mp->xd=3;
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
}