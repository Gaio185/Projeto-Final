/*****************************************************************//**
 * \file   Ligacoes.c
 * \brief  Declara��o de todas as fun��es pertinentes �s estruturas Ligacao e LigacoesLista
 * 
 * \author joaog
 * \date   May 2023
 *********************************************************************/
#include "Ligacoes.h"

/**
 * \brief recebe o peso, o codigo da origem e do destino de uma ligacao e devolve uma nova lista de liga��es sendo next nulo
 * \status funcional
 * \param peso Peso da liga��o a criar
 * \param codD C�digo do destino da liga��o a criar
 * \param codO C�digo da origem da liga��o a criar
 * \return Nova lista de liga��es
 */
LigacoesLista* CriarLigacoesLista(float peso, int codD, int codO) {
	LigacoesLista* novo = (LigacoesLista*)malloc(sizeof(LigacoesLista));
	novo->adj.peso = peso;
	novo->adj.codDestino = codD;
	novo->adj.codOrigem = codO;
	novo->next = NULL;
}

/**
 * \brief recebe duas listas de liga��es inserindo uma na outra no topo da lista
 * \status funcional
 * \param head Lista de liga��es a ser alterada
 * \param novo Lista de liga��es a ser inserida
 * \param res  Verifica��o l�gica da fun��o
 * \return     Lista de liga��es alterada
 */
LigacoesLista* InsereLigacao(LigacoesLista* head, LigacoesLista* novo, bool* res) {

	if (ExisteLigacao(head, novo->adj.codOrigem, novo->adj.codDestino) < 0) return head;

	if (head == NULL) {
		head = novo;
		*res = true;
		return head;
	}

	novo->next = head;
	head = novo;
	return head;
}

/**
 * \brief recebe uma lista de liga��es e o c�digo de origem e destino de uma liga��o e verifica se esta j� existe na lista devolvendo um inteiro
 * \status funcional
 * \param head Lista de liga��es
 * \param codO C�digo da cidade origem
 * \param codD C�digo da cidade destino
 * \return Inteiro (1 se n�o existir na lista, -1 se existir na lista)
 */
int ExisteLigacao(LigacoesLista* head, int codO, int codD) {
	LigacoesLista* aux = head;
	while (aux) {
		if (aux->adj.codOrigem == codO && aux->adj.codDestino == codD) {
			return -1;
		}
		else {
			aux = aux->next;
		}
	}
	return 1;
}

/**
 * \brief recebe uma lista de liga��es e uma string de caracteres do nome do ficheiro bin�rio onde dita lista ser� guardada
 * \status funcional
 * \param h Lista de liga��es a gravar
 * \param fileName String de caracteres do nome do ficheiro bin�rio 
 * \return Inteiro(1 se a fun��o correr bem, -2 ou -1 se, respetivamente, a lista seja nula ou o ficheiro seja nulo
 */
int GravaLigacoesB(LigacoesLista* h, char* fileName) {
	FILE* fp;
	if (h == NULL) return -2;
	fp = fopen(fileName, "wb");
	if (fp == NULL) return -1;
	LigacoesLista* aux = h;
	while (aux) {
		fwrite(&aux->adj, 1, sizeof(Ligacao), fp);
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}

/**
 * \brief recebe uma lista de liga��es e, se n�o for nula, demonstra todos os dados desta
 * \status funcional
 * \param head
 */
void MostraLigacoesLista(LigacoesLista* head) {
	if (head == NULL) return;
	printf("\tLigacoes: %d - (%.0f)\n", head->adj.codDestino, head->adj.peso);
	MostraLigacoesLista(head->next);
}