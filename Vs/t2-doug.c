// l123b - t1 (acerte a letra)
// programa para adivinhar uma string gerada aleatoriamente
// Douglas Ramos Charqueiro
// 2023-09-29

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "tecla.h"
#include "tela.h"

#define TEMPO 100
#define N_LETRAS 26

void remove_letra(char v[], int pos);
void apresentacao();
void encerramento();
void jogo();
bool quer_jogar_de_novo();
void preenche_vet(char v[], int min_len, int max_len);
void mostra_vet(char v[]);
void espera_enter();
void popular_matriz(char palavras[10][16]);

int main()
{

  srand(time(0));

  apresentacao();
  // gera um tamanho aleatorio
  //  for que vai gera uma letra aleatoria
  do
  {
    tela_ini();
    tecla_ini();
    jogo();
    tecla_fim();
    tela_fim();

  } while (quer_jogar_de_novo());

  encerramento();
}

int ler_banco_de_palavras(char palavras[920][16], const char *nome_do_arquivo)
{
  FILE *arquivo = fopen(nome_do_arquivo, "r");
  if (arquivo == NULL)
  {
    perror("Erro ao abrir o arquivo");
    return 0;
  }

  char linha[16];
  int i = 0;
  while (fgets(linha, sizeof(linha), arquivo) != NULL && i < 920)
  {
    // Remover o caractere de nova linha se estiver presente
    size_t len = strlen(linha);
    if (len > 0 && linha[len - 1] == '\n')
    {
      linha[len - 1] = '\0';
    }

    // Converter para minúsculas e filtrar palavras não válidas
    int valida = 1;
    for (int j = 0; linha[j] != '\0' && j < 15; j++)
    {
      if (linha[j] >= 'A' && linha[j] <= 'Z')
      {
        linha[j] = linha[j] - 'A' + 'a';
      }
      else if (linha[j] < 'a' || linha[j] > 'z')
      {
        valida = 0;
        break;
      }
    }
    if (valida)
    {
      strcpy(palavras[i], linha);
      i++;
    }
  }

  fclose(arquivo);
  return i; // Retorna o número de palavras lidas
}

void Sorteia_palavra(char v[], int min_len, int max_len)
{
  int len = min_len + rand() % (max_len - min_len + 1);
  for (int i = 0; i < len; i++)
  {
    v[i] = 'a' + rand() % 26;
  }
  v[len] = '\0'; // Termina a string com o caractere nulo
}

void popular_matriz(char palavras[10][16])
{
  char banco_de_palavras[920][16];
  int num_palavras = ler_banco_de_palavras(banco_de_palavras, "palavras.txt");

  for (int i = 0; i < 10; i++)
  {
    int indice_aleatorio = rand() % num_palavras;
    strcpy(palavras[i], banco_de_palavras[indice_aleatorio]);
    printf("Palavra %d: %s\n", i + 1, palavras[i]); // Imprime cada palavra
  }
}

void mostra_matriz(char palavras[10][16])
{
  tela_limpa();
  tela_lincol(1, 1);

  printf("Palavras:\n");
  for (int i = 0; i < 10; i++)
  {
    printf("%d: %s\n", i + 1, palavras[i]);
  }

  tela_atualiza();
}

int encontra_palavra_com_letra(char palavras[10][16], char letra)
{
  for (int i = 0; i < 10; i++)
  {
    if (palavras[i][0] != '\0' && palavras[i][0] == letra)
    {
      remove_letra(palavras[i], 0);
      return i;
    }
  }
  return -1;
}

void jogo()
{

  tela_limpa();
  tela_lincol(1, 1);

  int quantidade_de_palavras_acertadas = 0;

  char string_alvo[10][16]; // Matriz para as palavras que o jogador deve adivinhar
  popular_matriz(string_alvo);

  long t0 = time(0);
  int palavra_selecionada = -1; // Nenhuma palavra selecionada inicialmente

  while (true)
  {
    int resta = TEMPO - (time(0) - t0);
    if (resta <= 0)
    {
      printf("Tempo esgotado\n");
      break;
    }

    mostra_matriz(string_alvo); // Mostra todas as palavras
    printf("Você tem %d segundos\n", resta);

    if (palavra_selecionada == -1)
    {
      printf("Digite uma letra para selecionar uma palavra: ");
    }
    else
    {
      printf("Palavra selecionada: %s\n", string_alvo[palavra_selecionada]);
      printf("Digite a próxima letra: ");
    }

    char letra = tecla_le_char();

    if (palavra_selecionada == -1)
    {
      palavra_selecionada = encontra_palavra_com_letra(string_alvo, letra);
      if (palavra_selecionada == -1)
      {
        printf("Nenhuma palavra encontrada com essa letra. Tente novamente.\n");
      }
    }
    else
    {
      // Procura a letra na palavra selecionada e a remove se encontrada
      int letra_encontrada = 0;
      for (int i = 0; i < 10 && string_alvo[palavra_selecionada][i] != '\0'; i++)
      {
        if (string_alvo[palavra_selecionada][0] == letra)
        {
          remove_letra(string_alvo[palavra_selecionada], i);
          letra_encontrada = 1;
          break;
        }
      }

      if (!letra_encontrada)
      {
        printf("Letra não encontrada na palavra selecionada. Tente novamente.\n");
      }

      // Verifica se a palavra foi toda acertada
      if (string_alvo[palavra_selecionada][0] == '\0')
      {
        printf("Palavra %d acertada! Parabéns!\n", palavra_selecionada + 1);
        palavra_selecionada = -1; // Permite selecionar uma nova palavra

        quantidade_de_palavras_acertadas++;
      }

      if (quantidade_de_palavras_acertadas == 10)
      {
        printf("Parabéns, você acertou todas as palavras!\n");
        break;
      }
    }
  }
}

void espera_enter()
{
  while (getchar() != '\n')
  {
    // não faz nada
  }
}

void apresentacao()
{
  printf("Você deve digitar as palavras que aparecerão na tela.\n");
  printf("A ordem nao é importante.\n");
  printf("Tecle <enter> para iniciar. ");
  espera_enter();
}

void encerramento()
{
  printf("Até a próxima.\n");
}

bool quer_jogar_de_novo()
{
  espera_enter();

  printf("Digite 's' para jogar de novo: ");
  while (true)
  {
    char c = getchar();
    if (c == '\n')
    {
      return false;
    }
    else if (c == 's' || c == 'S')
    {
      espera_enter();
      return true;
    }
  }
}

void remove_letra(char v[], int pos)
{
  if (pos >= 0)
  {
    int len = strlen(v);
    for (int i = pos; i < len - 1; i++)
    {
      v[i] = v[i + 1];
    }
    v[len - 1] = '\0'; // Define o último caractere como nulo
  }
}
