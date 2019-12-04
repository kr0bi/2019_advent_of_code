#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
/*
	Fuel required to launch a given module is based on its mass. 
	Specifically, to find the fuel required for a module, 
		take its mass, divide by three, round down, and subtract 2.
*/

int find_fuel_required(int mass);

/*
	What is the sum of the fuel requirements for all of the modules on your spacecraft?
*/

int sum_all_fuel_requirements(int* fuel_requirements, int size);

/*
	So, for each module mass, calculate its fuel and add it to the total. 
	Then, 
	treat the fuel amount you just calculated as the input mass and repeat the process, 
	continuing until a fuel requirement is zero or negative.
*/

int sum_required_fuel_until (int mass);


int main(int argc, char **argv){
	//apri input
	char *filename = argv[1];
	FILE *file = fopen(filename, "r");

	//salva riga 0 su un array in posizione 0
	//incrementa la size dell'array che legge l'input
	//repeat
	int size = 100;
	int *array = malloc(size*sizeof(int));
	int read = 0;
	

	while(fscanf(file, "%d", &array[read]) == 1) {
		if(++read == size) {
			size*= 2;
			array = realloc(array, size*sizeof(int));
		}
	}

	fclose(file);

	for (int i=0; i<read; i++){
		array[i] = find_fuel_required(array[i]);
	}

	for (int i=0; i<read; i++){
		array[i] = sum_required_fuel_until(array[i]);
	}

	printf("sum of all fuel requirements: %d\n", sum_all_fuel_requirements(array, read));
	
	return 0;
}

int find_fuel_required(int mass){
	return (floor(mass/3)-2);
}

int sum_all_fuel_requirements(int* fuel_requirements, int size){
	int result=0;
	for (int i=0; i<size; i++){
		result += fuel_requirements[i];
	}
	return result;
}

int sum_required_fuel_until (int mass){
	int result = 0;
	while(mass>0){
		result += mass;
		mass = find_fuel_required(mass);
	}
	return result;
}