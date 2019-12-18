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
typedef  int ULONG ;
struct TYPE_3__ {int biWidth; int biBitCount; int biPlanes; int biHeight; } ;
typedef  TYPE_1__ BITMAPINFOHEADER ;

/* Variables and functions */

ULONG
GetBitmapSize(BITMAPINFOHEADER *pbih)
{
    ULONG WidthBits, WidthBytes;

    WidthBits = pbih->biWidth * pbih->biBitCount * pbih->biPlanes;
    WidthBytes = ((WidthBits + 31) & ~ 31) >> 3;

    return pbih->biHeight * WidthBytes;
}