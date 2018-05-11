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
Entrada: Arreglo de pixeles en escala de gris, cantidad de pixeles y un umbral
Salida: Arreglo con los pixeles binarizados.
Descripcion: Funcion que transforma todos los pixeles de un arreglo a una imagen binarizada
que contiene solo los colores blanco y negro. Esto depende de si el color esta por sobre el umbral
entonces el pixel sera blanco, en caso contrario, es negro.
*/
Pixel* pixeles_binario(Pixel* punteroPix, int cantidadPixeles, int umbral){
	int i;
	float porcentajeBlanco;
	Pixel* punteroPixelesBinario=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
	for(i=0;i<cantidadPixeles;i++){
		punteroPixelesBinario[i]=pixel_a_negro(punteroPix[i]);
		porcentajeBlanco=(100*punteroPixelesBinario[i].red)/255;
		if(porcentajeBlanco>umbral){
			punteroPixelesBinario[i].red=255;
			punteroPixelesBinario[i].green=255;
			punteroPixelesBinario[i].blue=255;
		}
		else{
			punteroPixelesBinario[i].red=0;
			punteroPixelesBinario[i].green=0;
			punteroPixelesBinario[i].blue=0;
		}

	}
	return punteroPixelesBinario;
}

void main(int argc, char *argv[]){
	printf("binarizador_de_imagen\n");
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	printf("%i\n",mp->xd);
	mp->xd=4;
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
}