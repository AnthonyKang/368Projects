#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"
#include <time.h>

int main(int argc, char ** argv)
{
	List *Head_list = NULL;
	//List *test_list = NULL;
	int n = 0;
	//int n = 0;
	//int k = 0;
	//int length = 0;
	clock_t start_t_sort;
	clock_t end_t_sort;
	clock_t start_t_io;
	clock_t end_t_io;
	//	int *gaps = NULL;
	//Node* temp = NULL;
	//List* temp_l = NULL;
	//List * new_list = NULL;	
	//	printf("hi\n");
	Head_list = List_construct(NULL);
	//Print_list(Head_list->node);
	start_t_io = clock();
        Head_list -> node = Load_File(argv[1],&n);
	end_t_io = clock();
	double total_t_io = (end_t_io - start_t_io)/(double)CLOCKS_PER_SEC;
	//Shell_Sort_Swag(Head_list->node);
	//test_list = List_Split(Head_list,3);
	//Insertion_Sort(Head_list->node);
	//test_list = List_Reform(test_list,n,n);
	//Print_list(Head_list->node);
	/*if(Head_list == NULL)
	{
		printf("initialize success");
		}*/
	/*Node * len = 0;
	len = Head_list ->node;
	while(len!=NULL)
	  {
	    len = len -> next;
	    length++:
	  }
	length = length -1;

	n = Save_File(argv[2], Head_list -> node);
	gaps = malloc(sizeof(int) * n);
	gaps = Gap_Array(gaps, n);
	while(gaps[k]>0)
	  {
	    k++;
	    }*/
	start_t_sort = clock();
	Shell_Sort_Final(Head_list -> node);
	end_t_sort = clock();
	double total_t_sort = (end_t_sort - start_t_sort)/(double)CLOCKS_PER_SEC;
	//Print_list(Head_list->node);
	start_t_io = clock();
	n = Save_File(argv[2], Head_list->node);
	end_t_io = clock();
	total_t_io = ((end_t_io - start_t_io)/(double)CLOCKS_PER_SEC)+total_t_io;
	printf("I/O time: %f\n", total_t_io);
	printf("Sorint time : %f\n", total_t_sort);
	free_node(Head_list->node);
	free(Head_list);
	//printf("array_len = %ld", array_len);
	//printf("k = %d in main\n", gaps[k-1]);
	//new_list = List_Split(Head_list,7);
	/*if(new_list->node == NULL)
	  {
	    printf("this is the head of the heads\n");
	  }
	if(new_list->next == NULL)
	  {
	    printf("new_list->next == NULL");
	    }*/
	//new_list = List_Reform(new_list, 7,n);
	//Print_list(new_list->node);
	//new_list = List_Split(new_list,4);
	//new_list = List_Reform(new_list,4,n);
	//printf("gaps[4] = %d", gaps[4]);
	//Print_list(new_list->node);
	return 0;
}
