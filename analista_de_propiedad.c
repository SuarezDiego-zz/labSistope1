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
Entrada: Arreglo con pixeles, cantidad de pixeles y un umbral.
Salida: Entero. En caso de ser 1, la imagen es cercana a negro, en caso contrario, no lo es.
Descripcion: Funcion que permite determinar si una imagen es cercana a negro.
*/
int nearlyBlack(Pixel* punteroPix, int cantidadPixeles, int umbral){
	int i;
	float porcentajeBlanco;
	long contador_negros=0;
	Pixel* punteroPixelesBinario=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
	for(i=0;i<cantidadPixeles;i++){
		punteroPixelesBinario[i]=pixel_a_negro(punteroPix[i]);
		porcentajeBlanco=(100*punteroPixelesBinario[i].red)/255;
		if(porcentajeBlanco<=umbral){
			contador_negros=contador_negros+1;
		}
	}
	if((contador_negros*100)>((cantidadPixeles-contador_negros)*100)){
		return 1;
	}
	else{
		return 0;
	}
}


/*
Se debe tener acceso a pixeles, el cual sale del proceso lector_de_imagen y Estructura.
argv[1] => umbral_nb
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	printf("%i\n", nearlyBlack(mp->pixeles,mp->estructura->cantidadDePares/4,argv[1]));
	printf("analista_de_propiedad\n");
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
	printf("proc 4\n");
}