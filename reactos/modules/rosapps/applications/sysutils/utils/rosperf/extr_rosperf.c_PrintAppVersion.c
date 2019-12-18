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
 int /*<<< orphan*/  KERNEL_VERSION_BUILD_STR ; 
 int /*<<< orphan*/  KERNEL_VERSION_STR ; 
 int /*<<< orphan*/  wprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PrintAppVersion(void)
{
  wprintf(L"RosPerf %S (Build %S)\n", KERNEL_VERSION_STR, KERNEL_VERSION_BUILD_STR);
}