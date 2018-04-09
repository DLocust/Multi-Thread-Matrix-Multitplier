#ifdef _WIN32
char full_direct[100] = ".\\text.txt";
char full_direct2[100] = ".\\textout.txt";
int rowcount2 = 0;
#else
char full_direct[100] = "./text.txt";
char full_direct2[100] = "./textout.txt";
int rowcount2 = -1;
#endif
#define HAVE_STRUCT_TIMESPEC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#pragma warning(disable : 4996)
int start = 0;
char ch1;
int rowcount;
int charcount;
int charcount2;
int matrix1_rows;
int matrix2_rows;
int matrix1_columns;
int matrix2_columns;
FILE *file;
FILE *filedest;
void *main_thread();
void *sub_thread(void *thread_id);
int j[1000];
int k[1000];;
int* dimension_array;
int dimensions;
int main() {
	int initiate = 0;
	int i;
	int j_index = 0;
	int k_index = 0;
	int val;
	int val2;
	file = fopen(full_direct, "r+");		
	filedest = fopen(full_direct2, "w+");
	if (file == NULL) {
		printf("Error Retrieving File \n");
		printf("Could not retrieve file from the following directory: %s \n", full_direct);
	}
int cont = 0;
	while ((ch1 = fgetc(file)) != EOF) {
		if (ch1 == '\n') {
			rowcount++;
		}
		if ((ch1 != '\n') && (ch1 != '*') && (ch1 != ' ')) {
			charcount++;
			val = ch1 - '0';
			j[j_index] = val;
			j_index++;
		}
		if (ch1 == '*') {
			cont = 1;
			break;
		}
	}
	if(cont == 1){
			matrix1_columns = charcount / rowcount;
			matrix1_rows = rowcount;
			while ((ch1 = getc(file)) != EOF) {
				if (ch1 != '*') {
					if (ch1 == '\n') {
						rowcount2++;
					}
					if ((ch1 != '\n') && (ch1 != EOF) && (ch1 != ' ')) {
						charcount2++;
						val2 = ch1 - '0';
						k[k_index] = val2;
						k_index++;
					}
					if (ch1 == EOF){
						break;
				}
			}
		}
	if (ch1 = fgetc(file) == EOF) {
		matrix2_columns = charcount2 / rowcount2;
		matrix2_rows = rowcount2;
		dimensions = matrix2_columns * matrix1_rows;
		if (matrix1_columns == matrix2_rows) {
			for (i = 0; i < charcount; i++) {
			}
			initiate = 1;
		}
		else {
			printf("The matrix dimensions don't match up \n");
			exit(1);
		}
		if (initiate == 1) {
			pthread_t main_t;
			pthread_t *sub_t = (pthread_t*)malloc(sizeof(pthread_t)*dimensions);
			pthread_attr_t attr;
			pthread_create(&main_t, NULL, main_thread, NULL);
			int* thread_id = malloc(sizeof(int)*dimensions);
			dimension_array = malloc(sizeof(int)*dimensions);
			for (i = 0; i < dimensions; i++) {
				thread_id[i] = i;
				pthread_create(&sub_t[i], NULL, sub_thread, (void *)&thread_id[i]);
			}
						for (i = 0; i < dimensions; i++) {
				pthread_join(sub_t[i], NULL);
			}
		
}}
start = 1;
main_thread();
return 0;
}
}
void *main_thread() {
	if(start == 1){
	int u=0;
		printf("These are the values in the output matrix. \nThe values will output in the correct format in the output file. \n");
	for(u=0;u<dimensions;u++){
		if((u != 0) && (u % matrix2_columns == 0)){
			fputc('\n', filedest);
		}
		fprintf(filedest, "%d ", dimension_array[u]);
		printf("Dimension array [%d] = %d \n", u, dimension_array[u]);
	}
	}
}
void *sub_thread(void *thread_id) {
	int i;
	int l;
	int c;
	int m;
	int a;
	int v;
	int q;
	int *my_thread_id = (int *)thread_id;
	int d;
	for(l=0;l<matrix2_rows;l++){ //Is equal to the matrix 2 rows
			if(*my_thread_id >= matrix2_columns){
			a = (int) (*my_thread_id / matrix2_columns);
			d = (*my_thread_id % matrix2_columns);
		}
		else{
			d = *my_thread_id;
		}
		m = matrix2_columns*l;
		q = m + d;
		c = a* matrix1_columns;
		v = l+c;
		dimension_array[*my_thread_id] += (j[v] * k[q]);
	}
main_thread();
}
