#include "biblio.h"

void init (T_Bibliotheque *ptrB)
{
    ptrB->nbLivres = 0;
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
        formaterTexte(ptrB->etagere[ptrB->nbLivres].auteur);

        printf("Saisissez le code du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].code, MAX_CODE, stdin);
        fflush(stdin);

        printf("Saisissez l'année du livre : \n");
        scanf("%d", &ptrB->etagere[ptrB->nbLivres].annee);
        fflush(stdin);

        printf("Saisissez l'éditeur du livre : \n");
        fgets(ptrB->etagere[ptrB->nbLivres].editeur, MAX, stdin);
        fflush(stdin);
        formaterTexte(ptrB->etagere[ptrB->nbLivres].editeur);

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
            afficherLivre(&ptrB->etagere[i]);
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

int supprimerLivre(T_Bibliotheque *ptrB, const T_Code recherche)
{
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        if (strcmp(ptrB->etagere[i].code, recherche)==0)
        {
            for (int y = i; y < ptrB->nbLivres; y++)
            {
                ptrB->etagere[y]= ptrB->etagere[y+1];
            }
        ptrB->nbLivres--;
        return i;
        } 
    }
    return -1;
}

void sauvegarde(T_Bibliotheque *ptrB)
{
    FILE *fic=NULL; //le type FILE
    int i;
    fic=fopen("baseLivres","w"); // w = le mode = write avec ECRASEMENT
    //fopen renvoie NULL si probleme (disque plein, disque non accessible ...
    if (fic!=NULL)
        {
        for(i=0;i<ptrB->nbLivres;i++)
            {
    //fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
        fwrite(  &(ptrB->etagere[i])        ,sizeof(T_livre),1,fic);
            }
        fclose(fic);
        puts("SAUVEGARDE REUSSIE ..............");
        }
        else puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}

void chargement(T_Bibliotheque *ptrB)
{
    FILE *fic=NULL; //le type FILE
    int i=0;
    fic=fopen("baseLivres","r"); // r = le mode read
    //fopen renvoie NULL si probleme (disque plein, disque non accessible ...
    if (fic!=NULL)
    {
        do
            {

            fread(  &(ptrB->etagere[i]) ,sizeof(T_livre),1,fic);
            i++;
            }
            while(!feof(fic));
        fclose(fic);
        ptrB->nbLivres=i-1;
        puts("CHARGEMENT  REUSSI ..............");
        }
        else 
        {
            puts("ECHEC DE CHARGEMENT  !!!!!  ");

        }
}


//Fonction formaterTexte
//Entrée : texte à formater
//Sortie : 1 lettre en majuscule et le reste en minuscule
//Utilité : Permet ici d'enlever les majuscules en milieu de mot qui peut gener si on cherche le livre
void formaterTexte(Tchaine recherche)
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

// TP 8 Partie n°2

int rechercherCode(const T_Bibliotheque *ptrB, const T_Code code)
{
    int compteur = 0;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {     
        if (strcmp(ptrB->etagere[i].code, code)==0)
        {
            compteur++;
            printf("Ce code de livre se trouve à la place %d dans l'étagère \n", i+1);
        }  
    }
    return compteur;
}

int emprunterLivre(T_Bibliotheque *ptrB)
    {
    T_Code code_tempo;
    char nom;
    if (ptrB->nbLivres < CAPACITE_BIBLIO)
        { 
            printf("Saisissez le code du livre que vous voulez emprunter:\n");
            fgets(code_tempo, MAX_CODE, stdin);
            fflush(stdin);
            int compteur = rechercherCode(ptrB,code_tempo);
            printf("Saisissez votre nom de famille:\n");
            fgets(ptrB->etagere[compteur].titre, MAX_TITRE, stdin);
            fflush(stdin);
            return 1;
        }
        else
        {
            return 0;
        }
    }
