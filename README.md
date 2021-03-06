# K-way merge sort
Em ciência da computação, algoritmos de k-way merge ou multiway merges são um tipo específico de algoritmos de mesclagem de sequência que se especializam em receber k listas ordenadas e mesclá-las em uma única lista ordenada. Esses algoritmos de mesclagem geralmente se referem a algoritmos de mesclagem que aceitam um número de listas ordenadas maiores que dois. As mesclagens bidirecionais também são chamadas de mesclagens binárias (binary merges).

O problema de k-way merge consiste em mesclar k vetores ordenados para produzir um único vetor ordenado com os mesmos elementos. Denote por n o número total de elementos. n é igual ao tamanho do vetor de saída e a soma dos tamanhos dos k vetores de entrada. Para simplificar, assumimos que nenhuma das matrizes de entrada está vazia. Como consequência k ≤ n, o que simplifica os tempos de execução relatados. O problema pode ser resolvido em O(n*log(k)) em tempo de execução com O(n) espaço. Existem vários algoritmos que atingem esse tempo de execução.

Além disso, k-way merges são usados em procedimentos de ordenação externa. Os algoritmos de ordenação externa são uma classe de algoritmos de ordenação que podem lidar com grandes quantidades de dados. A ordenação externa é necessária quando os dados que estão sendo ordenados não cabem na memória principal de um dispositivo de computação (geralmente a memória RAM) e, em vez disso, devem residir na memória externa, que por sua vez é mais lenta (geralmente um disco rígido). Os algoritmos de mesclagem k-way geralmente ocorrem no segundo estágio dos algoritmos de ordenação externa, assim como eles fazem para a ordenação por mesclagem (merge sort).

Uma mesclagem multidirecional (multiway merge) permite que os arquivos fora da memória sejam mesclados em menos passagens do que em uma mesclagem binária. Se houver 6 execuções que precisam ser mescladas, uma mesclagem binária precisaria ter 3 passagens de mesclagem, em oposição a uma única passagem de mesclagem de uma mesclagem de 6 vias. Essa redução de passes de mesclagem é especialmente importante considerando a grande quantidade de informações que geralmente estão sendo ordenadas em primeiro lugar, permitindo maiores velocidades no momento de ordenar e reduzindo a quantidade de acessos a memórias mais lentas.

Pensando nisso, foi desenvolvido um algoritmo em C para fazer a ordenação externa de dados utilizando o K-way merge sort.

## Requisitos
É necessário ter ter o compilador de C/C++ intalado em seu computador, também precisará da biblioteca windows.h.

### Execução
Basta compilar os arquivos contidos neste repositório e executá-los.
