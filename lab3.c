#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "header_estructuras.h"



void main(int argc, char *argv[]){
	int cantidad, umbral_b, umbral_nb;
  int cantidad_hebras = 0;
  int bandera = 0;
  int opt;
  char numeroDeImagen[100];
  char nombreImagenSalidaBinario[100];
  char nombreImagenSalidaEscalaG[100];
  char contador[2];
  strcpy(numeroDeImagen, "");
  strcpy(nombreImagenSalidaBinario, "");
  strcpy(nombreImagenSalidaEscalaG, "");
  char* imagen = "imagen_";
  char* imagenBinarizadaBase = "binario_";
  char* imagenEscalaGrisesBase = "blancoynegro_";
  
  while ((opt = getopt (argc, argv, "c:h:u:n:b")) != -1){
    switch (opt){
      case 'c':
        cantidad = atoi(optarg);
        break;
      case 'h':
        cantidad_hebras = atoi(optarg);
        break;
      case 'u':
        umbral_b = atoi(optarg);
        break;
      case 'n':
        umbral_nb = atoi(optarg);
        break;
      case 'b':
        bandera = 1;
        break;
      }
  }
  if (bandera == 1){
    printf("imagen        nearly black\n");
  }
  pthread_t hebras[cantidad_hebras];
  for (int i = 0; i < cantidad; i++){
    sprintf(contador, "%d", i+1);
    strcat(numeroDeImagen, imagen);
    strcat(numeroDeImagen, contador);
    strcat(numeroDeImagen, ".bmp");
    strcpy(nombreImagenSalidaBinario, imagenBinarizadaBase);
    strcpy(nombreImagenSalidaEscalaG, imagenEscalaGrisesBase);
    strcat(nombreImagenSalidaEscalaG, contador);
    strcat(nombreImagenSalidaBinario, contador);
    strcat(nombreImagenSalidaEscalaG, ".bmp");
    strcat(nombreImagenSalidaBinario, ".bmp");
    pthread_create(&hebras[0], NULL, (void*) &leerImagen, (void*) numeroDeImagen);
    pthread_join(hebras[0], NULL);
    printf("funciona %s\n", arr->par[0]);
    printf("LLEGA\n");
    //es=cortarEInvertirArreglo(es);
    //Pixel* pixeles=crearArregloPixeles(es->arregloBytesOrdenado,es->cantidadDePares/4);
    //Pixel* pixelesbn=pixeles_blanco_y_negro(pixeles,es->cantidadDePares/4);
    //Pixel* pixelesbinario=pixeles_binario(pixeles,es->cantidadDePares/4,umbral_b);
    //escribirImagen(pixelesbn,es,nombreImagenSalidaEscalaG);
    //escribirImagen(pixelesbinario,es,nombreImagenSalidaBinario);
    /*if (bandera == 1){
      if (nearlyBlack(pixeles,es->cantidadDePares/4,umbral_nb) ==1){
        printf("%s        yes\n", numeroDeImagen);
      }
      else{
        printf("%s        no\n", numeroDeImagen); 
      }
    }*/
    strcpy(numeroDeImagen, "");
    strcpy(nombreImagenSalidaBinario, "");
    strcpy(nombreImagenSalidaEscalaG, "");
  } 
}