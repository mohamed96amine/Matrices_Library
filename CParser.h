

#ifndef C_PARSER_H
#define C_PARSER_H

#define FICHIER_INTROUVABLE 30
#define EXCEPTION_TYPE_MATRICE 31
#define EXCEPTION_NB_LIGNES 32
#define EXCEPTION_NB_COLONNES 33
#define EXCEPTION_ACCOLADE_OUVRANTE 34
#define EXCEPTION_ACCOLADE_FERMANTE 35
#define EXCEPTION_NB_COLONNES_OU_LIGNES_INVALIDE 36


#include <cstdio>
#include <cstdlib>
#include "CMatrice.h"
#include <fstream>
#include "CException.h"
#include <iostream>


using namespace std;


class CParser
{
public:
	static CMatrice<double> *PARLireFichier(char* pcNomFichier);

private:
	static bool PARVerifier(char *,fstream&);
	static int PARExtraireNombre(fstream &);
	static double* PARLireColonnes(fstream &, unsigned int);
	
};
#endif