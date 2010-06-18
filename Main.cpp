//Automação em tempo Real - ELT012 - UFMG
//TRABALHO FINAL DE ATR 2010/01
//
//Autores:	Gustavo Barreto Garcia
//			Rafael Gilmar Ribeiro Gurgel
//

#define WIN32_LEAN_AND_MEAN

#include "Main.h"


using namespace std;

//Buffer Circular é um objeto global
LCircular LC;

//Mutex para controle de leitura do buffer circular
pthread_mutex_t le_lista;
pthread_mutexattr_t le_listaAttr;

int main(void)
{
	
	int i,j, status;
	char mensagem[22];

	for (i=0;i<22;i++)
		mensagem[i]='0';
	//Cria os objetos de leitura do CLP que gerarao threads
	LeCLP LeCLP1;
	LeCLP LeCLP2;
	
	//Cria um apontador para as threads a serem utilizadas
	pthread_t thread1;
	pthread_t thread2;
	
	//Inicializa o Mutex com controle de erro
	pthread_mutexattr_init(&le_listaAttr); //sempre retorna 0
    status = pthread_mutexattr_settype(&le_listaAttr, PTHREAD_MUTEX_ERRORCHECK);
	if (status != 0){
		printf ("Erro nos atributos do Mutex ! Codigo = %d\n", status);
		exit(0);
	}
	status = pthread_mutex_init(&le_lista, &le_listaAttr);
	if (status !=0){
		printf ("Erro na criação do Mutex! Codigo = %d\n", status);
		return 0;
	}
	//Inicializa a lista circular
	LC.inicializa();

	//Inicializa as threads de simulacao da Leitura do CLP
	LeCLP1.inicializa(100, 1, &thread1);						//parametros
	LeCLP2.inicializa(200, 2, &thread2);						//tempo de iteracao em ms, identificador, thread a ser utilizada

	for (i=0;i<100;i++)
	{
		status = LC.retira(mensagem);
		cout<<status<<" ";
		for (j=0;j<22;j++)
			cout<<mensagem[j];
		cout<<endl;
		system("pause");
	}

	system("pause");
	//LeCLP1.finaliza();
	//LeCLP2.finaliza();
	
	//Destroi mutex
	pthread_mutex_destroy(&le_lista);
		if (status !=0){
		printf ("Erro na destruição do Mutex! Código = %d\n", status);
		exit(0);
	}



	


	return 0;
}