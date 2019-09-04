#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int TAAddressCount; TYPE_1__* Address; } ;
struct TYPE_4__ {int /*<<< orphan*/  AddressLength; int /*<<< orphan*/  Address; int /*<<< orphan*/  AddressType; } ;
typedef  TYPE_2__* PTRANSPORT_ADDRESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TdiAddressSizeFromType (int /*<<< orphan*/ ) ; 

NTSTATUS TdiBuildNullTransportAddressInPlace(PTRANSPORT_ADDRESS A, UINT AddressType)
{
    A->TAAddressCount = 1;

    A->Address[0].AddressLength = TdiAddressSizeFromType(AddressType);
    if (!A->Address[0].AddressLength)
        return STATUS_INVALID_PARAMETER;

    A->Address[0].AddressType = AddressType;

    RtlZeroMemory(A->Address[0].Address, A->Address[0].AddressLength);

    return STATUS_SUCCESS;
}