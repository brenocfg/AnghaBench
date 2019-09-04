#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {scalar_t__ Index; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int* PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  TYPE_1__* PIP_INTERFACE ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  ATInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INFO ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  TDI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

TDI_STATUS
InfoTdiQueryGetATInfo(
    TDIEntityID ID,
    PIP_INTERFACE Interface,
    PNDIS_BUFFER Buffer,
    PUINT BufferSize)
{
    ULONG ATInfo[2];
    TDI_STATUS Status;

    TI_DbgPrint(DEBUG_INFO, ("Called.\n"));

    if (!Interface)
        return TDI_INVALID_PARAMETER;

    if (*BufferSize < sizeof(ATInfo))
        return STATUS_BUFFER_TOO_SMALL;

    /* FIXME: I have no idea what the first field should contain... */
    ATInfo[0] = 0;
    ATInfo[1] = Interface->Index;

    Status = InfoCopyOut((PCHAR)ATInfo,
                         sizeof(ATInfo),
                         Buffer,
                         BufferSize);

    TI_DbgPrint(DEBUG_INFO, ("Returning %08x\n", Status));

    return Status;
}