// TP GESTION D'UNE BIBLIOTHEQUE 
#include "biblio.h"

int menu()
{
	int choix;
// au programme du TP7 :
printf("\n\n 1 - ajouter un nouveau livre dans la bibliotheque "); 
printf("\n 2 - afficher tous les livres de la bibliotheque "); 
printf("\n 3 - rechercher un livre (par son titre)");  // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
printf("\n 5 - supprimer un livre de la bibliotheque");
// si les 5 choix ci dessus sont bien codés, modifiez votre structure T_Livre et passez à 5 champs (avec cote,editeur et annee)


// au programme du TP8 :
// ajouter le champ emprunteur à votre structure T_Livre
/*
printf("\n 6 - emprunter un livre de la bibliotheque");
printf("\n 7 - restituer/rendre un livre de la bibliotheque");
printf("\n 8 - trier les livres (par titre)");
printf("\n 9 - trier les livres (par auteur)");
printf("\n 10 - trier les livres (par annee)");
*/
// si les 5 choix (6-10) sont bien codés, changez le type T_Emp et remplacez-le par la structure T_Emp visible dans livre.h
// vous pourrez alors faire les menus 11,12,etc...
// printf("\n 11- lister les livres disponibles "); 
// printf("\n 12 - lister les emprunts en retard "); //on suppose qu'un emprunt dure 7 jours.
// printf("\n 13 - ... imaginez vous même vos propres fonctionnalités ")

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
init( &B );
chargement(&B);
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

	default :
			printf("\nVous n'avez pas saisis une valeur correct\n");
			break;
	
	
	}

}while(chx!=0);


sauvegarde(&B);



return 0;

}
