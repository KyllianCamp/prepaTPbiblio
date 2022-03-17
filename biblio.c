#include "biblio.h"

void init (T_Bibliotheque *ptrB)
{
    ptrB->nbLivres = 0;
}

void chargementNbrLivre (T_Bibliotheque *ptrB)
{
    FILE *file=NULL;
    file=fopen("nbrLivre","r");
    if (file!=NULL)
    {
        int val;
        fread(&val,sizeof(int),1,file);
        printf("nombre de livre : %d", val);
        fclose(file);
        ptrB->nbLivres = val;
    }
    else
        ptrB->nbLivres = 0;
}

void nbrLivre(T_Bibliotheque *ptrB)
{
    FILE *file=NULL;
    file = fopen("nbrLivre","w+");
    if (file!=NULL)
    {
        fwrite(&ptrB->nbLivres,sizeof(int),1,file);
        fclose(file);
    }
}

void sauvegarde(T_Bibliotheque *ptrB)
{
    FILE *fic=NULL; //le type FILE
    fic=fopen("baseLivres","a"); // w = le mode = write avec ECRASEMENT
    //fopen renvoie NULL si probleme (disque plein, disque non accessible ...
    if (fic!=NULL)
    {
    //fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
        fwrite( &(ptrB->etagere[0]),sizeof(T_livre),1,fic);
        fclose(fic);
        puts("SAUVEGARDE REUSSIE ..............");
        }
        else puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}

void sauvegardeTri(T_Bibliotheque *ptrB)
{
    FILE *fic=NULL; //le type FILE
    fic=fopen("baseLivresTri","a"); // w = le mode = write avec ECRASEMENT
    //fopen renvoie NULL si probleme (disque plein, disque non accessible ...
    if (fic!=NULL)
    {
    //fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
        fwrite(  &(ptrB->etagere[0]),sizeof(T_livre),1,fic);
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
        printf("Saisissez le titre du livre : \n");
        fgets(ptrB->etagere[0].titre, MAX_TITRE, stdin);
        fflush(stdin);
        formaterTexte(ptrB->etagere[0].titre);

        printf("Saisissez l'auteur du livre : \n");
        fgets(ptrB->etagere[0].auteur, MAX, stdin);
        fflush(stdin);
        formaterTexte(ptrB->etagere[0].auteur);

        printf("Saisissez le code du livre : \n");
        fgets(ptrB->etagere[0].code, MAX_CODE, stdin);
        fflush(stdin);

        printf("Saisissez l'année du livre : \n");
        scanf("%d", &ptrB->etagere[0].annee);
        fflush(stdin);

        printf("Saisissez l'éditeur du livre : \n");
        fgets(ptrB->etagere[0].editeur, MAX, stdin);
        fflush(stdin);
        formaterTexte(ptrB->etagere[0].editeur);
        ptrB->etagere[0].editeur[101]='!';

        printf("Saisissez le nombre d'exemplaire que vous avez : \n");
        scanf("%d", &ptrB->etagere[0].QuantiteExemplaire);
        fflush(stdin);

        ptrB->etagere[0].emprunteur.nomemprunteur[0]= '\0';
        ptrB->etagere[0].NbEmprunt = 0;
        printf("combien de fois \n");
        ptrB->nbLivres++;
        ptrB->nbLivresDispo++;
        return 1;
}

// 2 - afficher tous les livres de la bibliotheque
//Fonction afficherBibliotheque
//Entrée : Pointeur vers une bibliothèque
//Sortie : 
//Utilité : Permet d'afficher les informations de tous les livres dans la bibliothèque selectionné précedemment
int  afficherBibliotheque(T_Bibliotheque  *ptrB)
{
    if (ptrB->nbLivres > 0)
    {
        FILE *fic=NULL; //le type FILE
        fic=fopen("baseLivres","r"); // r = le mode read
        if (fic!=NULL)
        {
            printf("Les livres disponibles sont : \n");
            while(!feof(fic))
            {
                int retour = fread(&(ptrB->etagere[0]),sizeof(T_livre),1,fic);
                if (retour == 1)
                {
                    afficherLivre(&ptrB->etagere[0]);
                }
            }
            
        }
        printf("fin \n");
        fclose(fic);
        return 1;
    }
    return 0;
}

int  afficherBibliothequeTri(T_Bibliotheque  *ptrB)
{
    // printf("commencement \n");
    // FILE *fic=NULL; //le type FILE
    // fic=fopen("nbrLivre","r"); // r = le mode read
    // int val[1];
    // fread(val,sizeof(int),1,fic);
    // fclose(fic);
    if (ptrB->nbLivres > 0)
    {
        FILE *fic=NULL; //le type FILE
        fic=fopen("baseLivresTri","r"); // r = le mode read
        if (fic!=NULL)
        {
            printf("Les livres disponibles sont : \n");
            while(!feof(fic))
            {
                int retour = fread(&(ptrB->etagere[0]),sizeof(T_livre),1,fic);
                if (retour == 1)
                {
                    afficherLivre(&ptrB->etagere[0]);
                }
            }
            
        }
        printf("fin \n");
        fclose(fic);
        return 1;
    }
    return 0;
}
// 3 - rechercher un livre (par son titre)
//Fonction rechercherLivre
//Entrée : Pointeur vers une bibliothèque et Titre qui est demandé
//Sortie : Le compteur donc le rang où le livre se situe
//Utilité : Permet de rechercher l'emplacement(le rang) du livre dans la bibliothèque selectionné précedemment.
int rechercherLivre(const T_Bibliotheque *ptrB, const T_Titre recherche)
{
    FILE *fic=NULL; //le type FILE
    fic=fopen("baseLivres","r"); // r = le mode read
    int compteur = 0;
    int i = 0;
    if (fic!=NULL)
    {
        while (!feof(fic))
        {
            i++;
            int retour = fread(&(ptrB->etagere[0]),sizeof(T_livre),1,fic);
            if (strcmp(ptrB->etagere[0].titre, recherche)==0 && retour ==1)
            {
                compteur++;
                printf("Ce titre se trouve à la place %d dans l'étagère \n", i);
            }
            
        }
    }
    fclose(fic);
    return compteur;
}

// 4 - rechercher et afficher tous les livres d'un auteur
//Fonction rechercherAuteur
//Entrée : Pointeur vers une bibliothèque et Auteur qui est demandé
//Sortie : Le compteur donc le rang où le livre se situe
//Utilité : Permet de rechercher tous les livres dans la bibliothèque selectionné précedemment écris par cet auteur.
int rechercherAuteur(const T_Bibliotheque *ptrB, const T_Aut recherche)
{
    FILE *fic=NULL; //le type FILE
    fic=fopen("baseLivres","r"); // r = le mode read
    int compteur = 0;
    int i = 0;
    if (fic!=NULL)
    {
        while (!feof(fic))
        {
            i++;
            int retour = fread(&(ptrB->etagere[0]),sizeof(T_livre),1,fic);
            if (strcmp(ptrB->etagere[0].auteur, recherche)==0 && retour ==1)
            {
                compteur++;
                printf("Ce titre se trouve à la place %d dans l'étagère \n", i);
            }
        }
    }
    fclose(fic);
    return compteur;
}

// 5 - supprimer un livre de la bibliotheque
//Fonction supprimerrLivre
//Entrée : Pointeur vers une bibliothèque et Code qui est demandé.
//Sortie : Le compteur donc le rang où le livre se situe ou -1 si le livre n'est pas dans la bibliothèque
//Utilité : Permet de supprimer le livre dans la bibliothèque selectionné précedemment grâce au code fourni.
int supprimerLivre(T_Bibliotheque *ptrB, const T_Code recherche)
{
    FILE *fic=NULL; //le type FILE
    fic=fopen("baseLivres","r"); // r = le mode read
    if (fic!=NULL)
    {
        FILE *file = NULL;
        file=fopen("baseLivresTempo","a");
        if (file!=NULL)
        {
            while (!feof(fic))
            {
                int retour = fread(&ptrB->etagere[0],sizeof(T_livre),1,fic);
                if (strcmp(ptrB->etagere[0].code,recherche)!=0 && retour == 1)
                {
                    fwrite(&(ptrB->etagere[0]),sizeof(T_livre),1,file);
                }
            }
            fclose(file);
        }
        fclose(fic);
        remove("baseLivres");
        rename("baseLivresTempo","baseLivres");
        ptrB->nbLivres--;
        return 1;
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
// void trieTitre(T_Bibliotheque *ptrB)
// {
//     T_livre intermediaire;
//     for (int i = 0; i < ptrB->nbLivres; i++)
//     {
//         for (int y = (ptrB->nbLivres)-1; y > 0 ; y--)
//         {
//             if (strcmp(ptrB->etagere[y].titre, ptrB->etagere[y-1].titre) < 0)
//             {
//                 intermediaire = ptrB->etagere[y];
//                 ptrB->etagere[y]=ptrB->etagere[y-1];
//                 ptrB->etagere[y-1]=intermediaire;
//             }
//         }
//     }
// }

// void trieTitre(T_Bibliotheque *ptrB)
// {
//     // printf("commencement \n");
//     // FILE *fic=NULL; //le type FILE
//     // fic=fopen("nbrLivre","r"); // r = le mode read
//     // int val[1];
//     // fread(val,sizeof(int),1,fic);
//     // fclose(fic);
    
//     char ch[2],ch2[3000];
//     int c=0;
//     if (ptrB->nbLivres > 0)
//     {
//         FILE *fic=NULL; //le type FILE
//         fic=fopen("baseLivres","r"); // r = le mode read
//         if (fic!=NULL)
//         {
//             while((ch[0]=fgetc(fic))!=EOF)
//             {
//                 if(c==0)
//                 {
//                     printf("%c \n", ch[0]);
//                     strcat(ch2,ch);
//                     c++;
//                 }
//                 else
//                 {

//                     if(ch[0]=='\n')
//                     {
//                         printf("\n %c",ch2[1]);
//                         fflush(stdin);
//                         fclose(fic);
//                     }
//                     strcat(ch2,ch);
//                     printf("%c\n", ch[0]);
//                     c++;
//                 }
//             }
//         }
//         printf("fin \n");
//         fclose(fic);
//     }
// }


void trieTitre(T_Bibliotheque *ptrB)
{
    // printf("commencement \n");
    // FILE *fic=NULL; //le type FILE
    // fic=fopen("nbrLivre","r"); // r = le mode read
    // int val[1];
    // fread(val,sizeof(int),1,fic);
    // fclose(fic);
    
    char ch,ch2[3000],ch3[3000];
    int compteur=0 , beta=0;
    if (ptrB->nbLivres > 0)
    {
        FILE *fic=NULL; //le type FILE
        fic=fopen("baseLivres","r"); // r = le mode read
        if (fic!=NULL)
        {
             while (fgets(ch2,3000, fic) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
                        {
                            printf("%s", ch2); // On affiche la chaîne qu'on vient de lire
                            fflush(stdin);
                        }
            while (beta < 1)
            { 
                for(int i=0;i<2 ;i++)
                {
                    fseek(fic,compteur*188, SEEK_SET);
                    fgets(ch3 ,30000 ,fic);
                    
                    fflush(stdin);
                    if(strcmp(ch2, ch3) < 0)
                        {
                            strcpy(ch3,ch2);
                            compteur++;
                        }
                        fgets(ch3 ,30000 ,fic);
                        fflush(stdin);
                    
                }
                    fseek(fic,compteur*188, SEEK_SET);
                    fgets(ptrB->etagere[0].titre, MAX_TITRE, stdin);
                    fflush(stdin);
                    printf("a\n");
                    fseek(fic,86+compteur*188, SEEK_SET);
                    fgets(ptrB->etagere[0].code, MAX_CODE, stdin);
                    fflush(stdin);

                    fseek(fic,60+compteur*188, SEEK_SET);
                    fgets(ptrB->etagere[0].auteur, MAX, stdin);
                    fflush(stdin);

                    scanf("%d", &ptrB->etagere[0].annee);
                    fflush(stdin);

                    fgets(ptrB->etagere[0].editeur, MAX, stdin);
                    fflush(stdin);

                    formaterTexte(ptrB->etagere[0].editeur);
                    ptrB->etagere[0].editeur[101]='!' ;
                    beta++;
                    sauvegardeTri(&ptrB);
            }
        }
        printf("fin \n");
        fclose(fic);
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
// Nom fonction : listeLivreDispo
// Description : Lister les livres disponible actuellement dans la bibliothèque
// Entrée : pointeur vers une bibliothèque
// Sortie : 
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

// 12 - Lister les emprunts en retard
// Nom fonction : ListeLivreRetard
// Description : Lister les livres qui sont en retard de restitution (temps d'emprunt dépasse 7 jours)
// Entrée : pointeur vers une bibliothèque
// Sortie :
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
// Nom fonction : listeEmpruntPers
// Description : Lister les emprunts en cours d'une personne
// Entrée : pointeur vers une bibliothèque et chaine de caractère contenant le nom de l'emprunteur souhaité
// Sortie : 
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
// Nom fonction :  dernierLivreEmprunt
// Description : Fonction qui affiche le dernier livre emprunté dans la bibliothèque
// Entrée : Pointeur vers une bibliothèque
// Sortie : 
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
// Nom fonction : dernierEmprunt
// Description : Fonction affiche la dernière fois qu'un livre a été emprunté
// Entrée : Pointeur vers une bibliothèque et position du livre recherché
// Sortie : 
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

// Nom fonction : formaterTexte
// Description : Permet ici d'enlever les majuscules en milieu de mot qui peut gener si on cherche le livre et mettre la premiere lettre en majuscule
// Entrée : texte à formater
// Sortie :
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

// Nom fonction : rechercherCode
// Description : Permet de rechercher la position d'un livre dans la bibliothèque avec son code
// Entrée : pointeur vers une bibliothèque et code du livre recherché
// Sortie : renvoie la position du livre dans la bibliothèque
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
