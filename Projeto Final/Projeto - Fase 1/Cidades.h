/*****************************************************************//**
 * \file   Cidades.h
 * \brief  Inicialização das estruturas Cidade e CidadesLista e das respetivas funções
 * 
 * \author joaog
 * \date   May 2023
 *********************************************************************/
#ifndef L
#define L
#include "Ligacoes.h"

#pragma region ESTRUTURAS
typedef struct Cidade {
	char nome[MAX];
	int cod;
}Cidade;

typedef struct CidadesLista {
	Cidade ci;
	LigacoesLista* lig;
	struct CidadesLista* next;
}CidadesLista;
#pragma endregion

#pragma region FUNÇÕES
CidadesLista* CriarCidadesLista(char* nome, int cod);
CidadesLista* InsereCidade(CidadesLista* hearder, CidadesLista* novo, bool* b);
CidadesLista* InsereLigacaoCidade(CidadesLista* header, int codO, int codD, float peso, bool* res);
int ExisteCidade(CidadesLista* header, int cod);
CidadesLista* PercorreCidadesLista(CidadesLista* header, int cod);
int GravaCidadesListaB(CidadesLista* head, char* fileName);
CidadesLista* CarregarCidadesListaB(CidadesLista* h, char* fileName, bool* res);
CidadesLista* CarregarLigacoesListaB(CidadesLista* head, bool* res);
void MostraCidadesLista(CidadesLista* head);
#pragma endregion

#endif






