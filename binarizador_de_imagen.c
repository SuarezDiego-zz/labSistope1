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
Se debe tener acceso a pixeles, el cual sale del proceso lector_de_imagen y Estructura.
argv[1] => umbral_b
argv[2] => nombreImagenSalidaBinario
*/
void main(int argc, char *argv[]){
	/*
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixelesbinario=pixeles_binario(mp->pixeles,mp->cantidadDePares/4,argv[1]);
	escribirImagen(pixelesbinario,mp->cabeza_imagen,"picoBinario.bmp", mp->cantidadDePares);
	free(pixelesbinario);
	printf("binarizador_de_imagen\n");
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
	printf("proc 3\n");
	*/
}