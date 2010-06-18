#include "Main.h"



//Limpa a lista. E reinicia as variaveis internas.
void LCircular::inicializa(void)
{
	int i, j;
	//Limpa a lista
	for (i=1; i<100; i++)
	{
		for (j=1; j<20; j++)
			lista[i][j] = '0';
	}
	//Limpa indicadores
	plivre = 0;
	pocupada = 0xFFFF;
	cheia = 0;
}


int LCircular::adiciona(char mensagem[22])
{
	int i;

	if (cheia == 0)								//Adiciona apenas se a lista nao estiver cheia
	{
		for (i=0; i<22; i++)
			lista[plivre][i] = mensagem[i];		//Copia mensagem para a lista
		
		if (pocupada == 0xFFFF)					//pocupada caso a lista estiver vazia, recebe o indicador do primeiro dado
			pocupada = plivre;

		plivre = (plivre+1)%100;				//Incrementa indicador de proxima posicao livre

		if (plivre == pocupada)					//Checa se a lista esta cheia
		{
			cheia = 1;
			//Avisa que a lista esta cheia
		}

		return 0;								//Retorna status de sucesso
	}
	else										//caso a lista esteja cheia...
		return 1;								//apenas retorna status 1 (lista cheia).
}



int LCircular::retira(char mensagem[22])
{
	int i;
	if (pocupada == 0xFFFF)						//A lista esta vazia, logo nao ha o que retornar.
	{
		return 2;								//Retorna status de erro (lista vazia)
	}
	else										//caso contrario, copia a mensagem no vetor mensagem[20]
	{
		for (i=0; i<22; i++)
		{
			mensagem[i] = lista[pocupada][i];
		}

		pocupada = (pocupada+1)%100;			//incrementa indicador de primeira posicao ocupada

		if (pocupada == plivre)					//Caso a primeira posicao ocupada seja igual a proxima posical livre
		{
			pocupada = 0xFFFF;					//Indica que a lista esta vazia
		}

		cheia = 0;								//Como um dado sera retirado a lista nao pode estar cheia

		return 0;								//indica status de ok.
	}

}