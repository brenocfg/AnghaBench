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
typedef  int UCHAR ;
typedef  int* PUCHAR ;

/* Variables and functions */
 scalar_t__ IsAddressValid (scalar_t__) ; 

UCHAR GetUCHAR(ULONG addr)
{
    if(IsAddressValid(addr))
        return *(PUCHAR)addr;
    else
        return 0x82; // INVALID OPCODE
}