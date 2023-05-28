/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Inicializa��o da estrutura gestor e das respetivas fun��es
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/
#ifndef N
#define N
#include "Cliente.h"
#include "Meios.h"

#pragma region ESTRUTURA
typedef struct Gestor {
	ClienteLista* cl;
	MeiosLista* ml;
}Gestor;
#pragma endregion

Gestor* CriarGestor(ClienteLista* cl, MeiosLista* ml);





#endif