#ifndef SORTING_H
#define SORTING_H
typedef struct _node {
	long value;
	struct _node *next;
} Node;

typedef struct _list {
	Node *node;
	struct _list *next;
} List;
Node * move(Node*, int);
void Shell_Sort_Final(Node*);
Node * Shell_Sort(Node*);
Node * Shell_Sort_Swag(Node*);
void Print_list(Node*);
List * List_Reform(List*, int, int);
Node* node_insert_ascend(Node*, long);
List * List_Split(List * , int);
Node * Node_construct(long);
List * List_construct(Node*);
Node * Node_insert(Node*, long);
Node * Load_File(char*,int*);
int Save_File(char *, Node*);
int* Gap_Array(int* , int);
void free_node(Node*);
Node * Insertion_Sort(Node*);
#endif
