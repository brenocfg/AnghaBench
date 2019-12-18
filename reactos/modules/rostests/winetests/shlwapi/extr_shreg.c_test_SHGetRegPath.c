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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_TEST_KEY ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 scalar_t__ pSHRegGetPathA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sEmptyBuffer ; 
 int /*<<< orphan*/  sExpTestpath1 ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_SHGetRegPath(void)
{
	char buf[MAX_PATH];
        DWORD dwRet;

	if (!pSHRegGetPathA)
		return;

	strcpy(buf, sEmptyBuffer);
        dwRet = (*pSHRegGetPathA)(HKEY_CURRENT_USER, REG_TEST_KEY, "Test1", buf, 0);
	ok( ERROR_SUCCESS == dwRet, "SHRegGetPathA failed, ret=%u\n", dwRet);
	ok( 0 == strcmp(sExpTestpath1, buf) , "Comparing (%s) with (%s) failed\n", buf, sExpTestpath1);
}