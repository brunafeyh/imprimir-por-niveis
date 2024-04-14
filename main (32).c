#include <stdio.h>
#include <stdlib.h>

struct no { // estrutura de n´o para ´arvore bin´aria
    int info;
    struct no* esq;
    struct no* dir;
};

typedef struct no* arvore;
// estrutura de nó para fila
struct no_fila {
    arvore info;
    struct no_fila* prox;
};

typedef struct no_fila* fila;

int vazia(arvore r){
    return (r == NULL);
}

void libera_arvore(arvore r) {
    if (!vazia(r)) {
        libera_arvore(r->esq);
        libera_arvore(r->dir);
        free(r);
    }
}

// cria uma fila vazia
fila cria_fila() {
    return NULL;
}

// verifica se a fila está vazia
int vazia_fila(fila f) {
    return (f == NULL);
}

void libera_fila(fila f) {
    while (!vazia_fila(f)) { // enquanto a fila não estiver vazia
        fila aux = f->prox; // guarda o próximo nó da fila
        free(f); // libera a memória do nó atual
        f = aux; // avança para o próximo nó
    }
}

// insere um elemento na fila
fila insere_fila(fila f, arvore x) {
    fila novo = (struct no_fila*) malloc(sizeof(struct no_fila));
    novo->info = x;
    novo->prox = NULL;
    if (vazia_fila(f)) return novo;
    fila aux = f;
    while (aux->prox != NULL) aux = aux->prox;
    aux->prox = novo;
    return f;
}

// remove um elemento da fila
fila remove_fila(fila f, arvore* x) {
    if (vazia_fila(f)) return f;
    fila aux = f->prox;
    *x = f->info;
    free(f);
    return aux;
}


// imprime as chaves por níveis
void imprimir_por_niveis(arvore r) {
    fila f = NULL;
    f = insere_fila(f, r); // insere a raiz na fila
    while (!vazia_fila(f)) { // enquanto a fila não estiver vazia
        int n = 0; // contador de nós no nível atual
        fila aux = f; // ponteiro auxiliar para percorrer a fila
        while (aux != NULL) { // conta quantos nós há na fila
            n++;
            aux = aux->prox;
        }
        while (n > 0) { // enquanto houver nós no nível atual
            arvore x; // variável para armazenar o nó removido da fila
            f = remove_fila(f, &x); // remove o primeiro nó da fila
            printf("%d ", x->info); // imprime a chave do nó
            if (x->esq != NULL) f = insere_fila(f, x->esq); // insere o filho esquerdo na fila, se existir
            if (x->dir != NULL) f = insere_fila(f, x->dir); // insere o filho direito na fila, se existir
            n--; // decrementa o contador de nós no nível atual
        }
        printf("\n"); // imprime uma quebra de linha após cada nível
    }
    libera_fila(f); // libera a memória da fila
}

arvore insere_arvore_binaria(arvore r, int x){
    if(vazia(r)) {
        r = (struct no*) malloc(sizeof(struct no));
        r->info = x;
        r->esq = NULL;
        r->dir = NULL;
    }
    else if(x < r->info)
    r->esq = insere_arvore_binaria(r->esq, x);
    
    else // x >= r->info
    r->dir = insere_arvore_binaria(r->dir, x);
    
    return r;
}


int main(){
    arvore l1 = NULL;
    l1 = insere_arvore_binaria(l1, 10);
    l1 = insere_arvore_binaria(l1, 9);
    l1 = insere_arvore_binaria(l1, 30);
    l1 = insere_arvore_binaria(l1, 20);
    l1 = insere_arvore_binaria(l1, 15);
    l1 = insere_arvore_binaria(l1, 25);
    l1 = insere_arvore_binaria(l1, 27);


    imprimir_por_niveis(l1);
    libera_arvore(l1);
    l1 = NULL;

    return 0;
}

