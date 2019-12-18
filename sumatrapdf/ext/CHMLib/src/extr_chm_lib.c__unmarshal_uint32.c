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
typedef  unsigned char UInt32 ;

/* Variables and functions */

__attribute__((used)) static int _unmarshal_uint32(unsigned char **pData,
                             unsigned int *pLenRemain,
                             UInt32 *dest)
{
    if (4 > *pLenRemain)
        return 0;
    *dest = (*pData)[0] | (*pData)[1]<<8 | (*pData)[2]<<16 | (*pData)[3]<<24;
    *pData += 4;
    *pLenRemain -= 4;
    return 1;
}