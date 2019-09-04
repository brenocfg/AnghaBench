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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLTextContainer ;
typedef  int /*<<< orphan*/  IHTMLElement2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IHTMLElement2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement2_get_scrollLeft (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IHTMLTextContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLTextContainer_get_scrollLeft (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IID_IHTMLTextContainer ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * _get_elem2_iface (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void _elem_get_scroll_left(unsigned line, IUnknown *unk)
{
    IHTMLElement2 *elem = _get_elem2_iface(line, unk);
    IHTMLTextContainer *txtcont;
    LONG l = -1, l2 = -1;
    HRESULT hres;

    hres = IHTMLElement2_get_scrollLeft(elem, NULL);
    ok(hres == E_INVALIDARG, "expect E_INVALIDARG got 0x%08x\n", hres);

    hres = IHTMLElement2_get_scrollLeft(elem, &l);
    ok(hres == S_OK, "get_scrollTop failed: %08x\n", hres);
    IHTMLElement2_Release(elem);

    hres = IUnknown_QueryInterface(unk, &IID_IHTMLTextContainer, (void**)&txtcont);
    ok(hres == S_OK, "Could not get IHTMLTextContainer: %08x\n", hres);

    hres = IHTMLTextContainer_get_scrollLeft(txtcont, &l2);
    IHTMLTextContainer_Release(txtcont);
    ok(hres == S_OK, "IHTMLTextContainer::get_scrollLeft failed: %d\n", l2);
    ok(l == l2, "unexpected left %d, expected %d\n", l2, l);
}