#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct cliente {
  int id;
  char nome[50];
  char rg[10];
  struct c *prox;
} c;

c* alocarMemoria () {
  c *cliente = (c*)malloc(sizeof(c));
  return cliente;
}

void inserirFim (c **lista, int id, char nome[50], char rg[10]) {
  c *novo = alocarMemoria();

  novo->id = id;
  strcpy(novo->nome, nome);
  strcpy(novo->rg, rg);

  if (*lista == NULL) {
    novo->prox = NULL;
    lista = novo;
  } else {
    c* aux = lista;
    while (aux->prox != NULL) {
      aux = aux->prox;
    }
    novo->prox = NULL;
    aux->prox = novo;
  }
}

void inserirInicio (c **lista, int id, char nome[50], char rg[10]) {
  c *aux = alocarMemoria();

  aux->id = id;
  strcpy(aux->nome, nome);
  strcpy(aux->rg, rg);

  if (*lista == NULL) {
    aux->prox = NULL;
    lista = aux;
  } else {
    aux->prox = *lista;
    *lista = aux;
  }
}

void exibirProximos (c *lista) {
  c *aux = lista;

  if (aux != NULL) {
    do {
      printf("id - %d\n", aux->id);
      printf("nome - %s\n", aux->nome);
      printf("rg - %s\n\n", aux->rg);
      aux = aux->prox;
    } while (aux != NULL);
  }
}

void exibirProximosTres (c *lista) {
  c *aux = lista;
  int count = 1;

  if (aux != NULL) {
    do {
      printf("id - %d\n", aux->id);
      printf("nome - %s\n", aux->nome);
      printf("rg - %s\n\n", aux->rg);
      aux = aux->prox;
      count++;
    } while (aux != NULL || count != 3);
  }
}

int chamarProximo (c **lista) {
  c *aux = lista;
  printf("id - %d\n", aux->id);
  printf("nome - %s\n", aux->nome);
  printf("rg - %s\n\n", aux->rg);
  if (aux->prox != NULL) {
    lista = aux->prox;
  } else {
    return 0;
  }
  return 1;
}

void chamarPorTempo (c **cl1, c **cl2) {
  do {
    if (cl1 != NULL) 
      chamarProximo(&cl1);
    else if (cl2 != NULL) 
      chamarProximo(&cl2);
    sleep(30);
  } while (chamarProximo(&cl1) == 1 || chamarProximo(&cl2) == 1);
}

int validarRG(c **lista, char rg[10]) {
  c *aux = lista;

  if (aux != NULL) {
    do {
      if (strcmp(aux->rg, rg) == 0) {
        printf("%s, voce ja esta na fila, aguarde sua vez", aux->nome);
        return 0;
      }
      aux = aux->prox;
    } while (aux != NULL);
  }
  return 1;
}

int main() {
  c *clientePreferencial = NULL;
  c *cliente = NULL;
  int identificador = 1;
  int op;

  int senhaGerente = 1234;
  int senhaCaixa = 2222;

  chamarPorTempo(&clientePreferencial, &cliente);

  do {
    if (clientePreferencial != NULL) {
      chamarProximo(&clientePreferencial);
    } else if (cliente != NULL) {
      chamarProximo(&cliente);
    }
    sleep(30);
  } while (chamarProximo(&clientePreferencial) == 1 || chamarProximo(&cliente) == 1);
  
  do {
    printf("Selecione uma opcao abaixo:\n");
    printf("1) Cliente;\n");
    printf("2) Gerente;\n");
    printf("3) Caixa;\n");
    printf("Tecle 0 e ENTER para sair\n");
    scanf("%d", &op);

    switch (op) {
      case 1: {
        do {
          printf("Selecione uma opcao abaixo:\n");
          printf("1) Cadastrar-se na lista de espera;\n");
          printf("2) Exibir os proximos da fila;\n");
          printf("3) Visualizar quantos tem antes;\n");
          printf("9) Para voltar ao menu anterior;\n");
          printf("Tecle 0 e ENTER para sair\n");
          scanf("%d", &op);

          switch (op) {
            case 1: {
              identificador++;
              int id = identificador;
              char nome[50];
              char rg[10];
              int preferencial = 0;

              printf("Cadastro:\n");
              fflush(stdin);
              printf("Digite seu nome:\n");
              gets(nome);
              fflush(stdin);
              printf("Digite seu rg:\n");
              gets(rg);
              printf("Cliente preferencial? (1) sim | (2) nao\n");
              scanf("%d", &preferencial);

              do {
                switch (preferencial) {
                  case 1: {
                    if (validarRG(&clientePreferencial, rg) == 1) {
                      inserirFim(&clientePreferencial, id, nome, rg);
                    }
                    break;
                  }
                  case 2: {
                    if (validarRG(&cliente, rg) == 1) {
                      inserirFim(&cliente, id, nome, rg);
                    }
                    break;
                  }
                  default: {
                    printf("Digito incorreto, tente novamente.\n (1) sim | (2) nao\n");
                    break;
                  }
                }
              } while (preferencial != 1 || preferencial != 2);
              break;
            }
            case 2: {
              if (clientePreferencial != NULL) {
                chamarProximo(&clientePreferencial);
              } else if (cliente != NULL) {
                chamarProximo(&cliente);
              } else {
                printf("\nNao ha mais clientes para serem atendidos.");
              }
              break;
            }
            case 3: {
              if (clientePreferencial != NULL) {
                exibirProximosTres(clientePreferencial);
              } else if (cliente != NULL) {
                exibirProximosTres(cliente);
              } else {
                printf("\nNao ha mais clientes para serem atendidos.");
              }
              break;
            }
            case 4: {
              break;
            }
            case 5: {
              break;
            }
            case 6: {
              break;
            }
            default: {
              printf("Digito incorreto\n\n");
              break;
            }
          }
        } while (op != 0 || op != 9);
        break;
      }
      case 2: {
        int senha;
        int tentativas = 1;
        printf("Digite sua senha:\n");
        scanf("%d", &senha);

        while (senha != senhaGerente) {
          printf("Senha incorreta! Tente novamente:\n");
          scanf("%d", &senha);
          
          if (tentativas == 3) {
            break;
          }
        }

        printf("Selecione uma opcao abaixo:\n");
        printf("1) Chamar proximo da fila;\n");
        printf("9) Para voltar ao menu anterior;\n");
        printf("Tecle 0 e ENTER para sair\n");
        scanf("%d", &op);

        switch (op) {
            case 1: {
              if (clientePreferencial != NULL) {
                chamarProximo(&clientePreferencial);
              } else if (cliente != NULL) {
                chamarProximo(&cliente);
              } else {
                printf("\nNao ha mais clientes para serem atendidos.");
              }
              break;
            }
        break;
      }
    }
      case 3: {
        int senha;
        int tentativas = 1;
        printf("Digite sua senha:\n");
        scanf("%d", &senha);

        while (senha != senhaCaixa) {
          printf("Senha incorreta! Tente novamente:\n");
          scanf("%d", &senha);

          if (tentativas == 3) {
            break;
          }
        }

        printf("Selecione uma opcao abaixo:\n");
        printf("1) Visualizar quantos tem na fila;\n");
        printf("9) Para voltar ao menu anterior;\n");
        printf("Tecle 0 e ENTER para sair\n");
        scanf("%d", &op);
        
        break;
      }
      default: {
        printf("Digito incorreto\n\n");
        break;
      }
    }
  }while (op != 0);

  free(clientePreferencial);
  free(cliente);

  return 1;
}

/*
  c *inserir(c *a)
{
  c *p = NULL;
  p = (c *)malloc(sizeof(c *));
  fflush(stdin);
  printf("\nDigite o nome do cliente: ");
  gets(p->nome);
  fflush(stdin);
  printf("\nDigite o rg do cliente: ");
  gets(p->rg);
  p->prox = a;

  return p;
}

c *inserirInicio(c *inicio)
{
  c *p = inserir(inicio);

  return p;
}

//inserir nova pessoa na lista de espera
void insere_final(c **lista)
{
  c *n, *aux;

  inserir(n);
  n = (c *)malloc(sizeof(c));

  fflush(stdin);
  printf("\nDigite o nome do cliente: ");
  gets(n->nome);
  fflush(stdin);
  printf("\nDigite o rg do cliente: ");
  gets(n->rg);

  n->prox = NULL;

  if (*lista == NULL)
  {
    *lista = n;
  }
  else
  {
    aux = *lista;
    while (aux->prox != NULL)
      aux = aux->prox;
    aux->prox = n;
  }
}


//excluir a pessoa depois de atend�-la
void excluir(c **list)
{
  char nm[50];
  c *anterior, *atual;

  printf("\nInforme o nome do cliente que deseja excluir: ");
  gets(nm);

  anterior = *list;
  atual = *list;

  while (atual != NULL)
  {
    if (atual->nome[50] == nm[50])
    {
      free(atual);
      anterior->prox = atual->prox;
    }
  }
}

//buscar seu rg para ver quantos falta
void lista_buscar(c **list)
{
  int valor;

  printf("\nInforme o numero do cliente desejado: ");
  scanf("%d", &valor);

  c *n;

  for (n = (*list); n != NULL; n->prox)
  {
    if (valor == n->rg)
    {
      printf("\n %s  ->  %d.", n->nome, n->rg);
    }
  }
}
*/
