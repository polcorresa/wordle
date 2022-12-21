#include <stdio.h>
#include "colores.h"
#include "palabras.h"
#include "wordle.h"

void imprimir_tablero(wordle tablero) {
  int i, j;
  for (i = 0; i < INTENTOS; i++) {
    printf("\n    +-+-+-+-+-+-+-+-+-+-+\n    |");
    for (j = 0; j < NUM_LETRAS_PALABRA; j++) {

      switch(tablero.tab[i][j].color){
      case AMARILLO: 
        printf_color(YELLOW);
        break;
      case VERDE:
        printf_color(GREEN);
        break;
      default:
        printf_color(COLOR_DEFAULT);
      }
      printf(" %c ", tablero.tab[i][j].letra);
      printf_color(COLOR_DEFAULT);
      printf("|");
    }
  }
  printf("\n    +-+-+-+-+-+-+-+-+-+-+\n");
}



void inicializar_tablero(wordle *tablero) {
  int i, j;
  tablero->intento = 0;
  for (i = 0; i < INTENTOS; i++) {
    for (j = 0; j < NUM_LETRAS_PALABRA; j++) {
      tablero->tab[i][j].letra = ' ';
      tablero->tab[i][j].color = BLANCO;
    }
  }
}



void introducir_palabra(wordle *tablero) {
  int i, arb = 0;
  char basurero[50]; //para borrar el buffer
      i=0;
      printf("\n\nIntroduce a 5 letter word: ");
     do{
        scanf("%c", &tablero->tab[tablero->intento][i].letra);
        i++;
     }while(i<NUM_LETRAS_PALABRA);

     //vaciar el buffer
     do{
      i++;  
      scanf("%c", &basurero[i]);
    }while(basurero[i]!='\n');
}



void pasar_a_mayusculas(wordle *tablero){
  int i;
  for(i=0;i<NUM_LETRAS_PALABRA;i++){
    if(tablero->tab[tablero->intento][i].letra >= 'a'){
      tablero->tab[tablero->intento][i].letra -= 'a'-'A';
    }
  }
}



int menu_idiomas(){
  int idioma;
  do{
    //ordenat per a que el return coincideixi amb l'idioma correcte de palabras.c
    printf("\nLANGUAGE MENU\n0. Debug mode\n1. Catala\n2. English\n3. Espanyol\n4. Suomalainen\nSelect language: ");
    scanf("%d%*c", &idioma);
  }while((idioma<0)||(idioma >4));
  return idioma;
}


int comprobar(wordle *tablero, char palabra[NUM_LETRAS_PALABRA]){
  int i, j, cont=0;
  //comprobacion letra a letra de la palabra correcta con la ultima introducida
  for(i=0;i<NUM_LETRAS_PALABRA;i++){
    if(tablero->tab[tablero->intento][i].letra == palabra[i]){
      tablero->tab[tablero->intento][i].color = VERDE;
      cont++;
    }
    //si no es verde, buscar si hay una letra igual que no sea verde en el tablero (intento en el que estamos)
    if(tablero->tab[tablero->intento][i].color != VERDE){
      j=0;
      while((palabra[i]!=tablero->tab[tablero->intento][j].letra)&&(j<NUM_LETRAS_PALABRA)){
        j++;
      }
      if((j!=NUM_LETRAS_PALABRA)&&(tablero->tab[tablero->intento][j].color != VERDE)){
        tablero->tab[tablero->intento][j].color = AMARILLO;
      }
    }
  }
  //devuelve el numero de letras acertadas que hay
  return cont;
}

int menu_principal(){
  int opcion;
  do{
  printf("MENU\n1. Play\n2. Quit\nSelect option: ");
  scanf("%d%*c", &opcion);
}while((opcion<1)||(opcion>2));
  return opcion;
}

int existencia_palabra(wordle tablero, int idioma){
  int i;
  char palabra[NUM_LETRAS_PALABRA];
  //como almacenamos las palabras en un struct casillas necesitamos un vector para mandar a la funcion.
  for(i=0;i<NUM_LETRAS_PALABRA;i++){
    palabra[i] = tablero.tab[tablero.intento][i].letra;
  }
  if(es_palabra_correcta(idioma, palabra)){
    return 1;
  }
  else{
    printf("La palabra introducida no existe.\n");
  return 0;
  }
}

void inicializar_teclado(casilla tec[TECLAS]){
  int i;
  for(i=0;i<TECLAS;i++){
    tec[i].color = BLANCO;
  }
}


void imprimir_teclado(casilla tec[TECLAS]){
  int i;
  for(i=0;i<TECLAS;i++){
    printf("[");
    switch(tec[i].color){
      case NEGRO: printf_color(COLOR_LETRA_KO);
        break;
      case VERDE: printf_color(GREEN);
        break;
    case AMARILLO: printf_color(YELLOW);
        break;
    case BLANCO: printf_color(COLOR_DEFAULT);
    }
    printf("%c", tec[i].letra);
    printf_color(COLOR_DEFAULT);
    printf("]");
    //estilizado del teclado modo ordenador
    if(tec[i].letra == 'P'){printf("\n ");}
    else if(tec[i].letra == 'L'){printf("\n    ");}
    
    
  }
}

void comprobar_teclado(casilla tec[TECLAS], wordle tablero){
  int i, j;
  for(i=0;i<NUM_LETRAS_PALABRA;i++){
    j=0;
    //busqueda de la letra en el teclado que corresponde a la que examinamos en tablero
    while(tablero.tab[tablero.intento][i].letra != tec[j].letra){
      j++;
    }
    switch(tablero.tab[tablero.intento][i].color){
      case BLANCO: tec[j].color = NEGRO;
        break;
      case VERDE: tec[j].color = VERDE;
        break;
      case AMARILLO: tec[j].color = AMARILLO;
        break;
    }
  }
}

