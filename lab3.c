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
  cantidad_hebras=20;//20 hebras -------------------------papeo
  pthread_t hebras[cantidad_hebras];
  pthread_barrier_t barrier;
  pthread_barrier_t barrier2;
  int j,topeLanzamiento,auxpxh;
  pthread_barrier_init(&barrier, NULL, 1);
  pthread_barrier_init(&barrier2, NULL, 1);
  //pthread_barrier_init(&barrier2, NULL, 1);
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
    
    cortarEInvertirArreglo(ep->estructura);
    ancho=stringAHexadecimal(ep->estructura->par[18])*4096+stringAHexadecimal(ep->estructura->par[19])*256+stringAHexadecimal(ep->estructura->par[20])*16+stringAHexadecimal(ep->estructura->par[21]);

    printf("%i\n",ancho );
    ep->pixeles = (Pixel*)malloc(sizeof(Pixel));
    ep->pixeles = crearArregloPixeles(ep->estructura);

    epdp->cantidadPixeles=ep->estructura->cantidadDePares/4;
    int cantidadDeFilas=epdp->cantidadPixeles/ancho;
    printf("cantidadDeFilas%i\n",cantidadDeFilas);
    epdp->umbral = 50;
    epdp->umbral_nb = 10;
    epdp->punteroPix=ep->pixeles;
    if((cantidad_hebras)>=cantidadDeFilas){
      pixelesXhebra=ancho;
      topeLanzamiento=cantidadDeFilas;
    }
    else{
        topeLanzamiento=cantidad_hebras;
        auxpxh=(cantidadDeFilas/cantidad_hebras);
        pixelesXhebra=auxpxh*ancho;
    }
    if(cantidadDeFilas%cantidad_hebras>0){
        pixelesXhebraDeLaPrimera=pixelesXhebra+(cantidadDeFilas%cantidad_hebras)*ancho;
    }
    else{
        pixelesXhebraDeLaPrimera=pixelesXhebra;
    }
    for(j=0;j<topeLanzamiento;j++){
      pthread_create(&hebras[j], NULL, (void*) &pixeles_blanco_y_negro, (void*) epdp);
    }
    printf("ANTES DEL BARRIER\n");
    pthread_barrier_wait(&barrier);
    pthread_barrier_destroy(&barrier);
    printf("LUEGO DEL BARRIER\n");
    for(j=0;j<topeLanzamiento;j++){
      pthread_create(&hebras[j], NULL, (void*) &pixeles_binario, (void*) epdp);
    }
    //pthread_barrier_wait(&barrier2);
    pthread_barrier_wait(&barrier2);
    pthread_barrier_destroy(&barrier2);
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
    
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&lockNearlyBlack, NULL);
    pthread_mutex_init(&lockHebrasNB, NULL);

    
  
    printf("cantidadPixeles=%i\n",epdp->cantidadPixeles);
    printf("pixelesXhebra=%i\n",pixelesXhebra);
    printf("pixelesXhebraDeLaPrimera=%i\n",pixelesXhebraDeLaPrimera);
    printf("cantidad de hebras en nearlyBlack=%i\n",(topeLanzamiento) );
    for(j=0;j<topeLanzamiento;j++){
      pthread_create(&hebras[j], NULL, (void*) &nearlyBlack, (void*) epdp);
    }
    for(j=0;j<cantidad_hebras;j++){
      pthread_join(hebras[j], NULL);
    }
    printf("resultado nearly black=%i\n",resultadoNearlyBlack);
    printf("rnegros=%i\n",cantidadPixelesNegros);
    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&lockNearlyBlack);
    pthread_mutex_destroy(&lockHebrasNB);

    //fin nearly black


    strcpy(numeroDeImagen, "");
    strcpy(nombreImagenSalidaBinario, "");
    strcpy(nombreImagenSalidaEscalaG, "");
  } 
}