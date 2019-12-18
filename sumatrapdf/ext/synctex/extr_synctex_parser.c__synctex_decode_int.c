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
 size_t SYNCTEX_BUFFER_MIN_SIZE ; 
 char* SYNCTEX_CUR ; 
 scalar_t__ SYNCTEX_STATUS_BAD_ARGUMENT ; 
 scalar_t__ SYNCTEX_STATUS_EOF ; 
 scalar_t__ SYNCTEX_STATUS_NOT_OK ; 
 scalar_t__ SYNCTEX_STATUS_OK ; 
 scalar_t__ _synctex_buffer_get_available_size (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

synctex_status_t _synctex_decode_int(synctex_scanner_t scanner, int* value_ref) {
	char * ptr = NULL;
	char * end = NULL;
	int result = 0;
	size_t available = 0;
	synctex_status_t status = 0;
	if (NULL == scanner) {
		 return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	available = SYNCTEX_BUFFER_MIN_SIZE;
	status = _synctex_buffer_get_available_size(scanner, &available);
	if (status<SYNCTEX_STATUS_EOF) {
		return status;/*  Forward error. */
	}
	if (available==0) {
		return SYNCTEX_STATUS_EOF;/*  it is the end of file. */
	}
	ptr = SYNCTEX_CUR;
	if (*ptr==':' || *ptr==',') {
		++ptr;
		--available;
		if (available==0) {
			return SYNCTEX_STATUS_NOT_OK;/*  It is not possible to scan an int */
		}
	}
	result = (int)strtol(ptr, &end, 10);
	if (end>ptr) {
		SYNCTEX_CUR = end;
		if (value_ref) {
			* value_ref = result;
		}
		return SYNCTEX_STATUS_OK;/*  Successfully scanned an int */
	}	
	return SYNCTEX_STATUS_NOT_OK;/*  Could not scan an int */
}