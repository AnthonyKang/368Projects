#ifndef SHELLSORT_H
#define SHELLSORT_H
long * Load_File(char* , int*);
int Print_Seq(char*, int);
int Save_File(char*, long*, int);
void Shell_Insertion_Sort(long*, int, double*, double*);
void Shell_Selection_Sort(long*, int, double*, double*);
int* Gap_Array(int*, int);
int* Get_Gaps(int*, int);
#endif
