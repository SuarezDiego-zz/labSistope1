#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"	



/*
argv[1] => nombre de la imagen.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	unsigned char* cabeza_imagen=(unsigned char*)malloc(sizeof(unsigned char)*138);
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Estructura* es=leerImagen("imagen_2.bmp");
	es = cortarArreglo(es);
	es = invertirArreglo(es);
	for(int i=0;i<138;i++){
		mp->cabeza_imagen[i]=stringAHexadecimal(es->par[i]);
		//printf("iteracion:%i dentro:%i\n", i,cabeza_imagen[i]);
	}
	//mp->cabeza_imagen = *cabeza_imagen;
	mp->cantidadDePares=es->cantidadDePares;
	int o;
	Pixel* pixeles=crearArregloPixeles(es->arregloBytesOrdenado,es->cantidadDePares/4);
	//mp->pixeles=(Pixel)malloc((mp->cantidadDePares/4)*sizeof(Pixel));
	
	for(o=0;o<es->cantidadDePares/4;o++){
		free(es->arregloBytesOrdenado[o]);
	}
	free(es->arregloBytesOrdenado);
	for (int j = 0; j < 10; j++){
		//printf("%i\n", pixeles[j].red);
		printf("%i\n", mp->cabeza_imagen[j]);
	}
	printf("%d\n",mp->cantidadDePares/4 );
	write(mp->pipefd[1], mp,sizeof(MensajePipe));
	printf("lector_de_imagen\n");
}