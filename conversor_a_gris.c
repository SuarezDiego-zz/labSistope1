#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"


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


/*
Se debe tener acceso a pixeles, el cual sale del proceso anterior y a Estructura.
argv[1] => nombreImagenSalidaEscalaG.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixeles= obtenerPixelesPipe(mp);	
	Pixel* pixelesbn=pixeles_blanco_y_negro(pixeles,mp->cantidadDePares/4);
	//printf("el nombre es: %s\n", mp->nombreImagenBNSalida);
	escribirImagen(pixelesbn,mp->cabeza_imagen,mp->nombreImagenBNSalida, mp->cantidadDePares);
	free(pixelesbn);
	printf("conversor_a_gris\n");
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
	printf("proc 2\n");
	
}