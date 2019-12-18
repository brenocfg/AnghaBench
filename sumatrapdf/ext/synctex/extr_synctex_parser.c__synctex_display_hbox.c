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
typedef  int /*<<< orphan*/  synctex_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYNCTEX_CHILD (int /*<<< orphan*/ ) ; 
 int SYNCTEX_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNCTEX_DISPLAY (int /*<<< orphan*/ ) ; 
 int SYNCTEX_HEIGHT (int /*<<< orphan*/ ) ; 
 int SYNCTEX_HORIZ (int /*<<< orphan*/ ) ; 
 int SYNCTEX_LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNCTEX_SIBLING (int /*<<< orphan*/ ) ; 
 int SYNCTEX_TAG (int /*<<< orphan*/ ) ; 
 int SYNCTEX_VERT (int /*<<< orphan*/ ) ; 
 int SYNCTEX_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void _synctex_display_hbox(synctex_node_t node) {
	printf("....(%i,%i:%i,%i:%i,%i,%i\n",
		SYNCTEX_TAG(node),
		SYNCTEX_LINE(node),
		SYNCTEX_HORIZ(node),
		SYNCTEX_VERT(node),
		SYNCTEX_WIDTH(node),
		SYNCTEX_HEIGHT(node),
		SYNCTEX_DEPTH(node));
	SYNCTEX_DISPLAY(SYNCTEX_CHILD(node));
	printf("....)\n");
	SYNCTEX_DISPLAY(SYNCTEX_SIBLING(node));
}