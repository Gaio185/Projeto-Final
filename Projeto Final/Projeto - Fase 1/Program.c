/*****************************************************************//**
 * \file   Program.c
 * \brief  Execução e verificação do comportamento pretendido das funções
 * 
 * \author joaog
 * \date   March 2023
 *********************************************************************/
#include "Gestor.h"
#include "Cidades.h"

int main(){

#pragma region Testes
	
	bool res;

	Cliente* c = CriarCliente(232322114, "Joao Gaio", 12, "Rua 13");
	Cliente* g = CriarCliente(3, "Ze", 10, "DJFBS");
	ClienteLista* clientes = NULL;
	clientes = InsereCliente(clientes, c, &res);
	printf("%s", clientes->c.nome);
	clientes = InsereCliente(clientes, g, &res);
	printf("%s", clientes->c.nome);
	clientes = RemoveCliente(clientes, 3);
	printf("%s", clientes->c.nome);
	MeiosLista* meios = NULL;
	MeiosLista* m = CriarMeio(Bicicleta, 10, 500, 10, 32324324);
	meios = InsereMeio(meios, m, &res);
	Gestor* gestor = CriarGestor(clientes, meios);
	MeiosLista* m2 = CriarMeio(Trotinete, 1, 3, 1, 3234324);
	meios = InsereMeio(meios, m2, &res);
	MostrarMeios(meios);
	gestor->cl = clientes;
	printf("%d\n", c->saldo);
	c = AlugarMeio(c, m);
	printf("%d\n", c->saldo);

	//printf("%d\n", c->meio.bateria);
	bool r = GravaClientesB(clientes, "clientesb");
	int y = GravaMeiosB(meios, "meiosb");
	clientes = NULL;
	clientes = LerClientesB(clientes, "clientesb", &res);
	meios = LerMeiosB("meiosb");
	printf("%d\n", clientes->c.nif);
	printf("%s\n", clientes->c.nome);
	printf("%d\n", meios->m.numSerie);
	//printf("%d\n", meios->m.numSerie);
	

	
	CidadesLista* cidades = NULL;// = (CidadesLista*)malloc(sizeof(CidadesLista));
	LigacoesLista* ligacoes = NULL;

	LigacoesLista* ligacao1 = CriarLigacoesLista(10, 1, 2);
	ligacoes = InsereLigacao(ligacoes, ligacao1, &res);
	//printf("%d", ligacoes->adj.codOrigem);

	CidadesLista* cidade1 = CriarCidadesLista("Braga", 1);

	cidades = InsereCidade(cidades, cidade1, &res);
	//printf("%s\n", cidades->ci.nome);


	CidadesLista* cidade2 = CriarCidadesLista("Barcelos", 2);
	cidades = InsereCidade(cidades, cidade2, &res);
	//printf("%s\n", cidades->next->ci.nome);

	cidades = InsereLigacaoCidade(cidades, ligacao1->adj.codOrigem, ligacao1->adj.codDestino, ligacao1->adj.peso, &res);

	MostraCidadesLista(cidades);

	int x = GravaCidadesListaB(cidades, "Cidades", "Ligacoes");
	cidades = NULL;
	cidades = CarregarCidadesListaB(cidades, "Cidades", &res);
	cidades = CarregarLigacoesListaB(cidades, "Ligacoes", &res);
	MostraCidadesLista(cidades);

	
	
#pragma endregion
	
}
