/*****************************************************************//**
 * \file   Gestor.h
 * \brief  Inicialização da estrutura gestor e das respetivas funções
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