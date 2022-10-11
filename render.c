#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "bmp.h"
#include "render.h"

void getBufferArray(unsigned char* imageData, uint32_t size, const unsigned int bSize, color* buffer[bSize]) {
	int counter = 0;
	for (int i = 0; i < size; i += 4) {
		int r = imageData[i    ];
		int g = imageData[i + 1];
		int b = imageData[i + 2];
		int greyVal = ((float)r + (float)g + (float)b) / 3;

		color* col = (color*) malloc(sizeof(color));
		col->r = r; col->g = g; col->b = b; col->grey = greyVal;
		buffer[counter] = col;

		counter++;
	}
}

void loadASCIIBuffer(color** buffer, const unsigned int bSize, char symBuffer[bSize]) {
	for (int i = 0; i < bSize; i++) {
		color* pixel = buffer[i];
		float val = (float) pixel->grey;

		int lumIndex = round((val / 255.0) * 12.0); // Scale the brightness value

		symBuffer[i] = " .,-~:;=!*#$@"[lumIndex]; // Put the correct character in the output buffer
	}
}

void plotImage(char* symBuffer, int width, int height) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			int idx = j * width + i;
			putchar(symBuffer[idx]);
		}
		putchar('\n');
	}
}

// Matrix Operations

void swap(char* e1, char* e2) {
	/* *e1 = *e1 ^ *e2; */
	/* *e2 = *e1 ^ *e2; */
	/* *e1 = *e1 ^ *e2; */
	char temp = *e1;
	*e1 = *e2;
	*e2 = temp;

}

int idxIn1D(int x, int y, int width) {
	return (y * width + x);
}

void reverseCols(char* matrix, int width, int height) {
	for (int j = 0; j < height; j++)
        for (int i = 0, k = height - 1; i < k; i++, k--)
            swap(&matrix[idxIn1D(i, j, width)], &matrix[idxIn1D(i, k, width)]);
}

void transpose(char* matrix, int width, int height) {
    for (int j = 0; j < height; j++)
        for (int i = j; i < width; i++)
            swap(&matrix[idxIn1D(j, i, width)], &matrix[idxIn1D(i, j, width)]);
}

void rotate180(char* matrix, int width, int height) {
	transpose(matrix, width, height);
	reverseCols(matrix, width, height);
	transpose(matrix, width, height);
	reverseCols(matrix, width, height);
}
