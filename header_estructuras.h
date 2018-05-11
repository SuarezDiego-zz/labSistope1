typedef struct {
	int red;
	int green;
	int blue;
	int v;
} Pixel;

typedef struct{
   char** par;
   char** arregloBytes;
   char** arregloBytesOrdenado;
   int cantidadDePares;
   long largo;
}Estructura;

typedef struct{
   Estructura* estructura;
   Pixel* pixeles;
   int pipefd[2];
   int xd;
}MensajePipe;

long calcularTamano(char* nombreArchivo);
Estructura* leerImagen(char* nombreArchivo);
Estructura* cortarArreglo(Estructura* estr);
Estructura* invertirArreglo(Estructura* estr);
int stringAHexadecimal(char* stringEntrada);
Pixel* crearArregloPixeles(char** punteroStr,int cantidadPixeles);
Pixel pixel_a_negro(Pixel pix);
Pixel* pixeles_blanco_y_negro(Pixel* punteroPix, int cantidadPixeles);
Pixel* pixeles_binario(Pixel* punteroPix, int cantidadPixeles, int umbral);
int nearlyBlack(Pixel* punteroPix, int cantidadPixeles, int umbral);
void escribirImagen(Pixel* punteroPixeles, Estructura* est,char* nombreArchivo);
void main(int argc, char *argv[]);