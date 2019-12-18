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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void check_BitBlt_pixel(HDC hdcDst, HDC hdcSrc, UINT32 *dstBuffer, UINT32 *srcBuffer,
                               DWORD dwRop, UINT32 expected, int line)
{
    *srcBuffer = 0xFEDCBA98;
    *dstBuffer = 0x89ABCDEF;
    BitBlt(hdcDst, 0, 0, 1, 1, hdcSrc, 0, 0, dwRop);
    ok(expected == *dstBuffer,
        "BitBlt with dwRop %06X. Expected 0x%08X, got 0x%08X from line %d\n",
        dwRop, expected, *dstBuffer, line);
}