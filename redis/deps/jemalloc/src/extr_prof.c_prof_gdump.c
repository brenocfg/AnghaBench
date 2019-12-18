#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_3__ {int enq_gdump; scalar_t__ enq; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int DUMP_FILENAME_BUFSIZE ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* opt_prof_prefix ; 
 int /*<<< orphan*/  prof_active_get_unlocked () ; 
 int /*<<< orphan*/  prof_booted ; 
 int /*<<< orphan*/  prof_dump (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  prof_dump_filename (char*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_dump_seq_mtx ; 
 int /*<<< orphan*/  prof_dump_useq ; 
 TYPE_1__* prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 scalar_t__ tsdn_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsdn_tsd (int /*<<< orphan*/ *) ; 

void
prof_gdump(tsdn_t *tsdn) {
	tsd_t *tsd;
	prof_tdata_t *tdata;

	cassert(config_prof);

	if (!prof_booted || tsdn_null(tsdn) || !prof_active_get_unlocked()) {
		return;
	}
	tsd = tsdn_tsd(tsdn);
	if (tsd_reentrancy_level_get(tsd) > 0) {
		return;
	}

	tdata = prof_tdata_get(tsd, false);
	if (tdata == NULL) {
		return;
	}
	if (tdata->enq) {
		tdata->enq_gdump = true;
		return;
	}

	if (opt_prof_prefix[0] != '\0') {
		char filename[DUMP_FILENAME_BUFSIZE];
		malloc_mutex_lock(tsdn, &prof_dump_seq_mtx);
		prof_dump_filename(filename, 'u', prof_dump_useq);
		prof_dump_useq++;
		malloc_mutex_unlock(tsdn, &prof_dump_seq_mtx);
		prof_dump(tsd, false, filename, false);
	}
}