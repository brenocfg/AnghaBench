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
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int prof_tdata_should_destroy_unlocked (TYPE_1__*,int) ; 

__attribute__((used)) static bool
prof_tdata_should_destroy(tsdn_t *tsdn, prof_tdata_t *tdata,
    bool even_if_attached) {
	malloc_mutex_assert_owner(tsdn, tdata->lock);

	return prof_tdata_should_destroy_unlocked(tdata, even_if_attached);
}