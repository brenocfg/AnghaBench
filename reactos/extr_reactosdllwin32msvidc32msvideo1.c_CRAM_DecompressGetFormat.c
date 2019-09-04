#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int biSize; int biBitCount; int biClrUsed; int biWidth; int biHeight; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_14__ {TYPE_1__ bmiHeader; } ;
struct TYPE_13__ {scalar_t__ dwMagic; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  TYPE_2__ Msvideo1Context ;
typedef  int LRESULT ;
typedef  TYPE_3__* LPBITMAPINFO ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ CRAM_MAGIC ; 
 int ICERR_BADFORMAT ; 
 int ICERR_BADPARAM ; 
 int ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_3__*,TYPE_3__*) ; 
 int get_stride (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static LRESULT 
CRAM_DecompressGetFormat( Msvideo1Context *info, LPBITMAPINFO in, LPBITMAPINFO out )
{
    DWORD size;

    TRACE("ICM_DECOMPRESS_GETFORMAT %p %p %p\n", info, in, out);

    if( (info==NULL) || (info->dwMagic!=CRAM_MAGIC) )
        return ICERR_BADPARAM;

    size = in->bmiHeader.biSize;
    if (in->bmiHeader.biBitCount <= 8)
        size += in->bmiHeader.biClrUsed * sizeof(RGBQUAD);

    if (in->bmiHeader.biBitCount != 8 && in->bmiHeader.biBitCount != 16)
        return ICERR_BADFORMAT;

    if( out )
    {
        memcpy( out, in, size );
        out->bmiHeader.biWidth = in->bmiHeader.biWidth & ~1;
        out->bmiHeader.biHeight = in->bmiHeader.biHeight & ~1;
        out->bmiHeader.biCompression = BI_RGB;
        out->bmiHeader.biSizeImage = in->bmiHeader.biHeight *
                                     get_stride(out->bmiHeader.biWidth, out->bmiHeader.biBitCount);
        return ICERR_OK;
    }

    return size;
}