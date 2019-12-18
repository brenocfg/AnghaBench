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
typedef  int UINT_PTR ;

/* Variables and functions */
 int _get_sbh_threshold () ; 
 int /*<<< orphan*/  _set_sbh_threshold (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static void test_sbheap(void)
{
    void *mem;
    int threshold;

    if(sizeof(void*) == 8) {
        ok(!_set_sbh_threshold(0), "_set_sbh_threshold succeeded\n");
        ok(!_set_sbh_threshold(1000), "_set_sbh_threshold succeeded\n");
        return;
    }

    mem = malloc(1);
    ok(mem != NULL, "malloc failed\n");

    ok(_set_sbh_threshold(1), "_set_sbh_threshold failed\n");
    threshold = _get_sbh_threshold();
    ok(threshold == 16, "threshold = %d\n", threshold);

    ok(_set_sbh_threshold(8), "_set_sbh_threshold failed\n");
    threshold = _get_sbh_threshold();
    ok(threshold == 16, "threshold = %d\n", threshold);

    ok(_set_sbh_threshold(1000), "_set_sbh_threshold failed\n");
    threshold = _get_sbh_threshold();
    ok(threshold == 1008, "threshold = %d\n", threshold);

    free(mem);

    mem = malloc(1);
    ok(mem != NULL, "malloc failed\n");
    ok(!((UINT_PTR)mem & 0xf), "incorrect alignment (%p)\n", mem);

    mem = realloc(mem, 10);
    ok(mem != NULL, "realloc failed\n");
    ok(!((UINT_PTR)mem & 0xf), "incorrect alignment (%p)\n", mem);

    ok(_set_sbh_threshold(0), "_set_sbh_threshold failed\n");
    threshold = _get_sbh_threshold();
    ok(threshold == 0, "threshold = %d\n", threshold);

    free(mem);
}