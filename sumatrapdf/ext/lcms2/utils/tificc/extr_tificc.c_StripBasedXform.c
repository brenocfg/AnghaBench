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
typedef  int uint32 ;
typedef  int ttile_t ;
typedef  int tsize_t ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  OutOfMem (int) ; 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int TIFFNumberOfStrips (int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFReadEncodedStrip (int /*<<< orphan*/ *,int,unsigned char*,int) ; 
 int TIFFStripSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFTAG_IMAGELENGTH ; 
 int /*<<< orphan*/  TIFFTAG_IMAGEWIDTH ; 
 int /*<<< orphan*/  TIFFTAG_ROWSPERSTRIP ; 
 scalar_t__ TIFFWriteEncodedStrip (int /*<<< orphan*/ *,int,unsigned char*,int) ; 
 int /*<<< orphan*/  _TIFFfree (unsigned char*) ; 
 scalar_t__ _TIFFmalloc (int) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static
int StripBasedXform(cmsHTRANSFORM hXForm, TIFF* in, TIFF* out, int nPlanes)
{
    tsize_t BufSizeIn  = TIFFStripSize(in);
    tsize_t BufSizeOut = TIFFStripSize(out);
    unsigned char *BufferIn, *BufferOut;
    ttile_t i, StripCount = TIFFNumberOfStrips(in) / nPlanes;
    uint32 sw;
    uint32 sl;
    uint32 iml;
    int j;
    int PixelCount;

    TIFFGetFieldDefaulted(in, TIFFTAG_IMAGEWIDTH,  &sw);
    TIFFGetFieldDefaulted(in, TIFFTAG_ROWSPERSTRIP, &sl);
    TIFFGetFieldDefaulted(in, TIFFTAG_IMAGELENGTH, &iml);

    // It is possible to get infinite rows per strip
    if (sl == 0 || sl > iml)
        sl = iml;   // One strip for whole image

    BufferIn = (unsigned char *) _TIFFmalloc(BufSizeIn * nPlanes);
    if (!BufferIn) OutOfMem(BufSizeIn * nPlanes);

    BufferOut = (unsigned char *) _TIFFmalloc(BufSizeOut * nPlanes);
    if (!BufferOut) OutOfMem(BufSizeOut * nPlanes);


    for (i = 0; i < StripCount; i++) {

        for (j=0; j < nPlanes; j++) {

            if (TIFFReadEncodedStrip(in, i + (j * StripCount),
                BufferIn + (j * BufSizeIn), BufSizeIn) < 0)   goto cleanup;
        }

        PixelCount = (int) sw * (iml < sl ? iml : sl);
        iml -= sl;

        cmsDoTransform(NULL, hXForm, BufferIn, BufferOut, PixelCount);

        for (j=0; j < nPlanes; j++) {
            if (TIFFWriteEncodedStrip(out, i + (j * StripCount),
                BufferOut + j * BufSizeOut, BufSizeOut) < 0) goto cleanup;
        }

    }

    _TIFFfree(BufferIn);
    _TIFFfree(BufferOut);
    return 1;

cleanup:

    _TIFFfree(BufferIn);
    _TIFFfree(BufferOut);
    return 0;
}