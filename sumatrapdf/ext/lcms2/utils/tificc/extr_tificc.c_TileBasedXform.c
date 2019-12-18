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
 int TIFFNumberOfTiles (int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFReadEncodedTile (int /*<<< orphan*/ *,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TIFFTAG_TILELENGTH ; 
 int /*<<< orphan*/  TIFFTAG_TILEWIDTH ; 
 int TIFFTileSize (int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFWriteEncodedTile (int /*<<< orphan*/ *,int,unsigned char*,int) ; 
 int /*<<< orphan*/  _TIFFfree (unsigned char*) ; 
 scalar_t__ _TIFFmalloc (int) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static
int TileBasedXform(cmsHTRANSFORM hXForm, TIFF* in, TIFF* out, int nPlanes)
{
    tsize_t BufSizeIn  = TIFFTileSize(in);
    tsize_t BufSizeOut = TIFFTileSize(out);
    unsigned char *BufferIn, *BufferOut;
    ttile_t i, TileCount = TIFFNumberOfTiles(in) / nPlanes;
    uint32 tw, tl;
    int PixelCount, j;


    TIFFGetFieldDefaulted(in, TIFFTAG_TILEWIDTH,  &tw);
    TIFFGetFieldDefaulted(in, TIFFTAG_TILELENGTH, &tl);

    PixelCount = (int) tw * tl;

    BufferIn = (unsigned char *) _TIFFmalloc(BufSizeIn * nPlanes);
    if (!BufferIn) OutOfMem(BufSizeIn * nPlanes);

    BufferOut = (unsigned char *) _TIFFmalloc(BufSizeOut * nPlanes);
    if (!BufferOut) OutOfMem(BufSizeOut * nPlanes);


    for (i = 0; i < TileCount; i++) {

        for (j=0; j < nPlanes; j++) {

            if (TIFFReadEncodedTile(in, i + (j* TileCount),
                BufferIn + (j*BufSizeIn), BufSizeIn) < 0)   goto cleanup;
        }

        cmsDoTransform(NULL, hXForm, BufferIn, BufferOut, PixelCount);

        for (j=0; j < nPlanes; j++) {

            if (TIFFWriteEncodedTile(out, i + (j*TileCount),
                BufferOut + (j*BufSizeOut), BufSizeOut) < 0) goto cleanup;
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