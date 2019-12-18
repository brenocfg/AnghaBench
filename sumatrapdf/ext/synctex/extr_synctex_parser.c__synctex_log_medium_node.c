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
 scalar_t__ SYNCTEX_CHILD (scalar_t__) ; 
 scalar_t__ SYNCTEX_FRIEND (scalar_t__) ; 
 int SYNCTEX_HORIZ (scalar_t__) ; 
 int SYNCTEX_LINE (scalar_t__) ; 
 scalar_t__ SYNCTEX_PARENT (scalar_t__) ; 
 scalar_t__ SYNCTEX_SIBLING (scalar_t__) ; 
 int SYNCTEX_TAG (scalar_t__) ; 
 int SYNCTEX_VERT (scalar_t__) ; 
 int SYNCTEX_WIDTH (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,void*,...) ; 
 char* synctex_node_isa (scalar_t__) ; 

void _synctex_log_medium_node(synctex_node_t node) {
	printf("%s:%i,%i:%i,%i:%i\n",
		synctex_node_isa(node),
		SYNCTEX_TAG(node),
		SYNCTEX_LINE(node),
		SYNCTEX_HORIZ(node),
		SYNCTEX_VERT(node),
		SYNCTEX_WIDTH(node));
	printf("SELF:%p",(void *)node);
	printf(" SYNCTEX_PARENT:%p",(void *)SYNCTEX_PARENT(node));
	printf(" SYNCTEX_CHILD:%p",(void *)SYNCTEX_CHILD(node));
	printf(" SYNCTEX_SIBLING:%p",(void *)SYNCTEX_SIBLING(node));
	printf(" SYNCTEX_FRIEND:%p\n",(void *)SYNCTEX_FRIEND(node));
}