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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ thr_uid; scalar_t__ thr_discrim; scalar_t__ tctx_uid; } ;
typedef  TYPE_1__ prof_tctx_t ;

/* Variables and functions */

__attribute__((used)) static int
prof_tctx_comp(const prof_tctx_t *a, const prof_tctx_t *b) {
	uint64_t a_thr_uid = a->thr_uid;
	uint64_t b_thr_uid = b->thr_uid;
	int ret = (a_thr_uid > b_thr_uid) - (a_thr_uid < b_thr_uid);
	if (ret == 0) {
		uint64_t a_thr_discrim = a->thr_discrim;
		uint64_t b_thr_discrim = b->thr_discrim;
		ret = (a_thr_discrim > b_thr_discrim) - (a_thr_discrim <
		    b_thr_discrim);
		if (ret == 0) {
			uint64_t a_tctx_uid = a->tctx_uid;
			uint64_t b_tctx_uid = b->tctx_uid;
			ret = (a_tctx_uid > b_tctx_uid) - (a_tctx_uid <
			    b_tctx_uid);
		}
	}
	return ret;
}