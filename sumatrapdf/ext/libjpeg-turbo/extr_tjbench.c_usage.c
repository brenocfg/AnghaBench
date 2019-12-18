#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num; int denom; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int nsf ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* scalingfactors ; 

void usage(char *progname)
{
	int i;
	printf("USAGE: %s\n", progname);
	printf("       <Inputfile (BMP|PPM)> <Quality> [options]\n\n");
	printf("       %s\n", progname);
	printf("       <Inputfile (JPG)> [options]\n\n");
	printf("Options:\n\n");
	printf("-alloc = Dynamically allocate JPEG image buffers\n");
	printf("-bmp = Generate output images in Windows Bitmap format (default=PPM)\n");
	printf("-bottomup = Test bottom-up compression/decompression\n");
	printf("-tile = Test performance of the codec when the image is encoded as separate\n");
	printf("     tiles of varying sizes.\n");
	printf("-forcemmx, -forcesse, -forcesse2, -forcesse3 =\n");
	printf("     Force MMX, SSE, SSE2, or SSE3 code paths in the underlying codec\n");
	printf("-rgb, -bgr, -rgbx, -bgrx, -xbgr, -xrgb =\n");
	printf("     Test the specified color conversion path in the codec (default: BGR)\n");
	printf("-fastupsample = Use the fastest chrominance upsampling algorithm available in\n");
	printf("     the underlying codec\n");
	printf("-fastdct = Use the fastest DCT/IDCT algorithms available in the underlying\n");
	printf("     codec\n");
	printf("-accuratedct = Use the most accurate DCT/IDCT algorithms available in the\n");
	printf("     underlying codec\n");
	printf("-subsamp <s> = When testing JPEG compression, this option specifies the level\n");
	printf("     of chrominance subsampling to use (<s> = 444, 422, 440, 420, or GRAY).\n");
	printf("     The default is to test Grayscale, 4:2:0, 4:2:2, and 4:4:4 in sequence.\n");
	printf("-quiet = Output results in tabular rather than verbose format\n");
	printf("-yuvencode = Encode RGB input as planar YUV rather than compressing as JPEG\n");
	printf("-yuvdecode = Decode JPEG image to planar YUV rather than RGB\n");
	printf("-scale M/N = scale down the width/height of the decompressed JPEG image by a\n");
	printf("     factor of M/N (M/N = ");
	for(i=0; i<nsf; i++)
	{
		printf("%d/%d", scalingfactors[i].num, scalingfactors[i].denom);
		if(nsf==2 && i!=nsf-1) printf(" or ");
		else if(nsf>2)
		{
			if(i!=nsf-1) printf(", ");
			if(i==nsf-2) printf("or ");
		}
		if(i%8==0 && i!=0) printf("\n     ");
	}
	printf(")\n");
	printf("-hflip, -vflip, -transpose, -transverse, -rot90, -rot180, -rot270 =\n");
	printf("     Perform the corresponding lossless transform prior to\n");
	printf("     decompression (these options are mutually exclusive)\n");
	printf("-grayscale = Perform lossless grayscale conversion prior to decompression\n");
	printf("     test (can be combined with the other transforms above)\n");
	printf("-benchtime <t> = Run each benchmark for at least <t> seconds (default = 5.0)\n\n");
	printf("NOTE:  If the quality is specified as a range (e.g. 90-100), a separate\n");
	printf("test will be performed for all quality values in the range.\n\n");
	exit(1);
}