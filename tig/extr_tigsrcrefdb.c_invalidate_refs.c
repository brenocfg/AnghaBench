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
struct ref {int /*<<< orphan*/ * next; scalar_t__ valid; } ;

/* Variables and functions */

__attribute__((used)) static bool
invalidate_refs(void *data, void *ref_)
{
	struct ref *ref = ref_;

	ref->valid = 0;
	ref->next = NULL;
	return true;
}