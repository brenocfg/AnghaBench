#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int /*<<< orphan*/  bcBitCount; int /*<<< orphan*/  bcHeight; int /*<<< orphan*/  bcWidth; } ;
struct TYPE_4__ {int biSize; scalar_t__ biCompression; int /*<<< orphan*/  biBitCount; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BITMAPV5HEADER ;
typedef  int /*<<< orphan*/  BITMAPV4HEADER ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPCOREHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 

__attribute__((used)) static int DIB_GetBitmapInfo( const BITMAPINFOHEADER *header, LONG *width,
                              LONG *height, WORD *bpp, DWORD *compr )
{
    if (header->biSize == sizeof(BITMAPCOREHEADER))
    {
        const BITMAPCOREHEADER *core = (const BITMAPCOREHEADER *)header;
        *width  = core->bcWidth;
        *height = core->bcHeight;
        *bpp    = core->bcBitCount;
        *compr  = 0;
        return 0;
    }
    else if (header->biSize == sizeof(BITMAPINFOHEADER) ||
             header->biSize == sizeof(BITMAPV4HEADER) ||
             header->biSize == sizeof(BITMAPV5HEADER))
    {
        *width  = header->biWidth;
        *height = header->biHeight;
        *bpp    = header->biBitCount;
        *compr  = header->biCompression;
        return 1;
    }
    ERR("(%d): unknown/wrong size for header\n", header->biSize );
    return -1;
}