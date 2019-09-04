#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xform ;
struct TYPE_11__ {float member_0; float member_1; float member_2; float member_3; float member_4; float member_5; } ;
typedef  TYPE_1__ XFORM ;
struct TYPE_13__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_12__ {scalar_t__ left; scalar_t__ top; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ GM_COMPATIBLE ; 
 int GetClipBox (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ GetGraphicsMode (int /*<<< orphan*/ ) ; 
 int GetViewportOrgEx (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int GetWindowOrgEx (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int GetWorldTransform (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_buffer_dc_props(HDC hdc, const RECT *rect)
{
    static const XFORM ident = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
    XFORM xform;
    POINT org;
    RECT box;
    BOOL ret;

    ret = GetWorldTransform(hdc, &xform);
    ok(ret, "Failed to get world transform\n");
    ok(!memcmp(&xform, &ident, sizeof(xform)), "Unexpected world transform\n");

    ret = GetViewportOrgEx(hdc, &org);
    ok(ret, "Failed to get vport origin\n");
    ok(org.x == 0 && org.y == 0, "Unexpected vport origin\n");

    ret = GetWindowOrgEx(hdc, &org);
    ok(ret, "Failed to get vport origin\n");
    ok(org.x == rect->left && org.y == rect->top, "Unexpected window origin\n");

    ret = GetClipBox(hdc, &box);
    ok(ret, "Failed to get clip box\n");
    ok(box.left == rect->left && box.top == rect->top, "Unexpected clip box\n");

    ok(GetGraphicsMode(hdc) == GM_COMPATIBLE, "wrong graphics mode\n");
}