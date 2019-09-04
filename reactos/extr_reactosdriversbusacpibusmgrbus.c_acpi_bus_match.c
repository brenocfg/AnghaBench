#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_driver {int /*<<< orphan*/  ids; } ;
struct TYPE_6__ {TYPE_4__* cid_list; int /*<<< orphan*/  hardware_id; } ;
struct TYPE_7__ {scalar_t__ compatible_ids; scalar_t__ hardware_id; } ;
struct acpi_device {TYPE_2__ pnp; TYPE_3__ flags; } ;
struct TYPE_8__ {int Count; TYPE_1__* Ids; } ;
struct TYPE_5__ {int /*<<< orphan*/  String; } ;
typedef  TYPE_4__ ACPI_PNP_DEVICE_ID_LIST ;

/* Variables and functions */
 scalar_t__ strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_bus_match (
	struct acpi_device	*device,
	struct acpi_driver	*driver)
{
	int error = 0;

	if (device->flags.hardware_id)
		if (strstr(driver->ids, device->pnp.hardware_id))
			goto Done;

	if (device->flags.compatible_ids) {
		ACPI_PNP_DEVICE_ID_LIST *cid_list = device->pnp.cid_list;
		int i;

		/* compare multiple _CID entries against driver ids */
		for (i = 0; i < cid_list->Count; i++)
		{
			if (strstr(driver->ids, cid_list->Ids[i].String))
				goto Done;
		}
	}
	error = -2;

 Done:

	return error;
}