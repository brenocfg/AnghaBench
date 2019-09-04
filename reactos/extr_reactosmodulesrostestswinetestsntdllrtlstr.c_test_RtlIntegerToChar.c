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
struct TYPE_3__ {int base; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 size_t NB_INT2STR ; 
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 TYPE_1__* int2str ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  one_RtlIntegerToChar_test (size_t,TYPE_1__*) ; 
 scalar_t__ pRtlIntegerToChar (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_RtlIntegerToChar(void)
{
    NTSTATUS result;
    size_t test_num;

    for (test_num = 0; test_num < NB_INT2STR; test_num++)
      one_RtlIntegerToChar_test(test_num, &int2str[test_num]);

    result = pRtlIntegerToChar(int2str[0].value, 20, int2str[0].MaximumLength, NULL);
    ok(result == STATUS_INVALID_PARAMETER,
       "(test a): RtlIntegerToChar(%u, %d, %d, NULL) has result %x, expected: %x\n",
       int2str[0].value, 20, int2str[0].MaximumLength, result, STATUS_INVALID_PARAMETER);

    result = pRtlIntegerToChar(int2str[0].value, 20, 0, NULL);
    ok(result == STATUS_INVALID_PARAMETER,
       "(test b): RtlIntegerToChar(%u, %d, %d, NULL) has result %x, expected: %x\n",
       int2str[0].value, 20, 0, result, STATUS_INVALID_PARAMETER);

    result = pRtlIntegerToChar(int2str[0].value, int2str[0].base, 0, NULL);
    ok(result == STATUS_BUFFER_OVERFLOW,
       "(test c): RtlIntegerToChar(%u, %d, %d, NULL) has result %x, expected: %x\n",
       int2str[0].value, int2str[0].base, 0, result, STATUS_BUFFER_OVERFLOW);

    result = pRtlIntegerToChar(int2str[0].value, int2str[0].base, int2str[0].MaximumLength, NULL);
    ok(result == STATUS_ACCESS_VIOLATION,
       "(test d): RtlIntegerToChar(%u, %d, %d, NULL) has result %x, expected: %x\n",
       int2str[0].value, int2str[0].base, int2str[0].MaximumLength, result, STATUS_ACCESS_VIOLATION);
}