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
typedef  char wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ok (int,char*,char) ; 
 int p__wcsnset_s (char*,int,char,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__wcsnset_s(void)
{
    wchar_t text[] = { 't','e','x','t',0 };
    int r;

    if(!p__wcsnset_s) {
        win_skip("_wcsnset_s not available\n");
        return;
    }

    r = p__wcsnset_s(NULL, 0, 'a', 0);
    ok(r == 0, "r = %d\n", r);

    r = p__wcsnset_s(text, 0, 'a', 1);
    ok(r == EINVAL, "r = %d\n", r);
    ok(text[0] == 't', "text[0] = %d\n", text[0]);

    r = p__wcsnset_s(NULL, 2, 'a', 1);
    ok(r == EINVAL, "r = %d\n", r);

    r = p__wcsnset_s(text, 2, 'a', 3);
    ok(r == EINVAL, "r = %d\n", r);
    ok(text[0] == 0, "text[0] = %d\n", text[0]);
    ok(text[1] == 'e', "text[1] = %d\n", text[1]);

    text[0] = 't';
    r = p__wcsnset_s(text, 5, 'a', 1);
    ok(r == 0, "r = %d\n", r);
    ok(text[0] == 'a', "text[0] = %d\n", text[0]);
    ok(text[1] == 'e', "text[1] = %d\n", text[1]);

    text[1] = 0;
    r = p__wcsnset_s(text, 5, 'b', 3);
    ok(r == 0, "r = %d\n", r);
    ok(text[0] == 'b', "text[0] = %d\n", text[0]);
    ok(text[1] == 0, "text[1] = %d\n", text[1]);
    ok(text[2] == 'x', "text[2] = %d\n", text[2]);
}