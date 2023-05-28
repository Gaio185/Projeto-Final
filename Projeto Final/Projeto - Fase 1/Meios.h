/*****************************************************************//**
 * \file   Meios.h
 * \brief  Inicialização das estruturas TipoDeMeio, Meios e MeiosLista e das suas respetivas funções
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/

#ifndef DADO
#define DADO
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#pragma region ESTRUTURAS
typedef enum TipoDeMeio {
	Bicicleta = 1,
	Trotinete = 2,
}TipoDeMeio;

typedef struct Meios {
	TipoDeMeio tipo;
	int custo;
	int bateria;
	int consumo;
	int numSerie;
	bool alugado;
}Meios;

typedef struct MeiosLista {
	Meios m;
	struct MeiosLista* next;
}MeiosLista;
#pragma endregion

#pragma region FUNÇÕES
MeiosLista* CriarMeio(TipoDeMeio tipo, int custo, int bateria, int consumo, int numSerie);
MeiosLista* InsereMeio(MeiosLista* head, MeiosLista* novo, bool* res);
MeiosLista* RemoveMeio(MeiosLista* head, int numSerie);
int ExisteMeio(MeiosLista* head, int num);
Meios* DescontarPreço(Meios* m, int desconto);
int GravaMeiosB(MeiosLista* h, char fileName[]);
MeiosLista* LerMeiosB(char fileName[]);
MeiosLista* LerMeiosSim(char fileName[]);
void MostrarMeios(MeiosLista* head);
#pragma endregion
//MeiosLista* OrdenarMeiosConsumo(MeiosLista* m);





#endif