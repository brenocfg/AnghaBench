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
typedef  scalar_t__ ULONG ;
typedef  int* PCHAR ;
typedef  scalar_t__ LONG ;
typedef  int CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ GspMemoryError ; 
 int GspReadMemSafe (int*) ; 
 void** HexChars ; 

__attribute__((used)) static PCHAR
GspMem2Hex(PCHAR Address, PCHAR Buffer, LONG Count, BOOLEAN MayFault)
{
    ULONG i;
    CHAR ch;

    for (i = 0; i < (ULONG)Count; i++)
    {
        if (MayFault)
        {
            ch = GspReadMemSafe(Address);
            if (GspMemoryError)
                return Buffer;
        }
        else
        {
            ch = *Address;
        }
        *Buffer++ = HexChars[(ch >> 4) & 0xf];
        *Buffer++ = HexChars[ch & 0xf];
        Address++;
    }

    *Buffer = 0;
    return Buffer;
}