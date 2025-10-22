#include <stdint.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

void merge(int32_t * firstSeg, size_t firstSize, int32_t * secondSeg, size_t secondSize) {
	static int32_t sortingBuffer[100];	// Static for easier allocation

	size_t firstIdx = firstSize, secondIdx = secondSize, outIdx = (firstSize + secondSize);

	// for (int i = 0; i < firstSize; i++){
	// 	printf("%d ", firstSeg[i]);
	// }
	// printf(" + ");
	// for (int i = 0; i < secondSize; i++){
	// 	printf("%d ", secondSeg[i]);
	// }

	// printf("--> ");

	while (firstIdx != 0 && secondIdx != 0) {
		sortingBuffer[--outIdx] = \
			firstSeg[firstIdx-1] > secondSeg[secondIdx-1] ? \
			firstSeg[--firstIdx] : secondSeg[--secondIdx];
		// printf("%d[%lu][%lu]; ", sortingBuffer[outIdx], firstIdx, secondIdx);
	}
	while (firstIdx != 0 || secondIdx != 0) {
		sortingBuffer[--outIdx] = firstIdx ? firstSeg[--firstIdx] : secondSeg[--secondIdx];

	}

	outIdx = (firstSize + secondSize);


	// printf("--> ");
	for (int i = 0; i < (firstSize + secondSize); i++){
	}
	while (outIdx != 0) {
		outIdx--;
		// printf("%d ", sortingBuffer[outIdx]);
		firstSeg[outIdx] = sortingBuffer[outIdx];
	}
	// printf("\n");

}

void mergeSort(int32_t * array, size_t arraySize) {
	if (!array)
		return;

	{
		int32_t swapTmp;
		// First, sort in chunks of 2 (inline)
		for (size_t i = 0; i < (arraySize & ~1); i += 2) {
			if (array[i] > array[i+1]) {
				swapTmp = array[i];
				array[i] = array[i+1];
				array[i+1] = swapTmp;
			}
		}

	}

	size_t chunkSize = 2;

	while (chunkSize < arraySize) {
		size_t chunkStart = 0;

		while (chunkStart + chunkSize < arraySize) {
			merge(array+chunkStart, chunkSize, array+chunkStart+chunkSize, MIN(arraySize - (chunkStart + chunkSize), chunkSize));
			chunkStart += 2 * chunkSize;
		}

		chunkSize *= 2;
	}

}

int main() {
	// There is a guarantee of no more than 100 numbers, we can allocate this statically
	// and keep track of how much numbers there really are separately
	// 
	// Testing data does not exceed 32 bits
	int32_t sortingBuffer[100];

	size_t curIdx = 0;
	int rc;

	while ((rc = scanf("%d", sortingBuffer+curIdx)) == 1) {
		curIdx++;
	}

	// for (int i = 0; i < curIdx; i++)
	// 	printf("%d ", sortingBuffer[i]);
	// printf("\n");


	// The array has ended, let's sort!
	mergeSort(sortingBuffer, curIdx);

	// printf("\nResult: ");

	for (size_t i = 0; i < curIdx; i++) {
		printf("%d ", sortingBuffer[i]);
	}
	printf("\n");

}