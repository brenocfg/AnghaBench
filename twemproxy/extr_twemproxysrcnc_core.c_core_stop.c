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
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_deinit () ; 
 int /*<<< orphan*/  core_ctx_destroy (struct context*) ; 
 int /*<<< orphan*/  mbuf_deinit () ; 
 int /*<<< orphan*/  msg_deinit () ; 

void
core_stop(struct context *ctx)
{
    conn_deinit();
    msg_deinit();
    mbuf_deinit();
    core_ctx_destroy(ctx);
}