/*****************************************************************//**
 * \file   Header.h
 * \brief  Inicialização das estruturas Cliente e ClienteLista e das respetivas funções
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/

#ifndef DADOS
#define DADOS
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Meios.h"
#define N 20

#pragma region ESTRUTURAS
typedef struct Cliente{
	int nif;
	char nome[N];
	int saldo;
	char morada[N];
	char geocode[N];
	Meios aluguer;
}Cliente;

typedef struct ClienteLista {
	Cliente c;
	struct ClienteLista* next;
}ClienteLista;
#pragma endregion

#pragma region FUNÇÕES
ClienteLista* CriarCliente(int n, char nome[], int saldo, char morada[]);
ClienteLista* InsereCliente(ClienteLista* head, ClienteLista* c, bool* res);
ClienteLista* RemoveCliente(Cliente* clientes[], int pos);
int ExisteCliente(ClienteLista* head, int NIF);
Cliente* CarregarSaldo(Cliente* c, int saldo);
bool GravaClientesB(ClienteLista* head, char fileName[]);
ClienteLista* LerClientesB(ClienteLista* head, char fileName[], bool* res);
ClienteLista* LerClientesSim(char fileName[]);
Cliente* AlugarMeio(Cliente* c, Meios* m);
void ClientesLocal(ClienteLista* head, char* geocode);
void MostrarClientes(ClienteLista* head);
#pragma endregion

#endif



