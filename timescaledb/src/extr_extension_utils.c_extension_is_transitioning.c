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

/* Variables and functions */
 scalar_t__ CurrentExtensionObject ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 scalar_t__ creating_extension ; 
 scalar_t__ get_extension_oid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool inline extension_is_transitioning()
{
	/*
	 * Determine whether the extension is being created or upgraded (as a
	 * misnomer creating_extension is true during upgrades)
	 */
	if (creating_extension)
	{
		return get_extension_oid(EXTENSION_NAME, true) == CurrentExtensionObject;
	}
	return false;
}