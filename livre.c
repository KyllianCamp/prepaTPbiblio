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

