#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int red;
	int green;
	int blue;
} Pixel;

char* leerImagen(){
	FILE *archivoEntrada;
	char* nombreArchivo="1.bmp";
	archivoEntrada = fopen(nombreArchivo, "rb");
	int auxInt;
	char* textoStr=(char*)malloc(10000*sizeof(char));
	char* auxStr=(char*)malloc(10*sizeof(char));
	memset(textoStr,0,strlen(textoStr));
	while (!feof(archivoEntrada)) {
    	auxInt = fgetc(archivoEntrada);
    	sprintf(auxStr,"%02x",auxInt);
    	strcat(textoStr,auxStr);
	}
	int largo =strlen(textoStr);
	textoStr[largo-8]='\0';// le quita los f demas
	return textoStr;
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

Pixel* crearArregloPixeles(char** punteroStr,int cantidadPixeles){
	int i;
	int aux;
	Pixel* punteroPixel=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
	for(i=0;i<cantidadPixeles;i++){
		punteroPixel[i].red=stringAHexadecimal(punteroStr[i*3]);
		punteroPixel[i].green=stringAHexadecimal(punteroStr[i*3+1]);
		punteroPixel[i].blue=stringAHexadecimal(punteroStr[i*3+2]);
		printf("rojo=%i verde=%i azul=%i\n",punteroPixel[i].red,punteroPixel[i].green,punteroPixel[i].blue);
	}
	return punteroPixel;
}
void main(){
	char** tes=(char**)malloc(6*sizeof(char*));
	tes[0]="10";
	tes[1]="22";
	tes[2]="ff";
	tes[3]="12";
	tes[4]="24";
	tes[5]="fa";
	crearArregloPixeles(tes,2);
}