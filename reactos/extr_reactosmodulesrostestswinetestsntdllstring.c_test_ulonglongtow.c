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
struct TYPE_4__ {int mask; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int NB_ULONGLONG2STR ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  one_i64tow_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/  one_ui64tow_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/ * p_i64tow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * p_ui64tow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ulonglong2str ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ulonglongtow(void)
{
    int test_num;
    LPWSTR result;

    for (test_num = 0; test_num < NB_ULONGLONG2STR; test_num++) {
	if (ulonglong2str[test_num].mask & 0x10) {
	    one_i64tow_test(test_num, &ulonglong2str[test_num]);
	} /* if */
	if (p_ui64tow) {
	    if (ulonglong2str[test_num].mask & 0x20) {
		one_ui64tow_test(test_num, &ulonglong2str[test_num]);
	    } /* if */
	} /* if */
    } /* for */

    if (0) {
        /* Crashes on XP and W2K3 */
        result = p_i64tow(ulonglong2str[0].value, NULL, 10);
        ok(result == NULL,
           "(test d): _i64tow(0x%s, NULL, 10) has result %p, expected: NULL\n",
           wine_dbgstr_longlong(ulonglong2str[0].value), result);
    }

    if (p_ui64tow) {
        if (0) {
            /* Crashes on XP and W2K3 */
	    result = p_ui64tow(ulonglong2str[0].value, NULL, 10);
	    ok(result == NULL,
               "(test e): _ui64tow(0x%s, NULL, 10) has result %p, expected: NULL\n",
	       wine_dbgstr_longlong(ulonglong2str[0].value), result);
        }
    } /* if */
}