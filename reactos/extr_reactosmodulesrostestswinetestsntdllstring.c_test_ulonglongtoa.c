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
struct TYPE_4__ {int mask; } ;

/* Variables and functions */
 int NB_ULONGLONG2STR ; 
 int /*<<< orphan*/  one_i64toa_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/  one_ui64toa_test (int,TYPE_1__*) ; 
 int /*<<< orphan*/ * p_ui64toa ; 
 TYPE_1__* ulonglong2str ; 

__attribute__((used)) static void test_ulonglongtoa(void)
{
    int test_num;

    for (test_num = 0; test_num < NB_ULONGLONG2STR; test_num++) {
	if (ulonglong2str[test_num].mask & 0x01) {
	    one_i64toa_test(test_num, &ulonglong2str[test_num]);
	} /* if */
        if (p_ui64toa != NULL) {
	    if (ulonglong2str[test_num].mask & 0x02) {
		one_ui64toa_test(test_num, &ulonglong2str[test_num]);
	    } /* if */
	} /* if */
    } /* for */
}