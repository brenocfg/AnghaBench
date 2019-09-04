#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int member_2; int size; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ elem_vector_t ;
struct TYPE_11__ {int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  IHTMLElementCollection ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * HTMLElementCollection_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_all_list (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  elem_from_HTMLDOMNode (TYPE_2__*) ; 
 int /*<<< orphan*/  elem_vector_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elem_vector_normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 int /*<<< orphan*/  node_addref (TYPE_2__*) ; 

IHTMLElementCollection *create_all_collection(HTMLDOMNode *node, BOOL include_root)
{
    elem_vector_t buf = {NULL, 0, 8};

    buf.buf = heap_alloc(buf.size*sizeof(HTMLElement*));

    if(include_root) {
        node_addref(node);
        elem_vector_add(&buf, elem_from_HTMLDOMNode(node));
    }
    create_all_list(node->doc, node, &buf);
    elem_vector_normalize(&buf);

    return HTMLElementCollection_Create(buf.buf, buf.len);
}