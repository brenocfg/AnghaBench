#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_IMAGE_BMP ; 
 int FZ_IMAGE_GIF ; 
 int FZ_IMAGE_JBIG2 ; 
 int FZ_IMAGE_JPEG ; 
 int FZ_IMAGE_JPX ; 
 int FZ_IMAGE_JXR ; 
 int FZ_IMAGE_PNG ; 
 int FZ_IMAGE_PNM ; 
 int FZ_IMAGE_TIFF ; 
 int FZ_IMAGE_UNKNOWN ; 

int
fz_recognize_image_format(fz_context *ctx, unsigned char p[8])
{
	if (p[0] == 'P' && p[1] >= '1' && p[1] <= '7')
		return FZ_IMAGE_PNM;
	if (p[0] == 0xff && p[1] == 0x4f)
		return FZ_IMAGE_JPX;
	if (p[0] == 0x00 && p[1] == 0x00 && p[2] == 0x00 && p[3] == 0x0c &&
			p[4] == 0x6a && p[5] == 0x50 && p[6] == 0x20 && p[7] == 0x20)
		return FZ_IMAGE_JPX;
	if (p[0] == 0xff && p[1] == 0xd8)
		return FZ_IMAGE_JPEG;
	if (p[0] == 137 && p[1] == 80 && p[2] == 78 && p[3] == 71 &&
			p[4] == 13 && p[5] == 10 && p[6] == 26 && p[7] == 10)
		return FZ_IMAGE_PNG;
	if (p[0] == 'I' && p[1] == 'I' && p[2] == 0xBC)
		return FZ_IMAGE_JXR;
	if (p[0] == 'I' && p[1] == 'I' && p[2] == 42 && p[3] == 0)
		return FZ_IMAGE_TIFF;
	if (p[0] == 'M' && p[1] == 'M' && p[2] == 0 && p[3] == 42)
		return FZ_IMAGE_TIFF;
	if (p[0] == 'G' && p[1] == 'I' && p[2] == 'F')
		return FZ_IMAGE_GIF;
	if (p[0] == 'B' && p[1] == 'M')
		return FZ_IMAGE_BMP;
	if (p[0] == 0x97 && p[1] == 'J' && p[2] == 'B' && p[3] == '2' &&
		p[4] == '\r' && p[5] == '\n'  && p[6] == 0x1a && p[7] == '\n')
		return FZ_IMAGE_JBIG2;
	return FZ_IMAGE_UNKNOWN;
}