#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* synctex_node_t ;
struct TYPE_12__ {TYPE_1__* class; } ;
struct TYPE_11__ {scalar_t__ type; } ;

/* Variables and functions */
 TYPE_2__* SYNCTEX_CHILD (TYPE_2__*) ; 
 TYPE_2__* SYNCTEX_PARENT (TYPE_2__*) ; 
 TYPE_2__* SYNCTEX_SIBLING (TYPE_2__*) ; 
 scalar_t__ synctex_node_type_sheet ; 

synctex_node_t synctex_node_next(synctex_node_t node) {
	if (SYNCTEX_CHILD(node)) {
		return SYNCTEX_CHILD(node);
	}
sibling:
	if (SYNCTEX_SIBLING(node)) {
		return SYNCTEX_SIBLING(node);
	}
	if ((node = SYNCTEX_PARENT(node))) {
		if (node->class->type == synctex_node_type_sheet) {/*  EXC_BAD_ACCESS? */
			return NULL;
		}
		goto sibling;
	}
	return NULL;
}