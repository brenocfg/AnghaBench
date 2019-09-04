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
typedef  int ULONG ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static BYTE *GetData(BYTE *pData, ULONG *pLength)
{
    if ((*pData & 0x80) == 0x00)
    {
        *pLength = (*pData & 0x7f);
        return pData + 1;
    }

    if ((*pData & 0xC0) == 0x80)
    {
        *pLength = ((*pData & 0x3f) << 8 | *(pData + 1));
        return pData + 2;
    }

    if ((*pData & 0xE0) == 0xC0)
    {
        *pLength = ((*pData & 0x1f) << 24 | *(pData + 1) << 16 |
                    *(pData + 2) << 8 | *(pData + 3));
        return pData + 4;
    }

    *pLength = (ULONG)-1;
    return 0;
}