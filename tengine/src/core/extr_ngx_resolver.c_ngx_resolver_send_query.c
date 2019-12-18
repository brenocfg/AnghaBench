#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct TYPE_12__ {TYPE_5__* elts; } ;
struct TYPE_14__ {TYPE_2__* log; TYPE_1__ connections; } ;
typedef  TYPE_3__ ngx_resolver_t ;
struct TYPE_15__ {size_t last_connection; scalar_t__ naddrs; scalar_t__ naddrs6; int /*<<< orphan*/  qlen; int /*<<< orphan*/  query6; scalar_t__ tcp6; int /*<<< orphan*/  query; scalar_t__ tcp; } ;
typedef  TYPE_4__ ngx_resolver_node_t ;
struct TYPE_13__ {char* action; TYPE_5__* data; int /*<<< orphan*/ * handler; } ;
struct TYPE_16__ {TYPE_2__ log; } ;
typedef  TYPE_5__ ngx_resolver_connection_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_resolver_log_error ; 
 scalar_t__ ngx_resolver_send_tcp_query (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_resolver_send_udp_query (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_resolver_send_query(ngx_resolver_t *r, ngx_resolver_node_t *rn)
{
    ngx_int_t                   rc;
    ngx_resolver_connection_t  *rec;

    rec = r->connections.elts;
    rec = &rec[rn->last_connection];

    if (rec->log.handler == NULL) {
        rec->log = *r->log;
        rec->log.handler = ngx_resolver_log_error;
        rec->log.data = rec;
        rec->log.action = "resolving";
    }

    if (rn->naddrs == (u_short) -1) {
        rc = rn->tcp ? ngx_resolver_send_tcp_query(r, rec, rn->query, rn->qlen)
                     : ngx_resolver_send_udp_query(r, rec, rn->query, rn->qlen);

        if (rc != NGX_OK) {
            return rc;
        }
    }

#if (NGX_HAVE_INET6)

    if (rn->query6 && rn->naddrs6 == (u_short) -1) {
        rc = rn->tcp6
                    ? ngx_resolver_send_tcp_query(r, rec, rn->query6, rn->qlen)
                    : ngx_resolver_send_udp_query(r, rec, rn->query6, rn->qlen);

        if (rc != NGX_OK) {
            return rc;
        }
    }

#endif

    return NGX_OK;
}