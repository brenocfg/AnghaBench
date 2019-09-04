#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_4__ {int enq; int enq_idump; int enq_gdump; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bt2gctx_mtx ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_gdump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_idump (int /*<<< orphan*/ ) ; 
 TYPE_1__* prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_leave(tsd_t *tsd, prof_tdata_t *tdata) {
	cassert(config_prof);
	assert(tdata == prof_tdata_get(tsd, false));

	malloc_mutex_unlock(tsd_tsdn(tsd), &bt2gctx_mtx);

	if (tdata != NULL) {
		bool idump, gdump;

		assert(tdata->enq);
		tdata->enq = false;
		idump = tdata->enq_idump;
		tdata->enq_idump = false;
		gdump = tdata->enq_gdump;
		tdata->enq_gdump = false;

		if (idump) {
			prof_idump(tsd_tsdn(tsd));
		}
		if (gdump) {
			prof_gdump(tsd_tsdn(tsd));
		}
	}
}