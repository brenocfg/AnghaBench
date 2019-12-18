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
 int /*<<< orphan*/  ok (int,char*,int) ; 
 size_t p_strnlen (char const*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_strnlen(void)
{
    static const char str[] = "string";
    size_t res;

    if(!p_strnlen) {
        win_skip("strnlen not found\n");
        return;
    }

    res = p_strnlen(str, 20);
    ok(res == 6, "Returned length = %d\n", (int)res);

    res = p_strnlen(str, 3);
    ok(res == 3, "Returned length = %d\n", (int)res);

    res = p_strnlen(NULL, 0);
    ok(res == 0, "Returned length = %d\n", (int)res);
}