#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


double*		allocateVector(int, double);
double**	allocateMatrix(int, double);
void		loadAdjacencyMatrix(char*, double**);
void		generateTPMatrix(double**, int);
double*		calculatePageRank(double*, double**, int, double, int);
void		writeVector(char*, double*, int);
void		printTopK(double*, int, int);
void		printVector(double*, int);
void		printMatrix(double**, int);

int main(int argc, char *argv[]) {
	// argv[0] = [program name]
	// argv[1] is the file name that contains the adjacency matrix
	// argv[2] is the number of pages in the given Web graph
	// argv[3] is the value of damping factor (normally set to 0.85)
	// argv[4] is the number of iteration (in this assignment, set to 100)
	// argv[5] is the file name in which you want to record the PageRank scores
	// argv[6] specifies top K
	
	// Initialize variables from the command-line arguments
	char* inputFile = argv[1];
	int numPages = atoi(argv[2]);
	double d = atof(argv[3]);
	int numIteration = atoi(argv[4]);
	char* outputFile = argv[5];
	int topK = atoi(argv[6]);
	// Time variables to evalute the processing time
	time_t beginTime = 0, terTime = 0;
	
	// Allocate and initialize a vector for PageRank
	double* vector = allocateVector(numPages, 1.0/numPages);
	
	// Allocate a matrix
	double** matrix = allocateMatrix(numPages, 0.0);
	
	// Load the adjacency matrix from [inputFile]
	loadAdjacencyMatrix(inputFile, matrix);
		
	/* ASSIGNMENT FUNCTION NO.1 */
	// Generate the transition probability matrix from the adjacency matrix
	generateTPMatrix(matrix, numPages);
	
	// Record the CPU clock for beginning the calculation
	beginTime = clock();
	
	/* ASSIGNMENT FUNCTION NO.2 */
	// Calculate the PageRank scores and store them in the vector
	vector = calculatePageRank(vector, matrix, numPages, d, numIteration);
	
	// Record the CPU clock for terminating the calculation
	terTime = clock();
	
	// Print the processing time
	printf("Elapsed time is: %f sec\n", (double)(terTime-beginTime)/(double)CLOCKS_PER_SEC);
	
	// Output the PageRank scores
	writeVector(outputFile, vector, numPages);
	
	// Print the top k ranked pages and the corresponding scores
	printTopK(vector, numPages, topK);
	
	// Free the allocated vector and matrix
	free(vector);
	free(matrix);
	
	getch();
	return 0;
}

// Returns the pointer of a double-typed array
// int n: number of elements in the vector
// double initValue: initial value for each element
double* allocateVector(int n, double initValue) {
	int i;
	
	// Allocate a vector
	double* vector = (double*)malloc(sizeof(double)*n);
	
	// For each element, assign the initial value
	for (i = 0; i < n; i++) vector[i] = initValue;
	
	// Return the vector
	return vector;
}

// Returns the pointer of a double-typed, n*n array
// int n: number of rows (columns) in the matrix
// double initValue: initail value for each element
double** allocateMatrix(int n, double initValue) {
	int i, j;
	
	// A pointer for n * n matrix
	double** matrix;
	
	// Allocate n number of rows in the matrix
	matrix = (double**)malloc(sizeof(double*)*n);
	
	// For each row
	for (i = 0; i < n; i++) {
		// Allocate n number of columns in the matrix
		matrix[i] = (double*)malloc(sizeof(double)*n);
		
		// For each element, assign the initial value
		for (j = 0; j < n; j++) matrix[i][j] = initValue;
	}
	
	// Return the matrix
	return matrix;
}

// Loads the adjacency matric from [inputFile] into [matrix]
// char* inputFile: file name concatenated by its absolute or reletive path
// double** matrix: n*n array
void loadAdjacencyMatrix(char* inputFile, double** matrix) {
	// A string to get each row in [inputFile]
	char row[15000];
	FILE *stream;
	int i = 0, j = 0;
	char* element;
	
	// Open file stream from [inputFile]
	stream = fopen(inputFile, "r");
	if (stream == NULL) {
		printf("File open error\n");
		exit(1);
	}
	
	// Load the adjacency matrix
	while (!feof(stream)) {
		if (fgets(row, 15000, stream) == NULL) break;
		
		j = 0;
		element = strtok(row, " ");
		matrix[i][j++] = (double)atoi(element);
		while (element = strtok(NULL, " ")) {
			matrix[i][j++] = (double)atoi(element);			
		}
		
		i++;
	}
	
	// Close the file stream
	fclose(stream);
}

// Generates the transition probability matrix from the adjacency matrix
// double** matrix: n*n array containing the adjacency matrix
// int n: number of rows (of columns) in the matrix
void generateTPMatrix(double** matrix, int n) {
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int l = 0; l < n; l++)
		{
			if (matrix[i][l] != 0.0)
				++count;
		}
		
		for (int l = 0; l < n; l++)
		{
			if (count == 0)
				matrix[i][l] = 1.0 / (double)n;
			else
				matrix[i][l] /= count;
		}
	}
	return;
}

// Returns a vector that contains the PageRank scores for each page i
// double* vector: vec(R)
// double** matrix: transition probability matrix W
// int n: number of rows (columns) in the [matrix]
// double d: damping factor (normally set to 0.85)
// int numIteration: number of iteration
double* calculatePageRank(double* vector, double** matrix, int n, double d, int numIteration) {
	
	double* prevVector = (double*)malloc(sizeof(double) * n);

	for (int z = 0; z < numIteration; z++)
	{
		memcpy(prevVector, vector, sizeof(double) * n);
		memset(vector, 0, sizeof(double) * n);
		for (int i = 0; i < n; i++)
		{
			for (int l = 0; l < n; l++)
			{
				vector[i] += matrix[l][i] * prevVector[l];
			}
			vector[i] *= d;
			vector[i] += (1.0 - d) * 1.0 / (double)n;
		}
	}
	free(prevVector);
	return vector;
}

// Writes the [vector] in [outputFile]
// char* outputFile: file name concatenated by its absolute or reletive path
// double* vector: vector to be printed
// int n: number of element in the vector
void writeVector(char* outputFile, double* vector, int n) {
	char strElement[32];
	FILE *stream;
	int i;
	
	// Open file stream withe [outputFile] to write the vector
	stream = fopen(outputFile, "wb");
	if (stream == NULL) {
		printf("Output stream is NULL. Program terminates.\n");
		exit(1);
	}
	
	// For each element in the vector
	for (i = 0; i < n; i++) {
		// Generate a string that represents the element
		sprintf(strElement, "%f\n", vector[i]);
	
		// Write the string
		if (fputs(strElement, stream) == EOF) {
			printf("fputc() returns NULL. Program terminates.\n");
			exit(1);
		}
	}
	
	// Close the file stream
	fclose(stream);
}

// Prints the top k ranked pages and the corresponding scores
// double* vector: vector that contains the PageRank scores
// int topK: top k
void printTopK(double* vector, int n, int topK) {
	// Define a structure for sorting
	typedef struct _ID_SCORE {
		int pageID;
		double score;
	} ID_SCORE;
	
	int i, j;
	ID_SCORE* rank;
	
	// If topK is not positive or is greater than n,
	// then do nothing
	if ((topK <= 0) || (n < topK)) return;
	
	// Allocate an array of ID_SCORE
	rank = (ID_SCORE*)malloc(sizeof(ID_SCORE)*n);
	
	// Initilize the array
	for (i = 0; i < n; i++) {
		rank[i].pageID = i;
		rank[i].score = vector[i];
	}
	
	// Selection Sort
	for (i = 0; i < n; i++) {
		ID_SCORE temp;
		int index = i;
		
		for (j = i; j < n; j++) {
			if (rank[index].score < rank[j].score) index = j;
		}
		
		temp = rank[i];
		rank[i] = rank[index];
		rank[index] = temp;
	}
	
	// Print the top k ranked pages and the corresponding scores
	printf("Top-%d [pageID: score]\n", topK);
	for (i = 0; i < topK; i++) {
		printf("%4d: %f\n", rank[i].pageID, rank[i].score);
	}
	
	// Free the allocated rank vector
	free(rank);
}

void printVector(double* vector, int n) {
	int i;
	
	for (i = 0; i < n; i++) printf("%f\n", vector[i]);
}

void printMatrix(double** matrix, int n) {
	int i, j;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}
