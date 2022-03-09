// TP GESTION D'UNE BIBLIOTHEQUE 
#include "biblio.h"

#define _DEBUG_


int menu()
{

	int choix;
// au programme du TP7 :
printf("\n\n  1 - ajouter un nouveau livre dans la bibliotheque "); 
printf("\n  2 - afficher tous les livres de la bibliotheque "); 
printf("\n  3 - rechercher un livre (par son titre)");  // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
printf("\n  4 - rechercher et afficher tous les livres d'un auteur");
printf("\n  5 - supprimer un livre de la bibliotheque");
printf("\n  6 - emprunter un livre de la bibliotheque");
printf("\n  7 - restituer/rendre un livre de la bibliotheque");
printf("\n  8 - trier les livres (par titre)");
printf("\n  9 - trier les livres (par auteur)");
printf("\n 10 - trier les livres (par annee)");
printf("\n 11 - lister les livres disponibles ");
printf("\n 12 - lister les emprunts en retard "); //on suppose qu'un emprunt dure 7 jours.
printf("\n 13 - lister les emprunts de la personne "); 
printf("\n 14 - lister le dernier livre emprunté");
printf("\n 15 - lister le dernier emprunt d'un livre en particulier");
printf("\n 16 - nombre de fois qu'un livre a été emprunté");
printf("\n 17 - ajouter du stock aux livres présents");

printf("\n  0 - QUITTER");
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

#ifndef DEBUG
	chargement(&B);
#endif 

do
{
chx= menu();
switch(chx)
	{
	case  1 : //ajouter un nouveau livre dans la bibliotheque
			reponse = ajouterLivre(   &B  );
			if (reponse==1)
				printf(" ajout reussi !!");
			else
				printf("impossible d ajouter (bibliotheque pleine)");
			break;

	case 2 : //afficher tous les livres de la bibliotheque
			reponse=afficherBibliotheque(&B);
			if (reponse==0)	
					printf("La bibliotheque est vide \n");
			break;	
	
	case 3 : //rechercher un livre (par son titre)
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

	case 4 : //rechercher et afficher tous les livres d'un auteur
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

	case 5 : //supprimer un livre de la bibliotheque
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

	case 6 : //emprunter un livre de la bibliotheque
			if(B.nbLivres > 0 && B.nbLivresDispo > 0)
			{
				printf("Saisissez le code du livre que vous voulez emprunter:\n");
				fgets(codeRecherche, MAX_CODE, stdin);
				fflush(stdin);
				reponse = rechercherCode(&B,codeRecherche);
				if (reponse >= 0)
				{
					printf("Saisissez votre nom \n");
					fgets(nomEmprunteur, 50, stdin);
					formaterTexte(nomEmprunteur);
					fflush(stdin);
					emprunterLivre(&B, nomEmprunteur, reponse);
					nombreLivresEmpruntes++;
				}
				else
				{
					printf("Ce livre ne se trouve pas dans la bibliothèque \n");
				}
			}
			else
			{
				printf("\n La bibliothèque est vide \n");
			}
			break;

	case 7 : //restituer/rendre un livre de la bibliotheque
			if (nombreLivresEmpruntes > 0 )
			{
				printf("Saisissez le code du livre que vous souhaitez rendre \n");
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
					printf("Le livre ne provient pas de la bibliothèque\n");
				}
			}
			else 
			{
				printf("Aucun livre n'a été emprunté \n");
			}
			break;

	case 8 : //trier les livres (par titre)
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

	case 9 : //trier les livres (par auteur)
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

	case 10 : //trier les livres (par annee)
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

	case 11 : //lister les livres disponibles
			if (B.nbLivres > 0)
			{
				listeLivreDispo(&B);
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}
			break;

	case 12 : //lister les emprunts en retard
			if (nombreLivresEmpruntes > 0)
			{
				ListeLivreRetard(&B);
			}
			else
			{
				printf("Aucun livre n'as été emprunté \n");
			}
			
			break;

	case 13 : //lister les emprunts de la personne
			if (nombreLivresEmpruntes > 0)
			{
				printf("Saisissez le nom recherché : \n");
				fgets(nomEmprunteur, 50, stdin);
				formaterTexte(nomEmprunteur);
				fflush(stdin);
				listeEmpruntPers(&B, nomEmprunteur);
			}
			else
			{
				printf("Aucun livre n'as été emprunté \n");
			}
	
	case 14 : //lister le dernier livre emprunté
			if (B.nbLivres > 0)
			{
				dernierLivreEmprunt(&B);
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}

	case 15 : //lister le dernier emprunt d'un livre en particulier
			if (B.nbLivres > 0)
			{
				printf("Saisissez le code du livre que vous souhaitez \n");
				fgets(codeRecherche, K_MaxCode, stdin);
				fflush(stdin);
				reponse = rechercherCode(&B,codeRecherche);
				if (reponse >= 0)
				{
					dernierEmprunt(&B, reponse);
				}
				else
				{
					printf("Le livre ne se trouve pas dans la bibliothèque \n");
				}
			}
			else
			{
				printf("La bibliothèqye est vide \n");
			}
			break;

	case 16 : //nombre de fois qu'un livre a été emprunté
			if (B.nbLivres > 0)
			{
				printf("Saisissez le code du livre que vous cherchez \n");
				fgets(codeRecherche, K_MaxCode, stdin);
				fflush(stdin);
				reponse = rechercherCode(&B, codeRecherche);
				if (reponse >= 0)
				{
					if (B.etagere[reponse].NbEmprunt > 0)
					{
						printf("Le livre a été empruntés %d fois \n", B.etagere[reponse].NbEmprunt);
					}
					else
					{
						printf("Le livre n'as encore jamais été empruntés \n");
					}
				}
				else
				{
					printf("Le livre ne se trouve pas dans la bibliothèque \n");
				}
			}
			else
			{
				printf("La bibliothèque est vide");
			}
			break;

	case 17 :
			if (B.nbLivres > 0)
			{
				printf("Saisissez le code du livre à restocker : \n");
				fgets(codeRecherche, K_MaxCode, stdin);
				fflush(stdin);
				reponse = rechercherCode(&B,codeRecherche);
				if (reponse >= 0)
				{
					printf("Saisissez la quantité que vous souhaitez ajouter : \n");
					int quantite = 0;
					scanf("%d", &quantite);
					B.etagere[reponse].QuantiteExemplaire = B.etagere[reponse].QuantiteExemplaire + quantite;
					printf("Ajout réussi \n");
				}
				else
				{
					printf("Ce livre ne se trouve pas dans la bibliothèque \n");
				}
			}
			else
			{
				printf("La bibliothèque est vide \n");
			}
			break;

	case 0 :
			break;

	default :
			printf("\nVous n'avez pas saisis une valeur correct\n");
			break;
	
	}

}while(chx!=0);

#ifndef DEBUG
	sauvegarde(&B);
#endif

return 0;

}
