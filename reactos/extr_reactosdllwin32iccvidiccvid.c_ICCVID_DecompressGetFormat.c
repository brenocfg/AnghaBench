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
struct TYPE_14__ {scalar_t__ dwMagic; } ;
struct TYPE_12__ {int biSize; int biBitCount; int biClrUsed; int biSizeImage; int biHeight; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biCompression; } ;
struct TYPE_13__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int LRESULT ;
typedef  TYPE_2__* LPBITMAPINFO ;
typedef  TYPE_3__ ICCVID_Info ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ ICCVID_MAGIC ; 
 int ICERR_BADPARAM ; 
 int ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,TYPE_2__*,TYPE_2__*) ; 
 int get_stride (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static LRESULT ICCVID_DecompressGetFormat( ICCVID_Info *info, LPBITMAPINFO in, LPBITMAPINFO out )
{
    DWORD size;

    TRACE("ICM_DECOMPRESS_GETFORMAT %p %p %p\n", info, in, out);

    if( (info==NULL) || (info->dwMagic!=ICCVID_MAGIC) )
        return ICERR_BADPARAM;

    size = in->bmiHeader.biSize;
    if (in->bmiHeader.biBitCount <= 8)
        size += in->bmiHeader.biClrUsed * sizeof(RGBQUAD);

    if( out )
    {
        memcpy( out, in, size );
        out->bmiHeader.biBitCount = 24;
        out->bmiHeader.biCompression = BI_RGB;
        out->bmiHeader.biSizeImage = get_stride(in->bmiHeader.biWidth, 24) * in->bmiHeader.biHeight;
        return ICERR_OK;
    }
    return size;
}