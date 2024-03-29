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
      PONT aux = f->heap[pai];
      f->heap[pai] = elem;
      f->heap[i] = aux;
      f->heap[pai]->posicao = pai;
      f->heap[i]->posicao = i;

      i = elem->posicao;
      pai = (i-1)/2;
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
  PONT esq, dir, atual, troca;
  int i, e, d;
  atual = f->arranjo[id];
  atual->prioridade = novaPrioridade;
  i = atual->posicao;
  e = i*2+1;
  d = i*2+2;
  if(e > f->maxRegistros) return true;

  while(f->heap[e]!=NULL || f->heap[d]!=NULL){ //se tem filhos:orig
    if(f->heap[e]) esq = f->heap[e];
    else esq = NULL;
    if(f->heap[d]) dir = f->heap[d];
    else dir = NULL;
    if(esq && !dir){
      troca = esq;
      if(atual->prioridade < troca->prioridade){
        int posicaoPai = atual->posicao;
        atual->posicao = troca->posicao;
        troca->posicao = posicaoPai;
        f->heap[atual->posicao] = atual;
        f->heap[troca->posicao] = troca;
        if(atual->posicao*2+1 > f->maxRegistros) break;
      }
    }
    if(esq && dir){
      if(esq->prioridade > dir->prioridade) troca = esq;
      else troca = dir;
      if(atual->prioridade < troca->prioridade){
        int posicaoPai = atual->posicao;
        atual->posicao = troca->posicao;
        troca->posicao = posicaoPai;
        f->heap[atual->posicao] = atual;
        f->heap[troca->posicao] = troca;
        if(atual->posicao*2+1 > f->maxRegistros) break;
      }
    }
    i = atual->posicao;
    e = i*2+1;
    d = i*2+2;
  }
  return true;
}

PONT removerElemento(PFILA f){
  if(f->elementosNoHeap == 0){ //fila vazia
    return NULL;
  }
  PONT raiz = f->heap[0];
  if(f->elementosNoHeap == 1){ //apenas raiz
    int i = raiz->posicao;
    f->heap[0] = NULL;
    f->arranjo[raiz->id] = NULL;
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

  PONT atual = f->heap[f->elementosNoHeap-1];
  f->heap[f->elementosNoHeap-1] = NULL;
  f->heap[0] = atual;

  PONT esq, dir, troca;
  int i, e, d;
  i = atual->posicao;
  e = i*2+1;
  d = i*2+2;
  if(e > f->maxRegistros){
    f->arranjo[raiz->id] = NULL;
    f->elementosNoHeap--;
    return raiz;
  }
  printf("raiz %d \n\n\n\n", raiz->id);


  while(f->heap[e]!=NULL || f->heap[d]!=NULL){ //se tem filhos:orig
    if(f->heap[e]) esq = f->heap[e];
    else esq = NULL;
    if(f->heap[d]) dir = f->heap[d];
    else dir = NULL;
    if(esq && !dir){
      troca = esq;
      if(atual->prioridade < troca->prioridade){
        int posicaoPai = atual->posicao;
        atual->posicao = troca->posicao;
        troca->posicao = posicaoPai;
        f->heap[atual->posicao] = atual;
        f->heap[troca->posicao] = troca;
        if(atual->posicao*2+1 > f->maxRegistros) break;
      }
    }
    if(esq && dir){
      if(esq->prioridade > dir->prioridade) troca = esq;
      else troca = dir;
      if(atual->prioridade < troca->prioridade){
        int posicaoPai = atual->posicao;
        atual->posicao = troca->posicao;
        troca->posicao = posicaoPai;
        f->heap[atual->posicao] = atual;
        f->heap[troca->posicao] = troca;
        if(atual->posicao*2+1 > f->maxRegistros) break;
      }
    }
    i = atual->posicao;
    e = i*2+1;
    d = i*2+2;
  }
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
