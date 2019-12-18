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
struct instance {struct context* ctx; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_deinit () ; 
 int /*<<< orphan*/  conn_init () ; 
 struct context* core_ctx_create (struct instance*) ; 
 int /*<<< orphan*/  mbuf_deinit () ; 
 int /*<<< orphan*/  mbuf_init (struct instance*) ; 
 int /*<<< orphan*/  msg_deinit () ; 
 int /*<<< orphan*/  msg_init () ; 

struct context *
core_start(struct instance *nci)
{
    struct context *ctx;

    mbuf_init(nci);
    msg_init();
    conn_init();

    ctx = core_ctx_create(nci);
    if (ctx != NULL) {
        nci->ctx = ctx;
        return ctx;
    }

    conn_deinit();
    msg_deinit();
    mbuf_deinit();

    return NULL;
}