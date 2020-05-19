#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct cliente {
  int id;
  char nome[50];
  char rg[10];
  struct c *prox;
  // time_t inicial;
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

int excluirDaLista(c **lista) {
  char rg[10];
  c *anterior, *atual;

  fflush(stdin);
  printf("\nInforme seu RG: ");
  gets(rg);

  anterior = *lista;
  atual = *lista;

  while (atual != NULL) {
    if (atual->rg[50] == rg[50]) {
      free(atual);
      anterior->prox = atual->prox;
    } else {
      return 0;
    }
  }
  return 1;
}

void exibirTodosDaLista(c *lista){
	
	int aux = 0;
	if(lista != NULL){
		
		printf("\n%s - %d", lista->nome, lista->rg);
		aux ++;
		
	}
	
	exibirTodosDaLista(lista->prox);
	
	printf("\nHa um total de %d pessoas na fila.", aux);
	
}

int main() {
  c *clientePreferencial = NULL;
  c *cliente = NULL;
  int identificador = 1;
  int op;

  int senhaGerente = 1234;
  int senhaCaixa = 2222;

  //chamarPorTempo(&clientePreferencial, &cliente);

  /*do {
    if (clientePreferencial != NULL) {
      chamarProximo(&clientePreferencial);
    } else if (cliente != NULL) {
      chamarProximo(&cliente);
    }
    sleep(30);
  } while (chamarProximo(&clientePreferencial) == 1 || chamarProximo(&cliente) == 1);*/
  
  do {
  	system("cls");
    printf("Selecione uma opcao abaixo:\n");
    printf("1) Cliente;\n");
    printf("2) Caixa;\n");
    printf("3) Gerente;\n");
    printf("Tecle 0 e ENTER para sair\n");
    scanf("%d", &op);

    switch (op) {
      case 1: {
        do {
          system("cls");
          int op1;
          printf("Selecione uma opcao abaixo:\n");
          printf("1) Cadastrar-se na lista de espera;\n");
          printf("2) Exibir os proximos da fila;\n");
          printf("3) Visualizar quantos tem antes;\n");
          printf("4) Desistir do atendimento;\n");
          printf("9) Para voltar ao menu anterior;\n");
          printf("Tecle 0 e ENTER para sair\n");
          scanf("%d", &op);

          switch (op) {
            case 1: {
              system("cls");
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
              system("cls");
              if (clientePreferencial != NULL) {
                chamarProximo(&clientePreferencial);
              } else if (cliente != NULL) {
                chamarProximo(&cliente);
              } else {
                printf("\nNao ha mais clientes para serem atendidos.");
              }
              system("pause");
              break;
            }
            case 3: {
              system("cls");
              if (clientePreferencial != NULL) {
                exibirProximosTres(clientePreferencial);
              } else if (cliente != NULL) {
                exibirProximosTres(cliente);
              } else {
                printf("\nNao ha mais clientes para serem atendidos.");
              }
              system("pause");
              break;
            }
            case 4: {
              system("cls");
              int confimarcao;
              if (clientePreferencial != NULL) {
                confimarcao = excluirDaLista(&clientePreferencial);
                if (confimarcao == 0) {
                  confimarcao = excluirDaLista(&cliente);
                } else {
                  printf("Voce nao esta na lista!");
                }
              }
              system("pause");
              break;
            }
            default: {
              printf("Digito incorreto\n\n");
              break;
            }
        }
        break;
      } while (op != 0);
      
      do{
      case 2: {
      	int op;
      	system("cls");    
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
		
		system("cls");
        printf("Selecione uma opcao abaixo:\n");
        printf("1) Chamar proximo da fila;\n");
        printf("9) Para voltar ao menu anterior;\n");
        printf("Tecle 0 e ENTER para sair\n");
        scanf("%d", &op);

        switch (op) {
            case 1: {
              system("cls");
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
}while (op != 9);

      case 3: {
      	system("cls");
      	int op3;
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
		
		system("cls");
        printf("Selecione uma opcao abaixo:\n");
        printf("1) Visualizar quantos tem na fila;\n");
        printf("9) Para voltar ao menu anterior;\n");
        printf("Tecle 0 e ENTER para sair\n");
        scanf("%d", &op);
        
        if(op == 1) {
        	system("cls");
        	if (clientePreferencial != NULL) {
                exibirTodosDaLista(&clientePreferencial);
              } else if (cliente != NULL) {
                exibirTodosDaLista(&cliente);
              } else {
                printf("\nNao ha mais clientes para serem atendidos.");
              }
		}
		system("pause");
        
        break;
      }
      
      case 0: {
  			system("exit");
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
}while (op != 0);
}
