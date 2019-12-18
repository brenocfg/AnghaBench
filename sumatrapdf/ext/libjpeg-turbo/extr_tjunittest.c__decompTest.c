#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num; int denom; } ;
typedef  TYPE_1__ tjscalingfactor ;
typedef  int /*<<< orphan*/  tjhandle ;

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJSCALED (int,TYPE_1__) ; 
 scalar_t__ YUVDECODE ; 
 scalar_t__ YUVENCODE ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _tj (int /*<<< orphan*/ ) ; 
 scalar_t__ checkBuf (unsigned char*,int,int,int,int,TYPE_1__,int) ; 
 scalar_t__ checkBufYUV (unsigned char*,int,int,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 double gettime () ; 
 scalar_t__ malloc (unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned long) ; 
 char** pixFormatStr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** subNameLong ; 
 unsigned long tjBufSizeYUV (int,int,int) ; 
 int /*<<< orphan*/  tjDecompress2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  tjDecompressHeader2 (int /*<<< orphan*/ ,unsigned char*,unsigned long,int*,int*,int*) ; 
 int /*<<< orphan*/  tjDecompressToYUV (int /*<<< orphan*/ ,unsigned char*,unsigned long,unsigned char*,int) ; 
 int* tjPixelSize ; 
 scalar_t__ yuv ; 

void _decompTest(tjhandle handle, unsigned char *jpegBuf,
	unsigned long jpegSize, int w, int h, int pf, char *basename, int subsamp,
	int flags, tjscalingfactor sf)
{
	unsigned char *dstBuf=NULL;
	int _hdrw=0, _hdrh=0, _hdrsubsamp=-1;  double t;
	int scaledWidth=TJSCALED(w, sf);
	int scaledHeight=TJSCALED(h, sf);
	unsigned long dstSize=0;

	if(yuv==YUVENCODE) return;

	if(yuv==YUVDECODE)
		printf("JPEG -> YUV %s ... ", subNameLong[subsamp]);
	else
	{
		printf("JPEG -> %s %s ", pixFormatStr[pf],
			(flags&TJFLAG_BOTTOMUP)? "Bottom-Up":"Top-Down ");
		if(sf.num!=1 || sf.denom!=1)
			printf("%d/%d ... ", sf.num, sf.denom);
		else printf("... ");
	}

	_tj(tjDecompressHeader2(handle, jpegBuf, jpegSize, &_hdrw, &_hdrh,
		&_hdrsubsamp));
	if(_hdrw!=w || _hdrh!=h || _hdrsubsamp!=subsamp)
		_throw("Incorrect JPEG header");

	if(yuv==YUVDECODE) dstSize=tjBufSizeYUV(w, h, subsamp);
	else dstSize=scaledWidth*scaledHeight*tjPixelSize[pf];
	if((dstBuf=(unsigned char *)malloc(dstSize))==NULL)
		_throw("Memory allocation failure");
	memset(dstBuf, 0, dstSize);

	t=gettime();
	if(yuv==YUVDECODE)
	{
		_tj(tjDecompressToYUV(handle, jpegBuf, jpegSize, dstBuf, flags));
	}
	else
	{
		_tj(tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, scaledWidth, 0,
			scaledHeight, pf, flags));
	}
	t=gettime()-t;

	if(yuv==YUVDECODE)
	{
		if(checkBufYUV(dstBuf, w, h, subsamp)) printf("Passed.");
		else printf("FAILED!");
	}
	else
	{
		if(checkBuf(dstBuf, scaledWidth, scaledHeight, pf, subsamp, sf, flags))
			printf("Passed.");
		else printf("FAILED!");
	}
	printf("  %f ms\n", t*1000.);

	bailout:
	if(dstBuf) free(dstBuf);
}