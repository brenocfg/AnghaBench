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
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  VARLINK_ERROR_TIMEOUT ; 
 scalar_t__ VARLINK_PENDING_TIMEOUT ; 
 int /*<<< orphan*/  VARLINK_PROCESSING_TIMEOUT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_close (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_dispatch_local_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varlink_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int varlink_dispatch_timeout(Varlink *v) {
        assert(v);

        if (v->state != VARLINK_PENDING_TIMEOUT)
                return 0;

        varlink_set_state(v, VARLINK_PROCESSING_TIMEOUT);
        varlink_dispatch_local_error(v, VARLINK_ERROR_TIMEOUT);
        varlink_close(v);

        return 1;
}