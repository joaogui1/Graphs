#include "graph.h"
#include <string.h>

int min(int a, int b){
  return (a + b - abs(a - b))/2;
  // return (a > b)?b:a;
}

int noError() {	return 0; }

/*----------------------------------------------------------*/
/*	Create graph 	*/
graph* createGraph(int* n, int* dir, int* wei, int* error) {
	if((*n) >= MAXV || (*n) < 0) {
		*error = 1;
		return NULL;
	}

	graph* g = (graph*)calloc(sizeof(graph), 1);

	if(g == NULL) return NULL;

	g->numEdges = 0;
	g->numVertices = *n;
	g->directed = *dir;
	g->weighted = *wei;

	for(int i = 0; i < (*n); i++) {
		for(int j = 0; j < (*n); j++) {
			g->edges[i][j] = noEdge;
		}
	}

	*error = noError();
	return g;
}

void printEdges(graph* g){
	for(int i = 0; i < g->numVertices; i++) {
		for(int j = 0; j < g->numVertices; j++) {
			printf("%d ", g->edges[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

/*----------------------------------------------------------*/
/*	Insert edge in g from one vertex to another with a certain weight 	*/
void insertEdge(graph* g, int* from, int* to, elem* weight, int* error) {
	if(!g->weighted) *weight = 1;
	g->edges[*from][*to] = *weight;
	g->numEdges++;
	if(!g->directed) g->edges[*to][*from] = *weight;

	*error = noError();
	return;
}

/*----------------------------------------------------------*/
/*	Remove edge in g from one vertex to another 	*/
void removeEdge(graph* g, int* from, int* to, int* error) {
		if(*from < 0 || *to < 0 || *from >= g->numVertices || *to >= g->numVertices) {
		*error = 1;
		return;
	}

	if(g->edges[*to][*from] == noEdge){
		*error = 2;
		return;
	}

	g->edges[*from][*to] = noEdge;
	g->edges[*to][*from] = noEdge;
	*error = noError();
	return;
}

/*----------------------------------------------------------*/
/*	Transpose graph 	*/
graph* traspose(graph* g, int* error){

	graph* new = createGraph(&g->numVertices, &g->directed, &g->weighted, error);

	if(*error) return NULL;

	for(int i = 0; i < g->numVertices; i++) {
		for(int j = 0; j < g->numVertices; j++) {
			new->edges[i][j] = g->edges[j][i];
		}
	}

	*error = noError();
	return new;
}


/*----------------------------------------------------------*/
/*	Calculates the degree of a vertex 	*/
int degree(graph* g, int* v, int* error) {

	int degree = 0;
	for(int i = 0; i < g->numVertices; i++) {
		if(g->edges[*v][i] != noEdge) degree++;
	}

	return degree;
}

/*----------------------------------------------------------*/
/* 	Return weather a vertex has neighboors*/
int noNeighboor(graph* g, int *v, int* error){

	if(*v >= g->numVertices) {
		*error = 1;
		return 1;
	}

	*error = 0;
	return (degree(g, v, error) == 0);

}

/*----------------------------------------------------------*/
/*	 Return the first neighboor of a vertex 	*/
int firstNeighboor(graph* g, int *v, int* error){

	if(*v >= g->numVertices) {
		*error = 1;
		return 1;
	}

	*error = 0;
	int first = -1;
	for(int i = 0; i < g->numVertices; i++) {
		if(g->edges[*v][i]) {
			first = i;
			break;
		}
	}
	return first;
}

/*----------------------------------------------------------*/
/*	 go to the next neighboor 	*/
void nextNeighboor(graph* g, int* v, int* adj, elem* p, int* next, int* endList, int* error) {

	if(*v >= g->numVertices) {
		*error = 1;
		return;
	}

	*error = 0;
	*adj = *next;
	*p = g->edges[*v][*next];
	(*next)++;

	while(*next < g->numVertices && (g->edges[*v][*next] == noEdge)) (*next)++;
	if(*next >= g->numVertices) *endList = 1;
}

/* 	Return the id of the least weighted edge   */
int leastWeightedEdge(graph* g, int* u, int* v, int* error) {

	int min = -0x3f3f3f3f;

	for(int i = 0; i < g->numVertices; i++) {
		for(int j = 0; j < g->numVertices; j++) {
			if(g->edges[i][j] != noEdge && g->edges[i][j] < min) {
				*u = i;
				*v = j;
				min = g->edges[i][j];
			}
		}
	}

	return min;
}


void dfs(graph* g, int u, int* visited){
	visited[u] = 1;
	for(int i = 0; i < g->numVertices; i++)
		if(g->edges[u][i] && !visited[i])
			dfs(g, i, visited);
	return;
}

void tarjan(graph* g, int u, int* visited, int* low, int* time, int** isBridge, int* t, int p) {
	time[u] = (*t)++;
	low[u] = time[u];
	visited[u] = 1;

	for(int i = 0; i < g->numVertices; i++) {
		if(i == p) continue;

		if(g->edges[u][i] && !visited[i]) {
			tarjan(g, i, visited, low, time, isBridge, t, u);
			low[u] = min(low[u], low[i]);

			if(low[i] > time[u]) {
				isBridge[u][i] = 1;
				isBridge[i][u] = 1;
			}

		} else if(g->edges[u][i]) {
			low[u] = min(low[u], time[i]);
		}
	}

	return;
}

int hasCycle(graph* g, int* error) {

	for(int i = 0; i < g->numVertices; i++) {
		int deg = degree(g, &i, error);
		if(deg & 1 || !deg) {
			return 0;
		}
	}

	return 1;
}

void findBridges(graph* g, int** isBridge){
	int *low, *time, *visited, t = 0, zero = 0;
	low = calloc(g->numVertices, sizeof(int));
	time = calloc(g->numVertices, sizeof(int));
	visited = calloc(g->numVertices, sizeof(int));

	tarjan(g, 0, visited, low, time, isBridge, &zero, -1);
	free(low);
	free(time);
	free(visited);
}

void findEulerCycle(graph* g, int u, int size, int* path, int** isBridge, int* error) {
	if(degree(g, &u, error) == 1){
		path[size] = u;
		int i = firstNeighboor(g, &u, error);
		removeEdge(g, &u, &i, error);
		findBridges(g, isBridge);
		findEulerCycle(g, i, size+1, path, isBridge, error);
		return;
	} else {
		for(int i = 0; i < g->numVertices; i++) {
			if(g->edges[u][i] && !isBridge[u][i]) {
				path[size] = u;
				removeEdge(g, &u, &i, error);
				findBridges(g, isBridge);
				findEulerCycle(g, i, size+1, path, isBridge, error);
				return;
			}
		}
	}
	return;
}

int* eulerCycle(graph* g, int* error){

	if(!hasCycle(g, error)) return NULL;

	int* visited = calloc(g->numVertices, sizeof(int));
	int** isBridge = calloc(g->numVertices, sizeof(int*));

	for(int i = 0; i < g->numVertices; i++) {
		isBridge[i] = calloc(g->numVertices, sizeof(int));
	}
	findBridges(g, isBridge);

	// for(int i = 0; i < g->numVertices; i++) {
	// 	for(int j = 0; j < g->numVertices; j++) {
	// 		printf("%d ", isBridge[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	dfs(g, 0, visited);
	for(int i = 0; i < g->numVertices; i++) {
		if(!visited[i]) return NULL;
	}

	int* path = calloc(g->numEdges+1, sizeof(int));
	findEulerCycle(g, 0, 0, path, isBridge, error);

	free(visited);
	return path;
}

void destroyGraph(graph* g, int* error){
	if(g != NULL) free(g);
	*error = noError();
	return;
}

/*---------------------------------*/
void printGraph(graph* g){
  for(int i = 0; i < g->numVertices; i++){
    for(int j = 0; j < g->numVertices; j++){
      printf("%d ", g->edges[i][j]);
    }
    printf("\n");
  }
}