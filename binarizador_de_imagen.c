#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
Proceso encargado de transformar una imagen a blanco y negro a partir
del umbral definido por el usuario. Hace uso de la estructura MensajePipe para 
obtener los datos de la imagen y hacer la conversion segun lo indicado al momento de la ejecucion del archivo main.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixeles= obtenerPixelesPipe(mp);
	Pixel* pixelesbinario=pixeles_binario(pixeles,mp->cantidadDePares/4,mp->umbralBinarizacion);
	escribirImagen(pixelesbinario,mp->cabeza_imagen,mp->nombreImagenBinSalida, mp->cantidadDePares);
	free(pixelesbinario);
	write(mp->pipefd[1],mp,sizeof(MensajePipe));	
}