#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  description; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_clear (TYPE_1__*) ; 

__attribute__((used)) static Varlink* varlink_destroy(Varlink *v) {
        if (!v)
                return NULL;

        /* If this is called the server object must already been unreffed here. Why that? because when we
         * linked up the varlink connection with the server object we took one ref in each direction */
        assert(!v->server);

        varlink_clear(v);

        free(v->description);
        return mfree(v);
}