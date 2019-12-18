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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 unsigned int PROF_NCTX_LOCKS ; 
 unsigned int PROF_NTDATA_LOCKS ; 
 int /*<<< orphan*/  bt2gctx_mtx ; 
 scalar_t__ config_prof ; 
 int /*<<< orphan*/ * gctx_locks ; 
 int /*<<< orphan*/  malloc_mutex_postfork_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_thr_uid_mtx ; 
 scalar_t__ opt_prof ; 
 int /*<<< orphan*/  prof_active_mtx ; 
 int /*<<< orphan*/  prof_dump_mtx ; 
 int /*<<< orphan*/  prof_dump_seq_mtx ; 
 int /*<<< orphan*/  prof_gdump_mtx ; 
 int /*<<< orphan*/  prof_thread_active_init_mtx ; 
 int /*<<< orphan*/ * tdata_locks ; 
 int /*<<< orphan*/  tdatas_mtx ; 

void
prof_postfork_child(tsdn_t *tsdn) {
	if (config_prof && opt_prof) {
		unsigned i;

		malloc_mutex_postfork_child(tsdn, &prof_thread_active_init_mtx);
		malloc_mutex_postfork_child(tsdn, &next_thr_uid_mtx);
		malloc_mutex_postfork_child(tsdn, &prof_gdump_mtx);
		malloc_mutex_postfork_child(tsdn, &prof_dump_seq_mtx);
		malloc_mutex_postfork_child(tsdn, &prof_active_mtx);
		for (i = 0; i < PROF_NCTX_LOCKS; i++) {
			malloc_mutex_postfork_child(tsdn, &gctx_locks[i]);
		}
		for (i = 0; i < PROF_NTDATA_LOCKS; i++) {
			malloc_mutex_postfork_child(tsdn, &tdata_locks[i]);
		}
		malloc_mutex_postfork_child(tsdn, &tdatas_mtx);
		malloc_mutex_postfork_child(tsdn, &bt2gctx_mtx);
		malloc_mutex_postfork_child(tsdn, &prof_dump_mtx);
	}
}