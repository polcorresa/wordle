#include <stdio.h>
#include "colores.h"
#include "palabras.h"
#include "wordle.h"


int main() {
  char palabra[NUM_LETRAS_PALABRA];
  wordle tablero; 
  int idioma, quit, arb =0, i;
  casilla tec[TECLAS] = {{'Q', BLANCO},{'W', BLANCO},{'E', BLANCO},{'R', BLANCO},{'T', BLANCO},{'Y', BLANCO},{'U', BLANCO},{'I', BLANCO},{'O', BLANCO},{'P', BLANCO},{'A', BLANCO},{'S', BLANCO},{'D', BLANCO},{'F', BLANCO},{'G', BLANCO},{'H', BLANCO},{'J', BLANCO},{'K', BLANCO},{'L', BLANCO},{'Z', BLANCO},{'X', BLANCO},{'C', BLANCO},{'V', BLANCO},{'B', BLANCO},{'N', BLANCO},{'M', BLANCO}};

  inicializar_azar();

  do{
    quit = menu_principal();

    switch(quit){
    case 1: {
      inicializar_teclado(tec);
      inicializar_tablero(&tablero);
      idioma = menu_idiomas();
      palabra_al_azar(idioma,contar_palabras(idioma),palabra);


      do{
        imprimir_tablero(tablero);
        imprimir_teclado(tec);

        do{
          introducir_palabra(&tablero);
          pasar_a_mayusculas(&tablero);
        }while(existencia_palabra(tablero, idioma)!= 1);
        

        arb = comprobar(&tablero, palabra);
        comprobar_teclado(tec, tablero);
        tablero.intento++;
      }while((tablero.intento<INTENTOS)&&(arb<5));

      imprimir_tablero(tablero);

      if(arb==5){
        printf("CONGRATULATIONS! YOU WIN!\n\n");
      }
      else{
        printf("...Next time...\n\nAnswer: ");
      for(i=0;i<NUM_LETRAS_PALABRA;i++){
        printf("%c", palabra[i]);
      }
      printf("\n\n");}}
    }
      
  }while(quit != 2);
}