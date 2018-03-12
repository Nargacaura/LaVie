/**
  \file jeu.c
  \brief Source du "jeu"

 */ 
#include "jeu.h"
#include <stdio.h>

/* Fonction utilisée dans le niveau 1 [cyclique], remplacée par compte_voisins_vivants_c
int compte_voisins_vivants(int i, int j, grille g) {
  int v = 0;
  for(int templ=-1; templ<=1; templ++){
    for(int tempc=-1; tempc<=1; tempc++){
      if(templ!=0)
        v+=est_vivante(modulo(i+templ, g.nbl), modulo(j+tempc, g.nbc), g);
      else {
        if(tempc!=0)
          v+=est_vivante(modulo(i, g.nbl), modulo(j+tempc, g.nbc), g);
      }
    }
  }
  return v;
}*/

int compte_voisins_vivants_c(int i, int j, int distance, grille g){
  int v=0;
  for(int debutl=-distance; debutl<=distance; debutl++){
    for(int debutc=-distance; debutc<=distance; debutc++){
      if(debutl!=0)
        v+=est_vivante(modulo(i+debutl, g.nbl), modulo(j+debutc, g.nbc), g);
      else if(debutc!=0)
        v+=est_vivante(modulo(i, g.nbl), modulo(j+debutc, g.nbc), g);
    }
  }
  return v;
}

int compte_voisins_vivants_nc(int i, int j, int distance, grille g){
  int v=0;
  for(int debutl=-distance; debutl<=distance; debutl++){
    for(int debutc=-distance; debutc<=distance; debutc++){
      int templ=i+debutl, tempc=j+debutc;
      if(templ!=i){ if(templ<=g.nbl-1 && tempc<=g.nbc-1 && templ>=0 && tempc>=0) v+=est_vivante(templ, tempc, g); }
      else if(tempc!=j) {if(tempc<=g.nbc-1 && tempc>=0) v+=est_vivante(i, tempc, g); }
    }
  }
  return v;
}

void evolue(grille *g, grille *gc, int dist, int (*compte_v)(int, int, int, grille)) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; ++i) {
    for (int j=0; j < g->nbc; ++j) {
      if(!est_vivante(i, j, *gc) && compte_v(i, j, dist, *gc)==3) /** \brief Si elle est morte et a 3 voisins, elle naît */
        set_vivante(i, j, *g);
      else {
        if(est_vivante(i, j, *gc) &&
          (compte_v(i, j, dist, *gc)==2 || compte_v(i, j, dist, *gc)==3)) /** \brief Si elle est déjà vivante et qu'elle a entre 2 et 3 voisins, elle continue de vivre */
          set_vivante(i, j, *g);
        else set_morte(i, j, *g); /** \brief sinon elle meurt */
      }
    }
  }
}
