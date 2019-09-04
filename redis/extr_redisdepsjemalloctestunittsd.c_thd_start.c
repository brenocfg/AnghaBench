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

/* Variables and functions */
 int MALLOC_TSD_TEST_DATA_INIT ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  assert_x_eq (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  data_cleanup ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/ * tsd_fetch () ; 
 int /*<<< orphan*/  tsd_test_callback_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_test_data_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_test_data_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *
thd_start(void *arg) {
	int d = (int)(uintptr_t)arg;
	void *p;

	tsd_t *tsd = tsd_fetch();
	assert_x_eq(tsd_test_data_get(tsd), MALLOC_TSD_TEST_DATA_INIT,
	    "Initial tsd get should return initialization value");

	p = malloc(1);
	assert_ptr_not_null(p, "Unexpected malloc() failure");

	tsd_test_data_set(tsd, d);
	assert_x_eq(tsd_test_data_get(tsd), d,
	    "After tsd set, tsd get should return value that was set");

	d = 0;
	assert_x_eq(tsd_test_data_get(tsd), (int)(uintptr_t)arg,
	    "Resetting local data should have no effect on tsd");

	tsd_test_callback_set(tsd, &data_cleanup);

	free(p);
	return NULL;
}