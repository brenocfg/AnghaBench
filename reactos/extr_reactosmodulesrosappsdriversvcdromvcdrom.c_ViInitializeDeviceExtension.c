#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {scalar_t__ Length; scalar_t__ MaximumLength; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_6__ {scalar_t__ Length; scalar_t__ MaximumLength; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_9__ {TYPE_2__ ImageName; TYPE_1__ GlobalName; scalar_t__ ChangeCount; int /*<<< orphan*/ * VolumeObject; TYPE_3__* DeviceObject; } ;
struct TYPE_8__ {TYPE_4__* DeviceExtension; } ;
typedef  TYPE_3__* PDEVICE_OBJECT ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;

/* Variables and functions */

VOID
ViInitializeDeviceExtension(PDEVICE_OBJECT DeviceObject)
{
    PDEVICE_EXTENSION DeviceExtension;

    DeviceExtension = DeviceObject->DeviceExtension;

    /* Zero mandatory fields, the rest will be zeroed when needed */
    DeviceExtension->DeviceObject = DeviceObject;
    DeviceExtension->VolumeObject = NULL;
    DeviceExtension->ChangeCount = 0;
    DeviceExtension->GlobalName.Buffer = NULL;
    DeviceExtension->GlobalName.MaximumLength = 0;
    DeviceExtension->GlobalName.Length = 0;
    DeviceExtension->ImageName.Buffer = NULL;
    DeviceExtension->ImageName.MaximumLength = 0;
    DeviceExtension->ImageName.Length = 0;
}