#ifndef SORTING_H
#define SORTING_H
typedef struct _node {
	int thisnode;
	int parnode;
	int lcnode;
	int rcnode;
	char cutline;
	double width;
	double height;
	double xcoord;
	double ycoord; 
	char no_width;
	char no_height;
} Node;

Node * Load_File(char*, int*);
void Save_File(char*, Node*, int);
void Node_print(Node);
Node  Node_construct(int, int, int, int, char, double, double, char, char,double, double);
void Post_order_create(Node* , int* );
void pack(Node* , int , int , double , double );
void reroot(Node*, int, int, int, double*, double*, double*);
void In_Order(Node* , int);
void Pre_Order(Node*, int);
void Post_Order(Node*, int);

#endif