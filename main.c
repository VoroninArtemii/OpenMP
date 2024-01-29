#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv){
	const int count = 10000000;
	const int random_seed = 920214;
	const int threads[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int target;
	int *array = 0;
	int index = -1;
	srand(random_seed);
	array = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; i++){
		array[i] = rand() % 1000;
	}
	printf("Enter a target:\n");
	scanf("%d", &target);
	for (int j = 0; j < 8; j++){
		int flag = 0;
		double start = omp_get_wtime();
		#pragma omp parallel num_threads(threads[j]) shared(array, count, target, flag) reduction(max: index)
		{
			#pragma omp for
			for (int i = 0; i < count; i++){
				if (array[i] == target || flag == 1){
					if (!flag)
						index = i;
					i = count;
					flag = 1;
				}
			}
		}
		double end = omp_get_wtime();
		printf("Time for %d processors: %lf\n", threads[j], end - start);
	}
	printf("Found occurence of %d at index %d;\n", target, index);
	return 0;
}
