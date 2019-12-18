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
 int SYNCTEX_PAGE (scalar_t__) ; 
 scalar_t__ SYNCTEX_PARENT (scalar_t__) ; 
 scalar_t__ SYNCTEX_SIBLING (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,void*,...) ; 
 char* synctex_node_isa (scalar_t__) ; 

void _synctex_log_sheet(synctex_node_t sheet) {
	if (sheet) {
		printf("%s:%i\n",synctex_node_isa(sheet),SYNCTEX_PAGE(sheet));
		printf("SELF:%p",(void *)sheet);
		printf(" SYNCTEX_PARENT:%p",(void *)SYNCTEX_PARENT(sheet));
		printf(" SYNCTEX_CHILD:%p",(void *)SYNCTEX_CHILD(sheet));
		printf(" SYNCTEX_SIBLING:%p",(void *)SYNCTEX_SIBLING(sheet));
		printf(" SYNCTEX_FRIEND:%p\n",(void *)SYNCTEX_FRIEND(sheet));
	}
}