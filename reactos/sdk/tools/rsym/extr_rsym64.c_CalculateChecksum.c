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
typedef  int WORD ;
typedef  int ULONG ;
typedef  int DWORD ;

/* Variables and functions */

WORD
CalculateChecksum(DWORD Start, void *pFile, ULONG cbSize)
{
    WORD *Ptr = pFile;
    DWORD i;
    DWORD checksum = Start;

    for (i = 0; i < (cbSize + 1) / sizeof(WORD); i++)
    {
        checksum += Ptr[i];
        checksum = (checksum + (checksum >> 16)) & 0xffff;
    }

    return checksum ;
}