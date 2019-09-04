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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLDOMNode ;
typedef  int /*<<< orphan*/  IHTMLDOMChildrenCollection ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDOMChildrenCollection_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * _get_node_iface (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IHTMLDOMNode *_get_child_item(unsigned line, IHTMLDOMChildrenCollection *col, LONG idx)
{
    IHTMLDOMNode *node = NULL;
    IDispatch *disp;
    HRESULT hres;

    hres = IHTMLDOMChildrenCollection_item(col, idx, &disp);
    ok(hres == S_OK, "item failed: %08x\n", hres);

    node = _get_node_iface(line, (IUnknown*)disp);
    IDispatch_Release(disp);

    return node;
}