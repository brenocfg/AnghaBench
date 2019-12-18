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
 int /*<<< orphan*/  SYNCTEX_CHILD (scalar_t__) ; 
 int /*<<< orphan*/  SYNCTEX_DISPLAY (int /*<<< orphan*/ ) ; 
 int SYNCTEX_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  SYNCTEX_SIBLING (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void _synctex_display_sheet(synctex_node_t sheet) {
	if (sheet) {
		printf("....{%i\n",SYNCTEX_PAGE(sheet));
		SYNCTEX_DISPLAY(SYNCTEX_CHILD(sheet));
		printf("....}\n");
		SYNCTEX_DISPLAY(SYNCTEX_SIBLING(sheet));
	}
}