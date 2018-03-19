#ifndef CMATRICE_H
#define CMATRICE_H
#define HORS_LIMITE 20
#define TAILLE_MATRICES_DIFFERENTES 21
#define DIVISION_PAR_ZERO 21

template <class T>
class CMatrice{

protected:

	unsigned int uiMATLignes; // attribut pour le nombre de lignes
	unsigned int uiMATColonnes; // attribut pour le nombre de colonnes
	T **ptMATElements; // le tableau des valeurs 

public:

	CMatrice();
	CMatrice(CMatrice<T> const &);
	CMatrice(unsigned int, unsigned int);
	~CMatrice();


	//Getters : 
	unsigned int MATLireLignes();
	unsigned int MATLireColonnes();
	T MATLireValeur(unsigned int , unsigned int);

	//Setters: 
	void MATModifierValeur(unsigned int, unsigned int, T);

	//Methode d'affichage : 
	void MATAfficher();

	//Operations : 
	CMatrice<T>& MATTransposee();

	//Operateurs : 
	CMatrice<T>& operator+(CMatrice<T> const&);
	CMatrice<T>& operator-(CMatrice<T> const&);
	CMatrice<T>& operator*(CMatrice<T> const&);
	CMatrice<T>& operator*(double);
	CMatrice<T>& operator/(double);
	CMatrice<T>& operator=(CMatrice<T> const&);
	bool operator==(CMatrice<T> const&);
	bool operator!=(CMatrice<T> const&);
	CMatrice<T>& operator+=(CMatrice<T> const&);
	CMatrice<T>& operator-=(CMatrice<T> const&);
	CMatrice<T>& operator*=(CMatrice<T> const&);
	CMatrice<T>& operator*=(double);
	CMatrice<T>& operator/=(double);
	
};

/**************************************************************
* Constructeur par defaut.
**************************************************************
*
* Entree: néant
* sortie: néant
* necessite: néant
* entraine: Initialise l'objet.
*/
template <class T>
CMatrice<T>::CMatrice(){
	uiMATLignes = 0;
	uiMATColonnes = 0;
	ptMATElements = NULL;
}

/**************************************************************
* Constructeur de recopie.
**************************************************************
*
* Entree: Objet CMatrice.
* sortie: Objet CMatrice.
* necessite: néant.
* entraine: Crée un nouveau objet CMatrice identique a l'objet passé en paramètre.
*/
template <class T>
CMatrice<T>::CMatrice(CMatrice<T>const& MATObjetParam){
	uiMATLignes = MATObjetParam.uiMATLignes;
	uiMATColonnes = MATObjetParam.uiMATColonnes;
	ptMATElements = (T **) malloc (uiMATLignes * sizeof(T));
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		ptMATElements[uiBoucle1] = (T *) malloc(uiMATColonnes * sizeof(T));
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			ptMATElements[uiBoucle1][uiBoucle2] = MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2];
		}
	}
}


/**************************************************************
* Constructeur .
**************************************************************
*
* Entree: Le nombre de lignes et de colonnes.
* sortie: Objet CMatrice.
* necessite: néant.
* entraine: Un nouveau Objet CMatrice est Créé.
*/
template <class T>
CMatrice<T>::CMatrice(unsigned int uiMATLigneParam, unsigned int uiMATColonneParam){
	uiMATLignes = uiMATLigneParam;
	uiMATColonnes = uiMATColonneParam;
	ptMATElements = (T **) malloc (uiMATLigneParam * sizeof(T));
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLigneParam ; uiBoucle1++){
		ptMATElements[uiBoucle1] = (T *) malloc(uiMATColonneParam * sizeof(T));
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonneParam ; uiBoucle2++){
			ptMATElements[uiBoucle1][uiBoucle2] = 0;
		}
	}	
}
/**************************************************************
* Destructeur.
**************************************************************
*
* Entree: néant
* sortie: néant
* necessite: néant
* entraine: Detruit l'objet.
*/
template <class T>
CMatrice<T>::~CMatrice(){
	unsigned int uiBoucle;
	for(uiBoucle = 0; uiBoucle < uiMATLignes; uiBoucle++)
		free(ptMATElements[uiBoucle]);
	free(ptMATElements);
}
/**************************************************************
*  Methode qui retourne le nombre de lignes.
**************************************************************
*
* Entree: néant
* sortie: unsigned int le nombre de lignes.
* necessite: néant
* entraine: retourne le nombre de lignes.
*/
template <class T>
unsigned int CMatrice<T>::MATLireLignes(){
	return uiMATLignes;
}
/**************************************************************
* Methode qui retourne le nombre de colonnes.
**************************************************************
*
* Entree: néant.
* sortie: unsigned int le nombre de colonnes.
* necessite: néant.
* entraine: retourne le nombre de colonnes.
*/
template <class T>
unsigned int CMatrice<T>::MATLireColonnes(){
	return uiMATColonnes;
}
/**************************************************************
* Methode qui retourne la valeur a une position donnée.
**************************************************************
*
* Entree: La ligne et la colonne de la valeur.
* sortie: La valeur.
* necessite: néant.
* entraine: (retourne la valeur qui se trouve à la position passée en paramètre )
	ou (Exception HORS_LIMITE : uiMATLigneParam >= uiMATLignes ou uiMATColonneParam >= uiMATColonnes).
*/
template <class T>
T CMatrice<T>::MATLireValeur(unsigned int uiMATLigneParam, unsigned int uiMATColonneParam){
	if(uiMATLigneParam >= uiMATLignes || uiMATColonnes <=  uiMATColonneParam){
		CException  exception(HORS_LIMITE, "La ligne ou la colonne depasse la taille de la matrice");
		throw exception;
	}
	return ptMATElements[uiMATLigneParam][uiMATColonneParam];
}

/**************************************************************
* Methode qui modfiie la valeur a une position donnée.
**************************************************************
*
* Entree: La ligne , la colonne et la nouvelle valeur.
* sortie: néant.
* necessite: néant.
* entraine: Modifie la valeur qui se trouve à la position passée en paramètre
ou (Exception HORS_LIMITE : uiMATLigneParam >= uiMATLignes ou uiMATColonneParam >= uiMATColonnes).
*/
template <class T>
void CMatrice<T>::MATModifierValeur(unsigned int uiLigne, unsigned int uiColonne, T tElement){
	if(uiLigne >= uiMATLignes || uiColonne >=  uiMATColonnes){
		CException  exception(HORS_LIMITE, "La ligne ou la colonne depasse la taille de la matrice");
		throw exception;
	}
	ptMATElements[uiLigne][uiColonne] = tElement;
}
/**************************************************************
* Methode qui affiche la matrice .
**************************************************************
*
* Entree: néant.
* sortie: néant.
* necessite: néant.
* entraine: Affiche la matrice à l'ecran.
*/
template <class T>
void CMatrice<T>::MATAfficher(){
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++)
	{
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++)
			cout << ptMATElements[uiBoucle1][uiBoucle2] << "\t";
		cout << "\n"<<endl;
	}
}

/**************************************************************
* Methode qui calcule la transposée de la matrice.
**************************************************************
*
* Entree: néant.
* sortie: Un objet CMatrice.
* necessite: néant.
* entraine: La transposée de la matrice est retournée .
*/
template <class T>
CMatrice<T>& CMatrice<T>::MATTransposee()
{
	CMatrice<T> *pMATTemp = new CMatrice (uiMATColonnes, uiMATLignes);
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATColonnes ; uiBoucle1++){
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATLignes ; uiBoucle2++){
			pMATTemp->MATModifierValeur(uiBoucle1, uiBoucle2, ptMATElements[uiBoucle2][uiBoucle1]);
		}
	}
	return *pMATTemp;
}



/**************************************************************
* Operateur + .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie:  Un objet CMatrice.
* necessite: néant.
* entraine: (L'addition des deux matrices est retournée) ou
			(Exception TAILLE_MATRICES_DIFFERENTES les deux matrices n'ont pas la même taille).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator+(CMatrice<T> const&MATObjetParam)
{
	unsigned int uiBoucle1, uiBoucle2;
	if(uiMATLignes != MATObjetParam.uiMATLignes || uiMATColonnes != MATObjetParam.uiMATColonnes){
		CException  exception(TAILLE_MATRICES_DIFFERENTES, "Les deux matrices n'ont pas la même taille pour faire l'operation +.");
		throw exception;
	}
	CMatrice<T> *pMATTemp = new CMatrice (uiMATLignes, uiMATColonnes);
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			pMATTemp->MATModifierValeur(uiBoucle1, uiBoucle2, ptMATElements[uiBoucle1][uiBoucle2] + MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2]);
		}
	}
	return *pMATTemp;

}

/**************************************************************
* Operateur - .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: Un objet CMatrice.
* necessite: néant.
* entraine: La soustraction des deux matrices est retournée ou
			(Exception TAILLE_MATRICES_DIFFERENTES les deux matrices n'ont pas la même taille).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator-(CMatrice<T> const&MATObjetParam){
	if(uiMATLignes != MATObjetParam.uiMATLignes || uiMATColonnes != MATObjetParam.uiMATColonnes){
		CException  exception(TAILLE_MATRICES_DIFFERENTES, "Les deux matrices n'ont pas la même taille pour faire l'operation -.");
		throw exception;
	}
	CMatrice<T> *pMATTemp = new CMatrice (uiMATLignes, uiMATColonnes);
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			pMATTemp->MATModifierValeur(uiBoucle1, uiBoucle2, ptMATElements[uiBoucle1][uiBoucle2] - MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2]);
		}
	}
	return *pMATTemp;

}


/**************************************************************
* Operateur * .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: Un objet CMatrice.
* necessite: néant.
* entraine: La multiplication des deux matrices est retournée ou Une exception
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator*(CMatrice<T> const&MATObjetParam){
	if(uiMATColonnes != MATObjetParam.uiMATLignes){
		CException  exception(TAILLE_MATRICES_DIFFERENTES, "Le nombre de lignes de la premiere matrice doit etre egal au nombre de colonnes de la deuxieme matrice pour faire l'operation *.");
		throw exception;
	}
	CMatrice<T> *pMATTemp = new CMatrice (uiMATLignes, uiMATColonnes);
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			T tSomme = 0;
			for(unsigned int uiBoucle3 = 0; uiBoucle3 < uiMATColonnes; uiBoucle3++)
				tSomme += ptMATElements[uiBoucle1][uiBoucle3] * MATObjetParam.ptMATElements[uiBoucle3][uiBoucle2];
			pMATTemp->MATModifierValeur(uiBoucle1, uiBoucle2, tSomme);
		}
	}
	return *pMATTemp;
}

/**************************************************************
* Operteur *.
**************************************************************
*
* Entree: Un double.
* sortie: Un objet CMatrice.
* necessite: néant.
* entraine: La multiplication par dMultip est retournée.
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator*(double dMultip){
	unsigned int uiBoucle1, uiBoucle2;
	CMatrice<T> *pMATTemp = new CMatrice (uiMATLignes, uiMATColonnes);
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			pMATTemp->MATModifierValeur(uiBoucle1, uiBoucle2, dMultip * ptMATElements[uiBoucle1][uiBoucle2]);
		}
	}
	return *pMATTemp;
}
/**************************************************************
* Operteur /.
**************************************************************
*
* Entree: Un double.
* sortie: Un objet CMatrice.
* necessite: néant.
* entraine: La division par dDivis est retournée ou
			(Exception DIVISION_PAR_ZERO Le diviseur doit être different de 0).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator/(double dDivis){
	if(dDivis == 0){
		CException  exception(DIVISION_PAR_ZERO, "Le diviseur doit être different de 0");
		throw exception;
	}
	CMatrice<T> *pMATTemp = new CMatrice (uiMATLignes, uiMATColonnes);
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			pMATTemp->MATModifierValeur(uiBoucle1, uiBoucle2, ptMATElements[uiBoucle1][uiBoucle2] / dDivis);
		}
	}
	return *pMATTemp;
}

/**************************************************************
* Operteur =.
**************************************************************
*
* Entree: Un double.
* sortie: Un objet CMatrice.
* necessite: néant.
* entraine: Recopier l'objet passé en paramaètre dans l'objet courant ou
			(Exception TAILLE_MATRICES_DIFFERENTES Les deux matrices n'ont pas la même taille).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator=(CMatrice<T> const& MATObjetParam) {
	if(uiMATColonnes != MATObjetParam.uiMATColonnes || uiMATLignes != MATObjetParam.uiMATLignes){
		CException  exception(TAILLE_MATRICES_DIFFERENTES, "Les deux matrices n'ont pas la même taille pour faire l'operation =.");
		throw exception;
	}
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			MATModifierValeur(uiBoucle1, uiBoucle2, MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2]);
		}
	}
	return *this;
}
/**************************************************************
* Operteur == .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: Un booléen.
* necessite: néant.
* entraine: Vrai Si les deux matrices sont égales , Faux sinon.
*/
template <class T>
bool CMatrice<T>::operator==(CMatrice<T> const& MATObjetParam){
	if(uiMATColonnes != MATObjetParam.uiMATColonnes || uiMATLignes != MATObjetParam.uiMATLignes){
		return false;
	}
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			if(ptMATElements[uiBoucle1][uiBoucle2] != MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2]){
				return false;
			}
		}
	}
	return true;
}


/**************************************************************
* Operteur != .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: Un booléen.
* necessite: néant.
* entraine: Faux Si les deux matrices sont égales , Vrai sinon.
*/
template <class T>
bool CMatrice<T>::operator!=(CMatrice<T> const& MATObjetParam){
	if(uiMATColonnes != MATObjetParam.uiMATColonnes || uiMATLignes != MATObjetParam.uiMATLignes){
		return true;
	}
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			if(ptMATElements[uiBoucle1][uiBoucle2] != MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2]){
				return true;
			}
		}
	}
	return false;
}

/**************************************************************
* Operateur += .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: L'Objet courant.
* necessite: néant.
* entraine: (Ajoute les deux matrices et stocke le resultat dans la matrice courante )ou 
			(Exception TAILLE_MATRICES_DIFFERENTES  Les deux matrices n'ont pas la même taille.)
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator+=(CMatrice<T> const&MATObjetParam){
	if(uiMATLignes != MATObjetParam.uiMATLignes || uiMATColonnes != MATObjetParam.uiMATColonnes){
		CException  exception(TAILLE_MATRICES_DIFFERENTES, "Les deux matrices n'ont pas la même taille pour faire l'operation +=.");
		throw exception;
	}
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			ptMATElements[uiBoucle1][uiBoucle2] += MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2];
		}
	}
	return *this;
}
/**************************************************************
* Operateur -= .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: L'Objet courant.
* necessite: néant.
* entraine: (retourne l'objet courant contenant la soustraction des deux matrices )ou 
			(Exception TAILLE_MATRICES_DIFFERENTES  Les deux matrices n'ont pas la même taille.)
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator-=(CMatrice<T> const& MATObjetParam){
	if(uiMATLignes != MATObjetParam.uiMATLignes || uiMATColonnes != MATObjetParam.uiMATColonnes){
		CException  exception(TAILLE_MATRICES_DIFFERENTES, "Les deux matrices n'ont pas la même taille pour faire l'operation -=.");
		throw exception;
	}
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			ptMATElements[uiBoucle1][uiBoucle2] -= MATObjetParam.ptMATElements[uiBoucle1][uiBoucle2];
		}
	}
	return *this;
}
/**************************************************************
* Operateur *= .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: L'Objet courant.
* necessite: néant.
* entraine: (retourne l'objet courant contenant la multiplication des deux matrices ).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator*=(CMatrice<T> const&MATObjetParam){
	CMatrice<T> pMATTemp = (*this) *(MATObjetParam);
	(*this) = pMATTemp;
	return *this;
}

/**************************************************************
* Operateur *= .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: L'Objet courant.
* necessite: néant.
* entraine: (retourne l'objet courant contenant la multiplication par dMultip ).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator*=(double dMultip){
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++){
			ptMATElements[uiBoucle1][uiBoucle2] = dMultip * ptMATElements[uiBoucle1][uiBoucle2];
		}
	}
	return *this;
}


/**************************************************************
* Operateur /= .
**************************************************************
*
* Entree: Un objet CMatrice.
* sortie: L'Objet courant.
* necessite: néant.
* entraine: (retourne l'objet courant contenant la multiplication par dDivis ) ou
			(Exception DIVISION_PAR_ZERO Le diviseur doit être different de 0).
*/
template <class T>
CMatrice<T>& CMatrice<T>::operator/=(double dDivis){
	if(dDivis == 0){
		CException  exception(DIVISION_PAR_ZERO, "La division par zero n'est pas possible");
		throw exception;
	}
	unsigned int uiBoucle1, uiBoucle2;
	for(uiBoucle1 = 0; uiBoucle1 < uiMATLignes ; uiBoucle1++){
		for(uiBoucle2 = 0; uiBoucle2 < uiMATColonnes ; uiBoucle2++)
			ptMATElements[uiBoucle1][uiBoucle2] = ptMATElements[uiBoucle1][uiBoucle2] / dDivis;
	}
	return *this;
}



#endif


