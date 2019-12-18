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
typedef  char WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/ * HUSKEY ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pSHRegCloseUSKey (int /*<<< orphan*/ *) ; 
 scalar_t__ pSHRegOpenUSKeyW (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHRegCloseUSKey(void)
{
    static const WCHAR localW[] = {'S','o','f','t','w','a','r','e',0};
    LONG ret;
    HUSKEY key;

    if (!pSHRegOpenUSKeyW || !pSHRegCloseUSKey)
    {
        win_skip("SHRegOpenUSKeyW or SHRegCloseUSKey not available\n");
        return;
    }

    ret = pSHRegCloseUSKey(NULL);
    ok(ret == ERROR_INVALID_PARAMETER, "got %d\n", ret);

    ret = pSHRegOpenUSKeyW(localW, KEY_ALL_ACCESS, NULL, &key, FALSE);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = pSHRegCloseUSKey(key);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    /* Test with limited rights, specially without KEY_SET_VALUE */
    ret = pSHRegOpenUSKeyW(localW, KEY_QUERY_VALUE, NULL, &key, FALSE);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);

    ret = pSHRegCloseUSKey(key);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
}