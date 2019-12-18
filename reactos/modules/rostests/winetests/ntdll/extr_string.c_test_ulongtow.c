#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mask; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int NB_ULONG2STR ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  one_itow_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/  one_ltow_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/  one_ultow_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/ * p_itow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * p_ltow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * p_ultow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ulong2str ; 

__attribute__((used)) static void test_ulongtow(void)
{
    int test_num;
    LPWSTR result;

    for (test_num = 0; test_num < NB_ULONG2STR; test_num++) {
	if (ulong2str[test_num].mask & 0x10) {
	    one_itow_test(test_num, &ulong2str[test_num]);
	} /* if */
	if (ulong2str[test_num].mask & 0x20) {
	    one_ltow_test(test_num, &ulong2str[test_num]);
	} /* if */
	if (ulong2str[test_num].mask & 0x40) {
	    one_ultow_test(test_num, &ulong2str[test_num]);
	} /* if */
    } /* for */

    if (0) {
        /* Crashes on XP and W2K3 */
        result = p_itow(ulong2str[0].value, NULL, 10);
        ok(result == NULL,
           "(test a): _itow(%d, NULL, 10) has result %p, expected: NULL\n",
           ulong2str[0].value, result);
    }

    if (0) {
        /* Crashes on XP and W2K3 */
        result = p_ltow(ulong2str[0].value, NULL, 10);
        ok(result == NULL,
           "(test b): _ltow(%d, NULL, 10) has result %p, expected: NULL\n",
           ulong2str[0].value, result);
    }

    if (0) {
        /* Crashes on XP and W2K3 */
        result = p_ultow(ulong2str[0].value, NULL, 10);
        ok(result == NULL,
           "(test c): _ultow(%d, NULL, 10) has result %p, expected: NULL\n",
           ulong2str[0].value, result);
    }
}