#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SetRect(void)
{
    RECT rect;
    BOOL ret;

    ret = SetRect(NULL, 0, 0, 0, 0);
    ok(!ret, "got %d\n", ret);

    ret = SetRect(&rect, 1, 2, 3, 4);
    ok(ret, "got %d\n", ret);
    ok(rect.left == 1 && rect.top == 2 && rect.right == 3 && rect.bottom == 4,
        "got wrong rectangle\n");

    ret = SetRect(&rect, 10, 10, 5, 5);
    ok(ret, "got %d\n", ret);
    ok(rect.left == 10 && rect.top == 10 && rect.right == 5 && rect.bottom == 5,
        "got wrong rectangle\n");
}