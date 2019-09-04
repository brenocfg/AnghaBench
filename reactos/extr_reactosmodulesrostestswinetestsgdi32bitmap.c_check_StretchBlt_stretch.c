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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  StretchBlt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int get_dib_image_size (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void check_StretchBlt_stretch(HDC hdcDst, HDC hdcSrc, BITMAPINFO *dst_info, UINT32 *dstBuffer, UINT32 *srcBuffer,
                                     int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
                                     int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc,
                                     UINT32 *expected, int line)
{
    int dst_size = get_dib_image_size( dst_info );

    memset(dstBuffer, 0, dst_size);
    StretchBlt(hdcDst, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
               hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
    ok(memcmp(dstBuffer, expected, dst_size) == 0,
        "StretchBlt expected { %08X, %08X, %08X, %08X } got { %08X, %08X, %08X, %08X } "
        "stretching { %d, %d, %d, %d } to { %d, %d, %d, %d } from line %d\n",
        expected[0], expected[1], expected[2], expected[3],
        dstBuffer[0], dstBuffer[1], dstBuffer[2], dstBuffer[3],
        nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc,
        nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, line);
}