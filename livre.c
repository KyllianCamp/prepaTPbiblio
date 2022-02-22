#include "livre.h"


void saisirLivre(T_livre * ptrL)
{
lireChaine("TITRE :", (ptrL->titre), MAX_TITRE );
lireChaine("AUTEUR :", (ptrL->auteur ), MAX);
}

void afficherLivre(const T_livre *ptrL)
{
afficherChaine("TITRE :", (ptrL->titre));
afficherChaine("AUTEUR :", (ptrL->auteur));
afficherChaine("CODE :", (ptrL->code));
printf("\n");
printf("ANNEE : %d",ptrL->annee);
printf("\n");
afficherChaine("EDITEUR :", (ptrL->editeur));
printf("\n");
}

int heure()
{
  int h, min, s, day, mois, an;
  time_t now;
    
  // Renvoie l'heure actuelle
  time(&now);
  // Convertir au format heure locale
  printf("Aujourd'hui est : %s", ctime(&now));
  struct tm *local = localtime(&now);
  h = local->tm_hour;        
  min = local->tm_min;       
  s = local->tm_sec;       
  day = local->tm_mday;          
  mois = local->tm_mon + 1;     
  an = local->tm_year + 1900;  
  printf("La date : %02d/%02d/%d\n", day, mois, an);
  return 0;
}