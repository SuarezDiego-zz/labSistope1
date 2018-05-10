#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "header_estructuras.h"

/*
void main(int argc, char *argv[]){
	int cantidad, umbral_b, umbral_nb,i;
	int bandera = 0;
	int opt;
	char numeroDeImagen[12];
	char nombreImagenSalidaBinario[25];
	char nombreImagenSalidaEscalaG[25];
  	char contador[2];
	strcpy(numeroDeImagen, "");
	strcpy(nombreImagenSalidaBinario, "");
	strcpy(nombreImagenSalidaEscalaG, "");
	char* imagen = "imagen_";
	char* imagenBinarizadaBase = "binario_";
	char* imagenEscalaGrisesBase = "blancoynegro_";
  	while ((opt = getopt (argc, argv, "c:u:n:b")) != -1)
  	{
    	switch (opt)
    	{
      	case 'c':
        	        cantidad = atoi(optarg);
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
  	if (bandera == 1)
  	{
  		printf("imagen 				nearly black\n");
  	}
  	for (i = 0; i < cantidad; i++)
  	{
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
  		Estructura* es=leerImagen(numeroDeImagen);
		es = cortarArreglo(es);
		es = invertirArreglo(es);
		int o;
		Pixel* pixeles=crearArregloPixeles(es->arregloBytesOrdenado,es->cantidadDePares/4);
		for(o=0;o<es->cantidadDePares/4;o++){
			free(es->arregloBytesOrdenado[o]);
		}
		free(es->arregloBytesOrdenado);
		Pixel* pixelesbn=pixeles_blanco_y_negro(pixeles,es->cantidadDePares/4);
		escribirImagen(pixelesbn,es,nombreImagenSalidaEscalaG);
		free(pixelesbn);
		Pixel* pixelesbinario=pixeles_binario(pixeles,es->cantidadDePares/4,umbral_b);
		escribirImagen(pixelesbinario,es,nombreImagenSalidaBinario);
		free(pixelesbinario);
		if (bandera == 1)
		{
			if (nearlyBlack(pixeles,es->cantidadDePares/4,umbral_nb) ==1)
			{
				printf("%s 				yes\n", numeroDeImagen);
			}
			else
			{
				printf("%s 				no\n", numeroDeImagen);	
			}
			
		}
		strcpy(numeroDeImagen, "");
		strcpy(nombreImagenSalidaBinario, "");
		strcpy(nombreImagenSalidaEscalaG, "");
		liberarEstructura(es);
  	}	
}
*/
void main(int argc, char *argv[]){
	int pid_lector_de_imagen;
	int pid_conversor_a_gris;
	int pid_binarizador_de_imagen;
	int pid_analista_de_propiedad;
	int pid_escritor_de_imagen;
	int* pids_hijos= (int*)malloc(sizeof(int)*5);
	pids_hijos[0]=-1;
	pids_hijos[1]=-1;
	pids_hijos[2]=-1;
	pids_hijos[3]=-1;
	pids_hijos[4]=-1;
	int pid_main=getpid();
	printf("main\n");


	//pipe
	//fd[0] se lee
	//fd[1] se escribe
	
	int fd[2];
	pipe(fd);
	int input_int=20;
	write(fd[1],&input_int,sizeof(int));
	

	//crea los procesos solo si es el proceso main
	if(pid_main==getpid()){
		pid_lector_de_imagen=fork();
	}
	if(pid_main==getpid()){
		pid_conversor_a_gris=fork();
	}
	if(pid_main==getpid()){
		pid_binarizador_de_imagen=fork();
	}
	if(pid_main==getpid()){
		pid_analista_de_propiedad=fork();
	}
	if(pid_main==getpid()){
		pid_escritor_de_imagen=fork();
	}

	//guarda los pids de los hijos segun el proceso
	if(pid_lector_de_imagen==0){
		pids_hijos[0]=getpid();
	}
	if(pid_conversor_a_gris==0){
		pids_hijos[1]=getpid();
	}
	if(pid_binarizador_de_imagen==0){
		pids_hijos[2]=getpid();
	}
	if(pid_analista_de_propiedad==0){
		pids_hijos[3]=getpid();
	}
	if(pid_escritor_de_imagen==0){
		pids_hijos[4]=getpid();
	}
	

	//cambia el contenido y ejecucion de los hijos a la ejecucion correspondiente
	if(pids_hijos[0] == getpid()){
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execv("lector_de_imagen", argv);
	}
	if(pids_hijos[1] == getpid()){
		execv("conversor_a_gris", argv);
	}
	if(pids_hijos[2] == getpid()){
		execv("binarizador_de_imagen", argv);
	}
	if(pids_hijos[3] == getpid()){
		execv("analista_de_propiedad", argv);
	}
	if(pids_hijos[4] == getpid()){
		execv("escritor_de_resultados", argv);
	}
	
}