// TP GESTION D'UNE BIBLIOTHEQUE 
#include "biblio.h"

#define _DEBUG_

int menu()
{
	int choix;
// au programme du TP7 :
printf("\n\n 1 - ajouter un nouveau livre dans la bibliotheque "); 
printf("\n 2 - afficher tous les livres de la bibliotheque "); 
printf("\n 3 - rechercher un livre (par son titre)");  // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
printf("\n 5 - supprimer un livre de la bibliotheque");
printf("\n 6 - emprunter un livre de la bibliotheque");
printf("\n 7 - restituer/rendre un livre de la bibliotheque");
printf("\n 8 - trier les livres (par titre)");
printf("\n 9 - trier les livres (par auteur)");
printf("\n 10 - trier les livres (par annee)");
printf("\n 11 - lister les livres disponibles ");
printf("\n 12 - lister les emprunts en retard "); //on suppose qu'un emprunt dure 7 jours.
printf("\n 13 - lister les emprunts de la personne "); 
printf("\n 14 - lister les derniers emprunts");
printf("\n 15 - lister le dernier emprunt d'un livre en particulier");

printf("\n 0 - QUITTER");
printf("\n Votre choix : ");
scanf("%d[^\n]",&choix);getchar();
return choix;


}



int main()
{
int reponse,chx;
T_Bibliotheque B;
T_Titre titreRecherche;
T_Aut auteurRecherche;
T_Code codeRecherche;
int nombreLivresEmpruntes = 0;
char nomEmprunteur[50];
init( &B );

#ifndef _DEBUG_
	chargement(&B);
#endif

do
{
chx= menu();
switch(chx)
	{
	case  1 : reponse = ajouterLivre(   &B  );
				if (reponse==1)
					printf(" ajout reussi !!");
					else
					printf("impossible d ajouter (bibliotheque pleine)");
			break;
	case 2 : reponse=afficherBibliotheque(&B);
			if (reponse==0)	
					printf("La bibliotheque est vide \n");
			break;	
	
	case 3 :
			if (B.nbLivres != 0)
			{
				printf("Saisissez le titre que vous cherchez : ");
				fgets(titreRecherche, K_MaxTit, stdin);
				formaterTexte(titreRecherche);
				reponse = rechercherLivre(&B, titreRecherche);
				if (reponse == 0)
				{
					printf("\nLe livre ne se trouve pas dans la bibliothèque \n");
				}
				
			}
			else
			{
				printf("\nLa bibliothèque est vide \n");
			}
			break;

	case 4 :
			if (B.nbLivres != 0)
			{
				printf("Saisissez le nom de l'auteur que vous cherchez : ");
				fgets(auteurRecherche, K_MaxAut, stdin);
				formaterTexte(auteurRecherche);
				reponse = rechercherAuteur(&B, auteurRecherche);
				if (reponse == 0)
				{
					printf("\nAucun livre de cette auteur ne se trouve dans la bibliothèque");
				}
				
			}
			else
			{
				printf("\nLa bibliothèque est vide \n");
			}
			break;

	case 5 :
			if (B.nbLivres > 0)
			{
				printf("Saisissez le code du livre que vous souhaitez supprimer : \n");
				fgets(codeRecherche, K_MaxCode, stdin);
				reponse = supprimerLivre(&B, codeRecherche);
				if (reponse >= 0)
				{
					printf("Le livre se trouvait à la position %d \n", reponse);
					printf("Supression avec succès \n");
				}
				else
				{
					printf("\nCe livre ne se trouve pas dans la bibliothèque\n");
				}
				
			}
			else
			{
				printf("\n La bibliothèque est vide \n");
			}
			break;

	case 6 : 
			if(B.nbLivres > 0)
			{
				printf("Saisissez le code du livre que vous voulez emprunter:\n");
				fgets(codeRecherche, MAX_CODE, stdin);
				fflush(stdin);
				reponse = rechercherCode(&B,codeRecherche);
				if (reponse >= 0)
				{
					printf("Saisissez votre nom \n");
					fgets(nomEmprunteur, 50, stdin);
					fflush(stdin);
					emprunterLivre(&B, nomEmprunteur, reponse);
					nombreLivresEmpruntes++;
				}
				else
				{
					printf("Ce livre ne se trouve pas dans la bibliothèque \n");
				}
				
				// emprunterLivre(&B);
				// nombreLivresEmpruntes++;
				// emprunterLivre(&B);
				// printf("%s %u %u",B.etagere[1].emprunteur.nomemprunteur,B.etagere[1].emprunteur.lejour,B.etagere[1].emprunteur.lemois);
			}
			else
			{
				printf("\n La bibliothèque est vide \n");
			}
			break;

	case 7 :
			if (nombreLivresEmpruntes > 0 )
			{
				printf("Saisissez le livre que vous rendez \n");
				fgets(codeRecherche, K_MaxCode, stdin);
				reponse = restituerLivre(&B, codeRecherche);
				if (reponse >= 0)
				{
					printf("Le livre a été restituer à la place %d \n", reponse+1);
					printf("Restitution avec succès\n");
					nombreLivresEmpruntes--;
				}
				else
				{
					printf("Le livre ne se trouve pas dans la bibliothèque\n");
				}
			}
			else 
			{
				printf("Aucun livre n'a été emprunté \n");
			}
			break;

	case 8 : 
			if (B.nbLivres > 0)
			{
				trieTitre(&B);
				printf("Bibliothèque trié par titre avec succès \n");
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}
			break;

	case 9 :
			if (B.nbLivres > 0)
			{
				trieAuteur(&B);
				printf("Bibliothèque trié par auteur avec succès \n");
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}
			break;

	case 10 :
			if (B.nbLivres > 0)
			{
				trieAnnee(&B);
				printf("Bibliothèque trié par année avec succès \n");
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}
			break;

	case 11 :
			if (B.nbLivres > 0)
			{
				listeLivreDispo(&B);
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}
			break;

	case 13 :
			if (nombreLivresEmpruntes > 0)
			{
				printf("Saisissez le nom recherché : \n");
				fgets(nomEmprunteur, 50, stdin);
				fflush(stdin);

			}
			else
			{
				printf("Aucun livre n'as été emprunté ")
			}

	case 0 :
			break;

	default :
			printf("\nVous n'avez pas saisis une valeur correct\n");
			break;
	
	}

}while(chx!=0);

#ifndef _DEBUG_
	sauvegarde(&B);
#endif

return 0;

}
