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
struct server_pool {int /*<<< orphan*/  ctx; struct conn* p_conn; } ;
struct conn {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ,struct conn*) ;} ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct conn*) ; 

rstatus_t
proxy_each_deinit(void *elem, void *data)
{
    struct server_pool *pool = elem;
    struct conn *p;

    p = pool->p_conn;
    if (p != NULL) {
        p->close(pool->ctx, p);
    }

    return NC_OK;
}