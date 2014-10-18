#include <stdio.h>
#include <stdlib.h>
#include "river.h"


void Map_print(int num_vertices, Vertex * vertex_array, int num_lines)
{
	int i = 0;
	//printf("%d", num_vertices);
	for(i = 0; i < num_vertices; i++)
	{

		printf("%d", vertex_array[i].status);
		if(i > 0)
		{
			if((i+1) % (num_lines) == 0)
			{
				printf("\n");
			}
		}

	}

}

//Load information from the input file
Vertex * Load_File(char *Filename, int *num_vertices, int *num_lines)
{
	//open and initialize file
	FILE *myfile = NULL;
	Vertex * vertex_array = NULL;
	myfile = fopen(Filename, "r");
	if(myfile == NULL)
	{
		printf("File did not open");
	}
	int i = 0;
	int buffer = 0;
	int temp = 0;
	//account for ASCII
	while((buffer = fgetc(myfile)) != 10)
	{
		temp = (buffer - 48) + temp*10*i;
		//printf("%d \n", buffer);
		i++;
	}
	*num_lines = temp;
	//printf("%d\n", *num_lines);
	
	temp = *num_lines;
	*num_vertices = temp*(temp-1);

	vertex_array = malloc(sizeof(Vertex) * (*num_vertices));
	
	i = 0;
	while((buffer = fgetc(myfile)) != EOF)
	{
		//buffer = fgetc(myfile);
		//printf("%d \n", buffer);
	//scan some shit into here later
		if(buffer == '1')
		{
			if(i%(temp) == 0)
			{
				vertex_array[i] = Vertex_construct(1,i,0);
			}
			else
			{
				vertex_array[i] = Vertex_construct(1,i,1000);
			}
			
		//	printf("1\n");
			i++;
		}
		if(buffer == '0')
		{
			if(i%(temp) == 0)
			{
				vertex_array[i] = Vertex_construct(0,i,0);
			}
			else
			{
				vertex_array[i] = Vertex_construct(0,i,1000);
			}
			//printf("0\n");
			i++;
		}

	}
	//printf("%d",i);
	return vertex_array;
}

Vertex Vertex_construct(int status, int index, int weight)
{
	Vertex vertex;
	vertex.status = status;
	vertex.index = index;
	vertex.weight = weight;

	return vertex;
}

Edge Edge_construct(int vertex_one, int vertex_two, int weight)
{
	Edge edge;
	edge.vertex_one = vertex_one;
	edge.vertex_two = vertex_two;
	edge.weight = weight;

	return edge;
}

Edge * Edge_assign(Vertex * vertex_array,int num_lines, int num_vertices, int * total_edges)
{
	int i = 0;
	int sides = 0;
	int corners = 2;
	int middle = 0;
	int j = 0;
	//Edge edge = Edge_construct(1,1,1);

	//calculate the amount of edges per vertex type	
	sides = (num_lines-2)*2 + (num_lines-3);
	middle = num_vertices - corners - sides - 2 - (num_lines - 3);
	*total_edges = middle*7+sides*3+corners*2;

	Edge * edge_array = malloc(sizeof(Edge) * (*total_edges));
	//printf("corners = %d, sides = %d, middle = %d", corners,sides,middle);

	//initialize top left corner
	//link to right vertex;
	if(vertex_array[1].status == 1 && vertex_array[0].status == 1)
	{
		edge_array[j++] = Edge_construct(vertex_array[0].index, vertex_array[1].index,1);
	}
	else if(vertex_array[1].status != vertex_array[0].status)
	{
		edge_array[j++] = Edge_construct(vertex_array[0].index, vertex_array[1].index,2);
	}
	else
	{
		edge_array[j++] = Edge_construct(vertex_array[0].index, vertex_array[1].index,3);
	}
	//link to diagonal down right vertex
	if(vertex_array[num_lines+1].status == 1 && vertex_array[0].status == 1)
	{
		edge_array[j++] = Edge_construct(vertex_array[0].index, vertex_array[num_lines+1].index, 1);
	}
	else if(vertex_array[num_lines+1].status != vertex_array[0].status)
	{
		edge_array[j++] = Edge_construct(vertex_array[0].index, vertex_array[num_lines+1].index,2);
	}
	else
	{
		edge_array[j++] = Edge_construct(vertex_array[0].index, vertex_array[num_lines+1].index,3);
	}

	//initialize bottom left corner
	//link to right vertex
	if(vertex_array[num_lines*(num_lines-2)+1].status == 1 && vertex_array[num_lines*(num_lines-2)].status == 1)
	{
		edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2)].index, vertex_array[num_lines*(num_lines-2)+1].index, 1);
	}
	else if(vertex_array[num_lines*(num_lines-2)+1].status != vertex_array[num_lines*(num_lines-2)].status)
	{
		edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2)].index, vertex_array[num_lines*(num_lines-2)+1].index, 2);
	}
	else
	{
		edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2)].index, vertex_array[num_lines*(num_lines-2)+1].index, 3);
	}
	//link to diagonal up right vertex
	if(vertex_array[num_lines*(num_lines-2)+1-num_lines].status == 1 && vertex_array[num_lines*(num_lines-2)].status == 1)
	{
		edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2)].index, vertex_array[num_lines*(num_lines-2)+1-num_lines].index, 1);
	}
	else if(vertex_array[num_lines*(num_lines-2)+1-num_lines].status != vertex_array[num_lines*(num_lines-2)].status)
	{
		edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2)].index, vertex_array[num_lines*(num_lines-2)+1-num_lines].index, 2);
	}
	else
	{
		edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2)].index, vertex_array[num_lines*(num_lines-2)+1-num_lines].index, 3);
	}

	//initialize top row edges
	for(i = 1; i < num_lines-1; i++)
	{
		//link to right vertex
		if(vertex_array[i+1].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[i].index, vertex_array[i+1].index, 1);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[i].index, vertex_array[i+1].index, 2);
		}

		//link to down vertex
		if(vertex_array[i+num_lines].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[i].index, vertex_array[i+num_lines].index, 0);
		}
		else 
		{
			edge_array[j++] = Edge_construct(vertex_array[i].index, vertex_array[i+num_lines].index, 2);
		}

		//link to diagonal down right vertex
		if(vertex_array[i+num_lines+1].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[i].index, vertex_array[i+num_lines+1].index, 1);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[i].index, vertex_array[i+num_lines+1].index, 2);
		}

	}

	//initialize left row edges
	for(i = 1; i < num_lines - 2; i++)
	{
		//link to up right diagonal vertex
		if(vertex_array[i*num_lines-num_lines+1].status == 1 && vertex_array[i*num_lines].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines-num_lines+1].index, 1);
		}
		else if(vertex_array[i*num_lines-num_lines+1].status != vertex_array[i*num_lines].status)
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines-num_lines+1].index, 2);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines-num_lines+1].index, 3);
		}

		//link to right vertex
		if(vertex_array[i*num_lines+1].status == 1 && vertex_array[i*num_lines].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines+1].index, 1);
		}
		else if(vertex_array[i*num_lines+1].status != vertex_array[i*num_lines].status)
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines+1].index, 2);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines+1].index, 3);
		}

		//link to bot right diagonal vertex
		if(vertex_array[i*num_lines*2+1].status == 1 && vertex_array[i*num_lines].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines+num_lines+1].index, 1);
		}
		else if(vertex_array[i*num_lines*2+1].status != vertex_array[i*num_lines].status)
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines+num_lines+1].index, 2);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[i*num_lines].index, vertex_array[i*num_lines+num_lines+1].index, 3);
		}
	}

	//initialize bottom row edges
	for(i = 1; i < num_lines - 1; i++)
	{
		//link to up vertex
		if(vertex_array[num_lines*(num_lines-2) + i - num_lines].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2) + i].index, vertex_array[num_lines*(num_lines-2) + i - num_lines].index, 0);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2) + i].index, vertex_array[num_lines*(num_lines-2) + i - num_lines].index, 2);

		}
		//link to right vertex
		if(vertex_array[num_lines*(num_lines-2) + i + 1].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2) + i].index, vertex_array[num_lines*(num_lines-2) + i + 1].index, 1);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2) + i].index, vertex_array[num_lines*(num_lines-2) + i + 1].index, 2);
		}
		//link to up right vertex
		if(vertex_array[num_lines*(num_lines-2) + i - num_lines + 1].status == 1)
		{
			edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2) + i].index, vertex_array[num_lines*(num_lines-2) + i + 1 - num_lines].index, 1);
		}
		else
		{
			edge_array[j++] = Edge_construct(vertex_array[num_lines*(num_lines-2) + i].index, vertex_array[num_lines*(num_lines-2) + i + 1 - num_lines].index, 2);
		}

	}

	int k = 0;
	//initialize all middle vertex edges
	for(i = num_lines; i < num_lines * num_lines - num_lines * 2; i = i + num_lines)
	{
		for(k = 1; k < num_lines - 1; k++)
		{
			//link to up left vertex
			if(vertex_array[k+i-num_lines-1].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i-num_lines-1].index, 1);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i-num_lines-1].index, 2);
			}
			//link to up vertex
			if(vertex_array[k+i-num_lines].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i-num_lines].index, 0);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i-num_lines].index, 2);
			}
			//link to up right vertex
			if(vertex_array[k+i-num_lines+1].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i-num_lines+1].index, 1);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i-num_lines+1].index, 2);
			}
			//link to right vertex
			if(vertex_array[k+i+1].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+1].index, 1);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+1].index, 2);
			}
			//link to bottom right vertex
			if(vertex_array[k+i+num_lines+1].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+num_lines+1].index, 1);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+num_lines+1].index, 2);
			}
			//link to bottom vertex
			if(vertex_array[k+i+num_lines].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+num_lines].index, 0);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+num_lines].index, 2);
			}
			//link to bottom left vertex
			if(vertex_array[k+i+num_lines-1].status == 1)
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+num_lines-1].index, 1);
			}
			else
			{
				edge_array[j++] = Edge_construct(vertex_array[k+i].index, vertex_array[k+i+num_lines-1].index, 2);
			}
		}
	}




	//printf("j = %d\n", j);
	//printf("sides = %d\n",sides);
	//printf("middle = %d\n", middle);
	//printf("total edges = %d\n", *total_edges);
	return edge_array;

}


int Find_shortest(Vertex * vertex_array, Edge * edge_array, int num_lines, int num_vertices, int num_edges)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	//for every vertex
	//printf("vertex[2].weight = %d\n", vertex_array[2].weight);
	for(k = 0; k < num_lines; k++)
	{
	for(i = 0; i < num_vertices; i++)
	{
		if((i == 0) || (i%num_lines == 0))
		{
			/*if(vertex_array[i].status == 0)
			{
				vertex_array[i].weight = 1;
			}
			if(vertex_array[i].status == 1)
			{
				vertex_array[i].weight = 0;
			}*/
			if(count == 0)
			{
				vertex_array[i].weight = 0;
			}					
		}

		for(j = 0; j < num_edges; j++)
		{
			if(vertex_array[i].index == edge_array[j].vertex_one)
			{
				//printf("vertex_array[edge_array[j].vertex_two].weight = %d\n", vertex_array[edge_array[j].vertex_two].weight);
				//printf("vertex_array[i].weight + edge_array[j].weight = %d\n", vertex_array[i].weight + edge_array[j].weight);
				if(vertex_array[edge_array[j].vertex_two].weight > vertex_array[i].weight + edge_array[j].weight)
				{
					//printf("hi");
					//printf("vertex_2 = %d " , edge_array[j].vertex_two );
					vertex_array[edge_array[j].vertex_two].weight = vertex_array[i].weight + edge_array[j].weight;
					//printf("i = %d vertex[2].weight = %d\n",i, vertex_array[2].weight);
				}
			}
		
		}


	}
	count++;
}
	for(k = 0; k < num_vertices; k++)
	{
		//printf("index = %d weight = %d\n", vertex_array[k].index, vertex_array[k].weight);
	}

	int shortest_path = 1000;
	for(i = 1; i < num_lines; i++)
	{
		if(vertex_array[i*num_lines-1].weight < shortest_path)
		{
			shortest_path = vertex_array[i*num_lines-1].weight + 1;
		}
	}

	return shortest_path;
}



void Edge_print(Edge * edge_array, int total_edges)
{
	//printf("%d\n", total_edges);
	int i = 0;
	for(i = 0; i < total_edges; i++)
	{
		printf("vertex_one = %d vertex_two = %d weight = %d\n", edge_array[i].vertex_one, edge_array[i].vertex_two, edge_array[i].weight);
	}
}


int main(int argc, char ** argv)
{

	int num_vertices = 0;
	int num_lines = 0;
	int num_edges = 0;
	int shortest = 0;
	Vertex * vertex_array = NULL;
	Edge * edge_array = NULL;

	
	vertex_array = Load_File(argv[1], &num_vertices, &num_lines );
	//Map_print(num_vertices, vertex_array, num_lines);
	edge_array = Edge_assign(vertex_array, num_lines, num_vertices, &num_edges);
	//Edge_print(edge_array, num_edges);

	shortest = Find_shortest(vertex_array, edge_array, num_lines, num_vertices, num_edges);

	printf("%d\n", shortest);
	free(edge_array);
	free(vertex_array);
	return 0;
}