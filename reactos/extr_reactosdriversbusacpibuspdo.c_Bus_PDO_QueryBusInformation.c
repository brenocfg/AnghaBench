#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_6__ {scalar_t__ Information; } ;
struct TYPE_8__ {TYPE_1__ IoStatus; } ;
struct TYPE_7__ {scalar_t__ BusNumber; int /*<<< orphan*/  LegacyBusType; int /*<<< orphan*/  BusTypeGuid; } ;
typedef  TYPE_2__* PPNP_BUS_INFORMATION ;
typedef  int /*<<< orphan*/  PPDO_DEVICE_DATA ;
typedef  int /*<<< orphan*/  PNP_BUS_INFORMATION ;
typedef  TYPE_3__* PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 TYPE_2__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  GUID_ACPI_INTERFACE_STANDARD ; 
 int /*<<< orphan*/  InternalPowerBus ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
Bus_PDO_QueryBusInformation(
     PPDO_DEVICE_DATA     DeviceData,
      PIRP   Irp )
/*++

Routine Description:

    The PnP Manager uses this IRP to request the type and
    instance number of a device's parent bus. Bus drivers
    should handle this request for their child devices (PDOs).

Arguments:

    DeviceData - Pointer to the PDO's device extension.
    Irp          - Pointer to the irp.

Return Value:

    NT STATUS

--*/
{

    PPNP_BUS_INFORMATION busInfo;

    PAGED_CODE ();

    busInfo = ExAllocatePoolWithTag(PagedPool,
                                    sizeof(PNP_BUS_INFORMATION),
                                    'IpcA');

    if (busInfo == NULL) {
      return STATUS_INSUFFICIENT_RESOURCES;
    }

    busInfo->BusTypeGuid = GUID_ACPI_INTERFACE_STANDARD;

    busInfo->LegacyBusType = InternalPowerBus;

    busInfo->BusNumber = 0; //fixme

    Irp->IoStatus.Information = (ULONG_PTR)busInfo;

    return STATUS_SUCCESS;
}