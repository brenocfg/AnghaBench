#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  hardware_id; int /*<<< orphan*/  bus_address; } ;
struct TYPE_22__ {scalar_t__ hardware_id; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  surprise_removal_ok; int /*<<< orphan*/  removable; int /*<<< orphan*/  ejectable; int /*<<< orphan*/  lockable; } ;
struct TYPE_21__ {int /*<<< orphan*/  show_in_ui; int /*<<< orphan*/  functional; int /*<<< orphan*/  enabled; } ;
struct TYPE_20__ {TYPE_4__* states; } ;
struct acpi_device {TYPE_8__ pnp; TYPE_7__ flags; TYPE_6__ status; TYPE_5__ power; } ;
typedef  size_t ULONG ;
struct TYPE_24__ {scalar_t__ AcpiHandle; } ;
struct TYPE_18__ {int /*<<< orphan*/  valid; } ;
struct TYPE_19__ {scalar_t__ latency; TYPE_3__ flags; } ;
struct TYPE_16__ {TYPE_11__* Capabilities; } ;
struct TYPE_17__ {TYPE_1__ DeviceCapabilities; } ;
struct TYPE_15__ {int Version; int Size; scalar_t__* DeviceState; int HardwareDisabled; int NoDisplayInUI; size_t UINumber; void* SilentInstall; void* RawDeviceOK; int /*<<< orphan*/  Address; int /*<<< orphan*/  UniqueID; int /*<<< orphan*/  SurpriseRemovalOK; int /*<<< orphan*/  Removable; int /*<<< orphan*/  EjectSupported; int /*<<< orphan*/  LockSupported; void* WakeFromD3; void* WakeFromD2; void* WakeFromD1; void* WakeFromD0; void* DeviceD2; void* DeviceD1; scalar_t__ DeviceWake; scalar_t__ D3Latency; scalar_t__ D2Latency; scalar_t__ D1Latency; } ;
struct TYPE_14__ {TYPE_2__ Parameters; } ;
typedef  TYPE_9__* PPDO_DEVICE_DATA ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_10__* PIO_STACK_LOCATION ;
typedef  TYPE_11__* PDEVICE_CAPABILITIES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DEVICE_CAPABILITIES ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUTTON_HID_LID ; 
 size_t ACPI_D_STATE_COUNT ; 
 int /*<<< orphan*/  ACPI_PROCESSOR_HID ; 
#define  ACPI_STATE_D0 131 
#define  ACPI_STATE_D1 130 
#define  ACPI_STATE_D2 129 
#define  ACPI_STATE_D3 128 
 int /*<<< orphan*/  ACPI_THERMAL_HID ; 
 void* FALSE ; 
 TYPE_10__* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 void* PowerDeviceD0 ; 
 scalar_t__ PowerDeviceD1 ; 
 scalar_t__ PowerDeviceD2 ; 
 void* PowerDeviceD3 ; 
 size_t PowerSystemSleeping1 ; 
 size_t PowerSystemSleeping2 ; 
 size_t PowerSystemSleeping3 ; 
 size_t PowerSystemWorking ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 void* TRUE ; 
 int /*<<< orphan*/  acpi_bus_get_device (scalar_t__,struct acpi_device**) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
Bus_PDO_QueryDeviceCaps(
     PPDO_DEVICE_DATA     DeviceData,
      PIRP   Irp )
{

    PIO_STACK_LOCATION      stack;
    PDEVICE_CAPABILITIES    deviceCapabilities;
    struct acpi_device *device = NULL;
    ULONG i;

    PAGED_CODE ();

    if (DeviceData->AcpiHandle)
        acpi_bus_get_device(DeviceData->AcpiHandle, &device);

    stack = IoGetCurrentIrpStackLocation (Irp);

    //
    // Get the packet.
    //
    deviceCapabilities=stack->Parameters.DeviceCapabilities.Capabilities;

    //
    // Set the capabilities.
    //

    if (deviceCapabilities->Version != 1 ||
            deviceCapabilities->Size < sizeof(DEVICE_CAPABILITIES))
    {
       return STATUS_UNSUCCESSFUL;
    }

    deviceCapabilities->D1Latency = 0;
    deviceCapabilities->D2Latency = 0;
    deviceCapabilities->D3Latency = 0;

    deviceCapabilities->DeviceState[PowerSystemWorking] = PowerDeviceD0;
    deviceCapabilities->DeviceState[PowerSystemSleeping1] = PowerDeviceD3;
    deviceCapabilities->DeviceState[PowerSystemSleeping2] = PowerDeviceD3;
    deviceCapabilities->DeviceState[PowerSystemSleeping3] = PowerDeviceD3;

    for (i = 0; i < ACPI_D_STATE_COUNT && device; i++)
    {
        if (!device->power.states[i].flags.valid)
            continue;

        switch (i)
        {
           case ACPI_STATE_D0:
              deviceCapabilities->DeviceState[PowerSystemWorking] = PowerDeviceD0;
              break;

           case ACPI_STATE_D1:
              deviceCapabilities->DeviceState[PowerSystemSleeping1] = PowerDeviceD1;
              deviceCapabilities->D1Latency = device->power.states[i].latency;
              break;

           case ACPI_STATE_D2:
              deviceCapabilities->DeviceState[PowerSystemSleeping2] = PowerDeviceD2;
              deviceCapabilities->D2Latency = device->power.states[i].latency;
              break;

           case ACPI_STATE_D3:
              deviceCapabilities->DeviceState[PowerSystemSleeping3] = PowerDeviceD3;
              deviceCapabilities->D3Latency = device->power.states[i].latency;
              break;
        }
    }

    // We can wake the system from D1
    deviceCapabilities->DeviceWake = PowerDeviceD1;


    deviceCapabilities->DeviceD1 =
        (deviceCapabilities->DeviceState[PowerSystemSleeping1] == PowerDeviceD1) ? TRUE : FALSE;
    deviceCapabilities->DeviceD2 =
        (deviceCapabilities->DeviceState[PowerSystemSleeping2] == PowerDeviceD2) ? TRUE : FALSE;

    deviceCapabilities->WakeFromD0 = FALSE;
    deviceCapabilities->WakeFromD1 = TRUE; //Yes we can
    deviceCapabilities->WakeFromD2 = FALSE;
    deviceCapabilities->WakeFromD3 = FALSE;

    if (device)
    {
       deviceCapabilities->LockSupported = device->flags.lockable;
       deviceCapabilities->EjectSupported = device->flags.ejectable;
       deviceCapabilities->HardwareDisabled = !device->status.enabled && !device->status.functional;
       deviceCapabilities->Removable = device->flags.removable;
       deviceCapabilities->SurpriseRemovalOK = device->flags.surprise_removal_ok;
       deviceCapabilities->UniqueID = device->flags.unique_id;
       deviceCapabilities->NoDisplayInUI = !device->status.show_in_ui;
       deviceCapabilities->Address = device->pnp.bus_address;
    }

    if (!device ||
        (device->flags.hardware_id &&
         (strstr(device->pnp.hardware_id, ACPI_BUTTON_HID_LID) ||
          strstr(device->pnp.hardware_id, ACPI_THERMAL_HID) ||
          strstr(device->pnp.hardware_id, ACPI_PROCESSOR_HID))))
    {
        /* Allow ACPI to control the device if it is a lid button,
         * a thermal zone, a processor, or a fixed feature button */
        deviceCapabilities->RawDeviceOK = TRUE;
    }

    deviceCapabilities->SilentInstall = FALSE;
    deviceCapabilities->UINumber = (ULONG)-1;

    return STATUS_SUCCESS;

}