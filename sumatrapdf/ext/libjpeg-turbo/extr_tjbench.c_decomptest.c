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
typedef  int /*<<< orphan*/ * tjhandle ;
struct TYPE_3__ {int num; int denom; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJSCALED (int,TYPE_1__) ; 
 int TJ_GRAYSCALE ; 
 scalar_t__ YUVDECODE ; 
 int /*<<< orphan*/  _throwbmp (char*) ; 
 int /*<<< orphan*/  _throwtj (char*) ; 
 int /*<<< orphan*/  _throwunix (char*) ; 
 unsigned char abs (unsigned char) ; 
 double benchtime ; 
 scalar_t__ decomponly ; 
 scalar_t__ dotile ; 
 char* ext ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int flags ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 double gettime () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int min (int,int) ; 
 size_t pf ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ quiet ; 
 int savebmp (char*,unsigned char*,int,int,size_t,int) ; 
 TYPE_1__ sf ; 
 char* sigfig (double,int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 char* strrchr (char*,char) ; 
 char** subName ; 
 int* tjBlueOffset ; 
 int tjBufSizeYUV (int,int,int) ; 
 int tjDecompress2 (int /*<<< orphan*/ *,unsigned char*,unsigned long,unsigned char*,int,int,int,size_t,int) ; 
 int tjDecompressToYUV (int /*<<< orphan*/ *,unsigned char*,unsigned long,unsigned char*,int) ; 
 int tjDestroy (int /*<<< orphan*/ *) ; 
 int* tjGreenOffset ; 
 int /*<<< orphan*/ * tjInitDecompress () ; 
 int* tjPixelSize ; 
 int* tjRedOffset ; 
 scalar_t__ yuv ; 

int decomptest(unsigned char *srcbuf, unsigned char **jpegbuf,
	unsigned long *jpegsize, unsigned char *dstbuf, int w, int h,
	int subsamp, int jpegqual, char *filename, int tilew, int tileh)
{
	char tempstr[1024], sizestr[20]="\0", qualstr[6]="\0", *ptr;
	FILE *file=NULL;  tjhandle handle=NULL;
	int row, col, i, dstbufalloc=0, retval=0;
	double start, elapsed;
	int ps=tjPixelSize[pf];
	int yuvsize=tjBufSizeYUV(w, h, subsamp), bufsize;
	int scaledw=(yuv==YUVDECODE)? w : TJSCALED(w, sf);
	int scaledh=(yuv==YUVDECODE)? h : TJSCALED(h, sf);
	int pitch=scaledw*ps;
	int ntilesw=(w+tilew-1)/tilew, ntilesh=(h+tileh-1)/tileh;
	unsigned char *dstptr, *dstptr2;

	if(jpegqual>0)
	{
		snprintf(qualstr, 6, "_Q%d", jpegqual);
		qualstr[5]=0;
	}

	if((handle=tjInitDecompress())==NULL)
		_throwtj("executing tjInitDecompress()");

	bufsize=(yuv==YUVDECODE? yuvsize:pitch*scaledh);
	if(dstbuf==NULL)
	{
		if((dstbuf=(unsigned char *)malloc(bufsize)) == NULL)
			_throwunix("allocating image buffer");
		dstbufalloc=1;
	}
	/* Set the destination buffer to gray so we know whether the decompressor
	   attempted to write to it */
	memset(dstbuf, 127, bufsize);

	/* Execute once to preload cache */
	if(yuv==YUVDECODE)
	{
		if(tjDecompressToYUV(handle, jpegbuf[0], jpegsize[0], dstbuf, flags)==-1)
			_throwtj("executing tjDecompressToYUV()");
	}
	else if(tjDecompress2(handle, jpegbuf[0], jpegsize[0], dstbuf, scaledw,
		pitch, scaledh, pf, flags)==-1)
		_throwtj("executing tjDecompress2()");

	/* Benchmark */
	for(i=0, start=gettime(); (elapsed=gettime()-start)<benchtime; i++)
	{
		int tile=0;
		if(yuv==YUVDECODE)
		{
			if(tjDecompressToYUV(handle, jpegbuf[0], jpegsize[0], dstbuf, flags)==-1)
				_throwtj("executing tjDecompressToYUV()");
		}
		else for(row=0, dstptr=dstbuf; row<ntilesh; row++, dstptr+=pitch*tileh)
		{
			for(col=0, dstptr2=dstptr; col<ntilesw; col++, tile++, dstptr2+=ps*tilew)
			{
				int width=dotile? min(tilew, w-col*tilew):scaledw;
				int height=dotile? min(tileh, h-row*tileh):scaledh;
				if(tjDecompress2(handle, jpegbuf[tile], jpegsize[tile], dstptr2, width,
					pitch, height, pf, flags)==-1)
					_throwtj("executing tjDecompress2()");
			}
		}
	}

	if(tjDestroy(handle)==-1) _throwtj("executing tjDestroy()");
	handle=NULL;

	if(quiet)
	{
		printf("%s\n",
			sigfig((double)(w*h)/1000000.*(double)i/elapsed, 4, tempstr, 1024));
	}
	else
	{
		printf("D--> Frame rate:           %f fps\n", (double)i/elapsed);
		printf("     Dest. throughput:     %f Megapixels/sec\n",
			(double)(w*h)/1000000.*(double)i/elapsed);
	}
	if(yuv==YUVDECODE)
	{
		snprintf(tempstr, 1024, "%s_%s%s.yuv", filename, subName[subsamp],
			qualstr);
		if((file=fopen(tempstr, "wb"))==NULL)
			_throwunix("opening YUV image for output");
		if(fwrite(dstbuf, yuvsize, 1, file)!=1)
			_throwunix("writing YUV image");
		fclose(file);  file=NULL;
	}
	else
	{
		if(sf.num!=1 || sf.denom!=1)
			snprintf(sizestr, 20, "%d_%d", sf.num, sf.denom);
		else if(tilew!=w || tileh!=h)
			snprintf(sizestr, 20, "%dx%d", tilew, tileh);
		else snprintf(sizestr, 20, "full");
		if(decomponly)
			snprintf(tempstr, 1024, "%s_%s.%s", filename, sizestr, ext);
		else
			snprintf(tempstr, 1024, "%s_%s%s_%s.%s", filename, subName[subsamp],
				qualstr, sizestr, ext);
		if(savebmp(tempstr, dstbuf, scaledw, scaledh, pf,
			(flags&TJFLAG_BOTTOMUP)!=0)==-1)
			_throwbmp("saving bitmap");
		ptr=strrchr(tempstr, '.');
		snprintf(ptr, 1024-(ptr-tempstr), "-err.%s", ext);
		if(srcbuf && sf.num==1 && sf.denom==1)
		{
			if(!quiet) printf("Compression error written to %s.\n", tempstr);
			if(subsamp==TJ_GRAYSCALE)
			{
				int index, index2;
				for(row=0, index=0; row<h; row++, index+=pitch)
				{
					for(col=0, index2=index; col<w; col++, index2+=ps)
					{
						int rindex=index2+tjRedOffset[pf];
						int gindex=index2+tjGreenOffset[pf];
						int bindex=index2+tjBlueOffset[pf];
						int y=(int)((double)srcbuf[rindex]*0.299
							+ (double)srcbuf[gindex]*0.587
							+ (double)srcbuf[bindex]*0.114 + 0.5);
						if(y>255) y=255;  if(y<0) y=0;
						dstbuf[rindex]=abs(dstbuf[rindex]-y);
						dstbuf[gindex]=abs(dstbuf[gindex]-y);
						dstbuf[bindex]=abs(dstbuf[bindex]-y);
					}
				}
			}		
			else
			{
				for(row=0; row<h; row++)
					for(col=0; col<w*ps; col++)
						dstbuf[pitch*row+col]
							=abs(dstbuf[pitch*row+col]-srcbuf[pitch*row+col]);
			}
			if(savebmp(tempstr, dstbuf, w, h, pf,
				(flags&TJFLAG_BOTTOMUP)!=0)==-1)
				_throwbmp("saving bitmap");
		}
	}

	bailout:
	if(file) {fclose(file);  file=NULL;}
	if(handle) {tjDestroy(handle);  handle=NULL;}
	if(dstbuf && dstbufalloc) {free(dstbuf);  dstbuf=NULL;}
	return retval;
}