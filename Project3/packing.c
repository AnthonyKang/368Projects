#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "packing.h"


//Creates a Node
Node Node_construct(int thisnode, int parnode, int lcnode, int rcnode, char cutline, double width, double height, char no_width, char no_height, double xcoord, double ycoord)
{
	Node node;
	node.thisnode = thisnode;
	node.parnode = parnode;
	node.lcnode = lcnode;
	node.rcnode = rcnode;
	node.cutline = cutline;
	node.width = width;
	node.height = height;
	node.xcoord = xcoord;
	node.ycoord = ycoord;
	node.no_width = no_width;
	node.no_height = no_height;
	return node;
}

//Prints the values of a node
void Node_print(Node node)
{
	printf("this node = %d parnode = %d lcnode = %d rcnode = %d cutline = %c width = %le height = %le no_width = %c no_height = %c xcoord = %le ycoord = %le\n", node.thisnode, node.parnode, node.lcnode, node.rcnode, node.cutline, node.width, node.height, node.no_width, node.no_height, node.xcoord, node.ycoord);
}

void Screen_dump(Node * node_array, int length)
{
	//fprintf(stderr, "length = %d", length);
	printf("Preorder: ");
	Pre_Order(node_array, length);
	printf("\n\n");
	printf("Inorder: ");
	In_Order(node_array, length);
	printf("\n\n");
	printf("Postorder: ");
	Post_Order(node_array, length);
	printf("\n\n");
	printf("Width:  %le\n", node_array[length].width);
	printf("Height:  %le\n", node_array[length].height);

	

}
void Pre_Order(Node * node_array, int index)
{
	if(index <= -1)
	{
		return;
	}
	if(node_array[index].thisnode > 0)
	{
		printf("%d ", node_array[index].thisnode);
	}

	Pre_Order(node_array, node_array[index].lcnode-1);
	Pre_Order(node_array, node_array[index].rcnode-1);
}
void In_Order(Node * node_array, int index)
{
	if(index <= -1)
	{
		return;
	}
	In_Order(node_array, node_array[index].lcnode-1);
	if(node_array[index].thisnode > 0)
	{
		printf("%d ", node_array[index].thisnode);
	}
	In_Order(node_array, node_array[index].rcnode-1);
}
void Post_Order(Node * node_array, int index)
{
	if(index <= -1)
	{
		return;
	}
	Post_Order(node_array, node_array[index].lcnode-1);
	Post_Order(node_array, node_array[index].rcnode-1);
	if(node_array[index].thisnode > 0)
	{
		printf("%d ", node_array[index].thisnode);
	}
}
void Save_File(char *Filename, Node * node_array, int length)
{
	FILE *myfile = NULL;
	myfile = fopen(Filename, "w");
	int i = 0;
	int j = 0;
	
	if(myfile == NULL)
	{
		printf("output file failed to open");
		return ;
	}
	for(i = 0; i < length; i++)
	{
		if(node_array[i].lcnode == -1)
		{
			j++;
		}
	}
	fprintf(myfile,"%d\n",j);
	for(i = 0; i < j; i++)
	{
		fprintf(myfile, "%d %le %le %le %le\n", node_array[i].thisnode, node_array[i].width, node_array[i].height, node_array[i].xcoord, node_array[i].ycoord);
		
	}
	i--;
	printf("\nX-coordinate:  %le\n", node_array[i].xcoord);
	printf("Y-coordinate:  %le\n\n", node_array[i].ycoord);
	fclose(myfile);
}
//Opens file and returns a array of nodes
Node * Load_File(char *Filename, int *num_nodes)
{
	//load the file and check if it actually opened
	FILE *myfile = NULL;
	Node * node_array = NULL;
	myfile = fopen(Filename, "r");
	if(myfile == NULL)
	{
		printf("File did not open");
		return NULL;
	}

	//find the number of blocks
	int num_blocks = 0;
	fscanf(myfile, "%d", &num_blocks);
	//printf("num_blocks = %d\n", num_blocks);

	//find the number of nodes
	*num_nodes = 0;
	fscanf(myfile,"%d", num_nodes);
	//printf("num_nodes = %d\n", *num_nodes);

	//number of non block nodes
	int cut_nodes = 0;
	cut_nodes = *num_nodes - num_blocks;

	//allocate space for an array of nodes
	node_array = malloc(sizeof(Node)* (*num_nodes)); 

	//create each node and put it in the array
	int i = 0;
	int thisnode;
	int parnode;
	int lcnode;
	int rcnode;
	char cutline;
	double width;
	double height;
	char no_width;
	char no_height;
	
	
	for(i = 0; i < num_blocks; i++)
	{
		fscanf(myfile, "%d %d %d %d %c %le %le", &thisnode, &parnode, &lcnode, &rcnode, &cutline, &width, &height);
		//printf("%d %d %d %d %c %le %le\n", thisnode, parnode, lcnode , rcnode, cutline, width, height);
		node_array[i] = Node_construct(thisnode, parnode, lcnode, rcnode, cutline, width, height,0,0,0,0);

	}
	for(i = 0; i < cut_nodes; i++)
	{
		fscanf(myfile, "%d %d %d %d %c %c %c", &thisnode, &parnode, &lcnode, &rcnode, &cutline, &no_width, &no_height);
		//printf("%d %d %d %d %c %c %c\n", thisnode, parnode, lcnode , rcnode, cutline, no_width, no_height);
		node_array[i+(int)num_blocks] = Node_construct(thisnode, parnode, lcnode, rcnode, cutline,0,0, no_width, no_height, 0,0);
	}
/*
	for(i = 0; i < *num_nodes; i++)
	{
		Node_print(node_array[i]);
	}
*/
	fclose(myfile);
	return node_array;

}


void pack(Node * node_array, int array_size, int index, double l_width, double l_height)
{
	if(node_array[index].lcnode == -1)
	{
		
		node_array[index].xcoord = node_array[index].xcoord + l_width;
		node_array[index].ycoord = node_array[index].ycoord + l_height;
		return;
	}
	else
	{
		
		//Tree traverse right child before left child because left child coordinates depend on right child dimensions
		if(node_array[index].cutline == 'H')
		{
			pack(node_array, array_size, node_array[index].rcnode-1,l_width,l_height);
			pack(node_array, array_size, node_array[index].lcnode-1, l_width,node_array[node_array[index].rcnode-1].height + node_array[node_array[index].rcnode-1].ycoord);
			if(node_array[node_array[index].lcnode-1].width > node_array[node_array[index].rcnode-1].width)
			{
				node_array[index].width = node_array[node_array[index].lcnode-1].width;
			}
			else
			{
				node_array[index].width = node_array[node_array[index].rcnode-1].width;
			}
			node_array[index].height = node_array[node_array[index].lcnode-1].height + node_array[node_array[index].rcnode-1].height;
			
			
			return;
		}
		//Tree traverse left child before right child because left child coordinates depend on right child dimensions
		if(node_array[index].cutline == 'V')
		{
			pack(node_array, array_size, node_array[index].lcnode-1,l_width,l_height);
			pack(node_array, array_size, node_array[index].rcnode-1, node_array[node_array[index].lcnode-1].width + node_array[node_array[index].lcnode-1].xcoord, l_height);
			if(node_array[node_array[index].lcnode-1].height > node_array[node_array[index].rcnode-1].height)
			{
				node_array[index].height = node_array[node_array[index].lcnode-1].height;
			}
			else
			{
				node_array[index].height = node_array[node_array[index].rcnode-1].height;
			}
			node_array[index].width = node_array[node_array[index].lcnode-1].width + node_array[node_array[index].rcnode-1].width;
			return;
		}
	}
	return;
}

int main(int argc, char ** argv)
{
	Node * node_array = NULL;
	int array_size = 0;

	node_array = Load_File(argv[1], &array_size);
	//printf("array_size = %d\n", array_size);

	//time how long it takes to pack
	clock_t start_t_sort;
	clock_t end_t_sort;
	start_t_sort = clock();

	pack(node_array, array_size-1, array_size-1, 0,0);
	
	end_t_sort = clock();
	double total_t_sort = ((end_t_sort - start_t_sort)/(double)CLOCKS_PER_SEC);
	
	Screen_dump(node_array, array_size-1);

	Save_File(argv[2], node_array, array_size);
	printf("Elasped time: %le\n", total_t_sort);
	free(node_array);
	return 0;
}
