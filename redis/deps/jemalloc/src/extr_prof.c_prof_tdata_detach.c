#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_5__ {int attached; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prof_tdata_destroy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int prof_tdata_should_destroy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  tsd_prof_tdata_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_tdata_detach(tsd_t *tsd, prof_tdata_t *tdata) {
	bool destroy_tdata;

	malloc_mutex_lock(tsd_tsdn(tsd), tdata->lock);
	if (tdata->attached) {
		destroy_tdata = prof_tdata_should_destroy(tsd_tsdn(tsd), tdata,
		    true);
		/*
		 * Only detach if !destroy_tdata, because detaching would allow
		 * another thread to win the race to destroy tdata.
		 */
		if (!destroy_tdata) {
			tdata->attached = false;
		}
		tsd_prof_tdata_set(tsd, NULL);
	} else {
		destroy_tdata = false;
	}
	malloc_mutex_unlock(tsd_tsdn(tsd), tdata->lock);
	if (destroy_tdata) {
		prof_tdata_destroy(tsd, tdata, true);
	}
}