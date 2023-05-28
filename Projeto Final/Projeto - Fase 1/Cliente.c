/*****************************************************************//**
 * \file   Cliente.c
 * \brief  Declaração de todas as funções pertinentes às estruturas Cliente e ClienteLista
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/
#include "Cliente.h"
#include "Meios.h"

/**
 * \brief recebe os atributos necessarios a criar um struct apontador a struct cliente e devolve dito apontador
 * \status funcional
 * \param n NIF do cliente
 * \param Nome array de caracteres do nome do cliente
 * \param Saldo saldo do cliente
 * \param Morada array de caracteres da morada do cliente
 * \return Nova lista de clientes 
 */
ClienteLista* CriarCliente(int n, char nome[], int saldo, char morada[]) {
	ClienteLista* aux = (ClienteLista*)malloc(sizeof(ClienteLista));
	if (aux == NULL) return NULL;
	strcpy(aux->c.nome, nome);
	aux->c.saldo = saldo;
	strcpy(aux->c.morada, morada);
	aux->c.nif = n;
	Meios* m = (Meios*)malloc(sizeof(Meios*));
	aux->c.aluguer = *m;
	aux->next = NULL;
	return aux;
}

/**
 * \brief recebe dois apontadores para lista de clientes, inserindo uma na outra por ordem crescente de nif, devolvendo a lista alterada
 * \status funcional
 * \param head Lista de clientes a ser alterada 
 * \param novo Cliente a ser inserido
 * \param res Verificação lógica da função
 * \return Lista de clientes alterada
 */
ClienteLista* InsereCliente(ClienteLista* head, ClienteLista* novo, bool* res) {
	*res = false;

	if (head == NULL) {
		head = novo;
		*res = true;
		return head;
	}
	else
	{
		if (ExisteCliente(head, novo->c.nif) > 0) return head;

		ClienteLista* aux = head;
		ClienteLista* ant = aux;
		while (aux && (aux->c.nif < novo->c.nif)) {
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
 * \brief recebe um apontador para lista de clientes e o nif de um cliente de modo a retira-lo desta, devolvendo o apontador para lista
 * \status funcional
 * \param head Lista de ligações 
 * \param nif NIF do cliente a ser removido
 * \return Lista de ligações alterada
 */
ClienteLista* RemoveCliente(ClienteLista* head, int nif) {

	if (head == NULL) return head;
	if (!ExisteCliente(head, nif)) return head;

	ClienteLista* aux = head;
	ClienteLista* anterior = NULL;

	while (aux && aux->c.nif != nif) {
		anterior = aux;
		aux = aux->next;
	}

	if (anterior == NULL) {
		head = head->next;
		free(aux);
	}
	else {
		anterior->next = aux->next;
		free(aux);
	}
	return head;
}

/**
 * \brief recebe um apontador para lista e o nif de um cliente de modo a determinar se este existe na lista, devolvendo true caso exista e false caso contrário
 * \status funcional
 * \param head Lista de ligações
 * \param nif Nif de um cliente
 * \return true (caso o cliente exista na lista) false (caso o cliente não exista na lista
 */
int ExisteCliente(ClienteLista* head, int nif) {
	ClienteLista* aux;
	aux = head;

	while (aux != NULL) {
		if (aux->c.nif == nif) {
			return 1;
		}
		aux = aux->next;
	}

	return -1;
}

/**
 * \brief recebe um apontador cliente e um inteiro somando dito inteiro ao saldo do cliente e retornando um apontador para cliente
 * \status funcional
 * \param n
 * \param nome
 * \param saldo+
 * \param morada
 * \return
 */
Cliente* CarregarSaldo(Cliente* c, int s){
	c->saldo += s;
	return c;
}

/**
 * \brief recebe um apontador para lista e uma string de caracteres que representa o nome do ficheiro no qual a lista de clientes será guardada,
 * devolvendo um inteiro 
 * \status funcional
 * \param head Lista de ligações a gravar
 * \param fileName String de caracteres do nome do ficheiro binário
 * \return true (se a lista for gravada no ficheiro com sucesso) ou false (se a lista ou o ficheiro forem nulos)
 */
bool GravaClientesB(ClienteLista* head, char fileName[]) {
	if (head == NULL) return false;
	ClienteLista* aux = head;
	aux = head;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL) {
		return false;
	}

	while (aux) {
		fwrite(&aux->c, 1, sizeof(Cliente), fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
 * \brief recebe uma string de caracteres que corresponde ao nome do ficheiro do qual será efetuada a leitura de cada cliente no ficheiro e inserindo cada um deles numa lista de clientes, devolvendo um apontador para essa lista no final
 * \status funcional
 * \param fileName String de caracteres do nome do ficheiro binário
 * \param res Verificação lógica da função
 * \return Lista de clientes lida
 */
ClienteLista* LerClientesB(ClienteLista* head, char fileName[], bool* res) {
	*res = false;
	ClienteLista* auxL;

	FILE* fp;
	fp = fopen(fileName, "rb");
	if (fp == NULL) {
		return NULL;
	}
	
	Cliente aux;
	while (fread(&aux, 1, sizeof(Cliente), fp)) {
		auxL = CriarCliente(aux.nif, aux.nome, aux.saldo, aux.morada);
		head = InsereCliente(head, auxL, res);
	}

	fclose(fp);
	*res = true;
	return head;
}

/**
 * \brief recebe o nome do ficheiro do qual será lido cada cliente inserindo-o numa lista de clientes e devolvendo um apontador para essa lista no final
 * \status funcional
 * \param fileName String de caracteres do nome do ficheiro binário
 * \param res Verificação lógica da função
 * \return
 */
ClienteLista* LerClientesSim(char fileName[], bool* res) {
	*res = false;
	
	ClienteLista* h = (ClienteLista*)malloc(sizeof(ClienteLista));

	FILE* fp;
	fp = fopen(fileName, "r");
	
	Cliente* aux = (Cliente*)malloc(sizeof(Cliente));
	while (fscanf(fp, "%d;%s;%d;%s\n", &aux->nif, &aux->nome, &aux->saldo, &aux->morada)) {
		h = InsereCliente(h, aux, res);
	}

	fclose(fp);
}

/**
 * \brief recebe um apontador para cliente e um apontador para meio e apos verificar se nenhum deles é nulo verifica se o cliente tem saldo suficiente para alugar o meio, se sim é retirado o custo do meio ao seu saldo e o meio á adicionado ao cliente e devolve-se o cliente no final
 * \status funcional
 * \param c Cliente
 * \param m Meio a alugar
 * \return Cliente alterado
 */
Cliente* AlugarMeio(Cliente* c, Meios* m) {
	if (c == NULL && m == NULL) {
		return c;
	}
	

	if (c->saldo >= m->custo) {
		c->saldo -= m->custo;
		c->aluguer = *m;
		c->aluguer.alugado = true;
	}
	
	return c;
}

/**
 * \brief recebe uma lista de clientes e um geocódigo de uma localização e lista os que tem esse geocódigo
 * \status funcional
 * \param head Lista de clientes
 * \param geocode String de caracteres do geocódigo da localização
 */
void ClientesLocal(ClienteLista* head, char* geocode) {
	if (head == NULL) return NULL;

	ClienteLista* aux = head;
	while (aux) {
		if (strcmp(aux->c.geocode, geocode) == 0) {
			printf("NIF: %d, Nome: %s, Saldo: %d, Morada: %s, Geocódigo: %s\n", aux->c.nif, aux->c.nome, aux->c.saldo, aux->c.morada, aux->c.geocode);
		}
		aux = aux->next;
	}
}

/**
 * \brief recebe um apontador para lista de clientes e lista todos os clientes devolvendo nada
 * \status funcional
 * \param head Lista de clientes
  */
void MostrarClientes(ClienteLista* head) {
	ClienteLista* aux = head;
	while (aux != NULL) {
		printf("NIF: %d, Nome: %s, Saldo: %d, Morada: %s, Geocódigo: %s\n", aux->c.nif, aux->c.nome, aux->c.saldo, aux->c.morada, aux->c.geocode);
		aux = aux->next;
	}
}

