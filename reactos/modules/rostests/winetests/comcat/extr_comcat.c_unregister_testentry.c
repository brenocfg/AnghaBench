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
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void unregister_testentry(void)
{
	RegDeleteKeyA(HKEY_CLASSES_ROOT,
			"CLSID\\{deadcafe-beed-bead-dead-cafebeaddead}\\Implemented Categories\\{deadcafe-0000-0000-0000-000000000000}");
	RegDeleteKeyA(HKEY_CLASSES_ROOT,
			"CLSID\\{deadcafe-beed-bead-dead-cafebeaddead}\\Implemented Categories");
	RegDeleteKeyA(HKEY_CLASSES_ROOT,
			"CLSID\\{deadcafe-beed-bead-dead-cafebeaddead}");
}