#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* synctex_node_t ;
struct TYPE_8__ {TYPE_1__* class; } ;
struct TYPE_7__ {scalar_t__ type; } ;

/* Variables and functions */
 TYPE_2__* SYNCTEX_PARENT (TYPE_2__*) ; 
 scalar_t__ synctex_node_type_sheet ; 

synctex_node_t synctex_node_sheet(synctex_node_t node)
{
	while(node && node->class->type != synctex_node_type_sheet) {
		node = SYNCTEX_PARENT(node);
	}
	/*  exit the while loop either when node is NULL or node is a sheet */
	return node;
}