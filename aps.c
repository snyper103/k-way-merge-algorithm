#include "aps.h"
#define __STDC_WANT_LIB_EXT2__ 1 /**< Para poder usar a strdup. */
#include <stdio.h>  /**< Para poder usar funçoes de output e input. */
#include <time.h>   /**< Para poder auxiliar na criação de numeros aleatórios. */
#include <locale.h> /**< Para poder utilizar acentos. */
#include <string.h> /**< Para poder utilizar a strdup. */
#include <stdlib.h> /**< Para poder criar números aleatórios e alocação dinâmica de memoria. */
#include <windows.h>    /**< Para poder calcular o tempo. */

/** Apenas no arquivo .c
 *
 *  Início: 16.
 *  Término: 309.
 */

/**v Tipo arquivo, basicamente ele ira funcionar como uma lista linear estática. */
struct arquivo
{
    FILE* fp;   /**< Aponta para um arquivo. */
    int pos, tam, *buffer;  /**< pos = posição atual que está no arquivo,
                            *^ tam = tamanho maximo que está lista tem,
                            *^ *buffer = vetor*/
};

/**v Efetua a troca de valores entre duas variáveis. */
void SWAP( int* a, int* b )
{
    int temp; /**< Guardará um valor temporário. */

    /**v Efetua a tróca de valores. */
    temp = *b;
    *b = *a;
    *a = temp;
}

/**v Aqui é onde nos construimos a pilha e a arvore binária. */
void heapify( int* vet, int tam, int i )
{
    /**v Inicializa o maior como a raiz, esquerda = 2*i + 1, direita = 2*i + 2. */
    long iEsq = i*2 + 1, iDir = i*2 + 2, iMaior = i;

    /**v Se o filho esquerdo é maior que a raiz. */
    if ( (iEsq < tam) && (vet[iEsq] > vet[iMaior]) )
        iMaior = iEsq;

    /**v Se o filho direito é maior que a raiz. */
    if ( (iDir < tam) && (vet[iDir] > vet[iMaior]) )
        iMaior = iDir;

    /**v Se o maior não é a raiz. */
    if ( iMaior != i )
    {
        /**v Faz a troca de valores. */
        SWAP(&vet[i], &vet[iMaior]);

        /**v Recursivamente monta a heapify das sub-árvores. */
        heapify(vet, tam, iMaior);
    }
}

/**v Organizar um vetor utilizando pilhas e árvores binárias. */
void heapSort( int* vet, int tam )
{
    register int i;

    /**v constrói a pilha (rearranjar vetor). */
    for ( i = tam / 2 - 1; i >= 0; --i )
        heapify(vet, tam, i);

    /**v Um por um extrai um elemento do heap. */
    for ( i = tam - 1; i >= 0; --i )
    {
        /**v Move a raiz atual para o fim. */
        SWAP(&vet[0], &vet[i]);

        /**v Chama o heapify na pilha reduzida. */
        heapify(vet, i, 0);
    }
}

/**v Cria um arquivoe insere valores nele. */
short criaArquivo( const char* nomeArquivo, int* vet, int tam, short altLinha )
{
    register int i;
    FILE* fp = fopen(nomeArquivo, "a+");    /**< Abre ou cria um arquivo para ler, escrever e anexar. */

    if ( !fp )  /**< Checa para ver se a criação ou abertura do arquivo foi um sucesso. */
        return 0;

    /**v Escreve os valores do vetor no arquivo. */
    for ( i = 0; i < tam - 1; ++i )
        fprintf(fp, "%i\n", vet[i]);

    /**v Se altLinha for 0 escreverá no arquivo o ultimo valor sem o '\n'. */
    if ( !altLinha )
        fprintf(fp, "%i", vet[i]);

    else    /**< Caso contrário com '\n'. */
        fprintf(fp, "%i\n", vet[i]);

    fclose(fp); /**< Fecha o arquivo. */
    return 1;
}

/**v Preenche o vetor de buffer dentro da lista com valores do arquivo. */
short preencheBuffer( struct arquivo* arq, int k )
{
    register int i;

    if ( !arq->fp ) /**< Checa se o arquivo contém valores a serem inseridos. */
        return 0;

    arq->pos = 0;
    arq->tam = 0;

    /**v Preenche o vetor de buffers com valores. */
    for ( i = 0; i < k; ++i )
    {
        if ( (fscanf(arq->fp, " %i", &arq->buffer[ arq->tam ])) != EOF )    /**< Se não for o final do arquivo insira um valor no vetor. */
            ++arq->tam; /**< Atualiza o valor do tamanho máximo do vetor. */

        else    /**< Caso contrário, fecha o arquivo, fp apontará para NULL e para o for. */
        {
            fclose(arq->fp);    /**< Fecha o arquivo. */
            arq->fp = NULL; /**< fp aponta para NULL. */
            break;  /**< Para o for. */
        }
    }

    return 1;
}

/**v Acha o menor valor que há e ainda não foi encontrado dentre os arquivos. */
short achaMenor( struct arquivo* arq, int numArq, int k, int* menor )
{
    short bol = 1;
    register int i, j;

    /**v Procura a posição na lista do menor valor que ainda não foi encontrado. */
    for ( i = 0, j = -1; i < numArq; ++i )
    {
        /**v Se a posição deste elemento for menor que o tamanho dele, coparará para ver qual elemento é menor. */
        if ( arq[i].pos < arq[i].tam )
        {
            if ( j == -1 )  /**< Se for a primeira vez que está entrando no if, j é igual a i. */
                j = i;

            else    /**< Caso contrário, verifica qual elemento é menor. */
                if ( arq[i].buffer[ arq[i].pos ] < arq[j].buffer[ arq[j].pos ] )
                    j = i;  /**^ Se o valor na posição i for menor do que na j, j recebe i. */
        }
    }

    /**v Se em algum momento o for ter entrado no if. */
    if ( j != -1 )
    {
        *menor = arq[j].buffer[ arq[j].pos ];   /**< Atribui ao menor o valor achado. */
        ++arq[j].pos;   /**< atualiza a posição. */

        /**v Verifica se o elemento não chegou na sua quantidade máxima. */
        if ( arq[j].pos == arq[j].tam )
            bol = preencheBuffer(&arq[j], k); /**< Caso sim, atribua novos valores a ele. */

        if ( !bol ) /**< Checa para ver se o preencimento foi um sucesso. */
            return bol;

        return 1;   /**< retorna 1 para indicar que um valor ainda não encontrado foi achado. */
    }

    else
        return 0;   /**< 0 Caso não tenham encontrado nenhum valor novo. */
}

/**| Pega todos os arquivos temporários que foram criados
  *v e os fundem em apenas um arquivo final e ordenado. */
short kWayMerge( const char* nomeArquivo, int numArq, int k )
{
    char nomes[25];
    register int i,  qtdBuffer, count;
    int *ptrBuffers, menor;
    short bol;
    struct arquivo* arq;

    ptrBuffers = (int*)malloc(k * sizeof(int)); /**< Cria um vetor de tamanho K,
                                              *^ onde K é o tamanho do buffer que será utilizado. */
    arq = (struct arquivo*)malloc(numArq * sizeof(struct arquivo)); /**< Cria um vetor do tipo struct arquivo,
                                                                *^ funcionará similar a uma lista linear estática.*/

    /**v Verifica se os vetores foram alocados om sucesso. */
    if ( (!ptrBuffers) || (!arq) )
        return 0;

    /**v Preenche a lista arq com valores. */
    for ( i = 0; i < numArq; ++i )
    {
        sprintf(nomes, "temp%i.txt", i+1);

        arq[i].buffer = (int*)malloc(k * sizeof(int)); /**< Será onde ele carregará o máximo de valores possível
                                                    *^ para poder ornar futuramente. */
        arq[i].fp = fopen(nomes, "r");  /**< Abre um arquivo temporário. */
        if ( (!arq[i].buffer) || (!arq[i].fp) ) /**< Checa para ver se occoreu tudo correto até então. */
            return 0;

        arq[i].pos = 0;
        arq[i].tam = 0;

        bol = preencheBuffer(&arq[i], k); /**< Preencherá o arq[i].buffer com valores,
                                        *^ e também definirá o tamanho máximo, arq[i].tam. */

        if ( !bol ) /**< Checa para ver se o preencimento foi um sucesso. */
            return bol;
    }

    /**v Acha os menores valores dentre os arquivos temporários e os insere no arquivo final. */
    for ( qtdBuffer = 0, count = 0; achaMenor(arq, numArq, k, &menor); )
    {
        ptrBuffers[qtdBuffer] = menor;  /**< Atribui o menor valor achado no nosso vetor de buffer. */
        ++qtdBuffer;

        /**v Se o vetor de buffer estiver cheio, o inseriremos no arquivo. */
        if ( qtdBuffer == k )
        {
            if ( count == MAX - k ) /**< Se estiver inserindo os últimos valores, o ‘\n’ não deverá ser impresso. */
                bol = criaArquivo(nomeArquivo, ptrBuffers, k, 0);   /**< Insere no arquivo final */

            else    /**< Caso contrário imprimiremos o '\n'. */
                bol = criaArquivo(nomeArquivo, ptrBuffers, k, 1);   /**< Insere no arquivo final. */

            /**v Checa para ver se tudo ocorreu certo. */
            if ( !bol )
                return bol;

            qtdBuffer = 0;  /**< Zerá o indice do vetor, para podermos inserir mais nele, até que os arquivos acabem. */
            count += k; /**< Conta quantos arquivos já foram inseridos. */
        }
    }

    /**v Verifica se não há mais nada a ser inserido no arquivo. */
    if ( qtdBuffer != 0)
        bol = criaArquivo(nomeArquivo, ptrBuffers, qtdBuffer, 0);

    if ( !bol ) /**< Checa para ver se tudo ocorreu certo. */
        return bol;

    /**v Libera todos os vetores que foram alocados na memória. */
    for ( i = 0; i < numArq; ++i )
        free(arq[i].buffer);

    free(arq);  /**< Libera a nossa lista linear estática. */
    free(ptrBuffers);   /**< Libera o nosso vetor de buffer. */
    return 1;
}

/**| Função incumbida de criar e ordenar todos os arquivos temporários,
  *v além de retornar quantos arquivos foram criados. */
int criaArquivosTemporarios( const char* nomeArquivo )
{
    short bol;
    int* vet;
    register int count, total;
    char nomes[25];
    FILE* fp;

    fp = fopen(nomeArquivo, "r");   /**< Abre o arquivo. */
    vet = (int*)malloc(BUFFER_MAX * sizeof(int));   /**< Aloca o vetor, como o tamanho máximo possível pelo nosso buffer. */

    /**v Verifica se o vetor foi alocado e se o arquivo foi aberto corretamente. */
    if ( (!fp) || (!vet) )
        return (int)NULL;

    /**v Ordena os vetores, e cria arquivos com os dados ordenados. */
    for ( count = 0, total = 0; (fscanf(fp, " %i", &vet[total])) != EOF; )
    {
        ++total;

        if ( total == BUFFER_MAX )  /**< Se o total for igual ao tamanho do buffer
                                   *^ quer dizer que o vetor já está cheio e pode ser inserido em um arquivo temporário. */
        {
            ++count;    /**< Conta quantos arquivos tem. */

            sprintf(nomes, "temp%i.txt", count);    /**< Cria a string com o nome do arquivo a ser inserido. */
            heapSort(vet, BUFFER_MAX);  /**< Organiza o vetor. */
            bol = criaArquivo(nomes, vet, total, 0);    /**< Cria o arquivo destino deste vetor ordenado. */

            /**v Verifica se o arquivo foi criado com sucesso. */
            if ( !bol )
                return (int)NULL;

            total = 0; /**< Zerá o total para passar os valores restantes para o próximo arquivo. */
        }
    }

    /**v Verifica se ainda há valores a serem ordenados e passados para um arquivo. */
    if ( total > 0 )
    {
        ++count;

        sprintf(nomes, "temp%i.txt", count);
        heapSort(vet, BUFFER_MAX);
        bol = criaArquivo(nomes, vet, total, 0);

        if ( !bol )
            return (int)NULL;
    }

    fclose(fp); /**< Fecha o arquivo. */
    free(vet);  /**< Libera espaço alocado na memória. */
    return count;   /**< Retorna quantos arquivos foram criados. */
}

/** No arquivo .h
 *
 *  As funções abaixo o usuario poderá utilizar.
 *
 *  Início: 319.
 *  Término: 565.
 */

/**v Imprime o arquivo na tela. */
short imprimeArquivo( const char* nomeArquivo )
{
    FILE* fp = fopen(nomeArquivo, "r"); /**< Abre o arquivo para leitura. */
    int var;

    if ( !fp )  /**< Checa para ver se não houve erros ao abrir o arquivo. */
        return 0;

    /**v Imprime na tela os valores contidos no arquivo. */
    while ( (fscanf(fp, " %i", &var)) != EOF )
        printf("%i\n", var);

    fclose(fp); /**< Fecha o arquivo. */
    return 1;
}

/**v Criar um arquivo aleatório para teste. */
short criaArquivoAleatorio( const char* nomeArquivo )
{
    FILE* fp;
    int* vet;
    register int i, numAle;

    fp = fopen(nomeArquivo, "w+");
    vet = (int*)malloc(MAX * sizeof(int));

    /**v Faz com que a seed que o rand() usa nunca seja a mesma. */
    srand( time(NULL) );

    /**v Verifica se o arquivo foi aberto ou se o vetor foi criado com sucesso. */
    if ( (!fp) || (!vet) )
        return 0;

    /**v Preenche o vetor de 1 até MAX. */
    for ( i = 0; i < MAX; ++i )
        vet[i] = i + 1;

    /**v Desorganiza o vetor. */
    for ( i = 0; i < MAX; ++i )
    {
        /**v Atribui um valor aleatorio de 0 a MAX - 1. */
        numAle = rand() % MAX;

        /**v Efetua a troca de valores. */
        SWAP(&vet[i], &vet[numAle]);
    }

    /**v Transfere o que há no vetor para o arquivo. */
    for ( i = 0; i < MAX - 1; ++i )
        fprintf(fp, "%i\n", vet[i]);

    fprintf(fp, "%i", vet[i]); /**< Ultima linha não deverá ter '\n' */

    free(vet);  /**< Libera o espaço alocado na memória. */
    fclose(fp); /**< Fecha o arquivo. */
    return 1;
}

/**v Organiza o arquivo dado. */
short externalMergeSort( const char* nomeArquivo )
{
    char nomes[25];
    int numArq = criaArquivosTemporarios(nomeArquivo); /**< Retorna quantos arquivos temporários foram criados. */
    int k = BUFFER_MAX / (numArq + 1); /**< Cria o buffer que será utilizado. */
    register int i;
    short bol;

    remove(nomeArquivo);    /**< Deleta o arquivo. */
    bol = kWayMerge(nomeArquivo, numArq, k);    /**< Organiza o arquivo utilizando merge K way. */

    /**v Checa para ver se a ordenação foi um sucesso. */
    if ( !bol )
        return bol;

    /**v Deleta todos os arquivos temporários feitos. */
    for ( i = 0; i < numArq; ++i )
    {
        sprintf(nomes, "temp%i.txt", i+1);  /**< Escreve oque está entre aspas na string indicada. */
        remove(nomes);  /**< Deleta o arquivo com o nome contido na string nomes. */
    }

    return bol;
}

void menu( void )
{
    short bol, op = -1;
    char strNome[] = "dados.txt",* ptrPadrao,* ptrAntigo, strLiguagem[] = "Portuguese";
    double        pcFreq = 0.0f;        /**< Conta a frequencia (resolução do tempo). */
    __int64       counterStart = 0;  /**< valor do tempo. */
    LARGE_INTEGER li;            /**< Large interger para o valor do tempo. */
    double        elapsed = 0.0f;       /**< Tempo decorrido em segundos. */
    int           retcode = 1;       /**< Retorna um código. */

    /**v Guarda a configuração padrão do sistema. */
    ptrAntigo = setlocale(LC_ALL, NULL);
    ptrPadrao = (char*)strdup(ptrAntigo);
    if ( !ptrPadrao )
    {
        system("cls");
        printf("Erro ao alocar a linguagem padrao.\n");
        system("pause");
        exit(1);
    }

    /**v Muda para a desejada, assim poderá ter acentos próprios da linguagem. */
    setlocale(LC_ALL, strLiguagem);

    /**v Imprime o menu. */
    while ( op != 0 )
    {
        printf("\t#######\t...MENU!...\t#######\n"
               "[1] - Criar arquivo aleatório para teste.\n"
               "[2] - Abrir o arquivo.\n"
               "[3] - Imprimir na tela o arquivo.\n"
               "[4] - Ordenar o arquivo.\n"
               "[5] - Imprime o tempo gasto para a ordenação.\n"
               "[0] - Sair.\n"
               "-------------------------------------------------------\n"
               "Digite o número representante da opção desejada: ");
        scanf(" %hi%*[^\n]s", &op);

        /**v Determina oque o programa fará dependendo do que a pessoa digitou. */
        switch ( op )
        {
            case 1:
                elapsed = 0.0f;
                bol = criaArquivoAleatorio(strNome); /**< Cria o arquivo aleatório. */

                if ( !bol ) /**< Checa para ver se ocorreu tudo certo. */
                {
                    system("cls");  /**< Limpa a tela. */
                    printf("Erro ao criar o arquivo.\n");   /**< Imprime menssagem de erro. */
                    system("pause");    /**< Pausa o programa até que o usuário digite algo. */
                    exit(2);    /**< Fecha progra retornando 2. */
                }

                else    /** Caso contrário informa que ocorreu tudo certo. */
                {
                    system("cls");
                    printf("Sucesso ao criar o arquivo!.\n");
                    system("pause");
                }
            break;

            case 2:
                system("cls");
                printf("Abrindo o arquivo %s.\n", strNome);
                system(strNome);    /**< Abre o arquivo para o usuario dar uma olhada. */
                system("pause");
            break;

            case 3:
                system("cls");

                printf("\t#######\t...Início da impressão...\t#######\n\n");
                bol = imprimeArquivo(strNome);

                if ( !bol )
                {
                    system("cls");
                    printf("Erro ao imprimir o arquivo.\n");
                    system("pause");
                    exit(3);
                }

                else
                {
                    printf("\t#######\t...Término da impressão...\t#######\n");
                    system("pause");
                }
            break;

            case 4:
                system("cls");
                printf("Ordenando arquivo, isto pode levar algum tempo.\n");

                /**v Obtem a frequência do contador. */
                retcode = QueryPerformanceFrequency(&li);

                pcFreq = li.QuadPart;

                /**v Tempo de início (leia o valor atual do contador). */
                QueryPerformanceCounter(&li);
                counterStart = li.QuadPart;

                bol = externalMergeSort(strNome);

                /**v Para de contar o tempo (leia o valor atual do contador) e determine o tempo decorrido. */
                QueryPerformanceCounter(&li);
                elapsed = 1000.0 * ((li.QuadPart - counterStart) / pcFreq);


                if ( !bol )
                {
                    system("cls");
                    printf("Erro ao ordenar o arquivo.\n");
                    system("pause");
                    exit(4);
                }

                else
                {
                    system("cls");
                    printf("Sucesso ao ordenar o arquivo.\n");
                    system("pause");
                }
            break;

            case 5:
                system("cls");
                if ( !retcode )
                {
                    printf("Erro ao calcular o tempo decorrido.\n");
                    exit(5);
                    system("pause");
                }

                else
                {
                    /**v Imprime o tempo decorrido. */
                    printf("Para organizar o arquivo %s levou: %f milissegundos.\n", strNome, elapsed);
                    system("pause");
                }
            break;

            case 0:
                system("cls");
                printf("Saindo.\n");
                system("pause");
            break;

            default :
                system("cls");
                printf("Valor digitado não corresponde a nenhuma das opções existetes!.\n"
                       "Iremos apresentar o menu novamente, e porfavor digite certo.\n");
                system("pause");
        }

        system("cls");
    }

    /**v Volta o sistema para a configuração padrão. */
    setlocale(LC_ALL, ptrPadrao);

    free(ptrPadrao);    /**< Libera espaço alocado na memória. */
}
