#include "Main.h"


extern LCircular LC;
extern pthread_mutex_t le_lista;

//Construtor do objeto
int LeCLP::inicializa(int scan_time,int identificador,pthread_t* handle_thread)
{
	int status;						//Variavel para a leitura do status de criacao da thread
	int parametros;					//Vetor de parametros que sera enviado para a thread, pois ela recebe apenas um apontador para os parametros
	
	parametros = (scan_time * 10) + identificador; //Agrupa os dois parametros dentro de apenas uma variavel, isso é possivel pois ambos sao limitados.

	//Criação da thread utilizando a biblioteca phtreads com tratamento de erros.
	status = pthread_create(handle_thread, NULL, tfunc, (void *) parametros);
	if (!status) printf("Thread %d criada com Id= %0x \n", identificador, handle_thread);
	else printf ("Erro na criacao da thread %d! Codigo = %d\n", identificador, status);

	return 0;
}

int LeCLP::finaliza(void)
{
	int status;						//Variavel para a leitura do status de finalizacao da thread
	status = pthread_cancel(handle_thread);
	if (status == ESRCH) 
	{
		printf("Thread %0x encerrada \n", handle_thread);
	}
	return 0;
}



//Funcao principal da thread
//Essa funcao gera uma mensagem, e deposita na lista circular
void *tfunc(void *parametros)
{
	int status;
	int identificador, scan_time,i;
	int numseq = 0;						//Contador sequencial das mensagens
	char mensagem[22];					//Vetor que contém a mensagem a ser enviada
	HANDLE hTimer;						//handle generica nao utilizavel

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

	//Conversao do parametro em duas variáveis
	identificador = ((int) parametros) % 10;
	scan_time = ((int) parametros) / 10;

	//Configura o waitable timer
	SetWaitableTimer(
						hTimer,			//handle para o timer utilizado
						0,				//O timer será sinalizado logo que for criado
						scan_time,		//Periodo do timer em ms
						NULL,
						NULL,
						FALSE);

	//Loop principal
	while(1)
	{
		// Conquista MUTEX
		status = pthread_mutex_lock(&le_lista);
		if (status !=0){
		  if (status == EDEADLK) printf ("Erro EDEADLK na conquista do Mutex!\n");
		  else printf ("Erro inesperado na conquista do Mutex! Codigo = \n", status);
		  exit(0);
		}

		gera_msg(identificador, numseq, mensagem);
		numseq++;
		LC.adiciona(mensagem);

		// Libera MUTEX
		status = pthread_mutex_unlock(&le_lista);
		if (status !=0){
		  if (status == EPERM) printf ("Erro: tentativa de liberar mutex nao-conquistado!\n");
		  else printf ("Erro inesperado na liberacao do Mutex! Codigo = \n", status);
		  exit(0);
		}
		WaitForSingleObject(hTimer, scan_time); //Espera pela sinalização do Waitable timer para trabalhar novamente.
	}


	return 0;
}

//Funcao que gera uma mensagem segundo o padrao do ambiente de leitura
void gera_msg(int identificador, int numseq, char mensagem[22])
{
	int i;									//Variavel auxiliar
	SYSTEMTIME localTime;					//Variavel usada no TimeStamp

	srand ((unsigned int)time(NULL));		//Inicializa o gerador de numero aleatorios

	//Origem (1char)
		mensagem[0] =(identificador+48);	//Soma 48 para transformar no respectivo valor da tabela ASCII 

	//ID (6 char's)
	for (i=6;i>0;i--)						//A contagem deve ser invertida para passar corretamente o numero
	{
		if (numseq !=0)
		{
			mensagem[i] =(numseq%10+48);
			numseq = numseq/10;
		}
		else
			mensagem[i] = '0';
	}

	//Area (1 char aleatorio (letras maiusculas entre A e E))
	mensagem[7] = (rand()%4 + 65);			//Letras maiusculas em ASCII variam entre 65 e 69

	//Time Stamp (12 char's)
	GetLocalTime(&localTime);						//Le horario do relógio do sistema

	mensagem[8] = (localTime.wHour/10)+48;
	mensagem[9] = (localTime.wHour%10)+48;
	mensagem[10] = ':';

	mensagem[11] = (localTime.wMinute/10)+48;
	mensagem[12] = (localTime.wMinute%10)+48;
	mensagem[13] = ':';

	mensagem[14] = (localTime.wSecond/10)+48;
	mensagem[15] = (localTime.wSecond%10)+48;
	mensagem[16] = '.';

	mensagem[17] = (localTime.wMilliseconds/100)+48;
	mensagem[18] = ((localTime.wMilliseconds/10)%10)+48;
	mensagem[19] = (localTime.wMilliseconds%10)+48;

	//Codigo (2 char's aleatorios (numerais))
	mensagem[20] = (rand()%10 + 48);
	mensagem[21] = (rand()%10 + 48);
}