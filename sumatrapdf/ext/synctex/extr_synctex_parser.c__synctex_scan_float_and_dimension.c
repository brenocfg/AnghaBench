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
 int /*<<< orphan*/  LC_NUMERIC ; 
 size_t SYNCTEX_BUFFER_MIN_SIZE ; 
 char* SYNCTEX_CUR ; 
 scalar_t__ SYNCTEX_STATUS_BAD_ARGUMENT ; 
 scalar_t__ SYNCTEX_STATUS_EOF ; 
 scalar_t__ SYNCTEX_STATUS_ERROR ; 
 scalar_t__ SYNCTEX_STATUS_OK ; 
 scalar_t__ _synctex_buffer_get_available_size (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  _synctex_error (char*) ; 
 scalar_t__ _synctex_match_string (int /*<<< orphan*/ *,char*) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 float strtod (char*,char**) ; 

synctex_status_t _synctex_scan_float_and_dimension(synctex_scanner_t scanner, float * value_ref) {
	synctex_status_t status = 0;
	char * endptr = NULL;
	float f = 0;
#ifdef HAVE_SETLOCALE
	char * loc = setlocale(LC_NUMERIC, NULL);
#endif
	size_t available = 0;
	if (NULL == scanner || NULL == value_ref) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	available = SYNCTEX_BUFFER_MIN_SIZE;
	status = _synctex_buffer_get_available_size(scanner, &available);
	if (status<SYNCTEX_STATUS_EOF) {
		_synctex_error("problem with float.");
		return status;
	}
#ifdef HAVE_SETLOCALE
	setlocale(LC_NUMERIC, "C");
#endif
	f = strtod(SYNCTEX_CUR,&endptr);
#ifdef HAVE_SETLOCALE
	setlocale(LC_NUMERIC, loc);
#endif
	if (endptr == SYNCTEX_CUR) {
		_synctex_error("a float was expected.");
		return SYNCTEX_STATUS_ERROR;
	}
	SYNCTEX_CUR = endptr;
	if ((status = _synctex_match_string(scanner,"in")) >= SYNCTEX_STATUS_OK) {
		f *= 72.27f*65536;
	} else if (status<SYNCTEX_STATUS_EOF) {
report_unit_error:
		_synctex_error("problem with unit.");
		return status;
	} else if ((status = _synctex_match_string(scanner,"cm")) >= SYNCTEX_STATUS_OK) {
		f *= 72.27f*65536/2.54f;
	} else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"mm")) >= SYNCTEX_STATUS_OK) {
		f *= 72.27f*65536/25.4f;
	} else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"pt")) >= SYNCTEX_STATUS_OK) {
		f *= 65536.0f;
	} else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"bp")) >= SYNCTEX_STATUS_OK) {
		f *= 72.27f/72*65536.0f;
	}  else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"pc")) >= SYNCTEX_STATUS_OK) {
		f *= 12.0*65536.0f;
	}  else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"sp")) >= SYNCTEX_STATUS_OK) {
		f *= 1.0f;
	}  else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"dd")) >= SYNCTEX_STATUS_OK) {
		f *= 1238.0f/1157*65536.0f;
	}  else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"cc")) >= SYNCTEX_STATUS_OK) {
		f *= 14856.0f/1157*65536;
	} else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"nd")) >= SYNCTEX_STATUS_OK) {
		f *= 685.0f/642*65536;
	}  else if (status<0) {
		goto report_unit_error;
	} else if ((status = _synctex_match_string(scanner,"nc")) >= SYNCTEX_STATUS_OK) {
		f *= 1370.0f/107*65536;
	} else if (status<0) {
		goto report_unit_error;
	}
	*value_ref = f;
	return SYNCTEX_STATUS_OK;
}