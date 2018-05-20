#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixeles= obtenerPixelesPipe(mp);
	Pixel* pixelesbinario=pixeles_binario(pixeles,mp->cantidadDePares/4,mp->umbralBinarizacion);
	escribirImagen(pixelesbinario,mp->cabeza_imagen,mp->nombreImagenBinSalida, mp->cantidadDePares);
	free(pixelesbinario);
	write(mp->pipefd[1],mp,sizeof(MensajePipe));	
}