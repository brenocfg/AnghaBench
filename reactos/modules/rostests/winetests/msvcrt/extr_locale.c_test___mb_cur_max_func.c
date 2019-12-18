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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int p___mb_cur_max_func () ; 
 int* p__p___mb_cur_max () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test___mb_cur_max_func(void)
{
    int mb_cur_max;

    setlocale(LC_ALL, "C");

    /* for newer Windows */
    if(!p___mb_cur_max_func)
        win_skip("Skipping ___mb_cur_max_func tests\n");
    else {
        mb_cur_max = p___mb_cur_max_func();
        ok(mb_cur_max == 1, "mb_cur_max = %d, expected 1\n", mb_cur_max);

        /* some old Windows don't set chinese */
        if (!setlocale(LC_ALL, "chinese"))
            win_skip("Skipping test with chinese locale\n");
        else {
            mb_cur_max = p___mb_cur_max_func();
            ok(mb_cur_max == 2, "mb_cur_max = %d, expected 2\n", mb_cur_max);
            setlocale(LC_ALL, "C");
        }
    }

    /* for older Windows */
    if (!p__p___mb_cur_max)
        skip("Skipping __p___mb_cur_max tests\n");
    else {
        mb_cur_max = *p__p___mb_cur_max();
        ok(mb_cur_max == 1, "mb_cur_max = %d, expected 1\n", mb_cur_max);

        /* some old Windows don't set chinese */
        if (!setlocale(LC_ALL, "chinese"))
            win_skip("Skipping test with chinese locale\n");
        else {
            mb_cur_max = *p__p___mb_cur_max();
            ok(mb_cur_max == 2, "mb_cur_max = %d, expected 2\n", mb_cur_max);
            setlocale(LC_ALL, "C");
        }
    }
}