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
typedef  int /*<<< orphan*/  IHTMLDOMNode ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDOMNode_get_nodeType (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * _get_node_iface (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static LONG _get_node_type(unsigned line, IUnknown *unk)
{
    IHTMLDOMNode *node = _get_node_iface(line, unk);
    LONG type = -1;
    HRESULT hres;

    hres = IHTMLDOMNode_get_nodeType(node, &type);
    ok(hres == S_OK, "get_nodeType failed: %08x\n", hres);

    IHTMLDOMNode_Release(node);

    return type;
}