#include <stdio.h>


#define MAX 100
#define MAX_N 100
#define MAX_M 500

typedef struct{
	int data[MAX];
	int size;
}List;

typedef struct{
	int data[MAX];
	int size;
}Stack;

typedef struct{
	int n, m;
	int A[MAX_N][MAX_M];
}Graph;

///////////////////////////////////////////////////////////////////////////////////////////////

int mark[MAX];
void make_null_list(List *L){
	L->size = 0;
}

void push_back(List *L, int X){
	L->data[L->size] = X;
	L->size++;
}

int element_at(List *L, int Position){
	return L->data[Position - 1];
}

//////////////////////////////////////////////////////////////////////////////////////////////

void make_null_stack(Stack *S){
	S->size = 0;
}

void push(Stack *S, int X){
	S->data[S->size] = X;
	S->size++;
}

int top(Stack *S){
	return S->data[S->size - 1];
}

void pop(Stack *S){
	S->size--;
}

int empty(Stack *S){
	return S->size == 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void init(Graph *G, int n, int m){
	int i, j;
	G->n = n;
	G->m = m;
	for(i = 1; i <= G->n; i++){
		for(j = 1; j <= G->m; j++){
			G->A[i][j] = 0;
		}
		mark[i] = 0;
	}
	
}

void add_edge(Graph *G, int e, int x, int y){
	G->A[x][e] = 1;
	G->A[y][e] = 1;
}

List neighbours(Graph *G, int x){
	int y, e;
	List L;
	make_null_list(&L);
	for(y = 1; y <= G->n; y++){
		if(x == y) continue;
		for(e = 1; e <= G->m; e++){
			if(G->A[x][e] == 1 && G->A[y][e] == 1){
				push_back(&L, y);
				break;
			}
		}
	}
	return L;
}

int count_list(List *L){
	return L->size;
}
////////////////////////////////////////////////////////////////////////////

void depth_first_search(Graph *G, int x){
	Stack S;
	make_null_stack(&S);
    int j;
    if(mark[x] == 1) return;
	push(&S, x);
	while(!empty(&S)){
		int x = top(&S);
		pop(&S);
		if(mark[x] != 0) continue;
		printf("%d\n", x);
		mark[x] = 1;
		List L = neighbours(G, x); 
		for(j = 1; j <= count_list(&L); j++){
			int y = element_at(&L, j);
			push(&S, y);
		}
	}
	
	for(j = 1; j <= G->n; j++){
		if(mark[j] == 0) depth_first_search(G, j);
	}
	
	
	
}
////////////////////////////////////////////////////////////////////////////


int main(){
	Graph G;
	int n, m;
//	freopen("dt1.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init(&G, n, m);
	int e = 1;
	while(!feof(stdin)){
		int x, y;
		scanf("%d%d", &x, &y);
		add_edge(&G, e, x, y);
		e++;
	}
	depth_first_search(&G, 1);
	return 0;
}
