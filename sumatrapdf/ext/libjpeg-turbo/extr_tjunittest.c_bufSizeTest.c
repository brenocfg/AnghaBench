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
typedef  int /*<<< orphan*/ * tjhandle ;

/* Variables and functions */
 int RAND_MAX ; 
 int /*<<< orphan*/  TJFLAG_NOREALLOC ; 
 int /*<<< orphan*/  TJPF_BGRX ; 
 int TJ_NUMSAMP ; 
 scalar_t__ YUVENCODE ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwtj () ; 
 int /*<<< orphan*/  _tj (int /*<<< orphan*/ ) ; 
 scalar_t__ alloc ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int random () ; 
 scalar_t__ tjAlloc (unsigned long) ; 
 unsigned long tjBufSize (int,int,int) ; 
 unsigned long tjBufSizeYUV (int,int,int) ; 
 int /*<<< orphan*/  tjCompress2 (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char**,unsigned long*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tjDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tjEncodeYUV2 (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tjFree (unsigned char*) ; 
 int /*<<< orphan*/ * tjInitCompress () ; 
 scalar_t__ yuv ; 

void bufSizeTest(void)
{
	int w, h, i, subsamp;
	unsigned char *srcBuf=NULL, *dstBuf=NULL;
	tjhandle handle=NULL;
	unsigned long dstSize=0;

	if((handle=tjInitCompress())==NULL) _throwtj();

	printf("Buffer size regression test\n");
	for(subsamp=0; subsamp<TJ_NUMSAMP; subsamp++)
	{
		for(w=1; w<48; w++)
		{
			int maxh=(w==1)? 2048:48;
			for(h=1; h<maxh; h++)
			{
				if(h%100==0) printf("%.4d x %.4d\b\b\b\b\b\b\b\b\b\b\b", w, h);
				if((srcBuf=(unsigned char *)malloc(w*h*4))==NULL)
					_throw("Memory allocation failure");
				if(!alloc || yuv==YUVENCODE)
				{
					if(yuv==YUVENCODE) dstSize=tjBufSizeYUV(w, h, subsamp);
					else dstSize=tjBufSize(w, h, subsamp);
					if((dstBuf=(unsigned char *)tjAlloc(dstSize))==NULL)
						_throw("Memory allocation failure");
				}

				for(i=0; i<w*h*4; i++)
				{
					if(random()<RAND_MAX/2) srcBuf[i]=0;
					else srcBuf[i]=255;
				}

				if(yuv==YUVENCODE)
				{
					_tj(tjEncodeYUV2(handle, srcBuf, w, 0, h, TJPF_BGRX, dstBuf, subsamp,
						0));
				}
				else
				{
					_tj(tjCompress2(handle, srcBuf, w, 0, h, TJPF_BGRX, &dstBuf,
						&dstSize, subsamp, 100, alloc? 0:TJFLAG_NOREALLOC));
				}
				free(srcBuf);  srcBuf=NULL;
				tjFree(dstBuf);  dstBuf=NULL;

				if((srcBuf=(unsigned char *)malloc(h*w*4))==NULL)
					_throw("Memory allocation failure");
				if(!alloc || yuv==YUVENCODE)
				{
					if(yuv==YUVENCODE) dstSize=tjBufSizeYUV(h, w, subsamp);
					else dstSize=tjBufSize(h, w, subsamp);
					if((dstBuf=(unsigned char *)tjAlloc(dstSize))==NULL)
						_throw("Memory allocation failure");
				}

				for(i=0; i<h*w*4; i++)
				{
					if(random()<RAND_MAX/2) srcBuf[i]=0;
					else srcBuf[i]=255;
				}

				if(yuv==YUVENCODE)
				{
					_tj(tjEncodeYUV2(handle, srcBuf, h, 0, w, TJPF_BGRX, dstBuf, subsamp,
						0));
				}
				else
				{
					_tj(tjCompress2(handle, srcBuf, h, 0, w, TJPF_BGRX, &dstBuf,
						&dstSize, subsamp, 100, alloc? 0:TJFLAG_NOREALLOC));
				}
				free(srcBuf);  srcBuf=NULL;
				tjFree(dstBuf);  dstBuf=NULL;
			}
		}
	}
	printf("Done.      \n");

	bailout:
	if(srcBuf) free(srcBuf);
	if(dstBuf) free(dstBuf);
	if(handle) tjDestroy(handle);
}