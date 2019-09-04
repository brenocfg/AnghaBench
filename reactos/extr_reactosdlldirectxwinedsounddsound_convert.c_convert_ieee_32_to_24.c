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
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  float BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_advance (void const**,int,scalar_t__*,int*,int) ; 

__attribute__((used)) static void convert_ieee_32_to_24 (const void *src, void *dst, UINT src_stride,
        UINT dst_stride, INT count, UINT freqAcc, UINT adj)
{
    while (count > 0)
    {
        DWORD src_le = le32(*(DWORD *) src);
        float v = *((float *) &src_le);
        BYTE *dest24 = dst;

        if (v < -1.0f)
        {
            dest24[0] = 0;
            dest24[1] = 0;
            dest24[2] = 0x80;
        }
        else if (v > 1.0f)
        {
            dest24[0] = 0xff;
            dest24[1] = 0xff;
            dest24[2] = 0x7f;
        }
        else if (v < 0.0f)
        {
            dest24[0] = v * 8388608.0f;
            dest24[1] = v * 32768.0f;
            dest24[2] = v * 128.0f;
        }
        else if (v >= 0.0f)
        {
            dest24[0] = v * 8388608.0f;
            dest24[1] = v * 32768.0f;
            dest24[2] = v * 127.0f;
        }

        dst = (char *)dst + dst_stride;
        src_advance(&src, src_stride, &count, &freqAcc, adj);
    }
}