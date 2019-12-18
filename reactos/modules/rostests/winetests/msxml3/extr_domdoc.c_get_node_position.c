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
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IXMLDOMNode_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMNode_get_previousSibling (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int get_node_position(IXMLDOMNode *node)
{
    HRESULT r;
    int pos = 0;

    IXMLDOMNode_AddRef(node);
    do
    {
        IXMLDOMNode *new_node;

        pos++;
        r = IXMLDOMNode_get_previousSibling(node, &new_node);
        ok(SUCCEEDED(r), "get_previousSibling failed\n");
        IXMLDOMNode_Release(node);
        node = new_node;
    } while (r == S_OK);
    return pos;
}