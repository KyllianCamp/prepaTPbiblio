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
        fflush(stdin);
        formaterTexte(ptrB->etagere[ptrB->nbLivres].titre);

        printf("Saisissez l'auteur du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].auteur, MAX, stdin);
        fflush(stdin);
        // formaterTexte(ptrB->etagere[ptrB->nbLivres].auteur);

        printf("Saisissez le code du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].code, MAX_CODE, stdin);
        fflush(stdin);

        printf("Saisissez l'année du livre : \n");
        scanf("%d", &ptrB->etagere[ptrB->nbLivres].annee);
        fflush(stdin);

        printf("Saisissez l'éditeur du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].editeur, MAX, stdin);
        fflush(stdin);
        // formaterTexte(ptrB->etagere[ptrB->nbLivres].editeur);

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

int rechercherLivre(const T_Bibliotheque *ptrB, const T_Titre recherche)
{
    int compteur = 0;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {     
        if (strcmp(ptrB->etagere[i].titre, recherche)==0)
        {
            compteur++;
            printf("Ce titre se trouve à la place %d dans l'étagère \n", i+1);
        }  
    }
    return compteur;
}

int rechercherAuteur(const T_Bibliotheque *ptrB, const T_Aut recherche)
{
    int compteur = 0;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        if (strcmp(ptrB->etagere[i].auteur, recherche)==0)
        {
            compteur++;
            if (compteur==1)
            {
                printf("les livres disponibles de l'auteur %s sont : \n", recherche);
            }
            printf("-%s \n", ptrB->etagere[i].titre);
        }
    }
    return compteur;
}

//Fonction formaterTexte
//Entrée : texte à formater
//Sortie : 1 lettre en majuscule et le reste en minuscule
//Utilité : Permet ici d'enlever les majuscules en milieu de mot qui peut gener si on cherche le livre

void formaterTexte(T_Titre recherche)
{
    int i = 1;
    if (recherche[0]>= 'a' && recherche[0]<='z')
    {
        recherche[0]= recherche[0]+('A'-'a');
    }
    while (recherche[i]!= '\0')
    {
        if (recherche[i] >= 'A' && recherche [i]<='Z')
        {
            recherche[i]= recherche[i]+('a'-'A');
        }
        i++;
    }
}