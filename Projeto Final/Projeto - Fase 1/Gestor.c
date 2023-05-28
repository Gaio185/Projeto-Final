/*****************************************************************//**
 * \file   Gestor.c
 * \brief  Declaração de todas as funções pertinentes à estrutura Gestor
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/

#include "Gestor.h"

/**
 * \brief recebe dois apontadores, um para lista de clientes e um para lista de meios e criar um gestor com elas
 * \status funcional
 * \param cl Lista de clientes a inserir
 * \param ml Lista de meios a inserir
 * \param res Verificação lógica da função
 * \return Gestor resultante
 */
Gestor* CriarGestor(ClienteLista* cl, MeiosLista* ml, bool* res) {
	Gestor* h = (Gestor*)malloc(sizeof(Gestor));

	if (cl == NULL && ml == NULL) {
		return NULL;
	}

	h->cl = CriarCliente(cl->c.nif, cl->c.nome, cl->c.saldo, cl->c.morada);
	h->cl = InsereCliente(h->cl, cl, res);
	h->ml = CriarMeio(ml->m.tipo, ml->m.custo, ml->m.bateria, ml->m.consumo, ml->m.numSerie);
	h->ml = InsereMeio(h->ml, ml, res);

	return h;
}





