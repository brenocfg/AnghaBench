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

/* Variables and functions */
 size_t* tjBlueOffset ; 
 size_t* tjGreenOffset ; 
 int* tjPixelSize ; 
 size_t* tjRedOffset ; 

__attribute__((used)) static void pixelconvert(unsigned char *srcbuf, int srcpf, int srcbottomup,
	unsigned char *dstbuf, int dstpf, int dstbottomup, int w, int h)
{
	unsigned char *srcptr=srcbuf, *srcptr2;
	int srcps=tjPixelSize[srcpf];
	int srcstride=srcbottomup? -w*srcps:w*srcps;
	unsigned char *dstptr=dstbuf, *dstptr2;
	int dstps=tjPixelSize[dstpf];
	int dststride=dstbottomup? -w*dstps:w*dstps;
	int row, col;

	if(srcbottomup) srcptr=&srcbuf[w*srcps*(h-1)];
	if(dstbottomup) dstptr=&dstbuf[w*dstps*(h-1)];
	for(row=0; row<h; row++, srcptr+=srcstride, dstptr+=dststride)
	{
		for(col=0, srcptr2=srcptr, dstptr2=dstptr; col<w; col++, srcptr2+=srcps,
			dstptr2+=dstps)
		{
			dstptr2[tjRedOffset[dstpf]]=srcptr2[tjRedOffset[srcpf]];
			dstptr2[tjGreenOffset[dstpf]]=srcptr2[tjGreenOffset[srcpf]];
			dstptr2[tjBlueOffset[dstpf]]=srcptr2[tjBlueOffset[srcpf]];
		}
	}
}