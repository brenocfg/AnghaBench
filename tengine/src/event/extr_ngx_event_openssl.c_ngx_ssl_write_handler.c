#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_6__ {TYPE_3__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_ssl_write_handler(ngx_event_t *wev)
{
    ngx_connection_t  *c;

    c = wev->data;

    ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL write handler");

    c->read->handler(c->read);
}