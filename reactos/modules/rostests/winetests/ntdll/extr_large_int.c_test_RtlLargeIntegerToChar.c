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
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_3__ {int base; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int NB_LARGEINT2STR ; 
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 TYPE_1__* largeint2str ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  one_RtlLargeIntegerToChar_test (int,TYPE_1__*) ; 
 scalar_t__ pRtlLargeIntegerToChar (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_RtlLargeIntegerToChar(void)
{
    NTSTATUS result;
    int test_num;
    ULONGLONG value;

    for (test_num = 0; test_num < NB_LARGEINT2STR; test_num++) {
	one_RtlLargeIntegerToChar_test(test_num, &largeint2str[test_num]);
    } /* for */

    value = largeint2str[0].value;
    result = pRtlLargeIntegerToChar(&value, 20, largeint2str[0].MaximumLength, NULL);
    ok(result == STATUS_INVALID_PARAMETER,
       "(test a): RtlLargeIntegerToChar(0x%s, %d, %d, NULL) has result %x, expected: %x\n",
       wine_dbgstr_longlong(largeint2str[0].value), 20,
       largeint2str[0].MaximumLength, result, STATUS_INVALID_PARAMETER);

    result = pRtlLargeIntegerToChar(&value, 20, 0, NULL);
    ok(result == STATUS_INVALID_PARAMETER,
       "(test b): RtlLargeIntegerToChar(0x%s, %d, %d, NULL) has result %x, expected: %x\n",
       wine_dbgstr_longlong(largeint2str[0].value), 20,
       largeint2str[0].MaximumLength, result, STATUS_INVALID_PARAMETER);

    result = pRtlLargeIntegerToChar(&value, largeint2str[0].base, 0, NULL);
    ok(result == STATUS_BUFFER_OVERFLOW,
       "(test c): RtlLargeIntegerToChar(0x%s, %d, %d, NULL) has result %x, expected: %x\n",
       wine_dbgstr_longlong(largeint2str[0].value), largeint2str[0].base, 0, result, STATUS_BUFFER_OVERFLOW);

    result = pRtlLargeIntegerToChar(&value, largeint2str[0].base, largeint2str[0].MaximumLength, NULL);
    ok(result == STATUS_ACCESS_VIOLATION,
       "(test d): RtlLargeIntegerToChar(0x%s, %d, %d, NULL) has result %x, expected: %x\n",
       wine_dbgstr_longlong(largeint2str[0].value),
       largeint2str[0].base, largeint2str[0].MaximumLength, result, STATUS_ACCESS_VIOLATION);
}