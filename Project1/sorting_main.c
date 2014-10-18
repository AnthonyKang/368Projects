#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shellsort.h"
//#include <math.h>
//#include "sorting.c"
int main(int argc, char ** argv)
{
  if(argc < 5)
    {

      printf("Program requires inputs: i/s, input file, output file, output file");
      return EXIT_SUCCESS;
    }
  int Size = 0; 
  //nt * test = NULL;
  long * int_array = NULL;
  double computations = 0;
  double moves = 0;
  //int i = 0;
  clock_t start_t_sort;
  clock_t end_t_sort;
  clock_t start_t_io; 
  clock_t end_t_io;
  start_t_io = clock();
  int_array = Load_File(argv[2], &Size); //Loads integers from file into int_array
  Print_Seq(argv[3], Size); //Prints sequence generated into an output file
  end_t_io = clock();
  double total_t_io = (end_t_io - start_t_io)/(double)CLOCKS_PER_SEC;
  start_t_sort = clock();
  if(!strcmp(argv[1],"i"))
    {
    
      Shell_Insertion_Sort(int_array, Size, &computations, &moves);
    
    }
  if(!strcmp(argv[1],"s"))
    {
      Shell_Selection_Sort(int_array, Size, &computations, &moves);
    }  
  end_t_sort = clock();
  start_t_io = clock();
  Save_File(argv[4], int_array, Size);//Saves sorted list of integers into output file
  end_t_io = clock();
  total_t_io = ((end_t_io - start_t_io)/(double)CLOCKS_PER_SEC)+total_t_io;
  double total_t_sort =(end_t_sort - start_t_sort)/(double)CLOCKS_PER_SEC;
  printf("I/O time: %f\n", total_t_io);
  printf("Sorting time: %f\n", total_t_sort);
  free(int_array);  

  return 0;
}
