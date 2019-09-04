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
struct TYPE_3__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ xsltemplate ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  IXMLDOMNode_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xsltemplate_set_node( xsltemplate *This, IXMLDOMNode *node )
{
    if (This->node) IXMLDOMNode_Release(This->node);
    This->node = node;
    if (node) IXMLDOMNode_AddRef(node);
}