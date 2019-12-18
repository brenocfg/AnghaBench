#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* synctex_node_t ;
struct TYPE_11__ {TYPE_2__* class; } ;
struct TYPE_10__ {int type; TYPE_1__* scanner; } ;
struct TYPE_9__ {float unit; } ;

/* Variables and functions */
 TYPE_3__* SYNCTEX_PARENT (TYPE_3__*) ; 
 float SYNCTEX_WIDTH (TYPE_3__*) ; 
 float SYNCTEX_WIDTH_V (TYPE_3__*) ; 
#define  synctex_node_type_hbox 131 
 int synctex_node_type_sheet ; 
#define  synctex_node_type_vbox 130 
#define  synctex_node_type_void_hbox 129 
#define  synctex_node_type_void_vbox 128 

float synctex_node_box_visible_width(synctex_node_t node){
	if (!node) {
		return 0;
	}
	switch(node->class->type) {
		case synctex_node_type_vbox:
		case synctex_node_type_void_vbox:
		case synctex_node_type_void_hbox:
			return SYNCTEX_WIDTH(node)*node->class->scanner->unit;
		case synctex_node_type_hbox:
result:
			return SYNCTEX_WIDTH_V(node)*node->class->scanner->unit;
	}
	if ((node = SYNCTEX_PARENT(node)) && (node->class->type != synctex_node_type_sheet)) {
		goto result;
	}
	return 0;
}