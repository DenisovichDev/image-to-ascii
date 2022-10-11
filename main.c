#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"
#include "render.h"

void printArray (unsigned char* imageData, uint32_t size) {
	for (int i = 0; i < size; i += 4) {
		printf("[%d ", imageData[i    ]);
		printf("%d ",  imageData[i + 1]);
		printf("%d]",  imageData[i + 2]);
	}
}

void printCol (color** buffer, int width, int height) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			int idx = j * width + i;
			color* col = buffer[idx];
			/* printf("%d %d %d|", col->r, col->g, col->b); */
			printf(" %d ", col->grey);
		}
		printf("\n");
	}
}


int main() {
	DIBHeader bitmapInfo;
	unsigned char* bitmapData;

	bitmapData = loadBMP("images/ct.bmp", &bitmapInfo);

	int w = bitmapInfo.imgWidth, h = bitmapInfo.imgHeight;
	const unsigned int nPix = w * h; // number of pixels
	color* colBuff[nPix]; 	// Buffer of color data
	
	/* printArray(bitmapData, bitmapInfo.imageSizeBytes); */
	getBufferArray(bitmapData, bitmapInfo.imageSizeBytes, nPix, colBuff);

	char output[nPix];
	loadASCIIBuffer(colBuff, nPix, output);

	/* rotate180(output, w, h); */
	/* printCol(colBuff, w, h); */
	plotImage(output, w, h);

	return 0;
}
