#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define position_1 1
#define position_2 2
#define next_opcode 4

int get_opcode(int *array, int position);
int execute_opcode(int *array, int position, int size);
void do_case_1(int *array, int position, int size);
void do_case_2(int *array, int position, int size);
int get_next_opcode(int position);

int main(int argc, char **argv){

	//apri input
	char *filename = argv[1];
	FILE *file = fopen(filename, "r");

	//salva riga 0 su un array in posizione 0
	//incrementa la size dell'array che legge l'input
	//repeat
	int size = 1000;
	int *array = malloc(size*sizeof(int));
	int read = 0;
	

	while(fscanf(file, "%d,", &array[read]) == 1) {
		if(++read == size) {
			size*= 2;
			array = realloc(array, size*sizeof(int));
		}
	}

	fclose(file);
	int *arrayBackup = malloc(read*sizeof(int));
	//copia dell'array
	for (int i=0; i<read; i++){
		arrayBackup[i] = array[i];
	}
	for (int i=0; i<100; i++){
		for (int j=0; j<100; j++){
			for (int z=0; z<read; z++){
				array[z] = arrayBackup[z];
			}
			array[1] = i;
			array[2] = j;
			int position = 0;
			
			while (position<read){
				int res = execute_opcode(array, position, read);
				if (res==0){
					break;
				} else if (res==-1){
					fprintf(stderr, "errore\n");
				}
				position = get_next_opcode(position);
			}
			if (array[0]==19690720){
				printf("valore1: %d\nvalore2: %d ", array[1], array[2]);
				printf("\n");
				break;
			}		
		}
	}
	
	return 0;
}

int get_opcode (int *array, int position){
	return array[position];
}

int execute_opcode (int *array, int position, int size){
	switch (get_opcode(array, position)){
		case 1:
			do_case_1(array, position, size);
			break;
		case 2:
			do_case_2(array, position, size);
			break;
		case 99:
			return 0;
			break;
		default:
			printf("position: %d\n", position);
			fprintf(stderr, "errore\n");
			return -1;
			break;
	}
	return 1;
}

void do_case_1 (int *array, int position, int size){
	int sum = array[array[position+position_1]]+array[array[position+position_2]];
	array[array[position+3]]=sum;
}

void do_case_2 (int *array, int position, int size){
	int multiply = array[array[position+position_1]]*array[array[position+position_2]];
	array[array[position+3]]=multiply;
}

int get_next_opcode(int position){
	return position+next_opcode;
}