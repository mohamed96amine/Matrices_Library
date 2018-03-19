#ifndef CMATRICE_CARREE_H
#define CMATRICE_CARREE_H

#include "CMatrice.h"
#include <math.h>  

template <class T>
class CMatriceCarree : public CMatrice<T>{

public:

	//constructeurs
	CMatriceCarree();
	CMatriceCarree(CMatriceCarree<T> const & MatObjet);
	CMatriceCarree(unsigned int uiMatLigneColonne);
	~CMatriceCarree();


	//Methodes 
	double MACdeterminant();
	CMatriceCarree<T>& MACcomatrice();
	CMatriceCarree<T>& MACpuissance(unsigned int uiPuissance);
	CMatrice<T>& MACinverse();

	// operateurs
	CMatriceCarree<T>& operator^(unsigned int uiPuissance);
	
}; 

/**************************************************************
* Constructeur par defaut.
**************************************************************
*
* Entree: néant.
* sortie: Objet CMatriceCarree.
* necessite: néant.
* entraine: initialise un objet CMatriceCarree.
*/
template <class T>
CMatriceCarree<T>::CMatriceCarree() : CMatrice<T>() {

}

/**************************************************************
* Constructeur de recopie.
**************************************************************
*
* Entree: Objet CMatrice.
* sortie: Objet CMatriceCarree.
* necessite: néant.
* entraine: Crée un nouveau objet CMatrice identique a l'objet passé en paramètre.
*/
template <class T>
CMatriceCarree<T>::CMatriceCarree(CMatriceCarree<T> const & MACObjet) : CMatrice<T> (MACObjet){
}

/**************************************************************
* Constructeur .
**************************************************************
*
* Entree: Le nombre de lignes et de colonnes(egaux).
* sortie: Objet CMatriceCarree.
* necessite: néant.
* entraine: Crée un nouveau objet CMatrice de taille uiMatLigneColonne*uiMatLigneColonne.
*/
template <class T>
CMatriceCarree<T>::CMatriceCarree(unsigned int uiMatLigneColonne) : CMatrice<T> (uiMatLigneColonne, uiMatLigneColonne){

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
CMatriceCarree<T>::~CMatriceCarree(){
}



/**************************************************************
* Methode qui calcule le determinant de la matrice.
**************************************************************
*
* Entree: néant.
* sortie: Un double.
* necessite: néant.
* entraine: retourne le determinant de la matrice est retournée .
*/
template <class T>
double CMatriceCarree<T>::MACdeterminant(){
	double dDeterminant = 0;
	if(uiMATLignes == 1){
		dDeterminant = ptMATElements[0][0] ;
	}
	else if(uiMATLignes == 2)
		dDeterminant = ptMATElements[0][0] * ptMATElements[1][1] - ptMATElements[1][0] * ptMATElements[0][1];
	else
	{
		dDeterminant = 0;
		for(unsigned int uiBoucle = 0 ; uiBoucle < uiMATLignes; uiBoucle++)
		{
			CMatriceCarree<T> *pMACTemp = new CMatriceCarree<T>(uiMATLignes - 1);
			unsigned int uiIndice1, uiIndice2;
			uiIndice1 = 0;
			for(unsigned int uiBoucle1 = 0 ; uiBoucle1 < uiMATLignes; uiBoucle1++)
			{
				
				if(uiBoucle1 != uiBoucle)
				{
					uiIndice2 = 0;
					for(unsigned int uiBoucle2 = 1 ; uiBoucle2 < uiMATLignes; uiBoucle2++)
					{
						(*pMACTemp).MATModifierValeur(uiIndice1, uiIndice2, ptMATElements[uiBoucle1][uiBoucle2]);
						uiIndice2++;
					}
					uiIndice1++;
				}
			}
			dDeterminant += pow(-1, uiBoucle) * (*pMACTemp).MACdeterminant() * ptMATElements[uiBoucle][0] ;
		} 
	}
	return dDeterminant;
}


/**************************************************************
* Methode qui calcule la puissance de la matrice.
**************************************************************
*
* Entree: La puissance.
* sortie: Un Objet CMatriceCarree.
* necessite: néant.
* entraine: retourne la matrice à la puissance uiPuissance .
*/
template <class T>
CMatriceCarree<T>& CMatriceCarree<T>::MACpuissance(unsigned int uiPuissance){
	if(uiPuissance == 0){
		CMatriceCarree<T> *pMACTemp = new CMatriceCarree<T>(uiMATLignes);
		unsigned int uiBoucle;
		for(uiBoucle = 0 ; uiBoucle < uiPuissance - 1; uiBoucle++)
			(*pMACTemp).ptMATElements[uiBoucle][uiBoucle] = 1; 
		return *pMACTemp;
	}else{
		CMatriceCarree<T> *pMACTemp = new CMatriceCarree<T>(*this);
		unsigned int uiBoucle;
		for(uiBoucle = 0 ; uiBoucle < uiPuissance - 1; uiBoucle++)
			(*pMACTemp) *= (*this);
		return *pMACTemp;
	}
}

/**************************************************************
* Methode qui calcule la comatrice de la matrice.
**************************************************************
*
* Entree: néant.
* sortie: Un Objet CMatriceCarree.
* necessite: néant.
* entraine: retourne la comatrice .
*/
template <class T>
CMatriceCarree<T>& CMatriceCarree<T>::MACcomatrice(){
	CMatriceCarree<T> * pMACRes = new CMatriceCarree<T>(uiMATLignes);
	for(unsigned int uiBoucle1 = 0; uiBoucle1 < uiMATLignes; uiBoucle1++)
	{
		for(unsigned int uiBoucle2 = 0; uiBoucle2 < uiMATLignes; uiBoucle2++)
		{
			CMatriceCarree<T> * pMACTemp = new CMatriceCarree<T>(uiMATLignes - 1);
			unsigned int uiIndice1, uiIndice2;
			uiIndice1 = 0;
			for(unsigned int uiBoucle3 = 0 ; uiBoucle3 < uiMATLignes; uiBoucle3++)
			{
				uiIndice2 = 0;
				if(uiBoucle3 != uiBoucle1){
					for(unsigned int uiBoucle4 = 0 ; uiBoucle4 < uiMATLignes; uiBoucle4++)
					{
						if(uiBoucle4 != uiBoucle2)
						{
							(*pMACTemp).MATModifierValeur(uiIndice1, uiIndice2, ptMATElements[uiBoucle3][uiBoucle4]);
							uiIndice2++;
						}
					}
					uiIndice1++;
				}
			}
			(*pMACRes).ptMATElements[uiBoucle1][uiBoucle2] = (*pMACTemp).MACdeterminant() * pow(-1, uiBoucle1+uiBoucle2);
		}
	}
	return *pMACRes;
}

/**************************************************************
* Methode qui calcule l'inverse de la matrice.
**************************************************************
*
* Entree: néant.
* sortie: Un Objet CMatriceCarree.
* necessite: néant.
* entraine: retourne l'inverse de la matrice .
*/
template <class T>
CMatrice<T>& CMatriceCarree<T>::MACinverse()
{
	CMatrice<T> com = MACcomatrice();
	CMatrice<T> *pMATTemp = &com.MATTransposee();
	(*pMATTemp) /= MACdeterminant();
	return *pMATTemp;
}


/**************************************************************
* Operateur ^.
**************************************************************
*
* Entree: néant.
* sortie: Un Objet CMatriceCarree.
* necessite: néant.
* entraine: retourne la matrice à la puissance  uiPuissance .
*/
template <class T>
CMatriceCarree<T>& CMatriceCarree<T>::operator^(unsigned int uiPuissance){
	return MACpuissance(uiPuissance);
}




#endif
