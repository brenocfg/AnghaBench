#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_6__ {scalar_t__ Type; TYPE_1__ Address; } ;
typedef  size_t* PUCHAR ;
typedef  TYPE_2__* PIP_ADDRESS ;
typedef  int /*<<< orphan*/  IPv6_RAW_ADDRESS ;
typedef  int /*<<< orphan*/  IPv4_RAW_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ROUTER ; 
 scalar_t__ IP_ADDRESS_V4 ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

UINT CommonPrefixLength(
    PIP_ADDRESS Address1,
    PIP_ADDRESS Address2)
/*
 * FUNCTION: Computes the length of the longest prefix common to two addresses
 * ARGUMENTS:
 *     Address1 = Pointer to first address
 *     Address2 = Pointer to second address
 * NOTES:
 *     The two addresses must be of the same type
 * RETURNS:
 *     Length of longest common prefix
 */
{
    PUCHAR Addr1, Addr2;
    UINT Size;
    UINT i, j;
    UINT Bitmask;

    TI_DbgPrint(DEBUG_ROUTER, ("Called. Address1 (0x%X)  Address2 (0x%X).\n", Address1, Address2));

    /*TI_DbgPrint(DEBUG_ROUTER, ("Target  (%s) \n", A2S(Address1)));*/
    /*TI_DbgPrint(DEBUG_ROUTER, ("Adapter (%s).\n", A2S(Address2)));*/

    if (Address1->Type == IP_ADDRESS_V4)
        Size = sizeof(IPv4_RAW_ADDRESS);
    else
        Size = sizeof(IPv6_RAW_ADDRESS);

    Addr1 = (PUCHAR)&Address1->Address.IPv4Address;
    Addr2 = (PUCHAR)&Address2->Address.IPv4Address;

    /* Find first non-matching byte */
    for (i = 0; i < Size && Addr1[i] == Addr2[i]; i++);
    if( i == Size ) return 8 * i;

    /* Find first non-matching bit */
    Bitmask = 0x80;
    for (j = 0; (Addr1[i] & Bitmask) == (Addr2[i] & Bitmask); j++)
        Bitmask >>= 1;

    TI_DbgPrint(DEBUG_ROUTER, ("Returning %d\n", 8 * i + j));

    return 8 * i + j;
}