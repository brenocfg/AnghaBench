#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* synctex_node_t ;
struct TYPE_9__ {TYPE_1__* class; } ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SYNCTEX_IS_BOX (TYPE_2__*) ; 
 TYPE_2__* SYNCTEX_PARENT (TYPE_2__*) ; 
 int SYNCTEX_WIDTH (TYPE_2__*) ; 
 scalar_t__ synctex_node_type_sheet ; 

int synctex_node_box_width(synctex_node_t node){
	if (!node) {
		return 0;
	}
	if (SYNCTEX_IS_BOX(node)) {
result:
		return SYNCTEX_WIDTH(node);
	}
	if ((node = SYNCTEX_PARENT(node)) && (node->class->type != synctex_node_type_sheet)) {
		goto result;
	}
	return 0;
}