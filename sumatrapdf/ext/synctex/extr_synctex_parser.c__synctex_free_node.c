#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* synctex_node_t ;
struct TYPE_10__ {TYPE_1__* class; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* sibling ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SYNCTEX_CHILD (TYPE_2__*) ; 
 int /*<<< orphan*/  SYNCTEX_FREE (int /*<<< orphan*/ ) ; 
 TYPE_2__* SYNCTEX_SIBLING (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void _synctex_free_node(synctex_node_t node) {
	/* SumatraPDF: prevent stack overflow */
	synctex_node_t next;
	while (node) {
		(*((node->class)->sibling))(node);
		next = SYNCTEX_SIBLING(node);
		SYNCTEX_FREE(SYNCTEX_CHILD(node));
		free(node);
		node = next;
	}
	return;
}