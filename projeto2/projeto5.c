#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct arvore {
	int num;
	struct arvore *esquerda;
	struct arvore *direita;
}Arvore;

//verifica se arvore eh vazia
int verificaVazia(Arvore* arv){
	return arv==NULL;
}

Arvore* insereArvore(int valor, Arvore *arvore){
  Arvore *novo = (Arvore*)malloc(sizeof(Arvore));
  Arvore *aux = arvore;
  Arvore *ant;
  novo->num = valor;
  novo->esquerda = NULL;
  novo->direita = NULL;
  if(arvore == NULL){
    arvore = novo;
    return novo;
  }
  else{
    while(aux != NULL){
      ant = aux;
      if(valor > aux->num){
        aux = aux->direita;
      }
      else{
        aux = aux->esquerda;
      }
    }
    if(valor > ant->num){
      ant->direita = novo;
    }
    else{
      ant->esquerda = novo;
    }
  }
  return arvore;
}

//carrega arquivos para a arvore
Arvore *loadTreeFromFile(char *nome_arq) {
	FILE *arquivo = fopen(nome_arq, "r");
	int valor;
	
	Arvore *raiz = NULL;

	while( (fscanf(arquivo, "%d ", &valor)) != EOF) {
	raiz = insereArvore(valor, raiz);

  }
  
 return raiz;
}

Arvore *searchValue(Arvore *arv,int valor){
  Arvore *aux = arv,*ant = NULL;
  while(aux != NULL && aux->num != valor){
    ant = aux;
    if(valor > aux->num){
      aux = aux->direita;
    }
    else if(valor < aux->num){
      aux = aux->esquerda;
    }
  }
  if(ant == NULL)
    return aux;
  else if(aux->num == valor)
    return ant;
  else
    return NULL;
}

//Funcao que mostra arvore no estado atual
void showTree(Arvore *arv,int altura) {
    Arvore *aux = arv;
    int elementos = (pow(2,altura));
    elementos--;
    int ordem[elementos],i = 0,atual = 0,numNivel ,cont,j,
    espacosParede = 0,espacosEntre = 3,contAux,aumentaEspaco;
    if (aux == NULL){
      printf("Nao ha arvore carregada\n");
      return;
    }
    //printf("Numero de elementos no maximo da arvore de altura %d = %d \n",altura, elementos);
    ordem[i] = arv->num;
    //printf("ordem[%d] = %d \n",i, ordem[i]);
    i++;
    while(i < elementos){
        if(ordem[atual] == 0)
        {
          ordem[i] = 0;
          //printf("ordem[%d] = %d \n",i, ordem[i]);
          i++;
          ordem[i] = 0;
          //printf("ordem[%d] = %d \n",i, ordem[i]);
          i++;
        }
        else{
          aux = searchValue(arv,ordem[atual]);// como estou reaproveitando a funcao searchValue q devolve o pai, devo encontrar o valor novamente
          if(aux->esquerda != NULL){
            if(aux->esquerda->num == ordem[atual])
              aux = aux->esquerda;
          }
          if(aux->direita != NULL){
            if(aux->direita->num == ordem[atual])
              aux = aux->direita;
          }
          if (aux->esquerda != NULL)
            ordem[i]= aux->esquerda->num;
          else
            ordem[i] = 0;
          //printf("ordem[%d] = %d \n",i, ordem[i]);
          i++;
          if (aux->direita != NULL)
            ordem[i]= aux->direita->num;
          else
            ordem[i] = 0;
          //printf("ordem[%d] = %d \n",i, ordem[i]);
          i++;
        }
        atual++;
    }
    atual = 1;
    i = 1;
    j = 1;
    numNivel = 2;
    //espacosParede = ((espacosEntre - 1) / 2) + 1;
    aumentaEspaco = ((espacosEntre - 1) / 2) + 1;
    for(cont = 0; cont < (altura-1) ;cont++){
      espacosParede = espacosParede + aumentaEspaco;
      aumentaEspaco = 2*aumentaEspaco;
    }
    for(cont = 0; cont < (altura-1) ;cont++){
      espacosEntre = (2*espacosEntre) + 1;
    }
    //printf("espacos parede: %d\n", espacosParede);
    //printf("espacos entre: %d\n", espacosEntre);
    for(cont = 0;cont < espacosParede;cont++){
      printf(" ");
    }
    printf("%d\n",ordem[0]);
    aumentaEspaco = aumentaEspaco / 2;
    espacosParede = espacosParede - aumentaEspaco;
    aumentaEspaco = aumentaEspaco / 2;
    espacosEntre = espacosEntre - 1;
    espacosEntre = espacosEntre / 2;
    do{
      for(cont = 0;cont < espacosParede;cont++){
        printf(" ");
      }
      for(cont = 0;cont < numNivel;cont++){
        if(j % 2 == 1){
          if(ordem[j] != 0)
            printf("/");
          else
            printf(" ");
        }
        if(j % 2 == 0){
          if(ordem[j] != 0)
            printf("\\");
          else
            printf(" ");
        }
        if(cont < numNivel-1){
          for(contAux = 0; contAux < espacosEntre ;contAux++){
            printf(" ");
          }
        }
        j++;
      }
      printf("\n");
      for(cont = 0;cont < espacosParede;cont++){
        printf(" ");
      }
      for(cont = 0;cont < numNivel;cont++){
        if(i % 2 == 1){
          if(ordem[i] != 0)
            printf("%d",ordem[i]);
          else
            printf(" ");
        }
        if(i % 2 == 0){
          if(ordem[i] != 0)
            printf("%d",ordem[i]);
          else
            printf(" ");
        }
        if(cont < numNivel-1){
          if(ordem[i] >= 10){
            for(contAux = 0; contAux < espacosEntre-1;contAux++){
              printf(" ");
            }
          }
          else{
            for(contAux = 0; contAux < espacosEntre;contAux++){
              printf(" ");
            }
          }
        }
        i++;
      }
      printf("\n");
      numNivel = 2*numNivel;
      //atual++;
      //printf("espacos parede utilizado acima: %d\n", espacosParede);
      //printf("espacos entre utilizado acima: %d\n", espacosEntre);
      espacosParede = espacosParede - aumentaEspaco;
      aumentaEspaco = aumentaEspaco / 2;
      espacosEntre = espacosEntre - 1;
      espacosEntre = espacosEntre / 2;
      //printf("espacos parede: %d\n", espacosParede);
      //printf("espacos entre: %d\n", espacosEntre);
    }while(i < elementos);
}

//Verifica de arvore eh cheia (?)
void isFull() {
	
}

int getHeight(Arvore *arv) {
   if (arv == NULL) 
      return -1; // altura da árvore vazia
   else {
      int he = getHeight(arv->esquerda);
      int hd = getHeight(arv->direita);
      if (he < hd) {
		return hd + 1;
		}
      else{
		  
		  return he + 1;
		}
	}	
}

//remover valor
Arvore* retira(Arvore* arv, int valor){
	if (arv == NULL)
	return NULL;

	else if (arv->num > valor)
	arv->esquerda = retira(arv->esquerda, valor);

	else if (arv->num < valor)
	arv->direita = retira(arv->direita, valor);

	else { /* achou o elemento */
	if (arv->esquerda == NULL && arv->direita == NULL) { /* elemento sem filhos */
	free (arv);
	arv = NULL;
	}

	else if (arv->esquerda == NULL) { /* só tem filho à direita */
	Arvore* aux = arv;
	arv = arv->direita;
	free (aux);
	}

	else if (arv->direita == NULL) { /* só tem filho à esquerda */
	Arvore* aux = arv;
	arv = arv->esquerda;
	free (aux);
	}

	else { /* tem os dois filhos */
	Arvore* pai = arv;
	Arvore* filho = arv->esquerda;
	while (filho->direita != NULL) {
	pai = filho;
	filho = filho->direita;
	}

	arv->num = filho->num; /* troca as informações */
	filho->num = valor;
	arv->esquerda = retira(arv->esquerda,valor);
	}
}
	
return arv;
}

//BALANCEAR ARVORE
//balaceamento dinamico de arvore

Arvore *rotacionaDireita(Arvore *raiz,Arvore *pai,Arvore *raizReal) {
  Arvore *aux = raiz->direita;
  if (pai != NULL)
  {
    if (pai->esquerda == raiz)
    {
      pai->esquerda = aux;
    }
    else
    {
      pai->direita = aux;
    }
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
  }
  else
  {
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    raizReal = aux;
  }

  return raizReal;
}

Arvore *rotacionaEsquerda(Arvore *raiz,Arvore *pai,Arvore *raizReal) {
  Arvore *aux = raiz->esquerda;
  if (pai != NULL)
  {
    if (pai->esquerda == raiz)
    {
      pai->esquerda = aux;
    }
    else
    {
      pai->direita = aux;
    }
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
  }
  else
  {
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    raizReal = aux;
  }
  return raizReal;
}

 int verificaBalanceamento(Arvore *arv){
   int verificador;
   if (arv != NULL)
   {
     verificador = getHeight(arv->esquerda) - getHeight(arv->direita);
     if (verificador < -1 || verificador > 1) //Se menor que -1 ou maior que 1, arvores nao estao balanceadas
     {
       return 0;
     }
     else
     {
       return 1;
   	}
}
 
}
 
Arvore *balanceia(Arvore *raiz, Arvore *pai, Arvore *arv_balanceada) {
  if (raiz != NULL)
  {
    if (!verificaBalanceamento(raiz))
    {
      arv_balanceada = balanceia(raiz->esquerda,raiz,arv_balanceada);
      if (verificaBalanceamento(raiz))
      {
        return arv_balanceada;
      }
      arv_balanceada = balanceia(raiz->direita,raiz,arv_balanceada);
      if (verificaBalanceamento(raiz))
      {
        return arv_balanceada;
      }
      if (getHeight(raiz->esquerda) > getHeight(raiz->direita))
      {
        arv_balanceada = rotacionaEsquerda(raiz,pai,arv_balanceada);
      }
      else
      {
        arv_balanceada = rotacionaDireita(raiz,pai,arv_balanceada);
      }
    }
  }
  return arv_balanceada;
}

Arvore *balanceTree(Arvore *arv) {
   if (verificaVazia(arv))
   {
     printf("Arvore vazia\n");
     return arv;
   }
   if(!verificaBalanceamento(arv))
   {
     do
     {
       arv = balanceia(arv,NULL,arv);
     } while(!verificaBalanceamento(arv));
   }
   else
   {
     printf("Arvore ja esta balanceada\n");
   }
   return arv;
 }

//IMPRIMIR ARVORE
//sae = sub arvore esquerda
//sad = sub arvore direita

//imprime pre ordem - raiz, percorre sae, sad
void printPreOrder (Arvore *arv) {
	
	if (!verificaVazia(arv)) {
	
	printf("%d\n",arv->num);
	printPreOrder(arv->esquerda);
	printPreOrder(arv->direita);
	}
}

//imprime em ordem - sae, raiz, sad;
void printInOrder(Arvore *arv) {

	if (!verificaVazia(arv)) {
	
	printInOrder(arv->esquerda);
	printf("%d\n",arv->num);
	printInOrder(arv->direita);
	}
}

//imprime pos ordem - sae, sad, raiz
void printPostOrder(Arvore *arv) {

	if (!verificaVazia(arv)) {
	
	printPostOrder(arv->esquerda);
	printPostOrder(arv->direita);
	printf("%d\n",arv->num);
	}
}

int main() {

Arvore *arv;
int valor;

char nome_arq [16];
printf("Nome do Arquivo:\n");
gets(nome_arq);
arv = loadTreeFromFile(nome_arq);

int altura = getHeight(arv)+1;
printf("Altura: %d\n", altura);

printf("ANTES DO BALANCEAMENTO\n");
showTree(arv,altura);

arv = balanceTree(arv);

printf("DEPOIS DO BALANCEAMENTO\n");
showTree(arv,altura);

printf("Valor a ser retirado:");
scanf("%d", &valor);
arv=retira(arv,valor);

altura = getHeight(arv)+1;
showTree(arv,altura);

return 0;
}
