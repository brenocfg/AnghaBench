#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hash_unicodestring_test {char const* str; int hash; int /*<<< orphan*/  case_insensitive; } ;
typedef  int /*<<< orphan*/  strW ;
typedef  char WCHAR ;
struct TYPE_4__ {int Length; int MaximumLength; scalar_t__ Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HASH_STRING_ALGORITHM_INVALID ; 
 int /*<<< orphan*/  HASH_STRING_ALGORITHM_X65599 ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 struct hash_unicodestring_test* hash_test ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pRtlHashUnicodeString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_RtlHashUnicodeString(void)
{
    static const WCHAR strW[] = {'T','e','s','t',0,'1',0};
    const struct hash_unicodestring_test *ptr;
    UNICODE_STRING str;
    NTSTATUS status;
    ULONG hash;

    if (!pRtlHashUnicodeString)
    {
        win_skip("RtlHashUnicodeString is not available\n");
        return;
    }

    status = pRtlHashUnicodeString(NULL, FALSE, HASH_STRING_ALGORITHM_X65599, &hash);
    ok(status == STATUS_INVALID_PARAMETER, "got status 0x%08x\n", status);

    RtlInitUnicodeString(&str, strW);
    status = pRtlHashUnicodeString(&str, FALSE, HASH_STRING_ALGORITHM_X65599, NULL);
    ok(status == STATUS_INVALID_PARAMETER, "got status 0x%08x\n", status);

    status = pRtlHashUnicodeString(&str, FALSE, HASH_STRING_ALGORITHM_INVALID, &hash);
    ok(status == STATUS_INVALID_PARAMETER, "got status 0x%08x\n", status);

    /* embedded null */
    str.Buffer = (PWSTR)strW;
    str.Length = sizeof(strW) - sizeof(WCHAR);
    str.MaximumLength = sizeof(strW);
    status = pRtlHashUnicodeString(&str, FALSE, HASH_STRING_ALGORITHM_X65599, &hash);
    ok(status == STATUS_SUCCESS, "got status 0x%08x\n", status);
    ok(hash == 0x32803083, "got 0x%08x\n", hash);

    ptr = hash_test;
    while (*ptr->str)
    {
        RtlInitUnicodeString(&str, ptr->str);
        hash = 0;
        status = pRtlHashUnicodeString(&str, ptr->case_insensitive, HASH_STRING_ALGORITHM_X65599, &hash);
        ok(status == STATUS_SUCCESS, "got status 0x%08x for %s\n", status, wine_dbgstr_w(ptr->str));
        ok(hash == ptr->hash, "got wrong hash 0x%08x, expected 0x%08x, for %s, mode %d\n", hash, ptr->hash,
            wine_dbgstr_w(ptr->str), ptr->case_insensitive);

        ptr++;
    }
}