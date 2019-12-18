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
 int /*<<< orphan*/  pEnumMRUListA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pEnumMRUListW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_EnumMRUList(void)
{
    if (!pEnumMRUListA || !pEnumMRUListW)
    {
        win_skip("EnumMRUListA/EnumMRUListW entry point not found\n");
        return;
    }

    /* NULL handle */
    if (0)
    {
        /* crashes on NT4, passed on Win2k, XP, 2k3, Vista, 2k8 */
        pEnumMRUListA(NULL, 0, NULL, 0);
        pEnumMRUListW(NULL, 0, NULL, 0);
    }
}