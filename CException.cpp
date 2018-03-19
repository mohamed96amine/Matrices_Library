#include "CException.h"

/**************************************************************
* Constructeur par defaut.
**************************************************************
*
* Entree: néant.
* sortie: Un Objet CException.
* necessite: néant.
* entraine: Le nouveau objet CException est retourné.
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
* necessite: néant.
* entraine: Le nouveau objet CException est retourné.
*/
CException::CException(CException const& EXEObjetParam){
	uiEXENum = EXEObjetParam.uiEXENum;
	pcEXEMsg = _strdup(EXEObjetParam.pcEXEMsg);
}

/**************************************************************
* Constructeur .
**************************************************************
*
* Entree: Le Numéro de l'exception.
* sortie: Un Objet CException.
* necessite: néant.
* entraine: Le nouveau objet CException est retourné.
*/
CException::CException(unsigned int uiValeurParam){
	uiEXENum = uiValeurParam;
	pcEXEMsg = NULL;
}


/**************************************************************
* Constructeur .
**************************************************************
*
* Entree: Le Numéro de l'exception et le message à afficher.
* sortie: Un Objet CException.
* necessite: néant.
* entraine: Le nouveau objet CException est retourné.
*/
CException::CException(unsigned int uiEXENumParam, char * pcEXEMsgParam){
	uiEXENum = uiEXENumParam;
	pcEXEMsg = _strdup(pcEXEMsgParam);
}


/**************************************************************
* Destructeur .
**************************************************************
*
* Entree: néant.
* sortie: néant.
* necessite: néant.
* entraine: L'objet est détruit.
*/
CException::~CException(){
	free(pcEXEMsg);
}

/**************************************************************
* Methode qui retourne le numéro de l'exception .
**************************************************************
*
* Entree: néant.
* sortie: le numéro de l'exception.
* necessite: néant.
* entraine: Le numéro de l'exception est retourné.
*/
unsigned int CException::EXELireNum(){
	return uiEXENum;
}


/**************************************************************
*  Methode qui modifie le  le numéro de l'exception.
**************************************************************
*
* Entree: le nouveau numéro .
* sortie: néant.
* necessite: néant.
* entraine: La modification du numéro.
*/
void CException::EXEModifierNum(unsigned int uiEXENumParam){
	uiEXENum = uiEXENumParam;
}


/**************************************************************
* Methode qui retourne le message l'exception .
**************************************************************
*
* Entree: néant.
* sortie: néant.
* necessite: néant.
* entraine: Le message de l'exception est retourné.
*/
char * CException::EXELireMsg(){
	return pcEXEMsg;
}


/**************************************************************
*  Methode qui modifie le  le numéro de l'exception.
**************************************************************
*
* Entree: le nouveau numéro .
* sortie: néant.
* necessite: néant.
* entraine: La modification du numéro.
*/
void CException::EXEModifierMsg(char * pcEXEMsgParam){
	pcEXEMsg = _strdup(pcEXEMsgParam);
}

