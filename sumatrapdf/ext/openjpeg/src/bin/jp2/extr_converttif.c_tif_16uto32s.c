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
typedef  int /*<<< orphan*/  OPJ_UINT16 ;
typedef  size_t OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;

/* Variables and functions */

__attribute__((used)) static void tif_16uto32s(const OPJ_UINT16* pSrc, OPJ_INT32* pDst,
                         OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < length; i++) {
        pDst[i] = pSrc[i];
    }
}