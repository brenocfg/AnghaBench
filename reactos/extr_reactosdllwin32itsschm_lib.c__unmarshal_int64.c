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
typedef  int Int64 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL _unmarshal_int64(unsigned char **pData,
                             unsigned int *pLenRemain,
                             Int64 *dest)
{
    Int64 temp;
    int i;
    if (8 > *pLenRemain)
        return FALSE;
    temp=0;
    for(i=8; i>0; i--)
    {
        temp <<= 8;
        temp |= (*pData)[i-1];
    }
    *dest = temp;
    *pData += 8;
    *pLenRemain -= 8;
    return TRUE;
}