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
typedef  int UINT ;
typedef  int INT8 ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_advance (void const**,int,scalar_t__*,int*,int) ; 

__attribute__((used)) static void convert_ieee_32_to_8 (const void *src, void *dst, UINT src_stride,
        UINT dst_stride, INT count, UINT freqAcc, UINT adj)
{
    while (count > 0)
    {
        DWORD src_le = le32(*(DWORD *) src);
        float v = *((float *) &src_le);
        INT8 d = 0;

        if (v < -1.0f)
            d = -128;
        else if (v >  1.0f)
            d = 127;
        else
            d = v * 127.5f - 0.5f;

        *(BYTE *) dst = d ^ 0x80;

        dst = (char *)dst + dst_stride;
        src_advance(&src, src_stride, &count, &freqAcc, adj);
    }
}