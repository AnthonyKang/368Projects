#include <stdio.h>
#include <stdlib.h>
#include "shellsort.h"
int Save_File(char *Filename, long *Array, int Size)
{
  FILE *myfile = NULL;
  myfile = fopen(Filename, "w");
  int i = 0;
  int j = 0;
  long* sort_Array = NULL;
  if(myfile == NULL)
    {
      printf("file did not open");
      return EXIT_FAILURE;
    }
   while(Array[i] > 0)
    {
      i++;
    }
  sort_Array = malloc(sizeof(long)*(i+1));
  sort_Array[0] = Size;
  for(j = 1; j < i + 1 ; j++)
    {
      sort_Array[j] = Array[j-1];
    }
  for(j = 0; j< i+1; j++)
    {
      fprintf(myfile, "%ld\n", sort_Array[j]);
    }
  fclose(myfile);
  free(sort_Array);
  return j;

}
void Shell_Selection_Sort(long* Array, int Size, double* N_comp, double* N_move)
{
  int i = 0;
  int j = 0;
  int minimum = 0;
  long temp = 0;
  int* gaps = NULL;
  long comp_count =0;
  long move_count = 0;
  gaps = Gap_Array(gaps, Size);
  int sizeIndex;
  for(sizeIndex = sizeof(gaps)/sizeof(gaps[0])-1; sizeIndex >= 0; sizeIndex--)
    {
      for(j = 0; j < Size - 1; j++)
	{
	  minimum = j;
	  for(i = j+gaps[sizeIndex]; i< Size; i++)
	    {
	      if(Array[i] < Array[minimum])
		{
		  comp_count++;
		  minimum = i;
		}

	    }
	  if(minimum != j)
	    {
	      move_count = move_count + 3;
	      temp = Array[minimum];
	      Array[minimum] = Array[j];
	      Array[j] = temp;
	    }
	}
    }
  printf("Number of comparisons = %ld\n",comp_count);
  printf("Number of moves = %ld\n", move_count);
  *N_comp = comp_count;
  *N_move = move_count;
  free(gaps);
}
void Shell_Insertion_Sort(long *Array, int Size, double* N_comp, double *N_move)
{
  int i = 0;
  int j = 0;
  long comp_count = 0;
  long move_count = 0;
  long temp = 0;
  int* gaps = NULL;
  gaps = Gap_Array(gaps, Size);
  int sizeIndex=0;
  int k = 0;
  while(gaps[sizeIndex] > 0)
    {
      

      sizeIndex++;
    }
  sizeIndex = sizeIndex -1;
  for(k = sizeIndex; k >= 0; k--)
    {
      
      for(i = gaps[k]; i < Size; i++)
	{
	  move_count++;
	  temp = Array[i];
	  for(j = i; j >= gaps[k] && Array[j-gaps[k]]>temp; j-=gaps[k])
	    {
	      move_count++;
	      comp_count++;
	      Array[j] = Array[j - gaps[k]];
	    }
	  move_count++;
	  Array[j] = temp;
	}
    }
 printf("Number of comparisons: %ld\n", comp_count);
 printf("Number of moves: %ld\n", move_count);
 free(gaps); 
}
long * Load_File(char *Filename, int *Size)
{
  FILE *myfile = NULL;
  int i = 0;
  long temp = 0;
  long *int_array = NULL;
  long seek;
  myfile = fopen(Filename, "r");
  if(myfile == NULL)
    {
      printf("file did not open");
      return NULL;
    }
  else
    {
      while((fscanf(myfile, "%ld", &temp)) == 1)
	{
	  i++;
	}
    }
  
  seek = fseek(myfile, 1*sizeof(long), SEEK_SET);
  *Size = (i - 1);
  int_array = malloc(sizeof(long)*(i-1));
  if(seek == 0)
    {
      int_array = malloc(sizeof(long)*(i-1));
      int j = 0;
      for(j = 0; j< i-1; j++)
	{
	  fscanf(myfile, "%ld", &int_array[j]);
	}
      return int_array;
    }
  else
    {
      return NULL;
    }
  
  fclose(myfile);
}

int Print_Seq(char *Filename, int Size)
{
  
  int * gaps = NULL;
  int * gap_array_print = NULL;
  gaps = Gap_Array(gaps, Size);
  FILE *myfile = NULL;
  int i = 0;
  int j = 0;
  
  myfile = fopen(Filename, "w");
  if(myfile == NULL)
    {
      printf("File did not open");
      return EXIT_SUCCESS;
    }
  
  while(gaps[i]>0)
    {
      i++;
    }
  gap_array_print = malloc(sizeof(int)*(i+1));
  gap_array_print[0] = i;
  for(j = 1; j<i+1; j++)
    {
      gap_array_print[j] = gaps[j-1];
    
    }
  for(j = 0; j<i+1; j++)
    {
      fprintf(myfile, "%d\n", gap_array_print[j]);
    }
  fclose(myfile);
  return i;
}


int* Gap_Array(int * gap_array, int Size)
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
	      if(p == 0)
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
		  for(k = 0; k < (i -p); k++)
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
