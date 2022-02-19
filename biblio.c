#include "biblio.h"

void init (T_Bibliotheque *ptrB)
{
    ptrB->nbLivres = 0;
    for (int i = 0; i < CAPACITE_BIBLIO; i++)
    {
        strcpy(ptrB->etagere[i].emprunteur, "");
    }
    
}


int ajouterLivre(T_Bibliotheque  *ptrB)
{
    if (ptrB->nbLivres < CAPACITE_BIBLIO)
    { 
        printf("Saisissez le titre du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].titre, MAX_TITRE, stdin);

        printf("Saisissez l'auteur du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].auteur, MAX, stdin);

        printf("Saisissez le code du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].code, MAX_CODE, stdin);

        printf("Saisissez l'année du livre : \n");
        scanf("%d", &ptrB->etagere[ptrB->nbLivres].annee);

        printf("Saisissez l'éditeur du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].editeur, MAX, stdin);

        ptrB->nbLivres++;
        return 1;
    }

    else
    {
        return 0;
    }
}


int  afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
    if (ptrB->nbLivres != 0)
    {
        printf("Les livres disponibles sont : \n");
        for (int i = 0; i < ptrB->nbLivres; i++)
        {
            printf("-%s \n", ptrB->etagere[i].titre);
        }
        return 1;
    }
    else
        return 0;
}
