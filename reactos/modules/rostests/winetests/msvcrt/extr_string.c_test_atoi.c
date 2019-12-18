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
 int atoi (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_atoi(void)
{
    int r;

    r = atoi("0");
    ok(r == 0, "atoi(0) = %d\n", r);

    r = atoi("-1");
    ok(r == -1, "atoi(-1) = %d\n", r);

    r = atoi("1");
    ok(r == 1, "atoi(1) = %d\n", r);

    r = atoi("4294967296");
    ok(r == 0, "atoi(4294967296) = %d\n", r);
}