#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  synctex_node_type_t ;
typedef  TYPE_2__* synctex_node_t ;
struct TYPE_5__ {TYPE_1__* class; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  synctex_node_type_error ; 

synctex_node_type_t synctex_node_type(synctex_node_t node) {
	if (node) {
		return (((node)->class))->type;
	}
	return synctex_node_type_error;
}