/*
Definicion de estructuras.
*/
typedef struct {
	int red;
	int green;
	int blue;
	int v;
} Pixel;

typedef struct{
   char** par;
   char** arregloBytesOrdenado;
   int cantidadDePares;
   long largo;
}Estructura;

typedef struct{
   Pixel* punteroPix;
   int cantidadPixeles;
   int umbral;
}ProesadorDePixeles;

/*
Cabeceras de funciones
*/
long calcularTamano(char* nombreArchivo);
void leerImagen(void* nombreArchivo);
Estructura* cortarEInvertirArreglo(Estructura* estr);
int stringAHexadecimal(char* stringEntrada);
Pixel* crearArregloPixeles(char** punteroStr,int cantidadPixeles);
Pixel pixel_a_negro(Pixel pix);
Pixel* pixeles_blanco_y_negro(Pixel* punteroPix, int cantidadPixeles);
Pixel* pixeles_binario(Pixel* punteroPix, int cantidadPixeles, int umbral);
int nearlyBlack(Pixel* punteroPix, int cantidadPixeles, int umbral);
void escribirImagen(Pixel* punteroPixeles, Estructura* est, char* nombreArchivo);
void main(int argc, char *argv[]);

//DEFINICION DE FUNCIONES

/*
Entrada: Nombre de un archivo con formato bmp.
Salida: Cantidad de bytes que contiene dicho archivo.
Descripcion: Funcion que devuelve la cantidad total de bytes contenidos en una imagen con formato bmp.
*/
long calcularTamano(char* nombreArchivo){
   long largo;
   int x;
   FILE *archivoEntrada;
   printf("%s\n", nombreArchivo);
   archivoEntrada = fopen(nombreArchivo, "rb");
   unsigned char *bytesTamano = (unsigned char*) malloc(sizeof(unsigned char)*5);
   for(x=0;x<6;x++){
      if(!feof(archivoEntrada)){
         bytesTamano[x]=fgetc(archivoEntrada);
         }
      else{
         return 0;
         }
      }
   largo=(bytesTamano[5]*16777216)+(bytesTamano[4]*65536)+(bytesTamano[3]*256)+(bytesTamano[2]);
   fclose(archivoEntrada);

   free(bytesTamano);
   return largo;
 }

/*
Entrada: Nombre de la imagen que se quiere leer en formato en bmp.
Salida: un arreglo con todos los bytes de la imagen.
Descripcion: Funcion encargada de leer los bytes de la imagen y guardalos en un arreglo. En caso de que no exista la imagen, se muestra
una imagen por pantalla.
*/
void leerImagen(void* nombreArchivo){
   char* _nombreArchivo = (char*) nombreArchivo;
   int x;
   printf("ENTRAMOS\n");
   int j=0;
   long largo = calcularTamano(nombreArchivo);
   Estructura* arr = (Estructura*)malloc(sizeof(Estructura));
   FILE *archivoEntrada;
   archivoEntrada = fopen(nombreArchivo, "rb");
   if (archivoEntrada == NULL)
   {
      printf("No se ha encontrado imagen. \n");
      exit(1);
   }
   unsigned char auxInt;   
   char **par = (char **) malloc(sizeof(char *)*largo*4);
   for(x=0;x<largo*4;x++){
        par[x]=(char *) malloc(sizeof(char)*2);
   }
    arr->par = par;
   while (!feof(archivoEntrada)) {
      sprintf(par[j],"%02x",fgetc(archivoEntrada));
      par[j][2]= '\0';
      j++;
   }  
   par[j-1]='\0';
   arr->cantidadDePares = j-1;
   fclose(archivoEntrada);
   arr->largo = largo;
   return arr;
}

/*
Entrada: Estructura que guarda todos los arreglos necesarios para el procesamiento.
Salida: Misma estructura que entra pero con un arreglo adicional que contiene los pixeles invertidos de la imagen sin
la cabecera.
Descripcion: Funcion que recorre para cortar e invertir el orden de los pixeles en un nuevo arreglo.
*/
Estructura* cortarEInvertirArreglo(Estructura* estr){
   int j=0;
   int i;
   char **arregloBytesOrdenado = (char **) malloc(sizeof(char *)*estr->cantidadDePares);
   for (i = estr->cantidadDePares-1 ; i >= 138; i--)
   {
      arregloBytesOrdenado[j]=(char *) malloc(sizeof(char)*2);
      strcpy(arregloBytesOrdenado[j], estr->par[i]);
      j++;
      //free(estr->arregloBytes[i]);
   }
   estr->cantidadDePares = estr->cantidadDePares - 138;
   estr->arregloBytesOrdenado=arregloBytesOrdenado;
   //free(estr->arregloBytes);
   return estr;
}

/*
Entrada: Numero hexadecimal en formato de string.
Salida: Numero convertido a entero.
Descripcion: Convierte de hexadecimal a entero.
*/
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

/*
Entrada: Arreglo con todos los pixeles de la imagen en hexadecimal y un entero que indica cuantos pixeles hay.
Salida: Arreglo con todos los pixeles convertidos a entero.
Descripcion: Funcion que de todos los datos de la imagen crea un arreglo de pixeles.
*/
Pixel* crearArregloPixeles(char** punteroStr,int cantidadPixeles){
   int i;
   Pixel* punteroPixel=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
   for(i=0;i<cantidadPixeles;i++){
      punteroPixel[i].red=stringAHexadecimal(punteroStr[i*4+1]);
      punteroPixel[i].green=stringAHexadecimal(punteroStr[i*4+2]);
      punteroPixel[i].blue=stringAHexadecimal(punteroStr[i*4+3]);
      punteroPixel[i].v=stringAHexadecimal(punteroStr[i*4]);
   }
   return punteroPixel;
}

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
Entrada: Arreglo con pixeles y la cantidad de pixeles
Salida: Arreglo con todos los pixeles convertidos a escala de grises.
Descripcion: Funcion que transforma todos los pixeles de un arreglo a una escala de grises.
*/
Pixel* pixeles_blanco_y_negro(Pixel* punteroPix, int cantidadPixeles){
   int i;
   Pixel* punteroPixelesBlancoYNegro=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
   for(i=0;i<cantidadPixeles;i++){
      punteroPixelesBlancoYNegro[i]=pixel_a_negro(punteroPix[i]);
   }
   return punteroPixelesBlancoYNegro;
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

/*
Entrada: Arreglo con pixeles, cantidad de pixeles y un umbral.
Salida: Entero. En caso de ser 1, la imagen es cercana a negro, en caso contrario, no lo es.
Descripcion: Funcion que permite determinar si una imagen es cercana a negro.
*/
int nearlyBlack(Pixel* punteroPix, int cantidadPixeles, int umbral){
  long i;
  float porcentajeBlanco;
  unsigned long contador_negros=0;
  Pixel* punteroPixelesBinario=(Pixel*)malloc(cantidadPixeles*sizeof(Pixel));
  for(i=0;i<cantidadPixeles;i++){
    punteroPixelesBinario[i]=pixel_a_negro(punteroPix[i]);
    porcentajeBlanco=(100*punteroPixelesBinario[i].red)/255;
    if(porcentajeBlanco<=umbral){
      contador_negros=contador_negros+1;
    }
  }
  if((contador_negros*100)>((cantidadPixeles-contador_negros)*100)){
    return 1;
  }
  else{
    return 0;
  }
}

/*
Entrada: Arreglo con la imagen en escala de gris y la imagen binarizada, nombre que tendra el archivo que se escribe.
Salida: Ninguna.
Descripcion: Funcion que permite escribir las nuevas imagenes. Una en escala de grises y la otra binarizada segun el umbral
entregado por el usuario. Por otra parte, esta funcion tambien calcula las dimensiones que debe tener el archivo de salida a
traves de la cabecera de la imagen original.
*/
void escribirImagen(Pixel* punteroPixeles, Estructura* est, char* nombreArchivo){
   int i;
   unsigned long x;
   int j=138;
   double cantidadDePares= est->cantidadDePares;
   unsigned char* punteroFormatoSalida=(unsigned char*)malloc(sizeof(unsigned char)*(cantidadDePares+138));
   FILE *archivoSalida;
   archivoSalida = fopen(nombreArchivo, "wb");
   
   for(i=0;i<138;i++){
      punteroFormatoSalida[i]=stringAHexadecimal(est->par[i]);
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