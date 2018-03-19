#include "CException.h"

/**************************************************************
* Constructeur par defaut.
**************************************************************
*
* Entree: n�ant.
* sortie: Un Objet CException.
* necessite: n�ant.
* entraine: Le nouveau objet CException est retourn�.
*/
CException::CException(){
	uiEXENum = 0;
	pcEXEMsg = NULL;
}


/**************************************************************
* Constructeur de recopie.
**************************************************************
*
* Entree: Un Objet CException.
* sortie: Un Objet CException.
* necessite: n�ant.
* entraine: Le nouveau objet CException est retourn�.
*/
CException::CException(CException const& EXEObjetParam){
	uiEXENum = EXEObjetParam.uiEXENum;
	pcEXEMsg = _strdup(EXEObjetParam.pcEXEMsg);
}

/**************************************************************
* Constructeur .
**************************************************************
*
* Entree: Le Num�ro de l'exception.
* sortie: Un Objet CException.
* necessite: n�ant.
* entraine: Le nouveau objet CException est retourn�.
*/
CException::CException(unsigned int uiValeurParam){
	uiEXENum = uiValeurParam;
	pcEXEMsg = NULL;
}


/**************************************************************
* Constructeur .
**************************************************************
*
* Entree: Le Num�ro de l'exception et le message � afficher.
* sortie: Un Objet CException.
* necessite: n�ant.
* entraine: Le nouveau objet CException est retourn�.
*/
CException::CException(unsigned int uiEXENumParam, char * pcEXEMsgParam){
	uiEXENum = uiEXENumParam;
	pcEXEMsg = _strdup(pcEXEMsgParam);
}


/**************************************************************
* Destructeur .
**************************************************************
*
* Entree: n�ant.
* sortie: n�ant.
* necessite: n�ant.
* entraine: L'objet est d�truit.
*/
CException::~CException(){
	free(pcEXEMsg);
}

/**************************************************************
* Methode qui retourne le num�ro de l'exception .
**************************************************************
*
* Entree: n�ant.
* sortie: le num�ro de l'exception.
* necessite: n�ant.
* entraine: Le num�ro de l'exception est retourn�.
*/
unsigned int CException::EXELireNum(){
	return uiEXENum;
}


/**************************************************************
*  Methode qui modifie le  le num�ro de l'exception.
**************************************************************
*
* Entree: le nouveau num�ro .
* sortie: n�ant.
* necessite: n�ant.
* entraine: La modification du num�ro.
*/
void CException::EXEModifierNum(unsigned int uiEXENumParam){
	uiEXENum = uiEXENumParam;
}


/**************************************************************
* Methode qui retourne le message l'exception .
**************************************************************
*
* Entree: n�ant.
* sortie: n�ant.
* necessite: n�ant.
* entraine: Le message de l'exception est retourn�.
*/
char * CException::EXELireMsg(){
	return pcEXEMsg;
}


/**************************************************************
*  Methode qui modifie le  le num�ro de l'exception.
**************************************************************
*
* Entree: le nouveau num�ro .
* sortie: n�ant.
* necessite: n�ant.
* entraine: La modification du num�ro.
*/
void CException::EXEModifierMsg(char * pcEXEMsgParam){
	pcEXEMsg = _strdup(pcEXEMsgParam);
}

