#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp ;
struct TYPE_24__ {char* hardware_id; char* unique_id; char* device_name; TYPE_2__* cid_list; } ;
struct TYPE_23__ {int /*<<< orphan*/  compatible_ids; int /*<<< orphan*/  hardware_id; int /*<<< orphan*/  unique_id; } ;
struct acpi_device {TYPE_7__ pnp; TYPE_6__ flags; } ;
typedef  char WCHAR ;
typedef  void* ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_22__ {int /*<<< orphan*/  Status; void* Information; } ;
struct TYPE_26__ {TYPE_5__ IoStatus; } ;
struct TYPE_25__ {int /*<<< orphan*/  AcpiHandle; } ;
struct TYPE_20__ {int IdType; } ;
struct TYPE_21__ {TYPE_3__ QueryId; } ;
struct TYPE_19__ {int Count; TYPE_1__* Ids; } ;
struct TYPE_18__ {char* String; } ;
struct TYPE_17__ {int Length; char* Buffer; } ;
struct TYPE_16__ {TYPE_4__ Parameters; } ;
typedef  char* PWCHAR ;
typedef  TYPE_8__* PPDO_DEVICE_DATA ;
typedef  TYPE_9__* PIRP ;
typedef  TYPE_10__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
#define  BusQueryCompatibleIDs 131 
#define  BusQueryDeviceID 130 
#define  BusQueryHardwareIDs 129 
#define  BusQueryInstanceID 128 
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 char* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 TYPE_10__* IoGetCurrentIrpStackLocation (TYPE_9__*) ; 
 int /*<<< orphan*/  NT_ASSERT (int) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  PagedPool ; 
 TYPE_11__ ProcessorHardwareIds ; 
 int /*<<< orphan*/  ProcessorIdString ; 
 int /*<<< orphan*/  RtlCopyMemory (char*,char*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 char UNICODE_NULL ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int swprintf (char*,char*,...) ; 
 int /*<<< orphan*/  wcscpy (char*,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

NTSTATUS
Bus_PDO_QueryDeviceId(
     PPDO_DEVICE_DATA     DeviceData,
      PIRP   Irp )
{
    PIO_STACK_LOCATION      stack;
    PWCHAR                  buffer, src;
    WCHAR                   temp[256];
    ULONG                   length, i;
    NTSTATUS                status = STATUS_SUCCESS;
    struct acpi_device *Device;

    PAGED_CODE ();

    stack = IoGetCurrentIrpStackLocation (Irp);

    switch (stack->Parameters.QueryId.IdType) {

    case BusQueryDeviceID:

        /* This is a REG_SZ value */

        if (DeviceData->AcpiHandle)
        {
            acpi_bus_get_device(DeviceData->AcpiHandle, &Device);

            if (strcmp(Device->pnp.hardware_id, "Processor") == 0)
            {
                length = wcslen(ProcessorIdString);
                wcscpy(temp, ProcessorIdString);
            }
            else
            {
                length = swprintf(temp,
                                  L"ACPI\\%hs",
                                  Device->pnp.hardware_id);
            }
        }
        else
        {
            /* We know it's a fixed feature button because
             * these are direct children of the ACPI root device
             * and therefore have no handle
             */
            length = swprintf(temp,
                              L"ACPI\\FixedButton");
        }

        temp[length++] = UNICODE_NULL;

        NT_ASSERT(length * sizeof(WCHAR) <= sizeof(temp));

        buffer = ExAllocatePoolWithTag(PagedPool, length * sizeof(WCHAR), 'IpcA');

        if (!buffer) {
           status = STATUS_INSUFFICIENT_RESOURCES;
           break;
        }

        RtlCopyMemory (buffer, temp, length * sizeof(WCHAR));
        Irp->IoStatus.Information = (ULONG_PTR) buffer;
        DPRINT("BusQueryDeviceID: %ls\n",buffer);
        break;

    case BusQueryInstanceID:

        /* This is a REG_SZ value */

        /* See comment in BusQueryDeviceID case */
        if(DeviceData->AcpiHandle)
        {
           acpi_bus_get_device(DeviceData->AcpiHandle, &Device);

           if (Device->flags.unique_id)
              length = swprintf(temp,
                                L"%hs",
                                Device->pnp.unique_id);
           else
              /* FIXME: Generate unique id! */
              length = swprintf(temp, L"%ls", L"0");
        }
        else
        {
           /* FIXME: Generate unique id! */
           length = swprintf(temp, L"%ls", L"0");
        }

        temp[length++] = UNICODE_NULL;

        NT_ASSERT(length * sizeof(WCHAR) <= sizeof(temp));

        buffer = ExAllocatePoolWithTag(PagedPool, length * sizeof(WCHAR), 'IpcA');
        if (!buffer) {
           status = STATUS_INSUFFICIENT_RESOURCES;
           break;
        }

        RtlCopyMemory (buffer, temp, length * sizeof (WCHAR));
        DPRINT("BusQueryInstanceID: %ls\n",buffer);
        Irp->IoStatus.Information = (ULONG_PTR) buffer;
        break;

    case BusQueryHardwareIDs:

        /* This is a REG_MULTI_SZ value */
        length = 0;
        status = STATUS_NOT_SUPPORTED;

        /* See comment in BusQueryDeviceID case */
        if (DeviceData->AcpiHandle)
        {
            acpi_bus_get_device(DeviceData->AcpiHandle, &Device);
            
            if (!Device->flags.hardware_id)
            {
                /* We don't have the ID to satisfy this request */
                break;
            }

            DPRINT("Device name: %s\n", Device->pnp.device_name);
            DPRINT("Hardware ID: %s\n", Device->pnp.hardware_id);

            if (strcmp(Device->pnp.hardware_id, "Processor") == 0)
            {
                length = ProcessorHardwareIds.Length / sizeof(WCHAR);
                src = ProcessorHardwareIds.Buffer;
            }
            else
            {
                length += swprintf(&temp[length],
                                   L"ACPI\\%hs",
                                   Device->pnp.hardware_id);
                temp[length++] = UNICODE_NULL;

                length += swprintf(&temp[length],
                                   L"*%hs",
                                   Device->pnp.hardware_id);
                temp[length++] = UNICODE_NULL;
                temp[length++] = UNICODE_NULL;
                src = temp;
            }
        }
        else
        {
            length += swprintf(&temp[length],
                               L"ACPI\\FixedButton");
            temp[length++] = UNICODE_NULL;

            length += swprintf(&temp[length],
                               L"*FixedButton");
            temp[length++] = UNICODE_NULL;
            temp[length++] = UNICODE_NULL;
            src = temp;
        }

        NT_ASSERT(length * sizeof(WCHAR) <= sizeof(temp));

        buffer = ExAllocatePoolWithTag(PagedPool, length * sizeof(WCHAR), 'IpcA');

        if (!buffer) {
           status = STATUS_INSUFFICIENT_RESOURCES;
           break;
        }

        RtlCopyMemory (buffer, src, length * sizeof(WCHAR));
        Irp->IoStatus.Information = (ULONG_PTR) buffer;
        DPRINT("BusQueryHardwareIDs: %ls\n",buffer);
        status = STATUS_SUCCESS;
        break;

    case BusQueryCompatibleIDs:

        /* This is a REG_MULTI_SZ value */
        length = 0;
        status = STATUS_NOT_SUPPORTED;

        /* See comment in BusQueryDeviceID case */
        if (DeviceData->AcpiHandle)
        {
            acpi_bus_get_device(DeviceData->AcpiHandle, &Device);

            if (!Device->flags.hardware_id)
            {
                /* We don't have the ID to satisfy this request */
                break;
            }
            
            DPRINT("Device name: %s\n", Device->pnp.device_name);
            DPRINT("Hardware ID: %s\n", Device->pnp.hardware_id);
            
            if (strcmp(Device->pnp.hardware_id, "Processor") == 0)
            {
                length += swprintf(&temp[length],
                                   L"ACPI\\%hs",
                                   Device->pnp.hardware_id);
                temp[length++] = UNICODE_NULL;

                length += swprintf(&temp[length],
                                   L"*%hs",
                                   Device->pnp.hardware_id);
                temp[length++] = UNICODE_NULL;
                temp[length++] = UNICODE_NULL;
            }
            else if (Device->flags.compatible_ids)
            {
                for (i = 0; i < Device->pnp.cid_list->Count; i++)
                {
                    length += swprintf(&temp[length],
                                   L"ACPI\\%hs",
                                   Device->pnp.cid_list->Ids[i].String);
                    temp[length++] = UNICODE_NULL;
                    
                    length += swprintf(&temp[length],
                                   L"*%hs",
                                   Device->pnp.cid_list->Ids[i].String);
                    temp[length++] = UNICODE_NULL;
                }
                
                temp[length++] = UNICODE_NULL;
            }
            else
            {
                /* No compatible IDs */
                break;
            }
            
            NT_ASSERT(length * sizeof(WCHAR) <= sizeof(temp));

            buffer = ExAllocatePoolWithTag(PagedPool, length * sizeof(WCHAR), 'IpcA');
            if (!buffer)
            {
                status = STATUS_INSUFFICIENT_RESOURCES;
                break;
            }

            RtlCopyMemory (buffer, temp, length * sizeof(WCHAR));
            Irp->IoStatus.Information = (ULONG_PTR) buffer;
            DPRINT("BusQueryCompatibleIDs: %ls\n",buffer);
            status = STATUS_SUCCESS;
        }
        break;

    default:
        status = Irp->IoStatus.Status;
    }
    return status;
}