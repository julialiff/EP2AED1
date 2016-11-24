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
  /* completar */
  return false;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  /* completar */
  return false;
}

PONT removerElemento(PFILA f){
  /* completar */
  return NULL;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  /* completar */
  return false;
}

