#include "biblio.h"

void init (T_Bibliotheque *ptrB)
{
    ptrB->nbLivres = 0;
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

// 1 - ajouter un nouveau livre dans la bibliotheque
//Fonction ajouterLivre
//Entrée : Pointeur vers une bibliothèque
//Sortie : 
//Utilité : Permet d'ajouter un livre dans la bibliothèque selectionné précedemment
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

        printf("Saisissez le nombre d'exemplaire que vous avez : \n");
        scanf("%d", &ptrB->etagere[ptrB->nbLivres].QuantiteExemplaire);
        fflush(stdin);

        ptrB->etagere[ptrB->nbLivres].emprunteur.nomemprunteur[0]= '\0';
        ptrB->etagere[ptrB->nbLivres].NbEmprunt = 0;

        ptrB->nbLivres++;
        ptrB->nbLivresDispo++;
        return 1;
    }

    else
    {
        return 0;
    }
}

// 2 - afficher tous les livres de la bibliotheque
//Fonction afficherBibliotheque
//Entrée : Pointeur vers une bibliothèque
//Sortie : 
//Utilité : Permet d'afficher les informations de tous les livres dans la bibliothèque selectionné précedemment
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

// 3 - rechercher un livre (par son titre)
//Fonction rechercherLivre
//Entrée : Pointeur vers une bibliothèque et Titre qui est demandé
//Sortie : Le compteur donc le rang où le livre se situe
//Utilité : Permet de rechercher l'emplacement(le rang) du livre dans la bibliothèque selectionné précedemment.
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

// 4 - rechercher et afficher tous les livres d'un auteur
//Fonction rechercherAuteur
//Entrée : Pointeur vers une bibliothèque et Auteur qui est demandé
//Sortie : Le compteur donc le rang où le livre se situe
//Utilité : Permet de rechercher tous les livres dans la bibliothèque selectionné précedemment écris par cet auteur.
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

// 5 - supprimer un livre de la bibliotheque
//Fonction supprimerrLivre
//Entrée : Pointeur vers une bibliothèque et Code qui est demandé.
//Sortie : Le compteur donc le rang où le livre se situe ou -1 si le livre n'est pas dans la bibliothèque
//Utilité : Permet de supprimer le livre dans la bibliothèque selectionné précedemment grâce au code fourni.
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


// TP 8 Partie n°2

// 6 - emprunter un livre de la bibliotheque
//Fonction emprunterLivre
//Entrée : Pointeur vers une bibliothèque , Nom de l'emprunteur qui est demandé et la position qui est donné grâce à la focntion rechercherLivre()
//Sortie : 
//Utilité : Permet de modifier le nom de l'emprunteur d'un livre dans la bibliothèque selectionné précedemment.
int emprunterLivre(T_Bibliotheque *ptrB, char NomEmprunteur[], int position)
{

    strcpy(ptrB->etagere[position].emprunteur.nomemprunteur, NomEmprunteur);
    ptrB->etagere[position].QuantiteExemplaire--;
    ptrB->etagere[position].NbEmprunt++;

    time_t today;     
    //Renvoie l'heure actuelle
    time(&today);

    struct tm *local = localtime(&today);

    ptrB->etagere[position].emprunteur.lejour = local->tm_mday;
    ptrB->etagere[position].emprunteur.lemois = local->tm_mon +1;
    ptrB->etagere[position].emprunteur.lannee = local->tm_year + 1900;
    ptrB->etagere[position].emprunteur.ladate = local->tm_yday+1 + local->tm_year*365; 
    //La date contient donc le nombre de jour passé depuis le 1er janvier 1900.

    printf("Vous avez emprunté le livre le %02d/%02d/%d\n", ptrB->etagere[position].emprunteur.lejour, ptrB->etagere[position].emprunteur.lemois, 
    ptrB->etagere[position].emprunteur.lannee);
    
    return 1;
}

// 7 - restituer/rendre un livre de la bibliotheque
//Fonction restituerLivre
//Entrée : Pointeur vers une bibliothèque et Code qui est demandé
//Sortie : Le compteur donc le rang où le livre se situe où -1 si il n'est pas dans cette bibliothèque à cette instant
//Utilité : Permet de restituer le livre donc siupprimer le nom de l'emprunteur de ce livre dans la bibliothèque selectionné précedemment.
int restituerLivre(T_Bibliotheque *ptrB, const T_Code recherche)
{
    ptrB->nbLivresDispo++;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        if (strcmp(ptrB->etagere[i].code, recherche)==0)
        {
            if (ptrB->etagere[i].emprunteur.nomemprunteur[0]!='\0')
            {
                ptrB->etagere[i].emprunteur.nomemprunteur[0]= '\0';
                ptrB->etagere[i].QuantiteExemplaire++;
                return i;
            }
        }
    }
    
    return -1;
}

// 8 - trier les livres (par titre)
//Fonction trieTitre
//Entrée : Pointeur vers une bibliothèque
//Sortie : 
//Utilité : Permet de trier la bibliothèque avec les titres des livres.
void trieTitre(T_Bibliotheque *ptrB)
{
    T_livre intermediaire;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        for (int y = (ptrB->nbLivres)-1; y > 0 ; y--)
        {
            if (strcmp(ptrB->etagere[y].titre, ptrB->etagere[y-1].titre) < 0)
            {
                intermediaire = ptrB->etagere[y];
                ptrB->etagere[y]=ptrB->etagere[y-1];
                ptrB->etagere[y-1]=intermediaire;
            }
        }
    }
}

// 9 - trier les livres (par auteur)
void trieAuteur(T_Bibliotheque *ptrB)
//Fonction trieAuteur
//Entrée : Pointeur vers une bibliothèque
//Sortie : 
//Utilité : Permet de trier la bibliothèque avec les auteurs des livres.
{
    T_livre intermediaire;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        for (int y = (ptrB->nbLivres)-1; y > 0 ; y--)
        {
            if (strcmp(ptrB->etagere[y].auteur, ptrB->etagere[y-1].auteur) < 0)
            {
                intermediaire = ptrB->etagere[y];
                ptrB->etagere[y]=ptrB->etagere[y-1];
                ptrB->etagere[y-1]=intermediaire;
            }
        }
    }
}

// 10 - trier les livres (par annee)
//Fonction trieAnnee
//Entrée : Pointeur vers une bibliothèque
//Sortie : 
//Utilité : Permet de trier la bibliothèque avec l'année de création des livres.
void trieAnnee(T_Bibliotheque *ptrB)
{
    T_livre intermediaire;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        for (int y = (ptrB->nbLivres)-1; y > 0 ; y--)
        {
            if (ptrB->etagere[y].annee < ptrB->etagere[y-1].annee)
            {
                intermediaire = ptrB->etagere[y];
                ptrB->etagere[y]=ptrB->etagere[y-1];
                ptrB->etagere[y-1]=intermediaire;
            }
        } 
    }
}


// 11 - lister les livres disponibles
void listeLivreDispo(const T_Bibliotheque *ptrB)
{
    int compteur = 0;
    for (int i = 0; i < ptrB->nbLivres ; i++)
    {
        if (ptrB->etagere[i].emprunteur.nomemprunteur[0]=='\0')
        {
            compteur++;
            if (compteur == 1)
            {
                printf("Les livres disponibles sont : \n\n");
            }
            afficherLivre(&ptrB->etagere[i]);
            printf("\n");
        }
    }
    if (compteur == 0)
    {
        printf("Aucun livre n'est disponible pour l'instant \n");
    }
}

void ListeLivreRetard(const T_Bibliotheque *ptrB)
{
     time_t today;     
    //Renvoie l'heure actuelle
    time(&today);
    struct tm *local = localtime(&today);

    int compteur = 0;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        if (ptrB->etagere[i].emprunteur.nomemprunteur[0]!='\0')
        {
            int ecartDate = (local->tm_yday+1 + (local->tm_year*365)) - ptrB->etagere[i].emprunteur.ladate;
            if (ecartDate > 7)
            {
                compteur++;
                if (compteur == 1)
                {
                    printf("Les livres en retard de restitution sont : \n");
                }
                afficherLivre(&ptrB->etagere[i]);
                printf("\n");
            }
        }
    }
    if (compteur == 0)
    {
        printf("Aucune personne n'est en retard dans la restitution des livres");
    }
    
}

// 13 - lister les emprunts de la personne
void listeEmpruntPers (const T_Bibliotheque *ptrB, char emprunteur[])
{
    int compteur = 0;
    for (int i = 0; i < ptrB->nbLivres; i++)
    {
        if (strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, emprunteur)==0)
        {
            compteur++;
            if (compteur == 1)
            {
                printf("Les livres que vous avez en cours d'emprunt sont : \n");
            }
            afficherLivre(&ptrB->etagere[i]);
            printf("\n");
        }
    }
    if (compteur == 0)
    {
        printf("Vous n'avez empruntés aucun livre pour l'instant");
    }
}

// 14 - lister le dernier livre emprunté
void dernierLivreEmprunt(const T_Bibliotheque *ptrB)
{
    int position = 0;
    for (int i = 0 ; i < ptrB->nbLivres; i++)
    {
        if (ptrB->etagere[position].emprunteur.ladate <= ptrB->etagere[i].emprunteur.ladate)
        {
            if (ptrB->etagere[i].NbEmprunt > 0)
            {
                position = i;
            }
        }
    }
    if (ptrB->etagere[position].NbEmprunt > 0)
    {
        printf("Le dernier livre empruntés est : \n");
        afficherLivre(&ptrB->etagere[position]);
    }
    else
    {
        printf("Aucun livre n'a encore été emprunté \n");
    }
}

// 15 - lister le dernier emprunt d'un livre en particulier
void dernierEmprunt (const T_Bibliotheque *ptrB, int position)
{
    {
        if (ptrB->etagere[position].NbEmprunt > 0)
        {
            printf("Ce livre à été emprunté pour la dernière fois le %02d/%02d/%04d \n", ptrB->etagere[position].emprunteur.lejour,
            ptrB->etagere[position].emprunteur.lemois, ptrB->etagere[position].emprunteur.lannee);
        }
        else
        {
            printf("Ce livre n'as encore jamais été emprunté");
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////         Fonction Externe utilisé dans le TP            ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//Fonction rechercherCode
int rechercherCode(const T_Bibliotheque *ptrB, const T_Code code)
{
    int i = 0;
    while (strcmp(ptrB->etagere[i].code, code)!=0 && i < ptrB->nbLivres)
    {
        i++;
    }
    if (strcmp(ptrB->etagere[i].code,code)==0)
    {
        return i;
    }
return -1;
}
