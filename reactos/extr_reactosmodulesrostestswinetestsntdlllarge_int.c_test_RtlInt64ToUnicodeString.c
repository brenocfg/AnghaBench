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

/* Variables and functions */
 int NB_LARGEINT2STR ; 
 int /*<<< orphan*/ * largeint2str ; 
 int /*<<< orphan*/  one_RtlInt64ToUnicodeString_test (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_RtlInt64ToUnicodeString(void)
{
    int test_num;

    for (test_num = 0; test_num < NB_LARGEINT2STR; test_num++) {
	one_RtlInt64ToUnicodeString_test(test_num, &largeint2str[test_num]);
    } /* for */
}