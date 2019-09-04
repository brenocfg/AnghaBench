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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLRect ;
typedef  int /*<<< orphan*/  IHTMLElement2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLElement2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement2_getBoundingClientRect (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLRect_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLRect_get_bottom (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IHTMLRect_get_left (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IHTMLRect_get_right (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IHTMLRect_get_top (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IID_IHTMLRect ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * get_elem2_iface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_elem_bounding_client_rect(IUnknown *unk)
{
    IHTMLRect *rect, *rect2;
    IHTMLElement2 *elem2;
    LONG l;
    HRESULT hres;

    elem2 = get_elem2_iface(unk);
    hres = IHTMLElement2_getBoundingClientRect(elem2, &rect);
    ok(hres == S_OK, "getBoundingClientRect failed: %08x\n", hres);
    hres = IHTMLElement2_getBoundingClientRect(elem2, &rect2);
    IHTMLElement2_Release(elem2);
    ok(hres == S_OK, "getBoundingClientRect failed: %08x\n", hres);
    ok(rect != NULL, "rect == NULL\n");
    ok(rect != rect2, "rect == rect2\n");
    IHTMLRect_Release(rect2);

    test_disp((IUnknown*)rect, &IID_IHTMLRect, "[object]");

    l = 0xdeadbeef;
    hres = IHTMLRect_get_top(rect, &l);
    ok(hres == S_OK, "get_top failed: %08x\n", hres);
    ok(l != 0xdeadbeef, "l = 0xdeadbeef\n");

    l = 0xdeadbeef;
    hres = IHTMLRect_get_left(rect, &l);
    ok(hres == S_OK, "get_left failed: %08x\n", hres);
    ok(l != 0xdeadbeef, "l = 0xdeadbeef\n");

    l = 0xdeadbeef;
    hres = IHTMLRect_get_bottom(rect, &l);
    ok(hres == S_OK, "get_bottom failed: %08x\n", hres);
    ok(l != 0xdeadbeef, "l = 0xdeadbeef\n");

    l = 0xdeadbeef;
    hres = IHTMLRect_get_right(rect, &l);
    ok(hres == S_OK, "get_right failed: %08x\n", hres);
    ok(l != 0xdeadbeef, "l = 0xdeadbeef\n");

    IHTMLRect_Release(rect);
}