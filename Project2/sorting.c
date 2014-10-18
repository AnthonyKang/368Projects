#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
void Shell_Sort_Final(Node * head)
{

  int k = 1;
  int p = 0;
  Node * temp = NULL;
  int len = 0;
  int gap=0;
  int count=0;
  int j = 0;
  int i = 0;
  //  int l = 0;
  long temp_int = 0;
  Node * front = NULL;
  Node * back = NULL;
  temp = head;
  while(temp->next != NULL)
    {
      temp = temp->next;
      len++;
    }
  len = len+1;
  //printf("len = %d",len);
  while(k<len)
    {
      k = k*3;
      p = p+1;
    }
  k = k/3;
  p = p-1;
  //Print_list(head);
  // printf("p=%d",p);
  while(p>=0)
    {
      gap = k;
      count = p;
      do{
	for(j = gap; j<len;j++)
	  {
	    //printf("in for");
	    front = move(head,j);
	    
	    //Print_list(front);
	    temp_int = front -> value;
	    i = j;
	    back = move(head,(i-gap));
	    
	    while(i >= gap && back->value > temp_int)
	      {
		front = move(head,i);
		front->value = back ->value;
		i = i-gap;
		back = move(head,(i-gap));
		//Print_list(head);
		//printf("\n");

	      }
	    front = move(head,i);
	    front ->value = temp_int;
	  }
	gap = (gap/3) * 2;
	count = count - 1;
      }while(count>=0);
      k = k/3;
      p = p-1;
    }


  Print_list(head);


}

Node * move(Node * head, int moves)
{
  if(head == NULL)
    {
      return NULL;
    }
  Node * temp = NULL;
  temp = head;
  int i = 0;
  for(i = 0; i< moves;i++)
    {
      temp = temp->next;
    }
  return temp;

}


void free_node(Node*head)
{
  if(head == NULL)
    {
      return;
    }
  else
    {
      free_node(head->next);
      free(head);
    }
}
Node * Insertion_Sort(Node * head_node)
{
  Node * t = NULL;
  Node * c = NULL;
  int i = 0;
  int j = 0;
  int k = 0;
  int len = 0;
  Node * temp = NULL;
  //fprintf(stderr,"in insertion");
  temp = head_node;
  //fprintf(stderr,"temp = %ld",temp->value);
  while(temp->next != NULL)
    {
      temp = temp->next;
      len++;
    }
  //Print_list(head_node);
  //printf("len = %d\n", len);
  len = len + 1;
  long swap = 0;
  t = head_node;
  c = head_node;
  for(i = 1; i<len; i++)
    {
      for(k = 0; k<i;k++)
	{
	  // printf("i = %d, k = %d",i,k);
	  for(j = 0; j < i-k; j++)
	    {
	      if(t->next != NULL)
		{
		  t = t->next;
		}
	    }
	  for(j = 0; j < i-k-1; j++)
	    {
	      if(c->next != NULL)
		{
		  c = c->next;
		}
	    }
	  if((t != NULL) && (c!= NULL))
	    {
	      if(t->value < c->value)
		{
		  swap = t->value;
		  t->value = c->value;
		  c->value = swap;
		}
	      // printf("\n");
	      //Print_list(head_node);
	      //printf("t->value = %ld\n",t->value);
	      //printf("c->value = %ld\n",c->value);
	    }
	  c=head_node;
	  t=head_node;
	}
    }
  //Print_list(head_node);
 
  return NULL;
}
void  Print_list(Node* node)
{
  if(node == NULL)
    {
      printf("node is NULL");
    }
  while(node != NULL)
    {
      printf("Node = %ld\n", node->value);
      node = node -> next;
    }
}
Node * Shell_Sort_Swag(Node * head_node)
{
  int * gaps = NULL;
  int length = 0;
  Node * len = NULL;
  List * head_list = NULL;
  head_list = List_construct(head_node);
  List * l_dummy = NULL;
  Node * n_dummy = NULL;
  int sizeIndex = 0;
  len = head_node;
  while(len != NULL)
    {
      len = len->next;
      length++;
    }
  length = length - 1;
  gaps = Gap_Array(gaps,length);
  while(gaps[sizeIndex]>0)
    {
      sizeIndex++;
    }
  sizeIndex = sizeIndex - 1;
  int k = 0;
  int i = 0;
  for(k=sizeIndex;k>=0;k--)
    {
      head_list = List_Split(head_list, gaps[k]);
      l_dummy = head_list->next;
      for(i = 0; i < gaps[k]; i++)
	{
	  if(head_list->next == NULL)
	    {
	      printf("NULL");
	    }
	  // l_dummy = head_list -> next;
	  if(l_dummy->node == NULL)
	    {
	      printf("NULL");
	    }
	  n_dummy = l_dummy->node;
	  //printf("n_dummy =%ld\n", n_dummy->value);
	  if(l_dummy->next != NULL)
	    {
	      l_dummy = l_dummy->next;
	    }

	  l_dummy->node = Insertion_Sort(n_dummy);
	  Print_list(n_dummy);
	}
      
    }


  return NULL;
}
Node * Shell_Sort(Node * head_node)
{

  Node * t = NULL;
  Node * c = NULL;
  Node * b = NULL;
  Node * dummy = NULL;
  Node * len = NULL;
  long length = 0;
  len = head_node;
  while(len != NULL)
    {
      len = len->next;
      length++;
    }
  length = length - 1;
  //  printf("length = %ld\n ", length);
  long swap = 0;
  long count = 0;

  int * gaps = NULL;
  int i = 0;
  int j = 0;
  int l = 0;
  int x = 0;
  int h = 0;
  int k = 0;
  int sizeIndex = 0;
  gaps = Gap_Array(gaps, length);
  while(gaps[sizeIndex]>0)
   {
    sizeIndex++;
   }
  sizeIndex = sizeIndex -1;
  //  printf("sizeIndex = %d\n", sizeIndex);
  //  int n = 9;
  dummy = head_node;
  t = head_node;
  c = head_node;
  b = head_node;
  int check = 0;
    for(x = sizeIndex;x>=0;x--)
    {
      k=gaps[x];
      dummy = head_node;
      t = head_node;
      c = head_node;
      b = head_node;
      printf("k=%d\n",k);
  
  for(i = 0; i<k;i++)
    {
      count = 0;
      check = 0;
  
      while(check == 0)
	{
	  for(j = 0; j<k;j++)
	    {
	      if(t ->next != NULL)
		{
		  t = t->next;
		  
		}
	      else
		{
		  
		  if(check == 0)
		    {
		      dummy = dummy->next;
		      t = dummy;
		    }
		  check = 1;
		}
	      count++;
	    }
	      
	  for(h = 0; h<(count/k); h++)
	    {
	      
	      for(l = 0; l<count-h*k;l++)
		{
		  if(c!=NULL)
		  c = c->next;
		}
	      for(l = 0; l<count-h*k-k;l++)
		{
		  if(b!=NULL)
		  b = b->next;
		}
	      if((c != NULL) && (b != NULL))
		{
		  if(c->value < b->value)
		    {
		      swap = c->value;
		      c->value = b->value;
		      b->value = swap;
		    }
		}
	      c = dummy;
	      b = dummy;
	    }



	  
	} 
      b = dummy;
      c = dummy;

    }
  }
  //fprintf(stderr,"out of loop");
  
   
	
    free(gaps);
    return head_node;
}




List * List_Reform(List * list_head, int k,int n)
{
  List * list_dummy = NULL;
  Node * head_list_next = NULL;
  Node * dummy;
  int i = 0;
  fprintf(stderr,"in reform\n");

  list_dummy = list_head->next;
  list_head->node = list_dummy->node;
  head_list_next = list_head->node;
  list_dummy->node = head_list_next->next;
  head_list_next->next = NULL;
  fprintf(stderr,"before loop\n");
  Print_list(head_list_next);
  

  

  for(i = 0; i < n-1; i++)
    {
      if(list_dummy->next == NULL)
	{
	  list_dummy = list_head->next;
	}
      else
	{
	  list_dummy = list_dummy -> next;
	}
      dummy = list_dummy->node;
      head_list_next->next = dummy;
      list_dummy->node = dummy->next;
      dummy->next = NULL;
      head_list_next = head_list_next->next;
      Print_list(list_head->node);
    }
  /*
   for(i = 0;i < 3; i++)
    {
      Print_list(list_head->node);
      list_dummy = list_dummy->next;
      dummy = list_dummy->node;
      head_list_next = dummy;
      list_dummy->node = dummy->next;
      dummy->next = NULL;
      head_list_next = head_list_next->next;
    }
  */  

   // Print_list(list_head->node);
  return(list_head);

  
}
List * List_Split(List * list_head, int k)
{
  int i = 0;
  int count = 0;
  List * k_head = NULL;
  List * l_dummy = NULL;
  // List * printl = NULL;
  //List * fill  = NULL;
  Node * pop = NULL;
  Node * walk = NULL;
  Node * n_dummy = NULL;
  Node * print = NULL;
  walk = list_head ->node;
  
  k_head =  List_construct(walk);
  list_head->next = k_head;
  walk = walk->next;
  l_dummy = k_head;
  if(k_head == NULL)
    {
      // printf("k_head == NULL");
    }
  for(i = 0;i<k-1;i++)
    {
      // printf("walk = %ld\n", walk->value);
      l_dummy->next = List_construct(walk);
      l_dummy = l_dummy->next;
      print = l_dummy->node;
      //printf("node = %ld\n", print->value);
      
      walk = walk->next;
     
    }
  /* l_dummy = k_head;
  print = l_dummy->node;
  printf("l_dummy = %ld\n",print->value);
  printl = l_dummy->next;
  print = printl->node;
  printf("l_dummy = %ld\n", print->value);
  printl = printl->next;
  print = printl->node;
  printf("l_dummy = %ld\n",print->value);
  l_dummy = k_head;
  */
 
  //printf("walk = %ld\n",walk->value);
  l_dummy = k_head;
  while(walk != NULL)
    {      
      n_dummy = l_dummy -> node;
      pop = walk;
      walk = walk->next;
      pop->next = NULL;
      //Print_list(n_dummy);
      //printf("\n");
      for(i = 0; i < count; i++)
	{
	  n_dummy = n_dummy -> next;
	}
      n_dummy->next = pop;
      if(l_dummy -> next == NULL)
	{
	  l_dummy = k_head;
	}
      else
	{
	  
	  l_dummy = l_dummy -> next;
	  
	}
      //walk = walk -> next;
      if(l_dummy == k_head)
	{
	  count++;
	}
      

    }


  

  
  return list_head;

}



Node * node_insert_ascend(Node * head, long value)
{
  Node * new_node;
  if(head == NULL)
    {
      return Node_construct(value);
    }
  if((head->value) > value)
    {
      new_node = Node_construct(value);
      new_node->next = head;
      return new_node;
    }
  head->next = node_insert_ascend(head->next, value);
  return head;
}

Node * Node_construct(long value_num)
{
  Node * node = malloc(sizeof(Node));
  node -> value = value_num;
  node -> next = NULL;
  return node;

}
List * List_construct(Node * node)
{
  List * list = malloc(sizeof(List));
  list -> node = node;
  list -> next = NULL;
  return list;
}
Node * Node_insert(Node * front, long value)
{
  Node * node_insert;
  node_insert = Node_construct(value);
  node_insert -> next = front;
  return node_insert;
}

int Save_File(char *Filename, Node *list)
{
  int i = 0;
  FILE *myfile = NULL;
  myfile = fopen(Filename, "w");
  if(myfile == NULL)
    {
      printf("output file failed to open");
      return 0;
    }
 while(list != NULL)
    {
      i++;
      fprintf(myfile, "%ld\n", list -> value);
      list = list -> next;
    }
 fclose(myfile);
 return i;

}
Node * Load_File(char *Filename, int * n)
{
	FILE *myfile = NULL;
	long temp = 0;
	//List * head = NULL;
	Node * node_head = NULL;
	myfile = fopen(Filename, "r");
	if(myfile == NULL)
	{
		printf("file did not open");
		return NULL;
	}
	//printf("hi\n");
	while((fscanf(myfile, "%ld", &temp)) == 1)
	  {
	  
	    node_head = Node_insert(node_head, temp);
	    *n=*n+1;
	    
	  }
	//	head -> node = node_head;
	return node_head;
	fclose(myfile);
}

int* Gap_Array(int *gap_array, int Size)
{
  int n = 0;
  int j = 0;
  int p = 0;
  int guess = 1;
  int product = 0;
  int i = 0;
  int k = 0;
  int sub_product1 = 1;
  int sub_product2 = 1;
  while(guess < Size)
    {
      guess = guess*3;
      n++;
    }
  guess = guess/3;
  gap_array = malloc(sizeof(int)*guess);
  while(product*3 < Size)
    {
      for(i = 0; i < n; i++)
	{
	  for(p = i; p>=0; p--)
	    {
	      sub_product1 = 1;
	      sub_product2 = 1;
	      if(p ==0)
		{
		  sub_product1 = 1;
		}
	      else
		{
		  for(k = 0; k < p; k++)
		    {
		      sub_product1 = sub_product1 * 2;
		    }
		}
	      if((i-p) == 0)
		{
		  sub_product2 = 1;
		}
	      else
		{
		  for(k = 0; k< (i-p); k++)
		    {
		      sub_product2 = sub_product2 * 3;
		    }
		}
	      product = sub_product1*sub_product2;
	      if(product < Size)
		{
		  gap_array[j] = product;
		  j++;
		}
	    }
	}
    }

  return gap_array;

}


	




			
	
	

