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
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int GetPixel (int /*<<< orphan*/ ,int,int) ; 

void
ReadBits(HDC hDC, PDWORD OutBits)
{
    int x,y;

    for (y = 0; y < 8; y++)
    {
        DWORD Row = 0;
        for (x = 0; x < 8; x++)
            Row |= (0x80 & GetPixel(hDC, 2 + x, 3 + y)) >> x;
        OutBits[y] = Row;
    }
}