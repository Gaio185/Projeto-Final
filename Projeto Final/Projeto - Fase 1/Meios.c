/*****************************************************************//**
 * \file   Meios.c
 * \brief  Declaração de todas as funções pertinentes às estruturas TipoDeMeio e Meios e MeiosLista
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/
#include "Meios.h"

 /**
  * \brief recebe os atributos necessarios a criar um apontador a struct meios e devolve dito apontador
  * \status funcional
  * \param tipo Tipo de meio
  * \param custo Custo do meio
  * \param bateria Bateria do meio
  * \param consumo Consumo do meio
  * \param numSerie Número de série do meio
  * \return Nova lista de meios
  */
MeiosLista* CriarMeio(TipoDeMeio tipo, int custo, int bateria, int consumo, int numSerie) {
	MeiosLista* aux = (MeiosLista*)malloc(sizeof(MeiosLista));
	aux->m.tipo = tipo;
	aux->m.custo = custo;
	aux->m.bateria = bateria;
	aux->m.consumo = consumo;
	aux->m.numSerie = numSerie;
	aux->m.alugado = false;
	aux->next = NULL;
	return aux;
}

/**
 * \brief recebe dois apontadores para listas de meios, inserindo uma na outra  por ordem crecente de consumo
 * \status funcional
 * \param head Lista de meios a ser alterada
 * \param novo Lista de meios a ser inserida
 * \param res Verificação lógica da funçãp
 * \return Lista de meios alterada
 */
MeiosLista* InsereMeio(MeiosLista* head, MeiosLista* novo, bool* res) {
	*res = false;
	
	if (ExisteMeio(head, novo->m.numSerie) > 0) return head;

	if (head == NULL) {
		head = novo;
		*res = true;
		return head;
	}
	else
	{
		MeiosLista* aux = head;
		MeiosLista* ant = aux;
		while (aux && (aux->m.consumo < novo->m.consumo)) {
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
 * \brief recebe um apontador para lista de meios e o numero de serie de um meio de modo a retira-lo desta, devolvendo o apontador para lista
 * \status funcional
 * \param header Lista de meios
 * \param numserie Número de série do meio a remover
 * \return Lista de meios alterada
 */
MeiosLista* RemoveMeio(MeiosLista* header, int numSerie) {

	if (header == NULL) return header;
	if (!ExisteMeio(header, numSerie)) return header;

	MeiosLista* aux = header;
	MeiosLista* anterior = NULL;

	while (aux->m.numSerie != numSerie) {
		anterior = aux;
		aux = aux->next;
	}

	if (anterior == NULL) {
		header = header->next;
		free(aux);
	}
	else {
		anterior->next = aux->next;
		free(aux);
	}
	return header;
}

/**
 * \brief recebe um apontador para lista de meios e o numero de serie de um meio de modo a determinar se este existe na lista
 * \status funcional
 * \param head Lista de meios
 * \param numSerie Número de série do meio a encontrar
 * \return Inteiro(1 se o meio já existir na lista e -1 se o meio não existir na lista 
 */
int ExisteMeio(MeiosLista* head, int numSerie) {
	MeiosLista* aux;
	aux = head;

	while (aux != NULL) {
		if (aux->m.numSerie == numSerie) {
			return 1;
		}
		aux = aux->next;
	}

	return -1;
}

/**
 * \brief recebe um apontador de meios e um inteiro subtraindo dito inteiro ao custo do veiculo e retornando um apontador para meios
 * \status funcional
 * \param m Lista de meios
 * \param d Desconto a aplicar
 * \return Meio com o preço descontado
 */
Meios* DescontarPreço(Meios* m, int d){
	m->custo -= d;
	return m;
}

/**
 * \brief recebe um apontador para lista de meios e uma string de caracteres que representa o nome do ficheiro no qual a lista de meios será guardada,
 * devolvendo um inteiro
 * \status funcional
 * \param head Lista de Meios
 * \param fileName String de caracteres do nome do ficheiro
 * \return Inteiro(1 se a gravação for bem sucedida e -1 e -2 se, respetivamente, a lista for nula e o ficheiro for nulo
 */
int GravaMeiosB(MeiosLista* head, char fileName[]) {
	if (head == NULL) return (-1);
	MeiosLista* aux = head;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL) {
		return (-2);
	}
	while (aux != NULL) {
		fwrite(&aux->m, 1, sizeof(Meios), fp);
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}

/**
 * \brief recebe uma string de caracteres que corresponde ao nome do ficheiro do qual será efetuada a leitura de cada meio no ficheiro
 * e inserindo cada um deles numa lista de meios, devolvendo um apontador para essa lista no final
 * \status não compila, mas deveria funcionar
 * \param Lista de meios
 * \param fileName[] String de caracteres do nome do ficheiro binário a ler
 * \return
 */
MeiosLista* LerMeiosB(MeiosLista* head, char fileName[], bool* res) {
	*res = false;

	FILE* fp;
	fp = fopen(fileName, "rb");
	if (fp == NULL) {
		return NULL;
	}

	MeiosLista* novo;
	Meios aux;
	while (fread(&aux, 1, sizeof(Meios), fp)) {
		novo = CriarMeio(aux.tipo, aux.custo, aux.bateria, aux.consumo, aux.numSerie);
		head = InsereMeio(head, novo, res);
	}

	fclose(fp);
	*res = true;
	return head;
}

/**
 * \brief recebe o nome do ficheiro do qual será lido cada cliente inserindo-o numa lista de clientes e devolvendo um apontador para essa lista no final
 * \status Não funcional
 * \param fileName[] String de caracteres do nome do ficheiro de texto
 * \return
 */
MeiosLista* LerMeiosSim(char fileName[]) {
	MeiosLista* h = NULL;

	FILE* fp;
	fp = fopen(fileName, "r");

	Meios* aux = NULL;
	while (fscanf(fp, "%s;%d;%d;%d;%d\n", aux->tipo, aux->custo, aux->bateria, aux->consumo, aux->numSerie)) {
		h = InsereCliente(h, aux);
	}

	fclose(fp);
}

/**
 * \brief recebe um apontador para lista de meios e lista todos os meios devolvendo nada
 * \status funcional
 * \param head Lista de meios
 * \return
 */
void MostrarMeios(MeiosLista* head) {
	MeiosLista* aux = head;
	while (aux != NULL) {
		printf("Bateria: %d, Consumo: %d, Numero de Serie: %d, Custo: %d\n", aux->m.bateria, aux->m.consumo, aux->m.numSerie, aux->m.custo);
		aux = aux->next;
	}
}




