#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS	7
#define INF 		9999


//===========================================================================
// Dijkstra의 최단경로
//===========================================================================
char vdata[]={'A','B','C','D','E','F','G'};

int adj[MAX_VTXS][MAX_VTXS]={
	{	0,	7,	INF, INF,	3,	10, INF },
	{	7,	0,	  4,  10,	2,	 6, INF },
	{ INF,	4,	  0,   2, INF, INF, INF },
	{ INF, 10,	  2,   0,  11,	 9,   4 },
	{	3,	2,	INF,  11,	0, INF,   5 },
	{  10,	6,	INF,   9, INF,	 0, INF },
	{ INF, INF, INF,   4,	5, INF,   0 }};

int path[MAX_VTXS];
int dist[MAX_VTXS];
int found[MAX_VTXS];

void print_step(int step)				// 진행 단계별 상황출력 
{
	int i;
	printf(" Step%2d:", step);
	for (i = 0; i<MAX_VTXS; i++)
		if (dist[i] == INF) printf("  INF");
		else printf("%5d", dist[i]);
		printf("\n");
}
void print_shortest_path(int start, int end)	// 최종 경로 출력 
{
	printf("[최단경로: %c---%c] %c", vdata[end], vdata[start], vdata[end]);
	while (path[end] != start) {
		printf("-%c", vdata[path[end]]);
		end = path[end];
	}
	printf("-%c\n", vdata[path[end]]);
}
int choose_vertex()
{
	int i, min = INF, minpos = -1;

	for (i = 0; i<MAX_VTXS; i++)
		if (dist[i]< min && !found[i]) {
			min = dist[i];
			minpos = i;
		}
	return minpos;
}
// Dijkstra의 최단경로
void shortest_path_dijkstra(int start)
{
	int i, u, w;
	for (i = 0; i<MAX_VTXS; i++) {
		dist[i] = adj[start][i];
		path[i] = start;
		found[i] = 0;
	}
	found[start] = 1;
	dist[start] = 0;

	for (i = 0; i<MAX_VTXS; i++) {
		print_step(i + 1);			// 진행상황 출력용 
		u = choose_vertex();
		found[u] = 1;

		for (w = 0; w<MAX_VTXS; w++) {
			if (found[w] == 0) {
				if (dist[u] + adj[u][w] < dist[w]) {
					dist[w] = dist[u] + adj[u][w];
					path[w] = u;
				}
			}
		}
	}
}
void main()
{
	int i;

	shortest_path_dijkstra(0);

	for (i = 1; i<MAX_VTXS; i++)
		print_shortest_path(0, i);	// 0부터 i까지의 최단경로 출력 
}
