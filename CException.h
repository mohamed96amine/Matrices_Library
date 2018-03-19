#ifndef CEXCEPTION_H
#define CEXCEPTION_H


#include <iostream>


class CException{

	private:

		unsigned int uiEXENum;
		char* pcEXEMsg;

	public:

		// Constructeurs.
		CException();
		CException(CException const& EXEObjetParam);
		CException(unsigned int uiValeurParam);
		CException(unsigned int uiEXENumParam, char * pcEXEMsgParam);
		~CException();
		// Methodes : 
		unsigned int EXELireNum();
		void EXEModifierNum(unsigned int uiEXENumParam);
		char * EXELireMsg();
		void EXEModifierMsg(char * pcEXEMsgParam);
};

#endif