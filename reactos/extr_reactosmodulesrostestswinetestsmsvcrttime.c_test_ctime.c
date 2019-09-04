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
typedef  int time_t ;

/* Variables and functions */
 char* ctime (int*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void test_ctime(void)
{
    time_t badtime = -1;
    char* ret;
    ret = ctime(&badtime);
    ok(ret == NULL, "expected ctime to return NULL, got %s\n", ret);
}