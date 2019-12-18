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
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_TEST_BASEKEYA ; 
 int /*<<< orphan*/  REG_TEST_BASESUBKEYA ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mru_RegDeleteTreeA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delete_reg_entries(void)
{
    HKEY hKey;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, REG_TEST_BASEKEYA, 0, KEY_ALL_ACCESS,
                      &hKey))
        return;
    mru_RegDeleteTreeA(hKey, REG_TEST_BASESUBKEYA);
    RegCloseKey(hKey);
}