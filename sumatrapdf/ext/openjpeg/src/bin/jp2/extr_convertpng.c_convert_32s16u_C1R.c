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
typedef  int OPJ_UINT32 ;
typedef  size_t OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  void* OPJ_BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_32s16u_C1R(const OPJ_INT32* pSrc, OPJ_BYTE* pDst,
                               OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < length; i++) {
        OPJ_UINT32 val = (OPJ_UINT32)pSrc[i];
        *pDst++ = (OPJ_BYTE)(val >> 8);
        *pDst++ = (OPJ_BYTE)val;
    }
}