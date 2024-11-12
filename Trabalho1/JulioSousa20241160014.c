// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <locale.h>
#include <stdio.h>
#include "JulioSousa20241160014.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h> // strlen
#ifdef _WIN32
#include <windows.h>
#endif

DataQuebrada quebraData(char data[]);
void remove_accents(char *text);
int power(int base, int exp);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

int is_leap_year(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char date[])
{
  DataQuebrada dq = quebraData(date);

  if (dq.valido == 0)
    return 0;

  int day = dq.iDia;
  int month = dq.iMes;
  int year = dq.iAno;

  int is_day_valid = day >= 1 && day <= 31;
  int is_month_valid = month >= 1 && month <= 12;
  int is_year_valid = year >= 1900 && year <= 2100;

  if (!is_day_valid || !is_month_valid || !is_year_valid)
    return 0;

  int is_day_valid_for_month = 1;

  switch (month)
  {
  case 2:
    if (is_leap_year(year))
    {
      is_day_valid_for_month = day <= 29;
    }
    else
    {
      is_day_valid_for_month = day <= 28;
    }
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    is_day_valid_for_month = day <= 30;
    break;
  default:
    is_day_valid_for_month = day <= 31;
    break;
  }

  return is_day_valid_for_month;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char start_date[], char final_date[])
{
  DiasMesesAnos dma;

  if (q1(start_date) == 0)
  {
    dma.retorno = 2;
    return dma;
  }
  else if (q1(final_date) == 0)
  {
    dma.retorno = 3;
    return dma;
  }
  else
  {
    DataQuebrada start = quebraData(start_date);
    DataQuebrada end = quebraData(final_date);

    if (start.iAno > end.iAno || (start.iAno == end.iAno && start.iMes > end.iMes) || (start.iAno == end.iAno && start.iMes == end.iMes && start.iDia > end.iDia))
    {
      dma.retorno = 4;
      return dma;
    }

    dma.qtdAnos = end.iAno - start.iAno;
    dma.qtdMeses = end.iMes - start.iMes;
    dma.qtdDias = end.iDia - start.iDia;

    if (dma.qtdDias < 0)
    {
      dma.qtdDias += 30;
      dma.qtdMeses--;
    }

    if (dma.qtdMeses < 0)
    {
      dma.qtdMeses += 12;
      dma.qtdAnos--;
    }

    dma.retorno = 1;
    return dma;
  }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *text, char character, int is_case_sensitive)
{
  int diff_between_cases = 'a' - 'A';

  int root_of_lowercase = 'a';
  int limit_of_lowercase = 'z';
  int root_of_uppercase = 'A';
  int limit_of_uppercase = 'Z';

  int occurences = 0;

  for (int index = 0; index < strlen(text); index++)
  {
    char pointer = text[index];

    if (is_case_sensitive == 1)
    {
      if (pointer == character)
        occurences++;
    }
    else
    {
      if (pointer >= root_of_lowercase && pointer <= limit_of_lowercase)
      {
        pointer -= diff_between_cases;
      }

      if (character >= root_of_lowercase && character <= limit_of_lowercase)
      {
        character -= diff_between_cases;
      }

      if (pointer == character)
        occurences++;
    }
  }

  return occurences;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *text, char *target, int positions[30])
{
  remove_accents(text);
  remove_accents(target);

  int occurrences = 0;

  for (int index = 0; index < strlen(text); index++)
  {
    if (text[index] == target[0])
    {
      int matched = 1;

      for (int j = 0; j < strlen(target); j++)
      {
        if (text[index + j] != target[j])
        {
          matched = 0;
          break;
        }
      }

      if (matched)
      {
        positions[occurrences * 2] = index + 1;
        positions[occurrences * 2 + 1] = index + strlen(target);
        occurrences++;
      }
    }
  }

  return occurrences;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int number)
{
  int params[10];

  for (int counter = 0; counter < 10; counter++)
    params[counter] = -1;

  int index = 0;

  while (number > 0)
  {
    params[index] = number % 10;
    number /= 10;
    index++;
  }

  int result = 0;

  for (int counter = 0; counter < 10; counter++)
  {
    if (params[counter] == -1)
      break;

    result += params[counter] * power(10, index - 1);
    index--;
  }

  return result;
}

int power(int base, int exponent)
{
  int result = 1;

  for (int index = 0; index < exponent; index++)
  {
    result *= base;
  }

  return result;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int base_number, int target_number)
{
  int occurences = 0;

  int base_digits[30];
  int target_digits[30];

  for (int i = 0; i < 30; i++)
  {
    base_digits[i] = -1;
    target_digits[i] = -1;
  }

  int index = 0;

  while (base_number > 0)
  {
    base_digits[index] = base_number % 10;
    base_number /= 10;
    index++;
  }

  int is_composed_number = target_number > 9;

  if (is_composed_number)
  {
    index = 0;
    while (target_number > 0)
    {
      target_digits[index] = target_number % 10;
      target_number /= 10;
      index++;
    }
  }

  for (int i = 0; i < 30; i++)
  {
    if (base_digits[i] == -1)
      break;

    if (!is_composed_number)
    {
      if (base_digits[i] == target_number)
        occurences++;
    }
    else
    {
      int matched = 1;

      for (int j = 0; j < 30; j++)
      {
        if (target_digits[j] == -1)
          break;

        if (base_digits[i + j] != target_digits[j])
        {
          matched = 0;
          break;
        }
      }

      if (matched)
        occurences++;
    }
  }

  return occurences;
}

DataQuebrada quebraData(char data[])
{
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++)
  {
    sDia[i] = data[i];
  }
  if (i == 1 || i == 2)
  {                 // testa se tem 1 ou dois digitos
    sDia[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++)
  {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2)
  {                 // testa se tem 1 ou dois digitos
    sMes[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  j = j + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++)
  {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4)
  {                 // testa se tem 2 ou 4 digitos
    sAno[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}

// stolen from https://github.com/johncobain/INF029-Andrey-Gomes-da-Silva-Nascimento/blob/main/Trabalho1/AndreyGomes20241160024.c
// fazuelli
void remove_accents(char *text)
{
  int i, j = 0;
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#elif __linux__
  setlocale(LC_ALL, "Portuguese");
#else
#endif

  const char *comAcentos[] = {"Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
                              "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
                              "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
                              "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
                              "Ü", "Ú", "Û", "ü", "ú", "û", "ù",
                              "Ç", "ç"};

  const char *semAcentos[] = {"A", "A", "A", "A", "A", "A", "a", "a", "a", "a", "a",
                              "E", "E", "E", "E", "e", "e", "e", "e",
                              "I", "I", "I", "I", "i", "i", "i", "i",
                              "O", "O", "O", "O", "O", "o", "o", "o", "o", "o",
                              "U", "U", "U", "u", "u", "u", "u",
                              "C", "c"};

  char buffer[256];
  buffer[0] = '\0';

  for (int i = 0; i < strlen(text);)
  {
    int found = 0;
    // Tenta substituir cada caractere acentuado por seu equivalente
    for (int j = 0; j < sizeof(comAcentos) / sizeof(comAcentos[0]); j++)
    {
      int len = strlen(comAcentos[j]);

      if (strncmp(&text[i], comAcentos[j], len) == 0)
      {
        strcat(buffer, semAcentos[j]);
        i += len;
        found = 1;
        break;
      }
    }
    if (!found)
    {
      strncat(buffer, &text[i], 1);
      i++;
    }
  }
  strcpy(text, buffer);
}