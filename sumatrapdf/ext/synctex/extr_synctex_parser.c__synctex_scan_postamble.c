#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* synctex_scanner_t ;
typedef  int /*<<< orphan*/  synctex_decoder_t ;
struct TYPE_7__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int SYNCTEX_STATUS_BAD_ARGUMENT ; 
 int SYNCTEX_STATUS_EOF ; 
 int SYNCTEX_STATUS_OK ; 
 int /*<<< orphan*/  _synctex_decode_int ; 
 int _synctex_match_string (TYPE_1__*,char*) ; 
 int _synctex_next_line (TYPE_1__*) ; 
 int _synctex_scan_named (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _synctex_scan_post_scriptum (TYPE_1__*) ; 

int _synctex_scan_postamble(synctex_scanner_t scanner) {
	int status = 0;
	if (NULL == scanner) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	status = _synctex_match_string(scanner,"Postamble:");
	if (status < SYNCTEX_STATUS_OK) {
		return status;
	}
count_again:
	status = _synctex_next_line(scanner);
	if (status < SYNCTEX_STATUS_OK) {
		return status;
	}
	status = _synctex_scan_named(scanner,"Count:",&(scanner->count),(synctex_decoder_t)&_synctex_decode_int);
	if (status < SYNCTEX_STATUS_EOF) {
		return status; /*  forward the error */
	} else if (status < SYNCTEX_STATUS_OK) { /*  No Count record found */
		status = _synctex_next_line(scanner); /*  Advance one more line */
		if (status<SYNCTEX_STATUS_OK) {
			return status;
		}
		goto count_again;
	}
	/*  Now we scan the last part of the SyncTeX file: the Post Scriptum section. */
	return _synctex_scan_post_scriptum(scanner);
}