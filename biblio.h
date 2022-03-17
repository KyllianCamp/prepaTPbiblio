#ifndef BIBLIO_H   //compilation conditionnelle
#define BIBLIO_H


#include "livre.h"

#define CAPACITE_BIBLIO 20 // nb maximum de livres ds la bibliotheque

typedef  T_livre 	T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres;  //nb de livres actuellement ds la bibliotheque
	int nbLivresDispo; //nb de livres disponible à l'emprunt

} T_Bibliotheque;




//prototypes
void init (T_Bibliotheque *ptrB);
int ajouterLivre(T_Bibliotheque  *ptrB);
int afficherBibliotheque(T_Bibliotheque  *ptrB);
int rechercherLivre(const T_Bibliotheque *ptrB, const T_Titre recherche);
int rechercherAuteur(const T_Bibliotheque *ptrB, const T_Aut recherche);
int supprimerLivre(T_Bibliotheque *ptrB, const T_Code recherche);
int emprunterLivre(T_Bibliotheque *ptrB, char NomEmprunteur[], int position);
int restituerLivre(T_Bibliotheque *ptrB, const T_Code recherche);
void trieTitre(T_Bibliotheque *ptrB);
void trieAuteur(T_Bibliotheque *ptrB);
void trieAnnee(T_Bibliotheque *ptrB);
void listeLivreDispo(const T_Bibliotheque *ptrB);
int rechercherCode(const T_Bibliotheque *ptrB, const T_Code code);
void listeEmpruntPers (const T_Bibliotheque *ptrB, char emprunteur[]);
void ListeLivreRetard(const T_Bibliotheque *ptrB);
void dernierLivreEmprunt(const T_Bibliotheque *ptrB);
void dernierEmprunt (const T_Bibliotheque *ptrB, int reponse);


void sauvegarde(T_Bibliotheque *ptrB);
void chargement(T_Bibliotheque *ptrB);
void nbrLivre(T_Bibliotheque *ptrB);
void chargementNbrLivre (T_Bibliotheque *ptrB);

void formaterTexte(Tchaine recherche);
#endif