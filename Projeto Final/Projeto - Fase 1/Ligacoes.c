/*****************************************************************//**
 * \file   Ligacoes.c
 * \brief  Declaração de todas as funções pertinentes às estruturas Ligacao e LigacoesLista
 * 
 * \author joaog
 * \date   May 2023
 *********************************************************************/
#include "Ligacoes.h"

/**
 * \brief recebe o peso, o codigo da origem e do destino de uma ligacao e devolve uma nova lista de ligações sendo next nulo
 * \status funcional
 * \param peso Peso da ligação a criar
 * \param codD Código do destino da ligação a criar
 * \param codO Código da origem da ligação a criar
 * \return Nova lista de ligações
 */
LigacoesLista* CriarLigacoesLista(float peso, int codD, int codO) {
	LigacoesLista* novo = (LigacoesLista*)malloc(sizeof(LigacoesLista));
	novo->adj.peso = peso;
	novo->adj.codDestino = codD;
	novo->adj.codOrigem = codO;
	novo->next = NULL;
}

/**
 * \brief recebe duas listas de ligações inserindo uma na outra no topo da lista
 * \status funcional
 * \param head Lista de ligações a ser alterada
 * \param novo Lista de ligações a ser inserida
 * \param res  Verificação lógica da função
 * \return     Lista de ligações alterada
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
 * \brief recebe uma lista de ligações e o código de origem e destino de uma ligação e verifica se esta já existe na lista devolvendo um inteiro
 * \status funcional
 * \param head Lista de ligações
 * \param codO Código da cidade origem
 * \param codD Código da cidade destino
 * \return Inteiro (1 se não existir na lista, -1 se existir na lista)
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
 * \brief recebe uma lista de ligações e uma string de caracteres do nome do ficheiro binário onde dita lista será guardada
 * \status funcional
 * \param h Lista de ligações a gravar
 * \param fileName String de caracteres do nome do ficheiro binário 
 * \return Inteiro(1 se a função correr bem, -2 ou -1 se, respetivamente, a lista seja nula ou o ficheiro seja nulo
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
 * \brief recebe uma lista de ligações e, se não for nula, demonstra todos os dados desta
 * \status funcional
 * \param head
 */
void MostraLigacoesLista(LigacoesLista* head) {
	if (head == NULL) return;
	printf("\tLigacoes: %d - (%.0f)\n", head->adj.codDestino, head->adj.peso);
	MostraLigacoesLista(head->next);
}