/**
  \file main.c
  \brief Programme principal
  
*/
#include <stdlib.h>
#include <stdio.h>

#include "../hdr/grille.h"
#include "../hdr/io.h"
#include "../hdr/jeu.h"

int main (int argc, char ** argv) { /** \brief programme principal */
  if (argc != 2) {
    printf("Usage : %s <fichier grille>\n", argv[0]);
    return 1;
  }

  grille g, gc;
  init_grille_from_file(argv[1],&g);
  alloue_grille (g.nbl, g.nbc, &gc);
  affiche_grille(&g);

  debut_jeu(&g, &gc);

  libere_grille(&g);
  libere_grille(&gc);
  return EXIT_SUCCESS;
}
