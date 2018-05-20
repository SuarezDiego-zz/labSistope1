#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"	

/*
Proceso encargado de leer la imagen y convertirla en arreglos utiles para las etapas posteriores.
La cabecera de la imagen y su cuerpo, entre otros datos de utilidad son enviados a procesos siguientes
a traves del uso de pipes.
*/
void main(int argc, char *argv[]){
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	unsigned char* cabeza_imagen=(unsigned char*)malloc(sizeof(unsigned char)*138);
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Estructura* es=leerImagen(mp->nombreImagen);
	es = cortarEInvertirArreglo(es);

	for(int i=0;i<138;i++){
		mp->cabeza_imagen[i]=stringAHexadecimal(es->par[i]);
	}
	mp->cantidadDePares=es->cantidadDePares;
	int o;
	Pixel* pixeles=crearArregloPixeles(es->arregloBytesOrdenado,es->cantidadDePares/4);
	for(o=0;o<es->cantidadDePares/4;o++){
		free(es->arregloBytesOrdenado[o]);
	}
	free(es->arregloBytesOrdenado);
	write(mp->pipefd[1], mp,sizeof(MensajePipe));
}