#ifndef APS_H_INCLUDED
#define APS_H_INCLUDED
#define BUFFER_MAX 100 /**< buffer da mem�ria, quantidade m�xima de elementos que poder�o ser carregados por vez. */
#define MAX 2000    /**< Tamanho m�ximo do arquivo, quantidade m�xima de elementos que um arquivo poder� conter. */

short criaArquivoAleatorio( const char* nomeArquivo );
short externalMergeSort( const char* nomeArquivo );
short imprimeArquivo( const char* nomeArquivo );
void menu( void );

#endif
