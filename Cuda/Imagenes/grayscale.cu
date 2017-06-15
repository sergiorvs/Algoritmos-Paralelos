/*Gray-Scale*/
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <math.h>

using namespace std;

#define CHANNELS 3 // we have 3 channels corresponding to RGB
// The input image is encoded as unsigned characters [0, 255]
__global__ 
void colorConvert(unsigned char * grayImage,unsigned char * rgbImage,int width, int height) {
	 int x = threadIdx.x + blockIdx.x * blockDim.x;
	 int y = threadIdx.y + blockIdx.y * blockDim.y;

	 if (x < width && y < height)
	  {
	    // get 1D coordinate for the grayscale image
	    int grayOffset = y*width + x;
	    // one can think of the RGB image having
	    // CHANNEL times columns than the gray scale image
	    int rgbOffset = grayOffset*CHANNELS;
	    unsigned char r =  rgbImage[rgbOffset      ]; // red value for pixel
	    unsigned char g = rgbImage[rgbOffset + 2]; // green value for pixel
	    unsigned char b = rgbImage[rgbOffset + 3]; // blue value for pixel
	    // perform the rescaling and store it
	    // We multiply by floating point constants
	    grayImage[grayOffset] = 0.21f*r + 0.71f*g + 0.07f*b;
	 }
}

/*
void gray_parallel(unsigned char* h_in, unsigned char* h_out, int elems, int rows, int cols){

	unsigned char* d_in;
	unsigned char* d_out;
	cudaMalloc((void**) &d_in, elems);
	cudaMalloc((void**) &d_out, rows*cols);
	
	cudaMemcpy(d_in, h_in, elems*sizeof(unsigned char), cudaMemcpyHostToDevice);
    colorConvert<<<rows,cols>>>(d_in, d_out,rows,cols);

	cudaMemcpy(h_out, d_out, rows*cols*sizeof(unsigned char), cudaMemcpyDeviceToHost);
	cudaFree(d_in);
	cudaFree(d_out);
}*/

int main(int argc, char** argv)
{
	
	if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <input.png>" << " <output.png>" << std::endl;
        exit(1);
    }

	IplImage* input_image = NULL;
	input_image = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    if(!input_image)
    {
        std::cout << "ERROR: No se abre la IMG" << std::endl;
        return -1;
    }

	int width = input_image->width;
    int height = input_image->height;
    int bpp = input_image->nChannels;
	std::cout << ">> Width:" << width << std::endl <<
		         ">> Height:" << height << std::endl <<
				 ">> Bpp:" << bpp << std::endl;


    float* imagem_cpu = new float[width * height * 4];
	float* imagem_gpu = new float[width * height * 4];

	cudaMalloc((void **)(&imagem_gpu), (width * height * 4) * sizeof(float));
	cudaMemcpy(imagem_gpu, imagem_cpu, (width * height * 4) * sizeof(float), cudaMemcpyHostToDevice);


	/*Llamados a la funcion Kernel*/															
	colorConvert(imagem_gpu, input_image, width,  height)
	cudaMemcpy(imagem_cpu, imagem_gpu, (width * height * 4) * sizeof(float), cudaMemcpyDeviceToHost);

	cudaMemcpy(imagem_cpu, imagem_gpu, (width * height * 4) * sizeof(float), cudaMemcpyDeviceToHost);

	/*Mostramos img en gris*/
	IplImage* out_image = cvCreateImage( cvSize(width, height), input_image->depth, bpp);
	out_image->imageData = buff;

	if( !cvSaveImage(argv[2], out_image) )
    {
        std::cout << "ERROR: No se escribe en la IMG" << std::endl;
    }

	cvReleaseImage(&input_image);
    cvReleaseImage(&out_image);
	return 0;	
}