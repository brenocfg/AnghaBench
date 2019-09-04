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
typedef  int /*<<< orphan*/  tsd_t ;
struct prof_tdata_merge_iter_arg_s {int /*<<< orphan*/  cnt_all; } ;
struct prof_gctx_merge_iter_arg_s {int /*<<< orphan*/  leak_ngctx; } ;
struct prof_gctx_dump_iter_arg_s {int dummy; } ;
typedef  int /*<<< orphan*/  prof_tdata_t ;
typedef  int /*<<< orphan*/  prof_gctx_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_reentrancy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pre_reentrancy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int prof_dump_file (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ *,struct prof_tdata_merge_iter_arg_s*,struct prof_gctx_merge_iter_arg_s*,struct prof_gctx_dump_iter_arg_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_dump_mtx ; 
 int /*<<< orphan*/  prof_dump_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct prof_tdata_merge_iter_arg_s*,struct prof_gctx_merge_iter_arg_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_gctx_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_leakcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
prof_dump(tsd_t *tsd, bool propagate_err, const char *filename,
    bool leakcheck) {
	cassert(config_prof);
	assert(tsd_reentrancy_level_get(tsd) == 0);

	prof_tdata_t * tdata = prof_tdata_get(tsd, true);
	if (tdata == NULL) {
		return true;
	}

	pre_reentrancy(tsd, NULL);
	malloc_mutex_lock(tsd_tsdn(tsd), &prof_dump_mtx);

	prof_gctx_tree_t gctxs;
	struct prof_tdata_merge_iter_arg_s prof_tdata_merge_iter_arg;
	struct prof_gctx_merge_iter_arg_s prof_gctx_merge_iter_arg;
	struct prof_gctx_dump_iter_arg_s prof_gctx_dump_iter_arg;
	prof_dump_prep(tsd, tdata, &prof_tdata_merge_iter_arg,
	    &prof_gctx_merge_iter_arg, &gctxs);
	bool err = prof_dump_file(tsd, propagate_err, filename, leakcheck, tdata,
	    &prof_tdata_merge_iter_arg, &prof_gctx_merge_iter_arg,
	    &prof_gctx_dump_iter_arg, &gctxs);
	prof_gctx_finish(tsd, &gctxs);

	malloc_mutex_unlock(tsd_tsdn(tsd), &prof_dump_mtx);
	post_reentrancy(tsd);

	if (err) {
		return true;
	}

	if (leakcheck) {
		prof_leakcheck(&prof_tdata_merge_iter_arg.cnt_all,
		    prof_gctx_merge_iter_arg.leak_ngctx, filename);
	}
	return false;
}