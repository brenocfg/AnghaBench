#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {TYPE_2__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_22__ {TYPE_3__* resolved; } ;
typedef  TYPE_6__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_23__ {int /*<<< orphan*/ * value; TYPE_1__* addr; } ;
typedef  TYPE_7__ ngx_http_proxy_connect_address_t ;
struct TYPE_24__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_4__ name; } ;
typedef  TYPE_8__ ngx_addr_t ;
struct TYPE_19__ {int naddrs; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  host; int /*<<< orphan*/ * addrs; } ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ __ngx_parse_addr_port (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_http_complex_value (TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 TYPE_8__* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_set_address(ngx_http_request_t *r,
    ngx_http_proxy_connect_upstream_t *u, ngx_http_proxy_connect_address_t *address)
{
    ngx_int_t    rc;
    ngx_str_t    val;
    ngx_addr_t  *addr;

    if (address == NULL) {
        return NGX_DECLINED;
    }

    if (address->value == NULL) {

        u->resolved->naddrs = 1;
        u->resolved->addrs = NULL;
        u->resolved->sockaddr = address->addr->sockaddr;
        u->resolved->socklen = address->addr->socklen;
#if defined(nginx_version) && nginx_version >= 1011007
        u->resolved->name = address->addr->name;
#endif
        u->resolved->host = address->addr->name;

        return NGX_OK;
    }

    if (ngx_http_complex_value(r, address->value, &val) != NGX_OK) {
        return NGX_ERROR;
    }

    if (val.len == 0) {
        return NGX_DECLINED;
    }

    addr = ngx_palloc(r->pool, sizeof(ngx_addr_t));
    if (addr == NULL) {
        return NGX_ERROR;
    }

    rc = __ngx_parse_addr_port(r->pool, addr, val.data, val.len);
    if (rc == NGX_ERROR) {
        return NGX_ERROR;
    }

    if (rc != NGX_OK) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "invalid proxy connect address \"%V\"", &val);
        return NGX_DECLINED;
    }

    addr->name = val;
    u->resolved->sockaddr = addr->sockaddr;
    u->resolved->socklen = addr->socklen;
#if defined(nginx_version) && nginx_version >= 1011007
    u->resolved->name = addr->name;
#endif
    u->resolved->naddrs = 1;

    return NGX_OK;
}