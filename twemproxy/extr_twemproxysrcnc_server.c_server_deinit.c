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
typedef  scalar_t__ uint32_t ;
struct server {scalar_t__ ns_conn_q; int /*<<< orphan*/  s_conn_q; } ;
struct array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_deinit (struct array*) ; 
 scalar_t__ array_n (struct array*) ; 
 struct server* array_pop (struct array*) ; 

void
server_deinit(struct array *server)
{
    uint32_t i, nserver;

    for (i = 0, nserver = array_n(server); i < nserver; i++) {
        struct server *s;

        s = array_pop(server);
        ASSERT(TAILQ_EMPTY(&s->s_conn_q) && s->ns_conn_q == 0);
    }
    array_deinit(server);
}