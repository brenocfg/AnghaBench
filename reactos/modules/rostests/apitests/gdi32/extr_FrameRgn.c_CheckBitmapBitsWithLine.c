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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ UINT ;
typedef  size_t* PUCHAR ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 scalar_t__ GetPixel (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
void
CheckBitmapBitsWithLine(
    ULONG Line,
    HDC hdc,
    UINT cx,
    UINT cy,
    PUCHAR pjBits,
    COLORREF *pcrColors)
{
    UINT x, y, i;

    for (y = 0; y < cy; y++)
    {
        for (x = 0; x < cy; x++)
        {
            i = y * cx + x;
            ok(GetPixel(hdc, x, y) == pcrColors[pjBits[i]],
               "Wrong pixel at (%u,%u): expected 0x%08lx, got 0x%08lx\n",
               x, y, pcrColors[pjBits[i]], GetPixel(hdc, x, y));
        }
    }
}