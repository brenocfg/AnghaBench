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
typedef  scalar_t__ synctex_status_t ;
typedef  int /*<<< orphan*/ * synctex_scanner_t ;

/* Variables and functions */
 char* SYNCTEX_CUR ; 
 char* SYNCTEX_END ; 
 scalar_t__ SYNCTEX_STATUS_BAD_ARGUMENT ; 
 scalar_t__ SYNCTEX_STATUS_OK ; 
 scalar_t__ _synctex_buffer_get_available_size (int /*<<< orphan*/ *,size_t*) ; 

synctex_status_t _synctex_next_line(synctex_scanner_t scanner) {
	synctex_status_t status = SYNCTEX_STATUS_OK;
	size_t available = 0;
	if (NULL == scanner) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
infinite_loop:
	while(SYNCTEX_CUR<SYNCTEX_END) {
		if (*SYNCTEX_CUR == '\n') {
			++SYNCTEX_CUR;
			available = 1;
			return _synctex_buffer_get_available_size(scanner, &available);
		}
		++SYNCTEX_CUR;
	}
	/*  Here, we have SYNCTEX_CUR == SYNCTEX_END, such that the next call to _synctex_buffer_get_available_size
	 *  will read another bunch of synctex file. Little by little, we advance to the end of the file. */
	available = 1;
	status = _synctex_buffer_get_available_size(scanner, &available);
	if (status<=0) {
		return status;
	}
	goto infinite_loop;
}