#ifndef LECLP_H		//Diretiva de pre-processamento para evitar include's desnecessários
#define LECLP_H


//Objeto que criara a tarefa que simula a leitura de um clp e gera mensagens


//Cabecalho para funcao secundaria utilizada pelas threads
void gera_msg(int identificador, int numseq, char mensagem[22]);

//Cabecalho para funcao interna das threads
void *tfunc(void *parametros);



class LeCLP
{
public:
	int inicializa(								//Construtor do objeto. Gera uma thread que envia mensagens em um intervalo de tempo.
					int scan_time,				//Intervalo entre a geracao das mensagens
					int identificador,			//ID da mensagem a ser gerada.
					pthread_t *handle_thread);	//Identificador da thread a ser gerada
	int finaliza(void);							//Libera a memoria alocada pelos threads
	
private:
	void gera_mensagem(void);					//Gera uma mensagem e deposita ela na ListaCircular padrao.
	//void *tfunc(void *parametros);			//Funcao interna das threads.

	pthread_t handle_thread;					//handle para a thread gerada
	LCircular LC;								//Referência para o objeto lista circular
};


#endif