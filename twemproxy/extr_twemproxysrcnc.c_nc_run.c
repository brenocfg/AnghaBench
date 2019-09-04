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
struct instance {int dummy; } ;
struct context {int dummy; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 scalar_t__ core_loop (struct context*) ; 
 struct context* core_start (struct instance*) ; 
 int /*<<< orphan*/  core_stop (struct context*) ; 

__attribute__((used)) static void
nc_run(struct instance *nci)
{
    rstatus_t status;
    struct context *ctx;

    ctx = core_start(nci);
    if (ctx == NULL) {
        return;
    }

    /* run rabbit run */
    for (;;) {
        status = core_loop(ctx);
        if (status != NC_OK) {
            break;
        }
    }

    core_stop(ctx);
}