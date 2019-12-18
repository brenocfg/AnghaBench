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
typedef  int /*<<< orphan*/  RECT ;
typedef  int BOOL ;

/* Variables and functions */
 int EqualRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_EqualRect(void)
{
    RECT rect1, rect2;
    BOOL ret;

    SetRect(&rect1, 0, 0, 0, 0);
    SetRect(&rect2, 1, 1, 1, 1);

    ret = EqualRect(NULL, NULL);
    ok(!ret, "got %d\n", ret);

    ret = EqualRect(&rect1, NULL);
    ok(!ret, "got %d\n", ret);

    ret = EqualRect(NULL, &rect2);
    ok(!ret, "got %d\n", ret);

    ret = EqualRect(&rect1, &rect2);
    ok(!ret, "got %d\n", ret);

    SetRect(&rect1, 0, 0, 10, 10);
    SetRect(&rect2, 10, 10, 0, 0);

    ret = EqualRect(&rect1, &rect2);
    ok(!ret, "got %d\n", ret);

    ret = EqualRect(&rect1, &rect1);
    ok(ret, "got %d\n", ret);

    rect2 = rect1;
    ret = EqualRect(&rect1, &rect2);
    ok(ret, "got %d\n", ret);
}