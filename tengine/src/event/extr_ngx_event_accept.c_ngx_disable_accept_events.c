#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {scalar_t__ reuseport; TYPE_4__* connection; } ;
typedef  TYPE_2__ ngx_listening_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {size_t nelts; TYPE_2__* elts; } ;
struct TYPE_10__ {TYPE_1__ listening; } ;
typedef  TYPE_3__ ngx_cycle_t ;
struct TYPE_11__ {TYPE_6__* read; scalar_t__ num_async_fds; scalar_t__ async_enable; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_12__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DISABLE_EVENT ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int /*<<< orphan*/  ngx_del_async_conn (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_del_event (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_disable_accept_events(ngx_cycle_t *cycle, ngx_uint_t all)
{
    ngx_uint_t         i;
    ngx_listening_t   *ls;
    ngx_connection_t  *c;

    ls = cycle->listening.elts;
    for (i = 0; i < cycle->listening.nelts; i++) {

        c = ls[i].connection;

        if (c == NULL || !c->read->active) {
            continue;
        }

#if (NGX_HAVE_REUSEPORT)

        /*
         * do not disable accept on worker's own sockets
         * when disabling accept events due to accept mutex
         */

        if (ls[i].reuseport && !all) {
            continue;
        }

#endif

#if (NGX_SSL && NGX_SSL_ASYNC)
        if (c->async_enable && ngx_del_async_conn) {
            if (c->num_async_fds) {
                ngx_del_async_conn(c, NGX_DISABLE_EVENT);
                c->num_async_fds--;
            }
        }
#endif
        if (ngx_del_event(c->read, NGX_READ_EVENT, NGX_DISABLE_EVENT)
            == NGX_ERROR)
        {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}