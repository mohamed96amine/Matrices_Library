
#include "CParser.h"



/**************************************************************
* Methode qui lit un fichier et renvoie la matrice associ�e
**************************************************************
*
* Entree: Le nom du fichier .
* sortie: Un Objet CMatrice.
* necessite: n�ant.
* entraine: (La matrice du ficheir est retourn�e ) ou 
	ou (Exception FICHIER_INTROUVABLE : si le fichier est introuvable) 
	ou (Exception EXCEPTION_TYPE_MATRICE
			   ou EXCEPTION_NB_LIGNES
			   ou EXCEPTION_ACCOLADE_OUVRANTE
			   ou EXCEPTION_ACCOLADE_FERMANTE
			   ou EXCEPTION_NB_COLONNES
			   ou EXCEPTION_NB_LIGNES  : si il y'a un probl�me de syntaxe).
*/
CMatrice<double> *CParser::PARLireFichier(char * PARNomFichier){
	fstream pfFichier;
	pfFichier.open(PARNomFichier);
	unsigned int uiLignes, uiColonnes, uiBoucle1, uiBoucle;
	CMatrice<double> *MATObjet = new CMatrice<double>(); // On cr�e un nouveau objet matrice qui sera retourn�
	double *pdElements;
	if (pfFichier.is_open()){			// On ouvre le fichier
		if(PARVerifier("TypeMatrice=double",pfFichier)) {		// on verifie que la premi�re ligne est bien TypeMatrice=double
			if(PARVerifier("NBLignes=",pfFichier)){			// on verifie que la deuxi�me ligne est bien NBLignes=
				uiLignes = PARExtraireNombre(pfFichier);	// On lit le le nombre de colonnes du fichier
				if(uiLignes <= 0){							// si le nombre de lignes est negatif
					CException  EXEObjet(EXCEPTION_NB_LIGNES, "Erreur syntaxe, nombre de lignes inferieure � 0.");
					throw EXEObjet;
				}

				if(PARVerifier("NBColonnes=",pfFichier)){	// on verifie que la troisi�me ligne est bien NBLignes=
					uiColonnes = PARExtraireNombre(pfFichier);	// on lit le le nombre de colonnes du fichier
					if(uiColonnes <= 0){
						CException  EXEObjet(EXCEPTION_NB_COLONNES, "Erreur syntaxe, nombre de colonnes inferieure � 0.");
						throw EXEObjet;
					}
					if(PARVerifier("Matrice=[",pfFichier)){ 
						MATObjet = new CMatrice<double>(uiLignes, uiColonnes);
						for(uiBoucle= 0; uiBoucle < uiLignes ; uiBoucle++){
							pdElements = PARLireColonnes(pfFichier, uiColonnes);
							for(uiBoucle1 = 0; uiBoucle1 < uiColonnes ; uiBoucle1++){
								(*MATObjet).MATModifierValeur(uiBoucle, uiBoucle1, pdElements[uiBoucle1]);
							}
						}
						if(!PARVerifier("]",pfFichier)){
							CException  EXEObjet(EXCEPTION_ACCOLADE_FERMANTE, "accolade fermante manquante!");
							throw EXEObjet;
						}
					}else{
						CException  EXEObjet(EXCEPTION_ACCOLADE_OUVRANTE, "utilisez Matrice=[");
						throw EXEObjet;
					}
				}
			}else{
				CException  EXEObjet(EXCEPTION_NB_LIGNES, "utilisez NBLignes=");
				throw EXEObjet;
			}
		}else{
			CException  EXEObjet(EXCEPTION_TYPE_MATRICE, "Le type de matrice donn� n'est pas pris en charge utilisez TypeMatrice=double");
			throw EXEObjet;
		}
		pfFichier.close(); // on ferme le fichier.
	}else{
		CException  EXEObjet(FICHIER_INTROUVABLE, "le fichier est introuvable");
		throw EXEObjet;
	}
	return MATObjet;
}

/**************************************************************
* Methode qui verifie l'existence d'une chaine de caract�re dans un fichier.
**************************************************************
*
* Entree: La chaine de caract�re et le fichier.
* sortie: Un bool�an.
* necessite: n�ant.
* entraine: retourne Vrai si la chaine est dans le fichier , Faux sinon .
*/
bool CParser::PARVerifier(char *pChaine, fstream &fichier){
	char cChar = fichier.get();
	while(cChar == ' ' || cChar == '\n' || cChar == '\t'){
		cChar = fichier.get();
	}
	if(cChar != pChaine[0]){
		return false;
	}
	for(unsigned int uiBoucle = 1; uiBoucle < strlen(pChaine) ; uiBoucle++){
		
		if(fichier.get() != pChaine[uiBoucle]){
			return false;
		}
	}
	return true;
}



/**************************************************************
* Methode qui Extrait un nombre du fichier.
**************************************************************
*
* Entree: Le fichier.
* sortie: Un entier.
* necessite: n�ant.
* entraine: (l'entier dans le fichier est retourn�) ou 
			(Exception EXCEPTION_NB_COLONNES_OU_LIGNES_INVALIDE si le nombre n'est pas valide(negatif ou un caract�re a la place du nombre)).
*/
int CParser::PARExtraireNombre(fstream &fichier){

	char  pcNombre[30];
	unsigned int uiIndice;
	char c = fichier.get();
	while(c == ' ' || c == '\n' || c == '\t'){
		c = fichier.get();
	}
	if('0' <= c && c <= '9'){
		pcNombre[0] = c;
		c = fichier.peek();
		uiIndice = 1;
		while('0' <= c && c <= '9'){
			pcNombre[uiIndice] = fichier.get();
			c = fichier.peek();
			uiIndice++;
		}
		return atoi(pcNombre);
	}else{
		CException  EXEObjet(EXCEPTION_NB_COLONNES_OU_LIGNES_INVALIDE, "le nombre de lignes ou de colonnes est invalide.");
		throw EXEObjet;
	}
}

/**************************************************************
* Methode qui lit un tableau de colonnes.
**************************************************************
*
* Entree: Le fichier et le nombre de colonnes.
* sortie: Un tableau de double.
* necessite: n�ant.
* entraine: (le tableau des colonnes est retourn� ) ou 
			(Exception EXCEPTION_NB_COLONNES ).
*/
double* CParser::PARLireColonnes(fstream &fichier, unsigned int uiNbColonnes){
	double * pdElements; // le tableau de double retourn� 
	unsigned int uiIndice, uiBoucle, uiIndiceTab; 
	char pcLigne[1000]; // Variable qui stocke une ligne
	char pcNombre[100]; // chaine de caract�re qui contient le nombre � convertir en double
	char cChar = fichier.peek(); // lire le caract�re suivant
	while(cChar == ' ' || cChar == '\n' || cChar == '\t'){  // Avancer dans le fichier si le caract�re est un espace.
		fichier.get();
		cChar = fichier.peek(); 
	}
	fichier.getline(pcLigne, 1000); // lire toute la ligne
	uiIndiceTab = uiIndice = 0;
	pdElements = (double *)malloc(sizeof(double)*uiNbColonnes);  // On alloue la m�moire
	while(pcLigne[uiIndice] != '\0' ){ // parcourir la chaine 
		uiBoucle = 0;
		if(pcLigne[uiIndice] == '-'){ // si le nombre est negatif
			pcNombre[uiBoucle] ='-';
			uiBoucle++;
			uiIndice++;
		}
		if(pcLigne[uiIndice] <= '9' && '0' <= pcLigne[uiIndice]){
			
			pcNombre[uiBoucle] = pcLigne[uiIndice];
			uiIndice++;
			uiBoucle++;
			while((pcLigne[uiIndice] <= '9' && '0' <= pcLigne[uiIndice])  ){
				pcNombre[uiBoucle] = pcLigne[uiIndice];
				uiBoucle++;
				uiIndice++;
			}
			if(pcLigne[uiIndice] == '.'){ // nombre � virgule
				pcNombre[uiBoucle] = '.';
				uiBoucle++;
				uiIndice++;
			}
			while((pcLigne[uiIndice] <= '9' && '0' <= pcLigne[uiIndice])  ){
				pcNombre[uiBoucle] = pcLigne[uiIndice];
				uiBoucle++;
				uiIndice++;
			}
			if(uiIndiceTab >= uiNbColonnes){ // lever une exception si le nombre de colonnes ne correspond pas � NBCOLONNES.
				CException  EXEObjet(EXCEPTION_NB_COLONNES, "La taille de la ligne ne correspond pas a la taille donn�e.");
				throw EXEObjet;
			}
			pdElements[uiIndiceTab] = atof(pcNombre); // On convertit la chaine de caract�re en double.
			uiIndiceTab++;
			for(int i =0; i< 100;i++)pcNombre[i] = '\0'; // On vide la chaine de caract�re
		}
		else
		{
			uiIndice++;
		}	
	}
	return pdElements;		
}