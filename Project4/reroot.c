#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "reroot.h"

//prints the values of a node depending on if its a leaf node or a cutline node
void Node_print(Node node)
{
	if(node.width > 0)
	{
		printf("(%le,%le) lcnode = %d rcnode = %d\n", node.width, node.height, node.lcnode, node.rcnode);
	}
	if(node.width == 0)
	{
		printf("%c lcnode = %d rcnode = %d\n",node.cutline, node.lcnode, node.rcnode);
	}

}

//pre-order printing using recursion
void Pre_Order(Node * node_array, int index)
{
	if(index <= -1)
	{
		return;
	}
	if(node_array[index].cutline == '-')
	{
		printf("(%le,%le)",node_array[index].width, node_array[index].height);
	}
	if((node_array[index].cutline == 'V') || (node_array[index].cutline == 'H'))
	{
		printf("%c", node_array[index].cutline);
	}
	Pre_Order(node_array, node_array[index].lcnode);
	Pre_Order(node_array, node_array[index].rcnode);
}

//post order printing using iteration because the nodes are already sorted in post order
void Post_Order(Node * node_array, int index)
{
	int i = 0;
	for(i = 0; i < index+1; i++)
	{
		if(node_array[i].cutline == '-')
		{
			printf("(%le,%le)",node_array[i].width, node_array[i].height);
		}
		if((node_array[i].cutline == 'V') || (node_array[i].cutline == 'H'))
		{
			printf("%c", node_array[i].cutline);
		}
	}
}

//In order printing using recursion
void In_Order(Node * node_array, int index)
{
	
	if(index <= -1)
	{
		return;
	}          
	In_Order(node_array, node_array[index].lcnode);
	if(node_array[index].cutline == '-')
	{
		printf("(%le,%le)",node_array[index].width, node_array[index].height);
	}
	if((node_array[index].cutline == 'V') || (node_array[index].cutline == 'H'))
	{
		printf("%c", node_array[index].cutline);
	}
	In_Order(node_array, node_array[index].rcnode);
}

//builds a node 
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

//Writes the packed tree information from the input file in to an output file
void Save_File(char *Filename, Node * node_array, int length)
{
	FILE *myfile = NULL;
	myfile = fopen(Filename, "w");
	int i = 0;
	for(i = 0; i<length; i++)
	{
		//only print information of rectangles
		if(node_array[i].cutline == '-')
		{
			fprintf(myfile, "%le %le %le %le\n", node_array[i].width, node_array[i].height, node_array[i].xcoord, node_array[i].ycoord);
		}
		//fprintf(myfile, "%le %le %le %le\n", node_array[i].width, node_array[i].height, node_array[i].xcoord, node_array[i].ycoord);
	}
	fclose(myfile);
}

//Loads the information from the input file in to an array of nodes
Node * Load_File(char *Filename, int *num_nodes)
{	
	//number of nodes
	int count = 0;
	char buffer = 0;

	//open and initialize file
	FILE *myfile = NULL;
	Node * node_array = NULL;
	myfile = fopen(Filename, "r");
	if(myfile == NULL)
	{
		printf("File did not open");
		return NULL;
	}

	//find the number of nodes
	int cut_nodes = 0;
	int block_nodes = 0;
	*num_nodes = 0;
	while((buffer = fgetc(myfile)) != EOF)
	{
		//finds the number of nodes;
		if((buffer == '(') || (buffer == 'V') || (buffer == 'H'))
		{
			count++;
			if((buffer == 'V') || (buffer == 'H'))
			{
				//finds the number of cut nodes
				cut_nodes++;
			}
		}

	}
	*num_nodes = count;

	//number of block nodes
	block_nodes = *num_nodes - cut_nodes;

	//allocate space for an array of nodes
	node_array = malloc(sizeof(Node) * (*num_nodes));

	//create each node and put it in the array
	double width;
	double height;
	int i = 0;
	
	//move back to the beginning of the file

	fseek(myfile, 0, SEEK_SET);

	//read the nodes in to an array, recognizing that a '(' precedes a rectangle node
	while((buffer = fgetc(myfile)) != EOF)
	{
		if(buffer == '(')
		{
			fscanf(myfile,"%le", &width);
			buffer = fgetc(myfile);
			fscanf(myfile,"%le", &height);
			buffer = fgetc(myfile);
			node_array[i] = Node_construct(0,0,-1,-1,'-',width,height,0,0,0,0);
			i++;
		}
		if((buffer == 'V') || (buffer == 'H'))
		{
			
			node_array[i] = Node_construct(0,0,-1,-1,buffer,0,0,0,0,0,0);
			i++;
		}

		
	}


	//printf("number of nodes = %d\n", *num_nodes);
	fclose(myfile);


	return node_array;

}
void Post_order_create(Node * node_array , int * index)
{
	//post order craetion of tree.

	//variable to hold a temp value because I can't add two pointers directly
	int temp = 0;
	
	//index is decremented after each assignment to traverse backwards through the array

	//if it sees a cutline node, that means it must have a right child
	if((node_array[*index].cutline == 'H') || (node_array[*index].cutline == 'V'))
	{
		//setting the rcnode
		temp = *index;
		node_array[temp].rcnode = temp-1;
		*index = temp - 1;

		//recursively call until it sees leafnode
		Post_order_create(node_array, index);		
		node_array[temp].lcnode = *index;
		Post_order_create(node_array, index);
		return;
	}
	if(node_array[*index].cutline == '-')
	{
		
		temp = *index;
		*index = temp - 1;
		return;
	}

}

void pack(Node * node_array, int array_size, int index, double l_width, double l_height)
{
	//packs a given rectangle tree

	//if this node is a rectangle, modify its values based on the cutline and other rectangle
	if(node_array[index].lcnode == -1)
	{
		node_array[index].xcoord = node_array[index].xcoord + l_width;
		node_array[index].ycoord = node_array[index].ycoord + l_height;
		return;
	}
	else
	{
		if(node_array[index].cutline == 'H')
		{	
			//reassigns values based on whether the left child or the right child has the bigger width
			pack(node_array, array_size, node_array[index].rcnode,l_width,l_height);
			pack(node_array, array_size, node_array[index].lcnode, l_width, node_array[node_array[index].rcnode].height + node_array[node_array[index].rcnode].ycoord);
			if(node_array[node_array[index].lcnode].width > node_array[node_array[index].rcnode].width)
			{
				node_array[index].width = node_array[node_array[index].lcnode].width;
			}
			else
			{
					node_array[index].width = node_array[node_array[index].rcnode].width;
			}
			node_array[index].height = node_array[node_array[index].lcnode].height + node_array[node_array[index].rcnode].height;

			//makes sure the recalculate the x and y coordinates of the each rectangle containing two child tree traingles
			node_array[index].xcoord = node_array[index].xcoord + l_width;
			node_array[index].ycoord = node_array[index].ycoord + l_height;	
				
				return;
			
		}
		if(node_array[index].cutline == 'V')
		{
			//reassigns values based on whether the left child or the right child has the bigger height
			pack(node_array, array_size, node_array[index].lcnode,l_width,l_height);
			pack(node_array, array_size, node_array[index].rcnode, node_array[node_array[index].lcnode].width + node_array[node_array[index].lcnode].xcoord, l_height);
			if(node_array[node_array[index].lcnode].height > node_array[node_array[index].rcnode].height)
			{
				node_array[index].height = node_array[node_array[index].lcnode].height;
			}
			else
			{
				node_array[index].height = node_array[node_array[index].rcnode].height;
			}
			node_array[index].width = node_array[node_array[index].lcnode].width + node_array[node_array[index].rcnode].width;

			//makes sure the recalculate the x and y coordinates of the each rectangle containing two child tree traingles
			node_array[index].xcoord = node_array[index].xcoord + l_width;
			node_array[index].ycoord = node_array[index].ycoord + l_height;
			return;
		}
	}
	return;
}

void reroot(Node * node_array,int length, int root_index, int leaf_index, double * width, double * height, double * area)
{
	//if the node on the bottom edge is a leaf node, do nothing, because we don't reroot the first left and first right edges
	if(node_array[leaf_index].cutline == '-')
	{
		return;
	}

	//store the values of the original nodes on the edge to be rerooted
	int old_root_lcnode = node_array[root_index].lcnode;
	int old_root_rcnode = node_array[root_index].rcnode;
	int old_root_parnode = node_array[root_index].parnode;
	char old_root_cutline = node_array[root_index].cutline;
	double old_root_width = node_array[root_index].width;
	double old_root_height = node_array[root_index].height;
	double old_root_xcoord = node_array[root_index].xcoord;
	double old_root_ycoord = node_array[root_index].ycoord;
	int old_leaf_lcnode = node_array[leaf_index].lcnode;
	int old_leaf_rcnode = node_array[leaf_index].rcnode;
	int old_leaf_parnode = node_array[leaf_index].parnode;
	char old_leaf_cutline = node_array[leaf_index].cutline;
	double old_leaf_width = node_array[leaf_index].width;
	double old_leaf_height = node_array[leaf_index].height;
	double old_leaf_xcoord = node_array[leaf_index].xcoord;
	double old_leaf_ycoord = node_array[leaf_index].ycoord;

	//variable to store the area after performing rerooting to compare with the current smallest area
	double new_area = 0;
	double best_width = 0;
	double best_height = 0;
	
	//determine if child node is left child or right child
	//then reroot on the left edge
	if(leaf_index == node_array[root_index].lcnode)
	{
		node_array[root_index].lcnode = node_array[leaf_index].rcnode;
		node_array[leaf_index].rcnode = root_index;
	}
	else if (leaf_index == node_array[root_index].rcnode)
	{
		node_array[root_index].rcnode = node_array[leaf_index].rcnode;
		node_array[leaf_index].rcnode = root_index;
	}

	//calculate width and height of the original root node, which is now the child of the original child node
	if(node_array[root_index].cutline == 'H')
	{
		if(node_array[node_array[root_index].lcnode].width > node_array[node_array[root_index].rcnode].width)
			{
				node_array[root_index].width = node_array[node_array[root_index].lcnode].width;
			}
			else
			{
					node_array[root_index].width = node_array[node_array[root_index].rcnode].width;
			}
			node_array[root_index].height = node_array[node_array[root_index].lcnode].height + node_array[node_array[root_index].rcnode].height;
	}
	if(node_array[root_index].cutline == 'V')
	{
		if(node_array[node_array[root_index].lcnode].height > node_array[node_array[root_index].rcnode].height)
			{
				node_array[root_index].height = node_array[node_array[root_index].lcnode].height;
			}
			else
			{
				node_array[root_index].height = node_array[node_array[root_index].rcnode].height;
			}
			node_array[root_index].width = node_array[node_array[root_index].lcnode].width + node_array[node_array[root_index].rcnode].width;
	}

	//calculate width and height of the new root node, which was the original child node, using the newly calculated dimensions of the original root node
	if(node_array[leaf_index].cutline == 'H')
	{
		if(node_array[node_array[leaf_index].lcnode].width > node_array[node_array[leaf_index].rcnode].width)
			{
				node_array[leaf_index].width = node_array[node_array[leaf_index].lcnode].width;
			}
			else
			{
					node_array[leaf_index].width = node_array[node_array[leaf_index].rcnode].width;
			}
			node_array[leaf_index].height = node_array[node_array[leaf_index].lcnode].height + node_array[node_array[leaf_index].rcnode].height;
	}
	if(node_array[leaf_index].cutline == 'V')
	{
		if(node_array[node_array[leaf_index].lcnode].height > node_array[node_array[leaf_index].rcnode].height)
			{
				node_array[leaf_index].height = node_array[node_array[leaf_index].lcnode].height;
			}
			else
			{
				node_array[leaf_index].height = node_array[node_array[leaf_index].rcnode].height;
			}
			node_array[leaf_index].width = node_array[node_array[leaf_index].lcnode].width + node_array[node_array[leaf_index].rcnode].width;
	}

	//compare newly calculated area with old area

	new_area = node_array[leaf_index].width * node_array[leaf_index].height;
	best_width = node_array[leaf_index].width;
	best_height = node_array[leaf_index].height;
	
	//if the area is smaller then reassign the width and height used to calculate that area
	if(new_area < *area)
	{
		*area = new_area;
		*width = best_width;
		*height = best_height;
	}

	//call reroot on the left child
	reroot(node_array, length, leaf_index, node_array[leaf_index].lcnode, width, height, area);

	//unreroot the node and reassign its values
	node_array[root_index].lcnode = old_root_lcnode;
	node_array[root_index].rcnode = old_root_rcnode;
	node_array[root_index].parnode = old_root_parnode;
	node_array[root_index].cutline = old_root_cutline;
	node_array[root_index].width = old_root_width;
	node_array[root_index].height = old_root_height;
	node_array[root_index].xcoord = old_root_xcoord;
	node_array[root_index].ycoord = old_root_ycoord;
	node_array[leaf_index].lcnode = old_leaf_lcnode;
	node_array[leaf_index].rcnode = old_leaf_rcnode;
	node_array[leaf_index].parnode = old_leaf_parnode;
	node_array[leaf_index].cutline = old_leaf_cutline;
	node_array[leaf_index].width = old_leaf_width;
	node_array[leaf_index].height = old_leaf_height;
	node_array[leaf_index].xcoord = old_leaf_xcoord;
	node_array[leaf_index].ycoord = old_leaf_ycoord;

	//reroot along the other edge
	if(leaf_index == node_array[root_index].lcnode)
	{
		node_array[root_index].lcnode = node_array[leaf_index].lcnode;
		node_array[leaf_index].lcnode = root_index;
	}
	else if (leaf_index == node_array[root_index].rcnode)
	{
		node_array[root_index].rcnode = node_array[leaf_index].lcnode;
		node_array[leaf_index].lcnode = root_index;
	}

	//calculate width and height of the original root node, which is now the child of the original child node
	if(node_array[root_index].cutline == 'H')
	{
		if(node_array[node_array[root_index].lcnode].width > node_array[node_array[root_index].rcnode].width)
			{
				node_array[root_index].width = node_array[node_array[root_index].lcnode].width;
			}
			else
			{
					node_array[root_index].width = node_array[node_array[root_index].rcnode].width;
			}
			node_array[root_index].height = node_array[node_array[root_index].lcnode].height + node_array[node_array[root_index].rcnode].height;
	}
	if(node_array[root_index].cutline == 'V')
	{
		if(node_array[node_array[root_index].lcnode].height > node_array[node_array[root_index].rcnode].height)
			{
				node_array[root_index].height = node_array[node_array[root_index].lcnode].height;
			}
			else
			{
				node_array[root_index].height = node_array[node_array[root_index].rcnode].height;
			}
			node_array[root_index].width = node_array[node_array[root_index].lcnode].width + node_array[node_array[root_index].rcnode].width;
	}

	//calculate width and height of the new root node, which was the original child node, using the newly calculated dimensions of the original root node
	if(node_array[leaf_index].cutline == 'H')
	{
		if(node_array[node_array[leaf_index].lcnode].width > node_array[node_array[leaf_index].rcnode].width)
			{
				node_array[leaf_index].width = node_array[node_array[leaf_index].lcnode].width;
			}
			else
			{
					node_array[leaf_index].width = node_array[node_array[leaf_index].rcnode].width;
			}
			node_array[leaf_index].height = node_array[node_array[leaf_index].lcnode].height + node_array[node_array[leaf_index].rcnode].height;
	}
	if(node_array[leaf_index].cutline == 'V')
	{
		if(node_array[node_array[leaf_index].lcnode].height > node_array[node_array[leaf_index].rcnode].height)
			{
				node_array[leaf_index].height = node_array[node_array[leaf_index].lcnode].height;
			}
			else
			{
				node_array[leaf_index].height = node_array[node_array[leaf_index].rcnode].height;
			}
			node_array[leaf_index].width = node_array[node_array[leaf_index].lcnode].width + node_array[node_array[leaf_index].rcnode].width;
	}

	//same area width calculations as above
	new_area = node_array[leaf_index].width * node_array[leaf_index].height;
	best_width = node_array[leaf_index].width;
	best_height = node_array[leaf_index].height;
	

	if(new_area < *area)
	{
		*area = new_area;
		*width = best_width;
		*height = best_height;
	}

	//call reroot on the right child
	reroot(node_array, length, leaf_index, node_array[leaf_index].rcnode, width, height, area);

	//reassign values again to go back to the original tree
	node_array[root_index].lcnode = old_root_lcnode;
	node_array[root_index].rcnode = old_root_rcnode;
	node_array[root_index].parnode = old_root_parnode;
	node_array[root_index].cutline = old_root_cutline;
	node_array[root_index].width = old_root_width;
	node_array[root_index].height = old_root_height;
	node_array[root_index].xcoord = old_root_xcoord;
	node_array[root_index].ycoord = old_root_ycoord;
	node_array[leaf_index].lcnode = old_leaf_lcnode;
	node_array[leaf_index].rcnode = old_leaf_rcnode;
	node_array[leaf_index].parnode = old_leaf_parnode;
	node_array[leaf_index].cutline = old_leaf_cutline;
	node_array[leaf_index].width = old_leaf_width;
	node_array[leaf_index].height = old_leaf_height;
	node_array[leaf_index].xcoord = old_leaf_xcoord;
	node_array[leaf_index].ycoord = old_leaf_ycoord;

}

int main(int argc, char ** argv)
{
	Node * node_array = NULL;
	int array_size = 0;
	int i = 0;

	//Load the file
	node_array = Load_File(argv[1], &array_size);
	int index = array_size - 1;
	double area = 0;
	double width = 0;
	double height = 0;
	clock_t start_t_sort;
	clock_t end_t_sort;
	start_t_sort = clock();

	//Assign the lcnode and rcnode values to each node in the array
	Post_order_create(node_array, &index);
	
	printf("\n");
	printf("Preorder:");
	Pre_Order(node_array, array_size-1);
	printf("\n");
	printf("\n");
	printf("Inorder:");
	In_Order(node_array, array_size-1);
	printf("\n");
 	printf("\n");
	printf("Postorder:");
	Post_Order(node_array, array_size-1);
	printf("\n");
	printf("\n");

	//packs the tree
	pack(node_array, array_size, array_size-1,0,0);

	//Save information to output file
	Save_File(argv[2], node_array, array_size);
	printf("Width: %le\n", node_array[array_size-1].width);
	printf("Height: %le\n", node_array[array_size-1].height);
	
	//intializes base case area for non rerooted tree
	area = node_array[array_size-1].width * node_array[array_size-1].height;
	
	//initializes base case width and height for non rerooted tree
	width = node_array[array_size-1].width;
	height = node_array[array_size-1].height;

	end_t_sort = clock();
	double total_t_sort = ((end_t_sort - start_t_sort)/(double)CLOCKS_PER_SEC);

	start_t_sort = clock();
	reroot(node_array, array_size-1, array_size-1, node_array[array_size-1].lcnode, &width, &height, &area);
	reroot(node_array, array_size-1, array_size-1, node_array[array_size-1].rcnode, &width, &height, &area);
	end_t_sort = clock();
	double total_reroot = ((end_t_sort - start_t_sort)/(double)CLOCKS_PER_SEC);

	printf("\n");

	//finds the first traingle of the tree
	while(node_array[i].lcnode > -1)
	{
		i++;
	}

	printf("X-coordinate: %le\n", node_array[i].xcoord);
	printf("Y-coordinate: %le\n", node_array[i].ycoord);
	printf("\n");

	printf("Elasped time: %le\n", total_t_sort);
	printf("\n");

	printf("Best width: %le\n", width);
	printf("Best height: %le\n", height);

	printf("\n");
	printf("Elasped time for re-rooting: %le\n", total_reroot);

	

	
	
	free(node_array);
	
	return 0;
}