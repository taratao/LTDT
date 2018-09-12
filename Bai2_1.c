#include <stdio.h>


#define MAX 100
#define MAX_N 100
#define MAX_M 500

int parent[MAX];
int mark[MAX];

typedef struct{
	int data[MAX];
	int size;
}List;

typedef struct{
	int data[MAX];
	int front, rear;
}Queue;

typedef struct{
	int n, m;
	int A[MAX_N][MAX_M];
}Graph;

///////////////////////////////////////////////////////////////////////////////////////////////

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

void make_null_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

void push(Queue *Q, int X){
	Q->rear++;
	Q->data[Q->rear] = X;
}

int top(Queue *Q){
	return Q->data[Q->front];
}

void pop(Queue *Q){
	Q->front++;
}

int empty(Queue Q){
	return Q.front > Q.rear;
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
	parent[1] = 0;
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

void breath_first_search(Graph *G, int x){
	Queue frontier;
	make_null_queue(&frontier);
    int j;
    if(mark[x] == 1) return;
	push(&frontier, x);
	mark[x] = 1;
	while(!empty(frontier)){
		int x = top(&frontier);
		pop(&frontier);
		List L = neighbours(G, x); 
		for(j = 1; j <= count_list(&L); j++){
			int y = element_at(&L, j);
			if(mark[y] == 0) {
				mark[y] = 1;
				push(&frontier, y);
				parent[y] = x;
			}
		}
	}
	
	for(j = 1; j <= G->n; j++){
		if(mark[j] == 0) breath_first_search(G, j);
	}
	
}
////////////////////////////////////////////////////////////////////////////

void print(Graph G){
	int i, j;
	for(i = 1; i <= G.n; i++){
		for(j = 1; j <= G.m; j++){
			printf(" %d ", G.A[i][j]);
		}
		printf("\n");
	}
	
}

void printlist(List L){
	int i;
	for(i = 1; i <= L.size; i++){
		printf(" %d ", element_at(&L, i));
	}
}

int main(){
	Graph G;
	int n, m, j;
	scanf("%d%d", &n, &m);
	init(&G, n, m);
	int e = 1;
	while(!feof(stdin)){
		int x, y;
		scanf("%d%d", &x, &y);
		add_edge(&G, e, x, y);
		e++;
	}
	breath_first_search(&G, 1);
	for(j = 1; j <= G.n; j++){
		printf("%d %d\n", j, parent[j]);
	}
	return 0;
}
