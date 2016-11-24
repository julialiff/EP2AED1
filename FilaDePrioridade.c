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
  /* completar */
  return 0;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  /* completar */
  if(id >= f->maxRegistros || id < 0 || f->arranjo[id]!=NULL) return false;
  PONT elem = (PONT) malloc(sizeof(PONT)); // cria um elemento do tipo PONT
  elem->id = id;
  elem->prioridade = prioridade;
  f->arranjo[id] = elem;
  if(f->elementosNoHeap == 0){ //se não há elementos no heap
    f->heap[0] = elem;
    f->elementosNoHeap = f->elementosNoHeap + 1;
    elem->posicao = 0;
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

