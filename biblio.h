#ifndef BIBLIO_H   //compilation conditionnelle
#define BIBLIO_H


#include "livre.h"

#define CAPACITE_BIBLIO 20 // nb maximum de livres ds la bibliotheque

typedef  T_livre 	T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres;  //nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;




//prototypes
void init (T_Bibliotheque *ptrB);
int ajouterLivre(T_Bibliotheque  *ptrB);
int afficherBibliotheque(const T_Bibliotheque  *ptrB);
int rechercherLivre(const T_Bibliotheque *ptrB, const T_Titre recherche);
int rechercherAuteur(const T_Bibliotheque *ptrB, const T_Aut recherche);
int supprimerLivre(T_Bibliotheque *ptrB, const T_Code recherche);
int restituerLivre(T_Bibliotheque *ptrB, const T_Code recherche);
void trieTitre(T_Bibliotheque *ptrB);
int emprunterLivre(T_Bibliotheque *ptrB);
<<<<<<< HEAD
=======

>>>>>>> 942c3b10085f6dbfdd4006311190b5de7ea2ec2c

void sauvegarde(T_Bibliotheque *ptrB);
void chargement(T_Bibliotheque *ptrB);

void formaterTexte(T_Titre recherche);
#endif