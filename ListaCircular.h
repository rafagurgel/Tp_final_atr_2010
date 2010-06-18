#ifndef LISTACIRCULAR_H		//Diretiva de pré-processamento para evitar include's desnecessários
#define LISTACIRCULAR_H


//Objeto Lista circular
class LCircular
{
public:
	void inicializa(void);			 //Funcao para inicializar a Lista circular
	int adiciona(char mensagem[22]); //Funcao para adicionar uma mensagem na lista, ela retorna o status 0 (ok) e 1 (lista cheia).
	int retira(char mensagem[22]);	 //Funcao para retirar uma mensagem da lista. Retorna 2 caso nao ha mensagens disponiveis.

private:
	char lista[100][22];			//Lista que conterá mensagens
	int  plivre;					//Primeira posicao livre da lista
	int  pocupada;					//Primeira posicao com mensagem na lista. caso seja 0xFFFF nao ha mensagem.
	bool  cheia;					//Indica se a lista esta cheia. 1 Caso esteja cheia, 0 caso contrário.
};
//Cria o objeto Lista Circular



#endif