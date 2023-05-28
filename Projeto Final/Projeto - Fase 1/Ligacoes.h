/*****************************************************************//**
 * \file   Ligacoes.h
 * \brief  Inicialização das estruturas Ligacao e LigacoesLista e das respetivas funções
 * 
 * \author joaog
 * \date   May 2023
 *********************************************************************/
#ifndef DATA
#define DATA
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 20

#pragma region ESTRUTURAS
typedef struct Ligacao {
	float peso;
	int codOrigem;
	int codDestino;
}Ligacao;

typedef struct LigacoesLista {
	Ligacao adj;
	struct LigacoesLista* next;
}LigacoesLista;
#pragma endregion

#pragma region FUNÇÕES
Ligacao* CriarLigacao(float peso, int codD, int codO);
LigacoesLista* CriarLigacoesLista(float peso, int codD, int codO);
LigacoesLista* InsereLigacao(LigacoesLista* head, LigacoesLista* novo, bool* res);
int ExisteLigacao(LigacoesLista* head, int codO, int codD);
int GravaLigacoesB(LigacoesLista* head, char* fileName);
void MostraLigacoesLista(LigacoesLista* head);
#pragma endregion

#endif
