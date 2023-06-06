#include <stdio.h>

struct Cliente {
  char nome[50];
  int idade, id;
  float valorDevido;
};

struct Cliente *load();

void insert();

void save(struct Cliente cliente);

void select();

int getSize();

void delete();

int main(void) {
  int control = 0;
  do {
    printf("\nEscolha uma das opções\n");
    printf("1 - Insert\n");
    printf("2 - Select\n");
    printf("3 - Delete\n");
    __fpurge(stdin);
    scanf("%d",&control);
    switch(control){
      case 1:
        insert();
      break;
      case 2:
        select();
      break;
      case 3:
        delete();
      break;
    }
  } while(control != -1);
  
  return 0;
}

struct Cliente *load() {
  int size;

  FILE *list = fopen("clientes.dat", "rb");

  fread(&size, sizeof(int), 1, list);

  if (list == NULL) {
    printf("Erro na operação");
    exit(1);
  }

  struct Cliente *listonCache =
      (struct Cliente *)malloc((size + 1) * sizeof(struct Cliente));

  for (int count = 0; count < size; count++) {
    fread(&listonCache[count], sizeof(struct Cliente), 1, list);
  }

  fclose(list);

  return listonCache;
}

void insert() {
  struct Cliente cliente;
  printf("Informe o nome do cliente: ");
  __fpurge(stdin);
  fgets(cliente.nome, sizeof(cliente.nome), stdin);
  cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
  printf("Informe a idade do cliente: ");
  __fpurge(stdin);
  scanf("%d", &cliente.idade);
  printf("Informe o valor devido do cliente: ");
  __fpurge(stdin);
  scanf("%f", &cliente.valorDevido);
  printf("Informe o id do cliente: ");
  __fpurge(stdin);
  scanf("%d", &cliente.id);
  save(cliente);
}

void save(struct Cliente cliente) {
  int size;
  struct Cliente *listonCache = load();

  size = getSize();

  FILE *list = fopen("clientes.dat", "wb");

  if (list == NULL) {
    printf("\nErro na operação");
    exit(1);
  }

  size++;

  listonCache[size - 1] = cliente;

  fwrite(&size, sizeof(int), 1, list);

  for (int count = 0; count < size; count++) {
    fwrite(&listonCache[count], sizeof(struct Cliente), 1, list);
  }

  fclose(list);
}

int getSize() {
  int size = 0;

  FILE *list = fopen("clientes.dat", "rb");

  if (list == NULL) {
    printf("\nErro na operação");
    exit(1);
  }

  fread(&size, sizeof(int), 1, list);

  fclose(list);

  return size;
}

void select(){
  int size = getSize();
  struct Cliente *listonCache = load();
  int id = 0;
  printf("\nInforme um id para buscar um ou 0 para buscar todos: ");
  __fpurge(stdin);
  scanf("%d",&id);
  
  if( id == 0 && size != 0){
    printf("\n**********************************");
    for(int count = 0; count<size; count++){
        printf("\n=========================");
        printf("\nNome: %s",listonCache[count].nome);
        printf("\nIdade: %d",listonCache[count].idade);
        printf("\nValor devido: %.2f",listonCache[count].valorDevido);
        printf("\nID: %d",listonCache[count].id);
    }
    printf("\n**********************************");
  }
  else{
    int found = 0;
    for(int count = 0; count<size; count++){
      if(listonCache[count].id == id) {
        printf("\n**********************************");
        printf("\nNome: %s",listonCache[count].nome);
        printf("\nIdade: %d",listonCache[count].idade);
        printf("\nValor devido: %.2f",listonCache[count].valorDevido);
        printf("\nID: %d",listonCache[count].id);
        found = 1;
        printf("\n**********************************");
      }
    }
    if(!found){
      printf("\nNenhum cliente com o id %d foi encontrado.\n",id);
    }
  }
}

void delete() {
  
  int size = getSize(), id = 0, newCount = 0, found = 0;
  struct Cliente *listonCache = load();
  struct Cliente *newList =
    (struct Cliente *)malloc((size - 1) * sizeof(struct Cliente));

  
  printf("\nInforme um id para apagar o registro: ");
  __fpurge(stdin);
  scanf("%d",&id);

  for(int count = 0; count < size; count++) {
    if(listonCache[count].id != id) {
      newList[newCount] = listonCache[count];
      newCount++;
    }
    else{
      found++;
    }
  }

  FILE *list = fopen("clientes.dat", "wb");

  if (list == NULL) {
    printf("\nErro na operação");
    exit(1);
  }

  size--;

  fwrite(&size, sizeof(int), 1, list);

  for (int count = 0; count < size; count++) {
    fwrite(&newList[count], sizeof(struct Cliente), 1, list);
  }

  fclose(list);
  
  if(found == 0) {
    printf("\nCliente não encontrado");
  }
  else {
    printf("\nCliente removido com sucesso\n");
  }
}
