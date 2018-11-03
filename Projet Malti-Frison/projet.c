// Hind Malti
// Pierre Frison

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define X 10
#define Y 10

// définit les règles du jeu (bonus 1)
int regles_du_jeu(int nombre_voisins, int etat_cellule){
  switch(nombre_voisins){
  case 0:
    return 0;
  case 1:
    return 0;
  case 2:
    return etat_cellule;
  case 3:
    return 1;
  case 4:
    return 0;
  case 5:
    return 0;
  case 6:
    return 0;
  case 7:
    return 0;
  case 8:
    return 0;
  }
}

// fonctions de récupération de la grille sur l'entrée standard
void monfgets(char resu[], int size){
  char input[size+2]; 
  fgets(input, size+2, stdin);
  strncpy(resu, input, size);
}

void open_grid(int t[X][Y]){
  int i,j;
  char oneline[X]; // chaine
  for (i = 0; i < Y; i++){
    monfgets(oneline, X);
    for (j = 0 ; j < X; j++){
      int etat_cel;
      if(oneline[j] == '1')
	etat_cel = 1;
      else
	etat_cel = 0;
      
      t[i][j] = etat_cel;
    }
  }
  printf("opengrid : matrice initialisée\n");
}

// détecte un 1 (= continuer) ou un 0 (= fin du programme) après la grille dans le fichier
int iteration(){
  char resu[1];
  monfgets(resu, 1);
  if(resu[0] == '1')
    return 1;
  else
    return 0;
}

// lit entièrement le fichier, c'est à dire la grille et le nombre d'itérations à faire
int lire_fichier(int t[X][Y]){
  open_grid(t);

  int nombre_iteration = 1;
  int suivant = iteration();
  while(suivant == 1) {
    suivant = iteration();
    nombre_iteration++;
  }
  return nombre_iteration;
}

//random init
void init_rand(){srand(time(NULL));}
int hasard(){
  int rando = rand();
  return (rando % 2);
}

// fonction d'initialisation aléatoire (bonus 2)
void init_rand_grille(int T[X][Y]){
  for (int i = 0; i < X; i++){
    for (int j = 0; j < Y; j++) {
      T[i][j] = hasard();
    }
  }
}
// calcul de l'étape suivante de la cellule
int calc_cellule(int i, int j, int t[X][Y]){
  int com = 0;
  for (int x = i-1; x <= i+1; x++){
    for (int y = j-1; y<= j+1; y++){
      // il ne faut pas compter notre cellule
      if(x == i && y == j)
	continue;
      
      // cas des cotes de la grille
      int k = x;
      int l = y;
      if(k < 0) k = X-1;
      if(k > X-1) k = 0;
      if(l < 0) l = Y-1;
      if(l > Y-1) l = 0;
      // comptage des cases voisines
      if (t[k][l] == 1) com++;
    }
  }
  return regles_du_jeu(com, t[i][j]);
}

//calcul étape suivante de la grille
void calc_grille(int K[X][Y]){
  int b[X][Y];
  for(int i = 0; i < X; i++){
    for(int j = 0; j < Y; j++){
      b[i][j] = calc_cellule(i, j, K);
    }
  }
  // copier b dans k
  for(int i = 0; i < X; i++){
    for(int j = 0; j < Y; j++){
      K[i][j] = b[i][j];
    }
  }
}


//affiche la grille
void print_grille(int t[X][Y]){
  system("clear");

  // affichage carde (haut)
  printf(" ");
  for(int i = 0; i < X; i++){
    printf("_");
  }
  printf(" \n");
  
  for(int i = 0; i < X; i++){
    printf("|"); // affichage cadre (côté)
    for(int j = 0; j < Y; j++){
      if(t[i][j] == 0)
	printf(" "); // cellule morte --> un espace
      else
	printf("0"); // cellule vivante --> un 0
    }
    printf("|\n"); // affichage cadre (autre côté)
  }

  // affichage cadre (bas)
  printf(" ");
  for(int i = 0; i < X; i++){
    printf("_");
  }
  printf(" \n");
}

//main
int main(){
  init_rand();
  int t[X][Y];
  int n_iteration = lire_fichier(t);
  print_grille(t);
  for(int i = 0; i < n_iteration; i++){
    system("sleep 0.2");
    calc_grille(t);
    print_grille(t);
  }
}
