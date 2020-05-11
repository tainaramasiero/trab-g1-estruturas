#include <stdio.h>
#include <stdlib.h>

typedef struct cliente
{
  struct c *anterior;
  char nome[50];
  char rg[8];
  struct c *prox;
} c;

//excluir a pessoa depois de atend�-la
void excluir(c **list)
{
	char nm[50];
	c *anterior, *atual;
	
	printf("\nInforme o nome do cliente que deseja excluir: ");
	gets(nm);
	
	anterior = *list;
	atual = *list;
	
	while(atual != NULL){
		if(atual->nome[50] == nm[50]){
			free(atual);
			anterior->prox = atual->prox;
		}
	}
}


//inserir nova pessoa na lista de espera
void insere_final(c **lista)
{
 	c *n, *aux;
  	n = (c*)malloc(sizeof(c));
  
  	fflush(stdin);
  	printf("\nDigite o nome do cliente: ");
  	gets(n->nome);
  	fflush(stdin);
  	printf("\nDigite o rg do cliente: ");
  	gets(n->rg);
  
  	n->prox = NULL;
  	
  	if(*lista == NULL){
    	*lista = n;
	}
	else{
		aux = *lista;
		while (aux->prox != NULL)
      	aux = aux->prox;
    	aux->prox = n;	
  }
}

//buscar seu rg para ver quantos falta 
void lista_buscar(c **list)
{
	int valor;
	
	printf("\nInforme o numero do cliente desejado: ");
	scanf("%d", &valor);
	
	c *n;
	
    for(n=(*list); n != NULL; n->prox){
    	if(valor == n->rg){
        	printf("\n %s  ->  %d.", n->nome, n->rg);
        }
    }
}

int main()
{
  c *cliente = NULL;
  int op;
  do
  {
    printf("Selecione uma op��o abaixo:\n");
    printf("1) Cadastrar-se na lista de espera;\n");
    printf("2) Chamar o proximo aguardante;\n");
    printf("3) Exibir os proximos aguardantes;\n");
    printf("4) Visualizar quantos tem antes;");
    printf("Tecle 0 e ENTER para sair\n");
    printf("0 - sair\n");
    scanf("%d", &op);

    switch (op)
    {
    case 0:
    {
      break;
    }
    case 1:
    {
      break;
    }
    case 2:
    {
      break;
    }
    case 3:
    {
      break;
    }
    case 4:
    {
      break;
    }
    case 5:
    {
      break;
    }
    case 6:
    {
      break;
    }
    default:
    {
      printf("Digito incorreto\n\n");
      break;
    }
    }
  } while (op != 0);
  return 0;
}
