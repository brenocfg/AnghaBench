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
typedef  int /*<<< orphan*/  synctex_scanner_t ;
typedef  int /*<<< orphan*/ * synctex_node_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SYNCTEX_CUR ; 
 int /*<<< orphan*/ * SYNCTEX_END ; 
 int /*<<< orphan*/ * SYNCTEX_START ; 

synctex_node_t synctex_next_result(synctex_scanner_t scanner) {
	if (NULL == SYNCTEX_CUR) {
		SYNCTEX_CUR = SYNCTEX_START;
	} else {
		SYNCTEX_CUR+=sizeof(synctex_node_t);
	}
	if (SYNCTEX_CUR<SYNCTEX_END) {
		return *(synctex_node_t*)SYNCTEX_CUR;
	} else {
		return NULL;
	}
}