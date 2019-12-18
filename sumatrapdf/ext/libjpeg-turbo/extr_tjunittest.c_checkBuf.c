#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num; int denom; } ;
typedef  TYPE_1__ tjscalingfactor ;

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJSAMP_GRAY ; 
 int* alphaOffset ; 
 int /*<<< orphan*/  checkval (unsigned char,int) ; 
 int /*<<< orphan*/  checkval0 (unsigned char) ; 
 int /*<<< orphan*/  checkval255 (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* tjBlueOffset ; 
 int* tjGreenOffset ; 
 int* tjPixelSize ; 
 int* tjRedOffset ; 

int checkBuf(unsigned char *buf, int w, int h, int pf, int subsamp,
	tjscalingfactor sf, int flags)
{
	int roffset=tjRedOffset[pf];
	int goffset=tjGreenOffset[pf];
	int boffset=tjBlueOffset[pf];
	int aoffset=alphaOffset[pf];
	int ps=tjPixelSize[pf];
	int index, row, col, retval=1;
	int halfway=16*sf.num/sf.denom;
	int blocksize=8*sf.num/sf.denom;

	for(row=0; row<h; row++)
	{
		for(col=0; col<w; col++)
		{
			unsigned char r, g, b, a;
			if(flags&TJFLAG_BOTTOMUP) index=(h-row-1)*w+col;
			else index=row*w+col;
			r=buf[index*ps+roffset];
			g=buf[index*ps+goffset];
			b=buf[index*ps+boffset];
			a=aoffset>=0? buf[index*ps+aoffset]:0xFF;
			if(((row/blocksize)+(col/blocksize))%2==0)
			{
				if(row<halfway)
				{
					checkval255(r);  checkval255(g);  checkval255(b);
				}
				else
				{
					checkval0(r);  checkval0(g);  checkval0(b);
				}
			}
			else
			{
				if(subsamp==TJSAMP_GRAY)
				{
					if(row<halfway)
					{
						checkval(r, 76);  checkval(g, 76);  checkval(b, 76);
					}
					else
					{
						checkval(r, 226);  checkval(g, 226);  checkval(b, 226);
					}
				}
				else
				{
					if(row<halfway)
					{
						checkval255(r);  checkval0(g);  checkval0(b);
					}
					else
					{
						checkval255(r);  checkval255(g);  checkval0(b);
					}
				}
			}
			checkval255(a);
		}
	}

	bailout:
	if(retval==0)
	{
		for(row=0; row<h; row++)
		{
			for(col=0; col<w; col++)
			{
				printf("%.3d/%.3d/%.3d ", buf[(row*w+col)*ps+roffset],
					buf[(row*w+col)*ps+goffset], buf[(row*w+col)*ps+boffset]);
			}
			printf("\n");
		}
	}
	return retval;
}