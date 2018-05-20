#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	if(mp->esNearlyBlack==1){
		printf("|  %s  |       yes      |\n",mp->nombreImagen);
	}
	else{
		printf("|  %s  |       no       |\n",mp->nombreImagen);
	}
}