#include "FilaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxRegistros = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  res->heap = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) {
    res->arranjo[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

bool exibirLog(PFILA f){
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f){
  return f->elementosNoHeap;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  if(id >= f->maxRegistros || id < 0 || f->arranjo[id]!=NULL || f->elementosNoHeap == f->maxRegistros) return false;
  PONT elem = (PONT) malloc(sizeof(PONT)); // cria um elemento do tipo PONT
  elem->id = id;
  elem->prioridade = prioridade;
  f->arranjo[id] = elem;
  elem->posicao = f->elementosNoHeap;
  if(f->elementosNoHeap == 0){ //se não há elementos no heap
    f->heap[0] = elem;
    f->elementosNoHeap++;
  }
  else{
    int i = elem->posicao;
    f->heap[i] = elem;
    int pai = (i-1)/2;
    while(elem->prioridade > f->heap[pai]->prioridade){
      // printf("****************\n");
      // printf("f->heap[pai]->id: %d \n", f->heap[pai]->id);
      // printf("elem->id: %d \n", elem->id);
      PONT aux = f->heap[pai];
      f->heap[pai] = elem;
      f->heap[i] = aux;
      f->heap[pai]->posicao = pai;
      f->heap[i]->posicao = i;

      i = elem->posicao;
      pai = (i-1)/2;
      // f->elementosNoHeap++;
      // printf("****************\n");
      // printf("f->heap[pai]->id: %d \n", f->heap[pai]->id);
      // printf("elem->id: %d \n", elem->id);
      // printf("f->heap[i]->id: %d \n", f->heap[i]->id);
      // printf("****************\n");

    }
    f->elementosNoHeap++;
  }
  return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  if(id < 0 || id >= f->maxRegistros || f->arranjo[id] == NULL || f->arranjo[id]->prioridade >= novaPrioridade) return false;
  PONT elem = f->arranjo[id];
  elem->prioridade = novaPrioridade;

  int i = elem->posicao;
  f->heap[i] = elem;
  int pai = (i-1)/2;
  while(elem->prioridade > f->heap[pai]->prioridade){
    PONT aux = f->heap[pai];
    f->heap[pai] = elem;
    f->heap[i] = aux;
    f->heap[pai]->posicao = pai;
    f->heap[i]->posicao = i;

    i = elem->posicao;
    pai = (i-1)/2;
  }
  return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  if(id < 0 || id >= f->maxRegistros || f->arranjo[id] == NULL || f->arranjo[id]->prioridade <= novaPrioridade) return false;
  PONT esq, dir, atual;
  int i, e, s;

  return false;
}

PONT removerElemento(PFILA f){
  if(f->elementosNoHeap == 0){ //fila vazia
    return NULL;
  }
  PONT raiz = f->heap[0];
  if(f->elementosNoHeap == 1){ //apenas raiz
    int i = raiz->posicao;
    f->heap[0] = NULL;
    f->arranjo[i] = NULL;
    f->elementosNoHeap--;
    return raiz;
  }
  if(f->elementosNoHeap == 2){ //raiz + filho à esquerda
    PONT novoPai = f->heap[1];
    f->arranjo[raiz->id] = NULL;
    novoPai->posicao = 0;
    f->heap[0] = novoPai;
    f->heap[1] = NULL;
    f->elementosNoHeap--;
    return raiz;
  }

  PONT esq, dir, novoPai;
  int pai, i;

  esq = f->heap[1];
  dir = f->heap[2];

  printf("raiz %f\n ", raiz->prioridade);
  printf("esquerda %f \n", esq->prioridade);
  printf("direita %f \n", dir->prioridade);


  if(esq->prioridade > dir->prioridade) novoPai = esq;
  else novoPai = dir;
  printf("novo pai: %f \n", novoPai->prioridade);

  i = novoPai->posicao; //posição ATUAL do pai
  printf("i %d\n", i);

  pai = (i-1)/2;

  printf("pai %d\n", pai);

  printf("%d \n", ((i*2)+1));
  printf("%f \n", f->heap[3]->prioridade);
  if (f->heap[((i*2)+1)]) esq = f->heap[((i*2)+1)];
  else esq = NULL;
  printf("ESQUERDA PRIORIDADE %f \n\n", esq->prioridade);
  if (f->heap[((i*2)+2)]) dir = f->heap[((i*2)+2)];
  else dir = NULL;
  printf("DIREITA %p \n\n", dir);
  if(esq || dir){ //verifica se tem filhos
    //mexe nos filhos
    if(esq && !dir){
      novoPai->posicao = pai;
      f->heap[pai] = novoPai; //novoPai vira a raiz do heap
      f->heap[esq->posicao] = NULL;
      printf("f->heap[i] %f \n", f->heap[i]->prioridade);
      f->heap[i] = esq;
      esq->posicao = i; //i é a antiga posição do pai
    }
    if(dir && !esq){ //Não ocorre se tudo estiver certo
      novoPai->posicao = pai;
      f->heap[pai] = novoPai; //novoPai vira a raiz do heap
      f->heap[dir->posicao] = NULL;
      printf("f->heap[i] %f \n", f->heap[i]->prioridade);
      f->heap[i] = dir;
      dir->posicao = i; //i é a antiga posição do pai
    }
    if(esq && dir){
      PONT sobe = esq;
      if (esq->prioridade > dir->prioridade) sobe = esq;
      else sobe = dir;
    }
  }
  else{ //se não tem filhos
    novoPai->posicao = pai;
    f->heap[pai] = novoPai; //novoPai vira a raiz do heap
    f->heap[i] = NULL;
  }

  // laço de repetição fim


  f->arranjo[raiz->id] = NULL;
  f->elementosNoHeap--;
  return raiz;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  if(id >= f->maxRegistros || id < 0 || f->arranjo[id] == NULL) return false;
  else{
    *resposta = f->arranjo[id]->prioridade;
    return true;
  }
}

