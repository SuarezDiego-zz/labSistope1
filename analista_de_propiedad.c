#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
Proceso encargado de clasificar las imagenes segun si son cercanos a negro o no (nearly black).
Luego de clasificar si la imagen cumple con el requisito de ser nearly black segun el umbral definido, envia la 
informacion por el pipe hacia el siguiente proceso.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixeles= obtenerPixelesPipe(mp);	
	mp->esNearlyBlack=nearlyBlack(pixeles,mp->cantidadDePares/4,mp->umbralNB);
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
}