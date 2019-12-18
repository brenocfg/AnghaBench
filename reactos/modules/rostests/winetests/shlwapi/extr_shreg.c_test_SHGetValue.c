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
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MAX_PATH ; 
 int REG_EXPAND_SZ ; 
 int REG_SZ ; 
 int /*<<< orphan*/  REG_TEST_KEY ; 
 int SHGetValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,char*,int*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sEmptyBuffer ; 
 int /*<<< orphan*/  sExpTestpath1 ; 
 int /*<<< orphan*/  sTestpath1 ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_SHGetValue(void)
{
	DWORD dwSize;
	DWORD dwType;
        DWORD dwRet;
	char buf[MAX_PATH];

	strcpy(buf, sEmptyBuffer);
	dwSize = MAX_PATH;
	dwType = -1;
        dwRet = SHGetValueA(HKEY_CURRENT_USER, REG_TEST_KEY, "Test1", &dwType, buf, &dwSize);
	ok( ERROR_SUCCESS == dwRet, "SHGetValueA failed, ret=%u\n", dwRet);
        ok( 0 == strcmp(sExpTestpath1, buf) ||
            broken(0 == strcmp(sTestpath1, buf)), /* IE4.x */
            "Comparing of (%s) with (%s) failed\n", buf, sExpTestpath1);
        ok( REG_SZ == dwType ||
            broken(REG_EXPAND_SZ == dwType), /* IE4.x */
            "Expected REG_SZ, got (%u)\n", dwType);

	strcpy(buf, sEmptyBuffer);
	dwSize = MAX_PATH;
	dwType = -1;
        dwRet = SHGetValueA(HKEY_CURRENT_USER, REG_TEST_KEY, "Test2", &dwType, buf, &dwSize);
	ok( ERROR_SUCCESS == dwRet, "SHGetValueA failed, ret=%u\n", dwRet);
	ok( 0 == strcmp(sTestpath1, buf) , "Comparing of (%s) with (%s) failed\n", buf, sTestpath1);
	ok( REG_SZ == dwType , "Expected REG_SZ, got (%u)\n", dwType);
}