#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ barriers; int /*<<< orphan*/  pipe; void* them; void* me; } ;
typedef  TYPE_1__ Barrier ;

/* Variables and functions */
 void* safe_close (void*) ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 

void barrier_destroy(Barrier *b) {
        if (!b)
                return;

        b->me = safe_close(b->me);
        b->them = safe_close(b->them);
        safe_close_pair(b->pipe);
        b->barriers = 0;
}