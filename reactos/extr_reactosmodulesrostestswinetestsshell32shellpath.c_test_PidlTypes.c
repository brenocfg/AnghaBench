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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIDL_DESKTOP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  optionalShellValues ; 
 int /*<<< orphan*/  requiredShellValues ; 
 int /*<<< orphan*/  test_SHGetFolderPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_SHGetSpecialFolderPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ShellValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_PidlTypes(void)
{
    /* Desktop */
    test_SHGetFolderPath(FALSE, CSIDL_DESKTOP);
    test_SHGetSpecialFolderPath(FALSE, CSIDL_DESKTOP);

    test_ShellValues(requiredShellValues, ARRAY_SIZE(requiredShellValues), FALSE);
    test_ShellValues(optionalShellValues, ARRAY_SIZE(optionalShellValues), TRUE);
}