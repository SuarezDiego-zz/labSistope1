#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
Proceso encargado de escribir en la consola si la imagen que se procesa actualmente es nearly black
segun el dato que es enviado por el pipe del proceso anterior y si debe hacerlo dependiento de la bandera.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	if(mp->bandera==1){
		if(mp->esNearlyBlack==1){
			printf("|  %s  |       yes      |\n",mp->nombreImagen);
		}
		else{
			printf("|  %s  |       no       |\n",mp->nombreImagen);
		}
	}
}