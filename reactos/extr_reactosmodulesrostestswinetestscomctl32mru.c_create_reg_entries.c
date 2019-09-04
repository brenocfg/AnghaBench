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
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  REG_TEST_FULLKEY ; 
 int /*<<< orphan*/  REG_TEST_KEYA ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegCreateKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL create_reg_entries(void)
{
    HKEY hKey = NULL;

    ok(!RegCreateKeyA(HKEY_CURRENT_USER, REG_TEST_FULLKEY, &hKey),
       "Couldn't create test key \"%s\"\n", REG_TEST_KEYA);
    if (!hKey) return FALSE;
    RegCloseKey(hKey);
    return TRUE;
}