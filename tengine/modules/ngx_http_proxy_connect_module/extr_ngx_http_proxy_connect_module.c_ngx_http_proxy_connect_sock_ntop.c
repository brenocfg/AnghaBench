#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__ host; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_2__ ngx_http_upstream_resolved_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_10__ {TYPE_2__* resolved; } ;
typedef  TYPE_4__ ngx_http_proxy_connect_upstream_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  __ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_sock_ntop(ngx_http_request_t *r,
    ngx_http_proxy_connect_upstream_t *u)
{
    u_char                          *p;
    ngx_int_t                        len;
    ngx_http_upstream_resolved_t    *ur;

    ur = u->resolved;

    /* fix u->resolved->host to "<address:port>" format */

    p = ngx_pnalloc(r->pool, NGX_SOCKADDR_STRLEN);
    if (p == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    len = __ngx_sock_ntop(ur->sockaddr, ur->socklen, p, NGX_SOCKADDR_STRLEN, 1);

    u->resolved->host.data = p;
    u->resolved->host.len = len;

    return NGX_OK;
}