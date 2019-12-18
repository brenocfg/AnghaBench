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
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_gdump_mtx ; 
 int prof_gdump_val ; 

bool
prof_gdump_get(tsdn_t *tsdn) {
	bool prof_gdump_current;

	malloc_mutex_lock(tsdn, &prof_gdump_mtx);
	prof_gdump_current = prof_gdump_val;
	malloc_mutex_unlock(tsdn, &prof_gdump_mtx);
	return prof_gdump_current;
}