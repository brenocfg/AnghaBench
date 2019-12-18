#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* connection; } ;
typedef  TYPE_2__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_stream_phase_handler_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;scalar_t__ tcp_nodelay; } ;
typedef  TYPE_3__ ngx_stream_core_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {scalar_t__ type; TYPE_1__* log; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_11__ {int /*<<< orphan*/ * action; } ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 int /*<<< orphan*/  ngx_stream_finalize_session (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_stream_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_tcp_nodelay (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

ngx_int_t
ngx_stream_core_content_phase(ngx_stream_session_t *s,
    ngx_stream_phase_handler_t *ph)
{
    ngx_connection_t            *c;
    ngx_stream_core_srv_conf_t  *cscf;

    c = s->connection;

    c->log->action = NULL;

    cscf = ngx_stream_get_module_srv_conf(s, ngx_stream_core_module);

    if (c->type == SOCK_STREAM
        && cscf->tcp_nodelay
        && ngx_tcp_nodelay(c) != NGX_OK)
    {
        ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR);
        return NGX_OK;
    }

    cscf->handler(s);

    return NGX_OK;
}