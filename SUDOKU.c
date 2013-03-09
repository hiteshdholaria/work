/*
  Title			# SUDOKU solver in C language
	Author			# Hitesh Dholaria
	Email			# hitesh.dholaria@gmail.com

	Input 			# Following is a sample SUDOKU problem stored in the file named "problem.txt"
					# Here, 0 represents empty place
					# So, our overall goal is to replace such 0-places by some appropriate numbers
					# There are total of 9 rows, 9 columns and 9 blocks of size (3x3)

					008000050
					370009010
					000140007
					050020600
					001908300
					003060020
					700084000
					080200063
					090000400

	Time Complexity # O(rows^2) OR O(columns^2)
*/

#include<stdio.h>
#include<conio.h>

// Global array to hold main SUDOKU problem
int A[9][9];

void readProblem(void);
void printProblem(void);
int isProblemSolved(void);
void eliminatePossibility(int,int);
void getStartingIndicesOfBlock(int,int,int *,int *);

// Main function
int main() {

	int counter=0,number=0;
	int i=0,j=0,k=0,l=0,x=0,y=0;

	// First read the SUDOKU input problem into A[9][9]
	readProblem();
	printf("----- Problem -----\n\n");
	printProblem();

	// Main loop of the program
	// Keep running this loop, until the number of valid elements in array becomes 81
	// That is, until problem is solved

	while(!isProblemSolved()) {

		// Run this loop once for each of the number from 1 to 9
		// Every time increment this "number" and if it is overflown, reinitialize it to 1
		// This "number" is like "key" or "seed" for this main loop

		number++;
		if(number>9) {
			number=1;
		}

		// Eliminate possibility of being number at some of the 0-places by assigning -1 to those places

		for(i=0;i<9;i++) {
			for(j=0;j<9;j++) {
				if(A[i][j]==number) {
					eliminatePossibility(i,j);
				}
			}
		}

		// After eliminating possibilities,
		// if you find any 0-place,
		// then it means, there is a possibility of this "number" being at that place.
		// Count such 0-places in rows,columns and blocks
		// If it is only 1, then such 0-place must be updated by this "number",
		// (because of no other possibility at that 0-place and wer'e 100% sure about that!)
		
		// Moreover, eliminate possibilities again after updation

		// For all the rows

		for(i=0;i<9;i++) {
			counter=0;
			for(j=0;j<9;j++) {
				if(A[i][j]==0) {
					// Save column index of this 0-place
					k=j;
					counter++;
				}
			}
	
			if(counter==1) {
				A[i][k]=number;
				eliminatePossibility(i,k);
			}
		}

		// For all the columns

		for(i=0;i<9;i++) {
			counter=0;
			for(j=0;j<9;j++) {
				if(A[j][i]==0) {
					// Save row index of this 0-place
					k=j;
					counter++;
				}
			}
			if(counter==1) {
				A[k][i]=number;
				eliminatePossibility(k,i);
			}
		}

		// For all the blocks

		for(i=0;i<9;i+=3) {
			for(j=0;j<9;j+=3) {
				counter=0;
				for(k=i;k<i+3;k++) {
					for(l=j;l<j+3;l++) {
						if(A[k][l]==0) {
							// Save row and column indices of this 0-place
							x=k,y=l;
							counter++;
						}
					}
				}
				if(counter==1) {
					A[x][y]=number;
					eliminatePossibility(x,y);
				}
			}
		}
	}
	// Main loop ends here
	// Now, problem has been solved
	// So, printing the final solution

	printf("\n---- Solution ----\n\n");
	printProblem();
	getch();
	return 0;
}

// This function initializes problem array A[9][9] by reading SUDOKU elements from file

void readProblem(void) {
	int i,j;
	FILE *fp;
	fp = fopen("problem.txt","r");
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			A[i][j]=fgetc(fp)-48;
		}
		// Skip reading '\n' into array A[9][9]
		fgetc(fp);
	}
	fclose(fp);	
}

// This function prints problem array A[9][9]

void printProblem(void) {
	int i,j;
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
}

// This function returns 1(true), if number of valid elements(i.e. non-empty places) in A[9][9] is 81.
// Otherwise, returns 0(false)
// Also, note that whenever number of valid elements becomes 81,
// that means our SUDOKU problem has been solved completely.

int isProblemSolved(void) {
	int i,j,numberOfValidElements=0;
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			if(A[i][j]>0) {
				numberOfValidElements++;
			} else {
				A[i][j]=0;
			}
		}
	}
	if(numberOfValidElements<81) {
		return 0;
	} else {
		return 1;
	}
}

// Eliminate possibility of specific "number" being at some of the 0-places by assigning -1 to those places
// Arguments (row,column) represents indices of any arbitrary place in A[9][9]

void eliminatePossibility(int row,int column) {
	int i,j;

	// Eliminating possibility from all the rows corresponding to "column"
	for(i=0;i<9;i++) {
		if(A[i][column]==0) {
			A[i][column]=-1;
		}
	}

	// Eliminating possibility from all the columns corresponding to "row"
	for(i=0;i<9;i++) {
		if(A[row][i]==0) {
			A[row][i]=-1;
		}
	}

	// Eliminating possibility from all the places corresponding to "row" and "column"
	getStartingIndicesOfBlock(row,column,&row,&column);

	// Now, "row" and "column" contains the indices of the first element of the current block
	for(i=row;i<row+3;i++) {
		for(j=column;j<column+3;j++) {
			if(A[i][j]==0) {
				A[i][j]=-1;
			}
		}
	}
}

// This function returns the indices of the first element of the 3x3 block
// Here, specific block is being identified by the provided indices (i,j) of A[9][9]
// Resultant indices are returned by the pointers (*rowIndex,*columnIndex) to the calling function

void getStartingIndicesOfBlock(int i,int j,int *rowIndex,int *columnIndex) {
	if(i<3) {
		*rowIndex=0;
	} else if(i<6) {
		*rowIndex=3;
	} else {
		*rowIndex=6;
	}
	if(j<3) {
		*columnIndex=0;
	} else if(j<6) {
		*columnIndex=3;
	} else {
		*columnIndex=6;
	}
}
