#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  SubtractRect (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_SubtractRect(void)
{
    RECT rect1;
    RECT rect2;
    RECT rectr;
    BOOL result;

    /* source rectangles don't intersect */
    SetRect(&rect1, 50, 50, 150, 100);
    SetRect(&rect2, 250, 200, 1500, 1000);
    result = SubtractRect(&rectr, &rect1, &rect2);
    ok(result, "SubtractRect returned FALSE but subtraction should not be empty\n");
    ok(result && rectr.left == 50 && rectr.top == 50 && rectr.right ==150
       && rectr.bottom == 100, "wrong rect subtraction of SubtractRect (dest rect=%s)\n",
       wine_dbgstr_rect(&rectr));

    /* source rect 2 partially overlaps rect 1 */
    SetRect(&rect1, 2431, 626, 3427, 1608);
    SetRect(&rect2, 2499, 626, 3427, 1608);
    result = SubtractRect(&rectr, &rect1, &rect2);
    ok(result, "SubtractRect returned FALSE but subtraction should not be empty\n");
    ok(result && rectr.left == 2431 && rectr.top == 626 && rectr.right == 2499
       && rectr.bottom == 1608, "wrong rect subtraction of SubtractRect (dest rect=%s)\n",
       wine_dbgstr_rect(&rectr));

    /* source rect 2 partially overlaps rect 1 - dest is src rect 2 */
    SetRect(&rect1, 2431, 626, 3427, 1608);
    SetRect(&rect2, 2499, 626, 3427, 1608);
    result = SubtractRect(&rect2, &rect1, &rect2);
    ok(result, "SubtractRect returned FALSE but subtraction should not be empty\n");
    ok(result && rectr.left == 2431 && rectr.top == 626 && rectr.right == 2499
       && rectr.bottom == 1608, "wrong rect subtraction of SubtractRect (dest rect=%s)\n",
       wine_dbgstr_rect(&rectr));

    /* source rect 2 completely overlaps rect 1 */
    SetRect(&rect1, 250, 250, 400, 500);
    SetRect(&rect2, 50, 50, 1500, 1000);
    result = SubtractRect(&rectr, &rect1, &rect2);
    ok(!result, "SubtractRect returned TRUE but subtraction should be empty (dest rect=%s)\n",
       wine_dbgstr_rect(&rectr));

    /* source rect 2 completely overlaps rect 1 - dest is src rect 2 */
    SetRect(&rect1, 250, 250, 400, 500);
    SetRect(&rect2, 50, 50, 1500, 1000);
    result = SubtractRect(&rect2, &rect1, &rect2);
    ok(!result, "SubtractRect returned TRUE but subtraction should be empty (dest rect=%s)\n",
       wine_dbgstr_rect(&rect2));
}