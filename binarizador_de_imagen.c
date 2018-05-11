#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
Entrada: Un pixel RGB.
Salida: Un pixel en escala de grises
Descripcion: Funcion que convierte un pixel RGB a escala de grises
*/
Pixel pixel_a_negro(Pixel pix){
	int ecucion_de_luminiscencia=pix.red*0.3+pix.green*0.59+pix.blue*0.11;
	Pixel pixel_negro;
	pixel_negro.red=ecucion_de_luminiscencia;
	pixel_negro.green=ecucion_de_luminiscencia;
	pixel_negro.blue=ecucion_de_luminiscencia;
	pixel_negro.v=pix.v;
	return pixel_negro;
}

/*
Entrada: Arreglo de pixeles en escala de gris, cantidad de pixeles y un umbral
Salida: Arreglo con los pixeles binarizados.
Descripcion: Funcion que transforma todos los pixeles de un arreglo a una imagen binarizada
que contiene solo los colores blanco y negro. Esto depende de si el color esta por sobre el umbral
entonces el pixel sera blanco, en caso contrario, es negro.
*/
Pixel* pixeles_binario(Pixel* punteroPix, int cantidadPixeles, int umbral){
	int i;
	float porcentajeBlanco;
	Pixel* punteroPixelesBinario=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
	for(i=0;i<cantidadPixeles;i++){
		punteroPixelesBinario[i]=pixel_a_negro(punteroPix[i]);
		porcentajeBlanco=(100*punteroPixelesBinario[i].red)/255;
		if(porcentajeBlanco>umbral){
			punteroPixelesBinario[i].red=255;
			punteroPixelesBinario[i].green=255;
			punteroPixelesBinario[i].blue=255;
		}
		else{
			punteroPixelesBinario[i].red=0;
			punteroPixelesBinario[i].green=0;
			punteroPixelesBinario[i].blue=0;
		}

	}
	return punteroPixelesBinario;
}

int stringAHexadecimal(char* stringEntrada){
	int numeroHexa=0;
	int i;
	for(i=0;i<2;i++){
		if(stringEntrada[i]==48){
		}
		else if(stringEntrada[i]==49){
			if(i==0){
				numeroHexa=numeroHexa+16;
			}
			else{
				numeroHexa=numeroHexa+1;
			}
		}
		else if(stringEntrada[i]==50){
			if(i==0){
				numeroHexa=numeroHexa+32;
			}
			else{
				numeroHexa=numeroHexa+2;
			}
		}
		else if(stringEntrada[i]==51){
			if(i==0){
				numeroHexa=numeroHexa+48;
			}
			else{
				numeroHexa=numeroHexa+3;
			}
		}
		else if(stringEntrada[i]==52){
			if(i==0){
				numeroHexa=numeroHexa+64;
			}
			else{
				numeroHexa=numeroHexa+4;
			}
		}
		else if(stringEntrada[i]==53){
			if(i==0){
				numeroHexa=numeroHexa+80;
			}
			else{
				numeroHexa=numeroHexa+5;
			}
		}
		else if(stringEntrada[i]==54){
			if(i==0){
				numeroHexa=numeroHexa+96;
			}
			else{
				numeroHexa=numeroHexa+6;
			}
		}
		else if(stringEntrada[i]==55){
			if(i==0){
				numeroHexa=numeroHexa+112;
			}
			else{
				numeroHexa=numeroHexa+7;
			}
		}
		else if(stringEntrada[i]==56){
			if(i==0){
				numeroHexa=numeroHexa+128;
			}
			else{
				numeroHexa=numeroHexa+8;
			}
		}
		else if(stringEntrada[i]==57){
			if(i==0){
				numeroHexa=numeroHexa+144;
			}
			else{
				numeroHexa=numeroHexa+9;
			}
		}
		else if(stringEntrada[i]==97){
			if(i==0){
				numeroHexa=numeroHexa+160;
			}
			else{
				numeroHexa=numeroHexa+10;
			}
		}
		else if(stringEntrada[i]==98){
			if(i==0){
				numeroHexa=numeroHexa+176;
			}
			else{
				numeroHexa=numeroHexa+11;
			}
		}
		else if(stringEntrada[i]==99){
			if(i==0){
				numeroHexa=numeroHexa+192;
			}
			else{
				numeroHexa=numeroHexa+12;
			}
		}
		else if(stringEntrada[i]==100){
			if(i==0){
				numeroHexa=numeroHexa+208;
			}
			else{
				numeroHexa=numeroHexa+13;
			}
		}
		else if(stringEntrada[i]==101){
			if(i==0){
				numeroHexa=numeroHexa+224;
			}
			else{
				numeroHexa=numeroHexa+14;
			}
		}
		else if(stringEntrada[i]==102){
			if(i==0){
				numeroHexa=numeroHexa+240;
			}
			else{
				numeroHexa=numeroHexa+15;
			}
		}
	}
	return numeroHexa;
}

void escribirImagen(Pixel* punteroPixeles, Estructura* est,char* nombreArchivo){
	int i;
	unsigned long x;
	int j=138;
	unsigned char* punteroFormatoSalida=(unsigned char*)malloc(sizeof(unsigned char)*(est->cantidadDePares+138));
	FILE *archivoSalida;
	archivoSalida = fopen(nombreArchivo, "wb");
	
	for(i=0;i<138;i++){
		punteroFormatoSalida[i]=stringAHexadecimal(est->par[i]);
	}
	for (i = (est->cantidadDePares/4)-1 ; i >= 0; i--){
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
	MensajePipe* mp=(MensajePipe*)malloc(sizeof(MensajePipe));
	read(STDIN_FILENO, mp, sizeof(MensajePipe));
	Pixel* pixelesbinario=pixeles_binario(mp->pixeles,mp->estructura->cantidadDePares/4,argv[1]);
	escribirImagen(pixelesbinario,mp->estructura,argv[2]);
	free(pixelesbinario);
	printf("binarizador_de_imagen\n");
	printf("%i\n",mp->xd);
	mp->xd=4;
	write(mp->pipefd[1],mp,sizeof(MensajePipe));
}