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
struct test_async_object {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct test_async_object*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct test_async_object* mfree (struct test_async_object*) ; 

__attribute__((used)) static struct test_async_object *test_async_object_free(struct test_async_object *t) {
        assert(t);

        free(t->ifname);
        return mfree(t);
}