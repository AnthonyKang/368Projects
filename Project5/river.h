#ifndef RIVER_H
#define RIVER_H
typedef struct _vertex {
	int status;
	int index;
	int weight;
} Vertex;

typedef struct _edge {
	int vertex_one;
	int vertex_two;
	int weight;
} Edge;

Vertex * Load_File(char * , int *, int *);
Vertex Vertex_construct(int, int, int);
void Map_print(int, Vertex *, int);
Edge Edge_construct(int , int, int);
Edge * Edge_assign(Vertex*, int, int, int*);
int Find_shortest(Vertex* , Edge*, int, int, int);
void Edge_print(Edge*, int);


#endif