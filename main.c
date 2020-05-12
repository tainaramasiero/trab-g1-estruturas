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
  c *cliente = (cliente*)malloc(sizeof(cliente));
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

void chamarPorTempo (c **cl1, c **cl2) {
  do {
    if (cl1 != NULL) {
      chamarProximo(&cl1);
    } else if (cl2 != NULL) {
      chamarProximo(&cl2)
    }
    sleep(30);
  while (chamarProximo(&cl1) == 1 || chamarProximo(&cl2) == 1);
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

int validarNome(c **lista, char nome[50]) {
  c *aux = lista;

  if (aux != NULL) {
    do {
      if (strcmp(aux->nome, nome) === 0) {
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

  chamarPorTempo(&clientePreferencial, &cliente)

  do {
    if (clientePreferencial != NULL) {
      chamarProximo(&clientePreferencial);
    } else if (cliente != NULL) {
      chamarProximo(&cliente)
    }
    sleep(30);
  while (chamarProximo(&clientePreferencial) == 1 || chamarProximo(&cliente) == 1);
  

  do {
    printf("Selecione uma opcao abaixo:\n");
    printf("1) Cadastrar-se na lista de espera;\n");
    printf("2) Chamar o proximo da fila;\n");
    printf("3) Exibir os proximos da fila;\n");
    printf("4) Visualizar quantos tem antes;");
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
              if (validarNome(&clientePreferencial, nome) == 1) {
                inserirFim(&clientePreferencial, id, nome, rg);
              }
              break;
            }
            case 1: {
              if (validarNome(&cliente, nome) == 1) {
                inserirFim(&cliente, id, nome, rg);
              }
              break;
            }
            default: {
              printf("Digito incorreto, tente novamente.\n (1) sim | (2) nao\n")
              break;
            }
          }
        } while (preferencial != 1 || preferencial != 2)

        break;
      }
      case 2: {
        if (clientePreferencial != NULL) {
          chamarProximo(&clientePreferencial);
        } else if (cliente != NULL) {
          chamarProximo(&cliente)
        } else {
          printf("\nNao ha mais clientes para serem atendidos.");
        }
        break;
      }
      case 3: {
        if (clientePreferencial != NULL) {
          exibirProximos(clientePreferencial);
        } else if (cliente != NULL) {
          exibirProximos(cliente)
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
  } while (op != 0);
  return 0;
}
