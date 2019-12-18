#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_resolver_t ;
struct TYPE_8__ {TYPE_4__* udp; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_resolver_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {TYPE_1__* read; TYPE_2__* data; } ;
struct TYPE_7__ {int resolver; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_resolver_udp_read ; 
 scalar_t__ ngx_send (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ngx_udp_connect (TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_resolver_send_udp_query(ngx_resolver_t *r, ngx_resolver_connection_t  *rec,
    u_char *query, u_short qlen)
{
    ssize_t  n;

    if (rec->udp == NULL) {
        if (ngx_udp_connect(rec) != NGX_OK) {
            return NGX_ERROR;
        }

        rec->udp->data = rec;
        rec->udp->read->handler = ngx_resolver_udp_read;
        rec->udp->read->resolver = 1;
    }

    n = ngx_send(rec->udp, query, qlen);

    if (n == NGX_ERROR) {
        goto failed;
    }

    if ((size_t) n != (size_t) qlen) {
        ngx_log_error(NGX_LOG_CRIT, &rec->log, 0, "send() incomplete");
        goto failed;
    }

    return NGX_OK;

failed:

    ngx_close_connection(rec->udp);
    rec->udp = NULL;

    return NGX_ERROR;
}