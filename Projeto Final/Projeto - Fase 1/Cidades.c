/*****************************************************************//**
 * \file   Cidades.c
 * \brief  Declara��o de todas as fun��es pertinentes �s estruturas Cidade e CidadesLista
 * 
 * \author joaog
 * \date   May 2023
 *********************************************************************/
#include "Cidades.h"

/**
 * \brief recebe o nome e o codigo de uma cidade e devolve uma nova lista de cidades com tudo nulo exceto a cidade em si
 * \status funcional
 * \param nome Nome da cidade
 * \param cod  C�digo da cidade
 * \return	   Nova lista de cidades
 */
CidadesLista* CriarCidadesLista(char* nome, int cod) {
	CidadesLista* novo = (CidadesLista*)malloc(sizeof(CidadesLista));
	if (novo == NULL) return NULL;
	strcpy(novo->ci.nome, nome);
	novo->ci.cod = cod;
	novo->lig = NULL;
	novo->next = NULL;
	return novo;
}


/**
 * \brief recebe duas listas de cidades, inserindo uma delas na outra se a cidade ainda n�o existir por ordem crescente de codigo, devolvendo a lista resultante 
 * \status funcional
 * \param head Lista de cidades a ser alterada
 * \param novo Lista de cidades a ser inserida
 * \param res  Verifica��o l�gica da fun��o
 * \return	   Lista de cidades alterada
 */
CidadesLista* InsereCidade(CidadesLista* head, CidadesLista* novo, bool* res) {
	
	if (ExisteCidade(head, novo) > 0) return head;

	if (head == NULL) {
		head = novo;
		*res = true;
		return head;
	}
	else
	{
		CidadesLista* aux = head;
		CidadesLista* ant = aux;
		while (aux && (aux->ci.cod != novo->ci.cod)) {
			ant = aux;
			aux = aux->next;
		}

		if (aux == head) {
			novo->next = head;
			head = novo;
		}
		else
		{
			novo->next = aux;
			ant->next = novo;
		}
		*res = true;
	}
	return head;
}

/**
 * \brief recebe uma lista de cidades e um c�digo, procurando pela lista at� encontrar uma cidade com c�digo igual ao recebido na fun��o, devolvendo o pr�pio c�digo ou um numero negativo no caso de n�o existir
 * \status funcional
 * \param head Lista de cidades
 * \param cod  C�digo para encontrar uma cidade
 * \return     Inteiro(ou o c�digo da cidade encontrada ou -1)
 */
int ExisteCidade(CidadesLista* head, int cod) {
	CidadesLista* aux = head;
	while (aux) {
		if (aux->ci.cod == cod) {
			return cod;
		}
		else {
			aux = aux->next;
		}
	}
	return -1;
}

/**
 * \brief recebe uma lista de cidades e um c�digo para encontrar uma cidade e, ap�s percorrer a lista recursivamente at� encontrar uma cidade com c�digo igual ao recebido devolve a lista percorrida 
 * \status funcional
 * \param head Lista de cidades
 * \param cod  C�digo para encontrar uma cidade
 * \return	   Lista de Cidades percorrida
 */
CidadesLista* PercorreCidadesLista(CidadesLista* head, int cod) {
	if (head == NULL) return NULL;
	if (head->ci.cod == cod) return head;
	return(PercorreCidadesLista(head->next, cod));
}


/**
 * \brief recebe uma lista de cidades e paramentros que compoem uma liga��o de modo a inserir esta na lista se as cidades destino e origem existirem e se a liga��o n�o existir
 * \status funcional
 * \param head Lista de cidades
 * \param codO C�digo da cidade de origem
 * \param codD C�digo da cidade de destino
 * \param peso Valor do peso da liga��o � cidade
 * \param res  Verifica��o l�gica da fun��o
 * \return 
 */
CidadesLista* InsereLigacaoCidade(CidadesLista* head, int codO, int codD, float peso, bool* res)
{
	*res = false;				

	if (head == NULL) return head;	

	CidadesLista* aux = PercorreCidadesLista(head, codO);

	int cod = ExisteCidade(head, codD);

	if (aux == NULL || cod < 0) return head;	

	if ((ExisteLigacao(aux->lig, codO, codD) < 0)) return head; 
 
	LigacoesLista* lig = CriarLigacoesLista(peso, codO, codD);
	aux->lig = InsereLigacao(aux->lig, lig, res);

	return head;

	//return (InsereLigacaoCidade(head, codD, codO, peso, res)); ADICIONAR RECURSIVIDADE

}

/**
 * \brief recebe uma lista de cidades e duas strings, criando um ficheiro binario onde grava as cidades e liga��es da lista 
 * \status funcional
 * \param head Lista de cidades a ser gravada
 * \param fileName Nome do ficheiro para guardar a lista de cidades
 * \param fileNameII Nome do ficheiro para guardar a lista de liga��es
 * \return Inteiro(1 se a fun��o funcionar corretamente, -1 e -2 se, respetivamente, a lista e o ficheiro forem nulos
 */
int GravaCidadesListaB(CidadesLista* head, char* fileName, char* fileNameII) {
	if (head == NULL) return -1;

	FILE* fp;
	int r;
	fp = fopen(fileName, "wb");
	
	if (fp == NULL) return -2;

	CidadesLista* aux = head;

	while (aux != NULL) {
		fwrite(&aux->ci, 1, sizeof(Cidade), fp);
		if (aux->lig) {
			r = GravaLigacoesB(aux->lig, fileNameII);
		}
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}

/**
 * \brief recebe uma lista de cidades e uma string com um nome do ficheiro bin�rio do qual ser�o carregados dados para a lista recebida, retornando esta
 * \status funcional
 * \param head Lista de cidades 
 * \param fileName String de caracteres do nome do ficheiro binario a ser carregado
 * \param res Verifica��o l�gica da fun��o
 * \return Lista de cidades composta pelos dados carregados do ficheiro bin�rio
 */
CidadesLista* CarregarCidadesListaB(CidadesLista* head, char* fileName, bool* res) {
	*res = false;
	FILE* fp = fopen(fileName, "rb");

	if (fp == NULL) return NULL;
	Cidade aux;
	CidadesLista* novo;
	while (fread(&aux, 1, sizeof(Cidade), fp)) {
		novo = CriarCidadesLista(aux.nome, aux.cod);
		head = InsereCidade(head, novo, res);
	}

	fclose(fp);
	return head;
}

/**
 * \brief 
 * \status funcional
 * \param head Lista de cidades
 * \param fileName String de caracteres do nome do ficheiro bin�rio a ser carregado
 * \param res Verifica��o l�gica da fun��o
 * \return Lista de cidades composta pelos dados carregados do ficheiro bin�rio
 */
CidadesLista* CarregarLigacoesListaB(CidadesLista* head, char* fileName, bool* res) {
	*res = false;
	if (head == NULL) return -1;
	FILE* fp = fopen(fileName, "rb");
	Ligacao aux;
	CidadesLista* auxC = head;
	while (auxC) {
		if (fp != NULL) {
			while (fread(&aux, 1, sizeof(Ligacao), fp)) {
				head = InsereLigacaoCidade(head, aux.codDestino, aux.codOrigem, aux.peso, res);
			}
			fclose(fp);
		}
		auxC = auxC->next;
	}
	return head;
}

/**
 * \brief recebe uma lista de cidades e, se n�o for nula, demonstra todos os dados desta
 * \status funcional 
 * \param head
 */
void MostraCidadesLista(CidadesLista* head) {
	if (head == NULL) return;

	printf("Cidade: %d - %s\n",head->ci.cod , head->ci.nome);
	MostraLigacoesLista(head->lig);
	MostraCidadesLista(head->next);
}

