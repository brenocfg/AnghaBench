#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbSize; int dwGroupId; } ;
typedef  TYPE_1__* PCCRYPT_OID_INFO ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  CRYPT_OID_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int CRYPT_ENHKEY_USAGE_OID_GROUP_ID ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pWTHelperGetKnownUsages (int,TYPE_1__***) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_get_known_usages(void)
{
    BOOL ret;
    PCCRYPT_OID_INFO *usages;

    if (!pWTHelperGetKnownUsages)
    {
        skip("missing WTHelperGetKnownUsages\n");
        return;
    }
    SetLastError(0xdeadbeef);
    ret = pWTHelperGetKnownUsages(0, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pWTHelperGetKnownUsages(1, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pWTHelperGetKnownUsages(0, &usages);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    /* A value of 1 for the first parameter seems to imply the value is
     * allocated
     */
    SetLastError(0xdeadbeef);
    usages = NULL;
    ret = pWTHelperGetKnownUsages(1, &usages);
    ok(ret, "WTHelperGetKnownUsages failed: %d\n", GetLastError());
    ok(usages != NULL, "expected a pointer\n");
    if (ret && usages)
    {
        PCCRYPT_OID_INFO *ptr;

        /* The returned usages are an array of PCCRYPT_OID_INFOs, terminated with a
         * NULL pointer.
         */
        for (ptr = usages; *ptr; ptr++)
        {
            ok((*ptr)->cbSize == sizeof(CRYPT_OID_INFO) ||
             (*ptr)->cbSize == (sizeof(CRYPT_OID_INFO) + 2 * sizeof(LPCWSTR)), /* Vista */
             "unexpected size %d\n", (*ptr)->cbSize);
            /* Each returned usage is in the CRYPT_ENHKEY_USAGE_OID_GROUP_ID group */
            ok((*ptr)->dwGroupId == CRYPT_ENHKEY_USAGE_OID_GROUP_ID,
             "expected group CRYPT_ENHKEY_USAGE_OID_GROUP_ID, got %d\n",
             (*ptr)->dwGroupId);
        }
    }
    /* A value of 2 for the second parameter seems to imply the value is freed
     */
    SetLastError(0xdeadbeef);
    ret = pWTHelperGetKnownUsages(2, &usages);
    ok(ret, "WTHelperGetKnownUsages failed: %d\n", GetLastError());
    ok(usages == NULL, "expected pointer to be cleared\n");
    SetLastError(0xdeadbeef);
    usages = NULL;
    ret = pWTHelperGetKnownUsages(2, &usages);
    ok(ret, "WTHelperGetKnownUsages failed: %d\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pWTHelperGetKnownUsages(2, NULL);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
     "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
}