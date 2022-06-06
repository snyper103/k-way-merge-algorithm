#ifndef APS_H_INCLUDED
#define APS_H_INCLUDED
#define BUFFER_MAX 100 /**< buffer da memória, quantidade máxima de elementos que poderão ser carregados por vez. */
#define MAX 2000    /**< Tamanho máximo do arquivo, quantidade máxima de elementos que um arquivo poderá conter. */

short criaArquivoAleatorio( const char* nomeArquivo );
short externalMergeSort( const char* nomeArquivo );
short imprimeArquivo( const char* nomeArquivo );
void menu( void );

#endif
