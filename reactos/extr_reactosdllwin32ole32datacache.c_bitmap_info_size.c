#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_7__ {int bcBitCount; } ;
struct TYPE_5__ {int biSize; unsigned int biClrUsed; int biBitCount; scalar_t__ biCompression; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  RGBTRIPLE ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;
typedef  TYPE_3__ BITMAPCOREHEADER ;

/* Variables and functions */
 scalar_t__ BI_BITFIELDS ; 
 scalar_t__ DIB_RGB_COLORS ; 
 unsigned int max (int,int) ; 

__attribute__((used)) static int bitmap_info_size( const BITMAPINFO * info, WORD coloruse )
{
    unsigned int colors, size, masks = 0;

    if (info->bmiHeader.biSize == sizeof(BITMAPCOREHEADER))
    {
        const BITMAPCOREHEADER *core = (const BITMAPCOREHEADER *)info;
        colors = (core->bcBitCount <= 8) ? 1 << core->bcBitCount : 0;
        return sizeof(BITMAPCOREHEADER) + colors *
            ((coloruse == DIB_RGB_COLORS) ? sizeof(RGBTRIPLE) : sizeof(WORD));
    }
    else  /* assume BITMAPINFOHEADER */
    {
        colors = info->bmiHeader.biClrUsed;
        if (colors > 256) /* buffer overflow otherwise */
            colors = 256;
        if (!colors && (info->bmiHeader.biBitCount <= 8))
            colors = 1 << info->bmiHeader.biBitCount;
        if (info->bmiHeader.biCompression == BI_BITFIELDS) masks = 3;
        size = max( info->bmiHeader.biSize, sizeof(BITMAPINFOHEADER) + masks * sizeof(DWORD) );
        return size + colors * ((coloruse == DIB_RGB_COLORS) ? sizeof(RGBQUAD) : sizeof(WORD));
    }
}