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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  return_VALUE (int) ; 

__attribute__((used)) static int
acpi_device_register (
	struct acpi_device	*device,
	struct acpi_device	*parent)
{
	int			result = 0;

	if (!device)
		return_VALUE(AE_BAD_PARAMETER);

	return_VALUE(result);
}