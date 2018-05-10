all: main lector_de_imagen conversor_a_gris binarizador_de_imagen analista_de_propiedad escritor_de_resultados

main:
	gcc -Wall -w -o main main.c
lector_de_imagen:
	gcc -Wall -w -o lector_de_imagen lector_de_imagen.c
conversor_a_gris:
	gcc -Wall -w -o conversor_a_gris conversor_a_gris.c
binarizador_de_imagen:
	gcc -Wall -w -o binarizador_de_imagen binarizador_de_imagen.c
analista_de_propiedad:
	gcc -Wall -w -o analista_de_propiedad analista_de_propiedad.c
escritor_de_resultados:
	gcc -Wall -w -o escritor_de_resultados escritor_de_resultados.c