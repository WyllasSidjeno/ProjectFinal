/*
Auteur : Christopher Perreault
Version : 2.0
Description du jeu :
				Le jeu est compris d'un certain nombre de rounds (Habituellement 10) où l'utilisateur doit choisir dans une banque de donnée de couleurs (normalement 6) un certain nombre de couleur (habituellement 4).
				Si il n'y arrive pas après le nombre de round, alors il perd la partie.
				Le jeu inclus :
								- Une évaluation automatique permettant de savoir si les couleurs de l'utilisateur sont soit bien placé ou mal placé dépendant du choix que celui-ci a effectué.
								- La possibilité de retourner en arrière avec la touche backspace du clavier.
								- Une écran de victoire si il y a lieu et une écran de défaute si il y a lieu.
								- Une affichage montrant les informations classés en colonnes ajustable (Si jamais les valeurs viendraient à changer) qu'à partir de la section des variables modifiables.
								- La possibilité de ne pas faire évaluer son choix de couleurs si l'utilisateur change d'avis.
Étapes :
		1) Afficher le menu
		2) Prendre l'entrée de l'utilisateur
		3) Évaluer la série de l'utilisateur et celle aléatoire du programme.
		4) Affiche le nombre de caractère soit bien placées soit mal placées et s'assure de mettre fin au jeu si celui-ci est terminé
		5) Affiche le message de fin du jeu.
*/

#include <iostream>
#include <iomanip>
#include <conio.h>	
#include <string>
#include <H:\Programmation\TI\TI\cvm 21.h>
#include <windows.h>

using namespace std;

int main()
{
	//** Valeurs modifiables   Ces valeurs peuvent être modifié afin de changer le jeu. Aucune donnée autre que ceux-ci ont besoin d'être modifiée pour ajuster le reste du jeu.
	const int NBCOULEURS = 6;
	string Couleurs[NBCOULEURS] = { "(R)ouge", "(V)ert", "(B)leu", "(J)aune", "(M)auve" , "(C)yan" };
	char choixCouleur[NBCOULEURS] = { 'R', 'V', 'B', 'J', 'M', 'C' };
	const int NBESSAIETOTAL = 10;																				
	const int NBCHARACDEMANDE = 4;

	//** Menu et affichage principale || Dans tout les cas, larg_variable est égale à la largeur(x) de la variable et haut_variable est égale à la hauteur(y) de la variable
	const string SPACER = " , ";		// Fait de l'espacement entre les couleurs.

	const string titre = "JEU DES COULEURS";
	const int larg_titre = (120 - titre.size()) / 2,	haut_titre = 1;

	const string reglagetitre = "R\220GLAGES DE LA PARTIE";
	const int haut_reglagetitre = haut_titre + 3,		larg_reglagetitre = (120 - reglagetitre.size()) / 2;

	const string messagedebogage = "Activer le mode en d\202bogage ? (O/N) : ";
	int larg_messagedebogage = ((120 - messagedebogage.size()) / 2) - messagedebogage.size(),	haut_messagedebogage = haut_reglagetitre + 1;

	int larg_Couleur = 9,	haut_Couleur =	haut_titre + 4;		// Positionnement pour le placement des couleurs
	int larg_header	= 9	,	haut_Header	 =	haut_Couleur + 3;	// Positionnement pour l'entête du programme # Essais Bien placées Mal places
	int haut_essai1 = haut_Header + 2, larg_essai1 = 14;		// Positionnement du début de l'entrée de l'utilisateur
	int larg_messageEvaluation = 2,		haut_messageEvaluation = 14 + NBESSAIETOTAL;; // Positionnement de la demande d'évaluation.

	string messageCodeSecret = "Code Secret :";
	int larg_codeSecret = ((120 - messageCodeSecret.size()) / 2) + messageCodeSecret.size() - NBCHARACDEMANDE, haut_codeSecret = 15 + NBESSAIETOTAL;

	int larg_bienPlacees = 25 + (NBCHARACDEMANDE * 2), larg_malPlacees = 42 + (NBCHARACDEMANDE * 2);	//Positionnement du bien placée et du mal placées
	//** Tableaux
	char CouleurChoisie[NBCHARACDEMANDE] = {};		// Choix des couleurs de l'utilisateur
	char CodeSecret[NBCHARACDEMANDE] = {};			// Les couleurs choisis aléatoirement par le jeu

	bool characCodeDejaVerifie[NBCHARACDEMANDE];	// Valeur booléenne qui indique si l'emplacement du code a déjà été vérifié pour éliminer les doublons dans les bien et mal placées.

	//** BOOL et Confirmations
	bool evaluer = false;								// Mentionne si l'utilisateur souhaite évaluer ou non.
	bool characInvalide = true;							// Informe si le charactère utilisé actuellement est invalide ou non. Débute par invalide.
	bool FinJeu = false;								// Informe si le jeu est terminé, échec ou réussite.

	char confirmationdebogage;							// Char qui confirme la demande de débogage, doit être répondu par O/N
	char characEvaluation;								// Char qui confirme la demande d'évaluation. doit être répondu par O/N

	//** Valeurs de jeu
	int bienPlacees, malPlacees;						// Le nombre de couleur mal et bien placéesplacées.
	int repetition;										// Le nombre de répétition consécutive d'essaie. S'enclenche après une évaluation terminée seulement.

	srand(int(time(0)));								// Initialise la table le générateur de nombre aléatoire avec comme seed le temps de la machine.

	
	// 1) Afficher le menu de débogage ainsi que le menu titre et les valeurs aléatoires. 
	//  Et demande si l'utilisateur souhaite débogger ou non.

	for (int i = 0; i < NBCHARACDEMANDE; ++i)
		CodeSecret[i] = choixCouleur[rand() % NBCOULEURS];

	gotoxy(larg_titre, haut_titre);	// ------------------// 1.1) Affichage du menu titre.
	cout << titre;

	gotoxy(larg_reglagetitre, haut_reglagetitre); //----// 1.2) Affichage du sous-titre des réglages
	cout << reglagetitre;

	gotoxy(larg_messagedebogage, haut_messagedebogage);	// 1.3) Affichage de la demande de déboggage­ à l'utilisateur et s'assure qu'il répondent une valeur valide avec le do while
	cout << messagedebogage;
	do
	{
		confirmationdebogage = toupper(_getch());
	} while(confirmationdebogage != 'O' && confirmationdebogage != 'N');
		
	gotoxy(larg_reglagetitre, haut_reglagetitre); //---// 1.4) Nettoie l'écran après la prise de réponse sur le déboggage
	clreoscr();

	if (confirmationdebogage == 'O') //----------------// 1.5) Affiche le code secret si l'utilisateur a répondu oui.
	{
		gotoxy(larg_codeSecret, haut_codeSecret);
		cout << messageCodeSecret;
		for (int i = 0; i < NBCHARACDEMANDE; ++i)
			cout << " " << CodeSecret[i];
	}

	gotoxy(larg_Couleur, haut_Couleur);	//-------------// 1.6) Affiche les choix de couleurs. (R)ouge, ...
	for (int i = 0; i < NBCOULEURS; ++i)
		if (i == (NBCOULEURS - 1))
			cout << Couleurs[i];
		else
			cout << Couleurs[i] << SPACER;

	gotoxy(larg_header, haut_Header);	//-------------// 1.7) Affiche le header
	cout << '#' << setw(larg_header / 2) << "" << "Essais" << setw(NBCHARACDEMANDE*2) << "" << "Bien plac\202e(s)" << setw(larg_header / 2) << "" << "Mal plac\202e(s)";

	gotoxy(larg_header, haut_essai1);	//-------------// 1.8) Affiche toutes les cases de choix dans le format 1) 2) 3) .. etc
	for (int i = 0; i < NBESSAIETOTAL; ++i)	
	{
		gotoxy(larg_header - 2, haut_essai1 + i);
		cout << setw(2) << i+1 << ")";
	}

	repetition = 0;	// Représente le nombre de fois que le code a été répété.

	// 2) Prend l'entrée de l'utilisateur afin de le comparer avec le code secret. Elle se répète si l'utilisateur ne souhaite pas évaluer et recule s'il souhaite effacer.
	do
	{
		do
		{
			evaluer = false;
			for (int positionnement = 0; positionnement < NBCHARACDEMANDE; ++positionnement) 
			{
				characInvalide = true;
				gotoxy(larg_essai1 + (positionnement * 2), haut_essai1 + repetition), clreol();

				do 
				{
					CouleurChoisie[positionnement] = toupper(_getch());

					if (CouleurChoisie[positionnement] == '\b')
					{
						if (positionnement > 0)
							positionnement -= 2;
						else
							positionnement -= 1;
						characInvalide = false;
					}
					else
						for (int couleur = 0; couleur < NBCOULEURS; ++couleur)
							if (CouleurChoisie[positionnement] == choixCouleur[couleur])
							{
								characInvalide = false;
								cout << CouleurChoisie[positionnement];
							}
				} while (characInvalide);
			}

			gotoxy(larg_messageEvaluation, haut_messageEvaluation); // 2.7) Demande si l'utilisateur souhaite évaluer. Doit être répondu par oui ou non avec le do while suivant. Aucune autre entrée permise. Affiche la réponse par la suite.
			cout << "\220valuer ? (O/N) : ";
			do
			{
				clreol();
				characEvaluation = toupper(_getch());
			} while (characEvaluation != 'O' && characEvaluation != 'N');
			cout << characEvaluation;

			if (characEvaluation == 'O')
				evaluer = true;
		} while (evaluer == false);

		
		for (int i = 0; i < NBCHARACDEMANDE; ++i)
			characCodeDejaVerifie[i] = false;
		bienPlacees = 0, malPlacees = 0;

		for (int i = 0; i < NBCHARACDEMANDE; ++i)
			if (CouleurChoisie[i] == CodeSecret[i])
			{
				++bienPlacees;
				characCodeDejaVerifie[i] = true;
			}
			else
				for (int n = 0; n < NBCHARACDEMANDE; ++n)
					if (CouleurChoisie[i] == CodeSecret[n] && characCodeDejaVerifie[n] == false && CouleurChoisie[n] != CodeSecret[n])
					{
						++malPlacees;
						characCodeDejaVerifie[n] = true;
						break;
					}

		// 4) Affiche le nombre de caractère qui sont bien placées et/ou mal placées.
		gotoxy(larg_bienPlacees, haut_essai1 + repetition);
		cout << bienPlacees;
		gotoxy(larg_malPlacees, haut_essai1 + repetition);
		cout << malPlacees;

		// 5) S'informe si l'utilisateur a soit gagné (En ayant eu tout son code bien placées ) ou perdu (S'il a dépassé le nombre d'essaie permise)
		if (bienPlacees == NBCHARACDEMANDE || repetition >= NBESSAIETOTAL-1)
			FinJeu = true;

		++repetition; // Augmente la répétition du programme
	} while (FinJeu == false);

	// 6) Affiche soit le message de réussite, soit le message d'échec et laisse un certain temps à l'utilisateur afin de pouvoir visualiser le message.
	gotoxy(larg_messageEvaluation, haut_messageEvaluation);
	clreol();
	if(bienPlacees >= NBCHARACDEMANDE)
		cout << " Bravo, vous avez gagn\202 !  :)";
	else
		cout << " Vous avez perdu !  :( ";
	Sleep(5000);
}