#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int red;
	int green;
	int blue;
} Pixel;

typedef struct{
   char** par;
   char** arregloBytes;
   char** arregloBytesOrdenado;
   int cantidadDePares;
}Estructura;

Estructura* leerImagen(){
	int x,k;
	int i=0;
	int j=0;
	char funcion[30];
	Estructura* arr = (Estructura*)malloc(sizeof(Estructura));
	FILE *archivoEntrada;
	char* nombreArchivo="x.bmp";
	archivoEntrada = fopen(nombreArchivo, "rb");
	int auxInt;	
	char **par = (char **) malloc(sizeof(char *)*1000);
	for(x=0;x<1000;x++){
        par[x]=(char *) malloc(sizeof(char)*1000);
	}
    arr->par = par;	
	char* textoStr=(char*)malloc(10000*sizeof(char));
	char* auxStr=(char*)malloc(10*sizeof(char));
	memset(textoStr,0,strlen(textoStr));
	while (!feof(archivoEntrada)) {
    	auxInt = fgetc(archivoEntrada);
    	sprintf(auxStr,"%02x",auxInt);
    	strcat(textoStr,auxStr);
    	strcpy(par[j], auxStr);
    	//printf("%s\n", par[j]);
    	j++;
	//printf("%s \n", auxStr);
	}
	par[j-1]='\0';
	for (k = 0; k < j; ++k)
	{
		//printf("%s asd\n", par[k]);
	}
	arr->cantidadDePares = j-1;
	//int largo =strlen(textoStr);
	//textoStr[largo-10]='\0';// le quita los f demas
	//printf("%s\n", textoStr);
	//printf("llega.\n");
	return arr;
}

Estructura* cortarArreglo(Estructura* estr){
	int a=0;
	int i,k,x;
	char **arregloBytes = (char **) malloc(sizeof(char *)*1000);
	for(x=0;x<1000;x++){
        arregloBytes[x]=(char *) malloc(sizeof(char)*1000);
	}
	for (i = 53; i < estr->cantidadDePares; ++i)//veeeeeeeeeeeeeeeer
	{
		strcpy(arregloBytes[a], estr->par[i]);
		printf("%s\n",arregloBytes[a]);
		a++;
		
	}
	estr->cantidadDePares = estr->cantidadDePares - 56;
	for (k = 0; k < estr->cantidadDePares; ++k)
	{
		//printf("%s\n", arregloBytes[k]);
	}
	estr->arregloBytes = arregloBytes;
	return estr;
}

Estructura* invertirArreglo(Estructura* estr){
	int j=0;
	int i;
	printf("%i\n",estr->cantidadDePares);
	char **arregloBytesOrdenado = (char **) malloc(sizeof(char *)*estr->cantidadDePares);
	for (i = estr->cantidadDePares-1 ; i >= 0; i--)
	{
		arregloBytesOrdenado[j]=(char *) malloc(sizeof(char)*3);
		strcpy(arregloBytesOrdenado[j], estr->arregloBytes[i]);
		//printf("%s\n",arregloBytesOrdenado[j]);
		j++;
	}
	estr->arregloBytesOrdenado=arregloBytesOrdenado;
	return estr;
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
		printf("%s %s %s\n",punteroStr[i*3],punteroStr[i*3+1],punteroStr[i*3+2]);
	}
	return punteroPixel;
}

Pixel pixel_a_negro(Pixel pix){
	int ecucion_de_luminiscencia=pix.red*0.3+pix.green*0.59+pix.blue*0.11;
	Pixel pixel_negro;
	pixel_negro.red=ecucion_de_luminiscencia;
	pixel_negro.green=ecucion_de_luminiscencia;
	pixel_negro.blue=ecucion_de_luminiscencia;
	printf("%i\n",ecucion_de_luminiscencia);
	return pixel_negro;
}

void main(){
	char** tes=(char**)malloc(6*sizeof(char*));
	tes[0]="10";
	tes[1]="22";
	tes[2]="ff";
	tes[3]="12";
	tes[4]="24";
	tes[5]="fa";
	//Pixel* puntero=crearArregloPixeles(tes,2);
	//pixel_a_negro(puntero[0]);

	Estructura* es=leerImagen();
	cortarArreglo(es);
	invertirArreglo(es);
	//printf("%s\n",es->par[0]);
	//printf("%s\n",es->arregloBytes[0]);
	//printf("%s\n",es->arregloBytesOrdenado[0]);
	//printf("%i\n",es->cantidadDePares/3);
	Pixel* pixeles=crearArregloPixeles(es->arregloBytesOrdenado,es->cantidadDePares/3);
}