#include <stdio.h>
#include "colores.h"
#include "palabras.h"
#define NUM_LETRAS_PALABRA 5
#define INTENTOS 6
#define BLANCO 0
#define AMARILLO 1
#define VERDE 2
#define NEGRO 3
#define TECLAS 26



typedef struct {
  char letra;
  int color;
} casilla;

typedef struct {
  casilla tab[INTENTOS][NUM_LETRAS_PALABRA];
  int intento;
} wordle;

//MAIN
int menu_idiomas();
int menu_principal();

//TABLERO
void imprimir_tablero(wordle tablero);
void inicializar_tablero(wordle *tablero);

//GESTION PALABRRAS
void introducir_palabra(wordle *tablero);
void pasar_a_mayusculas(wordle *tablero);
int existencia_palabra(wordle tablero, int idioma);
int comprobar(wordle *tablero, char palabra[NUM_LETRAS_PALABRA]);

//TECLADO
void inicializar_teclado(casilla tec[TECLAS]);
void imprimir_teclado(casilla tec[TECLAS]);
void comprobar_teclado(casilla tec[TECLAS], wordle tablero);