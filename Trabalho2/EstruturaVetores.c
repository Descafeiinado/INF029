#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

void sort(int *integers, int n);

void quickSort(int *list, int low, int high);
int partition(int *list, int low, int high);

void swap(int *integers, int i, int j);

bool validatePosition(int posicao);

typedef struct Data
{
  int *array;

  int sentinel;
  int length;
} Data;

Data *data;

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  if (tamanho < 1)
    return TAMANHO_INVALIDO;

  posicao--;

  if (data[posicao].array != NULL)
    return JA_TEM_ESTRUTURA_AUXILIAR;

  data[posicao].array = (int *)malloc(sizeof(int) * tamanho);

  if (data[posicao].array == NULL)
    return SEM_ESPACO_DE_MEMORIA;

  data[posicao].length = tamanho;
  data[posicao].sentinel = 0;

  return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  if (data[posicao].sentinel == data[posicao].length)
    return SEM_ESPACO;

  data[posicao].array[data[posicao].sentinel] = valor;
  data[posicao].sentinel++;

  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  if (data[posicao].sentinel == 0)
    return ESTRUTURA_AUXILIAR_VAZIA;

  data[posicao].array[data[posicao].sentinel] = 0;
  data[posicao].sentinel--;

  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  if (data[posicao].sentinel == 0)
    return ESTRUTURA_AUXILIAR_VAZIA;

  int index = -1;

  for (int i = 0; i < data[posicao].sentinel; i++)
  {
    if (data[posicao].array[i] == valor)
    {
      index = i;
      break;
    }
  }

  if (index == -1)
    return NUMERO_INEXISTENTE;

  for (int i = index; i < data[posicao].sentinel; i++)
  {
    data[posicao].array[i] = data[posicao].array[i + 1];
  }

  data[posicao].sentinel--;

  return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  for (int i = 0; i < data[posicao].sentinel; i++)
  {
    vetorAux[i] = data[posicao].array[i];
  }

  return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  for (int i = 0; i < data[posicao].sentinel; i++)
  {
    vetorAux[i] = data[posicao].array[i];
  }

  sort(vetorAux, data[posicao].sentinel);

  return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
  int index = 0;

  for (int i = 0; i < TAM; i++)
  {
    if (data[i].array != NULL)
    {
      for (int j = 0; j < data[i].sentinel; j++)
      {
        vetorAux[index] = data[i].array[j];
        index++;
      }
    }
  }

  if (index == 0)
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

  return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
  int index = 0;

  for (int i = 0; i < TAM; i++)
  {
    if (data[i].array != NULL)
    {
      for (int j = 0; j < data[i].sentinel; j++)
      {
        vetorAux[index] = data[i].array[j];
        index++;
      }
    }
  }

  if (index == 0)
    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

  sort(vetorAux, index);

  return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  novoTamanho = data[posicao].length + novoTamanho;

  if (novoTamanho < 1)
    return NOVO_TAMANHO_INVALIDO;

  int *newArray = (int *)malloc(sizeof(int) * novoTamanho);

  if (newArray == NULL)
    return SEM_ESPACO_DE_MEMORIA;

  for (int i = 0; i < data[posicao].sentinel; i++)
  {
    newArray[i] = data[posicao].array[i];
  }

  free(data[posicao].array);

  data[posicao].array = newArray;
  data[posicao].length = novoTamanho;

  if (data[posicao].sentinel > novoTamanho)
    data[posicao].sentinel = novoTamanho;

  return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
  if (!validatePosition(posicao))
    return POSICAO_INVALIDA;

  posicao--;

  if (data[posicao].array == NULL)
    return SEM_ESTRUTURA_AUXILIAR;

  if (data[posicao].sentinel == 0)
    return ESTRUTURA_AUXILIAR_VAZIA;

  return data[posicao].sentinel;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
  No *start = (No *)malloc(sizeof(No));
  No *current = start;

  for (int i = 0; i < TAM; i++)
  {
    if (data[i].array != NULL)
    {
      for (int j = 0; j < data[i].sentinel; j++)
      {
        No *node = (No *)malloc(sizeof(No));

        node->conteudo = data[i].array[j];
        node->prox = NULL;

        current->prox = node;
        current = node;
      }
    }
  }

  return start;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
  No *current = inicio->prox;
  int index = 0;

  while (current != NULL)
  {
    vetorAux[index] = current->conteudo;
    current = current->prox;
    index++;
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
  No *current = *inicio;
  No *next = NULL;

  while (current != NULL)
  {
    next = current->prox;
    free(current);
    current = next;
  }

  *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar()
{
  data = (Data *)malloc(sizeof(Data) * TAM);

  for (int index = 0; index < TAM; index++)
  {
    data[index].array = NULL;

    data[index].length = 0;
    data[index].sentinel = 0;
  }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
  for (int index = 0; index < TAM; index++)
  {
    if (data[index].array != NULL)
    {
      free(data[index].array);
    }
  }

  free(data);
}

bool validatePosition(int posicao)
{
  return posicao >= 1 && posicao <= 10;
}

// sorting methods | implementations

void sort(int *integers, int n)
{
  quickSort(integers, 0, n - 1);
}

void quickSort(int *list, int low, int high)
{
  if (low < high)
  {
    int pivotIndex = partition(list, low, high);
    quickSort(list, low, pivotIndex - 1);
    quickSort(list, pivotIndex + 1, high);
  }
}

int partition(int *list, int low, int high)
{
  int pivot = list[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
  {
    if (list[j] <= pivot)
    {
      i++;
      swap(list, i, j);
    }
  }

  swap(list, i + 1, high);
  return i + 1;
}

void swap(int *integers, int i, int j)
{
  int temp = integers[i];
  integers[i] = integers[j];
  integers[j] = temp;
}