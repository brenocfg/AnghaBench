#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ synctex_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYNCTEX_FREE (int /*<<< orphan*/ ) ; 
 scalar_t__ SYNCTEX_NAME (scalar_t__) ; 
 int /*<<< orphan*/  SYNCTEX_SIBLING (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void _synctex_free_input(synctex_node_t node){
	if (node) {
		SYNCTEX_FREE(SYNCTEX_SIBLING(node));
		free(SYNCTEX_NAME(node));
		free(node);
	}
}