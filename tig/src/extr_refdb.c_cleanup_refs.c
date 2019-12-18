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
struct ref_opt {int /*<<< orphan*/  changed; } ;
struct ref {scalar_t__* id; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WATCH_REFS ; 

__attribute__((used)) static bool
cleanup_refs(void *data, void *ref_)
{
	struct ref_opt *opt = data;
	struct ref *ref = ref_;

	if (!ref->valid) {
		ref->id[0] = 0;
		opt->changed |= WATCH_REFS;
	}

	return true;
}