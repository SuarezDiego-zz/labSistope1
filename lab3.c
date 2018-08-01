#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "header_estructuras.h"

void main(int argc, char *argv[]){
	int cantidad, umbral_b, umbral_nb;
  int bandera = 0;
  int opt;
  char numeroDeImagen[50];
  char nombreImagenSalidaBinario[50];
  char nombreImagenSalidaEscalaG[50];
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
  cantidad_hebras=2;//2 hebras -------------------------papeo
  pthread_t hebras[cantidad_hebras];
  ep =(EstructuraPrincipal*)malloc(sizeof(EstructuraPrincipal));
  epdp =(EstructuraProcesadorDePixeles*)malloc(sizeof(EstructuraProcesadorDePixeles));
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
    printf("funciona %s\n", ep->estructura->par[0]);
    printf("cantidad_de_pares: %i \n", ep->estructura->cantidadDePares);
    printf("largo: %i \n", ep->estructura->largo);
    printf("LLEGA\n");
    cortarEInvertirArreglo(ep->estructura);
    epdp->cantidadPixeles=ep->estructura->cantidadDePares/4;
    epdp->umbral=50;
    ep->pixeles = crearArregloPixeles(ep->estructura);
    pixeles_blanco_y_negro(epdp);
    pixeles_binario(epdp);
    printf("PASA POR AQUI\n");
    escribirImagen(ep->pixelesbinario,ep->estructura,nombreImagenSalidaEscalaG);
    escribirImagen(ep->pixelesbn,ep->estructura,nombreImagenSalidaBinario);
    /*if (bandera == 1){
      if (nearlyBlack(pixeles,es->cantidadDePares/4,umbral_nb) ==1){
        printf("%s        yes\n", numeroDeImagen);
      }
      else{
        printf("%s        no\n", numeroDeImagen); 
      }
    }*/




    //inicio nearly black
    
    /*int j;
    pthread_mutex_init(&lock, NULL);
    cortarEInvertirArreglo(ep->estructura);
    Pixel* pixeles=crearArregloPixeles(ep->estructura);
    epdp->punteroPix=pixeles;
    pixelesXhebra= epdp->cantidadPixeles/(cantidad_hebras+1);
    printf("cantidadPixeles%i\n",epdp->cantidadPixeles);
    printf("pixelesXhebra%i\n",pixelesXhebra);
    printf("cantidad de hebras%i\n",(cantidad_hebras+1) );
    for(j=1;j<=cantidad_hebras;j++){
      pthread_create(&hebras[j], NULL, (void*) &nearlyBlack, (void*) epdp);
    }
    for(j=0;j<=cantidad_hebras;j++){
      pthread_join(hebras[j], NULL);
    }
    printf("resultado nearly black=%i\n",resultadoNearlyBlack);
    pthread_mutex_destroy(&lock);
    */
    //fin nearly black


    strcpy(numeroDeImagen, "");
    strcpy(nombreImagenSalidaBinario, "");
    strcpy(nombreImagenSalidaEscalaG, "");
  } 
}