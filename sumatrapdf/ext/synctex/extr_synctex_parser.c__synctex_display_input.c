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
 int /*<<< orphan*/  SYNCTEX_DISPLAY (int /*<<< orphan*/ ) ; 
 char* SYNCTEX_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYNCTEX_SIBLING (int /*<<< orphan*/ ) ; 
 int SYNCTEX_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

void _synctex_display_input(synctex_node_t node) {
	printf("....Input:%i:%s\n",
		SYNCTEX_TAG(node),
		SYNCTEX_NAME(node));
	SYNCTEX_DISPLAY(SYNCTEX_SIBLING(node));
}