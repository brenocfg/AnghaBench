#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int value; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int NB_STR2LONG ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int patol (int /*<<< orphan*/ ) ; 
 TYPE_1__* str2long ; 

__attribute__((used)) static void test_atol(void)
{
    int test_num;
    int result;

    for (test_num = 0; test_num < NB_STR2LONG; test_num++) {
        result = patol(str2long[test_num].str);
        ok(result == str2long[test_num].value,
           "(test %d): call failed: _atol(\"%s\") has result %d, expected: %d\n",
           test_num, str2long[test_num].str, result, str2long[test_num].value);
    }
}