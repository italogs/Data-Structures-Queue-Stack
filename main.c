#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no{
	int info;
	struct no *prox;
}TNO;

typedef struct fila{
	TNO *ini,*fim;
}TFila;

typedef struct pilha{
	TNO *prim;
}TPilha;


TFila *inicializa(){
	TFila *f = (TFila *)malloc(sizeof(TFila));
	f->ini = f->fim = NULL;
	return f;
}


TPilha *p_inicializa(){
	TPilha *p = (TPilha *)malloc(sizeof(TPilha));
	p->prim = NULL;
	return p;
}


int vazia(TFila *f){
	return !f->ini;
}

int p_vazia(TPilha *p){
	return !p->prim;
}

void push(TPilha *p, int info){
	TNO *novo = (TNO *)malloc(sizeof(TNO));
	novo->info = info;
	novo->prox = p->prim;
	p->prim = novo;

}
int pop(TPilha *p){
	if(p_vazia(p)) exit(1);
	int resp = p->prim->info;
	TNO *q = p->prim;
	p->prim = p->prim->prox;
	free(q);
	return resp;
}

void p_libera(TPilha *p){
	TNO *q = p->prim;
	while(q){
		TNO *t = q;
		q = q->prox;
		free(t);
	}
	free(p);
}


void insere(TFila *f, int info) {
	TNO *novo = (TNO *)malloc(sizeof(TNO));
	novo->prox = NULL;
	novo->info = info;
	if(!f->fim)
		f->ini = f->fim = novo;
	else {
		f->fim->prox = novo;
		f->fim = novo;
	}
}


void print_fila(TFila *f){
	if(vazia(f)) return;
	TNO *aux = f->ini;
	while(aux){
		printf("%d, ",aux->info);
		aux=aux->prox;
	}
	printf("\n");
}


void print_pilha(TPilha *p){
	if(p_vazia(p)) return;
	TNO *aux = p->prim;
	while(aux){
		printf("%d, ",aux->info);
		aux=aux->prox;
	}
	printf("\n");
}

int retira(TFila *f){
	if(vazia(f)) exit(1);

	int resp = f->ini->info;
	TNO *p = f->ini;
	f->ini = f->ini->prox;
	if(!f->ini)
		f->fim = NULL;
	free(p);
	return resp;
}

void libera(TFila *f){
	TNO *p = f->ini,*q;
	while(p){
		q = p;
		p=p->prox;
		free(q);
	}
	free(f);
}

//LISTA 2 (PILHAS E FILAS)

//a)
TFila *p2f(TPilha *p){
	if(p_vazia(p)) return NULL;
	TFila *retorno = inicializa(), *aux = inicializa();
	while(!p_vazia(p)){
		int elem = pop(p);
		insere(retorno,elem);
		insere(aux,elem);
	}
	while(!vazia(aux)){
		push(p,retira(aux));
	}
	libera(aux);
	return retorno;
}

//b)
TFila *inv_fila(TFila *f){
	if(vazia(f)) return f;
	TFila *retorno = inicializa(),*aux = inicializa();
	TPilha *paux = p_inicializa();
	while(!vazia(f)){
		int elem = retira(f);
		push(paux,elem);
		insere(aux,elem);
	}
	while(!p_vazia(paux)){
		insere(retorno,pop(paux));
		insere(f,retira(aux));
	}
	libera(aux);
	p_libera(paux);
	return retorno;
}
//c)
TFila *sep_fila(TFila *f){
	if(vazia(f)) return NULL;
	TFila *par = inicializa(), *impar = inicializa();
	while(!vazia(f)){
		int elem = retira(f);
		if(elem%2==0){
			insere(par,elem);
		} else {
			insere(impar,elem);
		}
	}
	while(!vazia(impar)){
		insere(f,retira(impar));
	}
	libera(impar);
	return par;
}
//d)
TFila *junta_filas(TFila *f1,TFila *f2) {
	if(vazia(f1) && vazia(f2)) return NULL;
	TFila *aux = inicializa(),*retorno = inicializa();
	while(!vazia(f1)){
		int elem = retira(f1);
		insere(aux,elem);
		insere(retorno,elem);
	}
	while(!vazia(aux)){
		insere(f1,retira(aux));
	}

	while(!vazia(f2)){
		int elem = retira(f2);
		insere(aux,elem);
		insere(retorno,elem);
	}
	while(!vazia(aux)) {
		int elem = retira(aux);
		insere(f2,elem);
	}
	libera(aux);
	return retorno;
}
//e)
void retira_pares(TPilha *p){
	if(p_vazia(p)) return;
	TPilha *aux = p_inicializa();
	while(!p_vazia(p)){
		int elem = pop(p);
		if(elem %2!=0){
			push(aux,elem);
		}
	}
	while(!p_vazia(aux)){
		push(p,pop(aux));
	}
	p_libera(aux);
}
//f)
TPilha *f2p(TFila *f){
	if(vazia(f)) return NULL;
	TPilha *pilha = p_inicializa(), *p_aux = p_inicializa();
	TFila *f_aux = inicializa();
	while(!vazia(f)){
		int elem = retira(f);
		push(p_aux,elem);
		insere(f_aux,elem);
	}
	while(!p_vazia(p_aux)){
		push(pilha,pop(p_aux));
	}
	while(!vazia(f_aux)){
		insere(f,retira(f_aux));
	}
	libera(f_aux);
	p_libera(p_aux);
	return pilha;
}

//g)
void separa_filas(TFila *f,TFila *par,TFila *impar){
	if(vazia(f)) return;
	TFila *aux = inicializa();
	while(!vazia(f)){
		int elem = retira(f);
		if(elem % 2 == 0) {
			insere(par,elem);
		} else {
			insere(impar,elem);
		}
		insere(aux,elem);
	}
	while(!vazia(aux)) {
		insere(f,retira(aux));
	}
	libera(aux);
}


int main(){


	TFila *f1 = inicializa();
	TFila *f2 = inicializa();
	TFila *f3 = inicializa();

	// TPilha *p = p_inicializa();

	insere(f1,1);
	insere(f1,2);
	insere(f1,3);
	insere(f1,4);
	insere(f1,5);
	insere(f1,6);
	insere(f1,7);
	insere(f1,8);
	separa_filas(f1,f2,f3);
	print_fila(f1);
	print_fila(f2);
	print_fila(f3);

	// push(p,1);
	// push(p,3);
	// push(p,4);
	// push(p,5);
	// push(p,6);
	// push(p,7);

	// print_fila(p2f(p));
	// print_pilha(f2p(f));
	// print_fila(f);
	// print_fila(inv_fila(f));

	// TFila *f2 = sep_fila(f);
	// print_fila(f);
	// print_fila(f2);

	// print_fila(junta_filas(f,f2));
	// retira_pares(p);
	// print_pilha(p);
	return 0;
}