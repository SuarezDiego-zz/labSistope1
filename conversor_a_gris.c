#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
Proceso encargado de transformar una imagen a escala de grises y generar la imagen en base a la formula
entregada. Hace uso de la estructura MensajePipe para obtener los datos de la imagen y hacer la conversion.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixeles= obtenerPixelesPipe(mp);	
	Pixel* pixelesbn=pixeles_blanco_y_negro(pixeles,mp->cantidadDePares/4);
	escribirImagen(pixelesbn,mp->cabeza_imagen,mp->nombreImagenBNSalida, mp->cantidadDePares);
	free(pixelesbn);
	write(mp->pipefd[1],mp,sizeof(MensajePipe));	
}