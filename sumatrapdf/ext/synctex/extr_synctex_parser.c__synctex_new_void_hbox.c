#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  synctex_void_box_node_t ;
typedef  TYPE_1__* synctex_scanner_t ;
typedef  TYPE_2__* synctex_node_t ;
typedef  scalar_t__ synctex_class_t ;
struct TYPE_7__ {scalar_t__ class; } ;
struct TYPE_6__ {scalar_t__ class; } ;

/* Variables and functions */
 TYPE_2__* _synctex_malloc (int) ; 
 int /*<<< orphan*/  synctex_class_void_hbox ; 
 scalar_t__ synctex_node_type_void_hbox ; 

synctex_node_t _synctex_new_void_hbox(synctex_scanner_t scanner) {
	synctex_node_t node = _synctex_malloc(sizeof(synctex_void_box_node_t));
	if (node) {
		node->class = scanner?scanner->class+synctex_node_type_void_hbox:(synctex_class_t)&synctex_class_void_hbox;
	}
	return node;
}