#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* synctex_node_t ;
struct TYPE_8__ {TYPE_2__* class; } ;
struct TYPE_7__ {TYPE_1__* scanner; } ;
struct TYPE_6__ {int unit; float x_offset; } ;

/* Variables and functions */
 int SYNCTEX_HORIZ (TYPE_3__*) ; 

float synctex_node_visible_h(synctex_node_t node){
	if (!node) {
		return 0;
	}
	return SYNCTEX_HORIZ(node)*node->class->scanner->unit+node->class->scanner->x_offset;
}