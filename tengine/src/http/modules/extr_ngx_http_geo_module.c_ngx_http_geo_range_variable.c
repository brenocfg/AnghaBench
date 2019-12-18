#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct in6_addr {int* s6_addr; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_19__ {TYPE_5__* connection; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_20__ {int /*<<< orphan*/ * value; scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_7__ ngx_http_geo_range_t ;
struct TYPE_16__ {TYPE_7__** low; int /*<<< orphan*/ * default_value; } ;
struct TYPE_17__ {TYPE_3__ high; } ;
struct TYPE_21__ {TYPE_4__ u; } ;
typedef  TYPE_8__ ngx_http_geo_ctx_t ;
struct TYPE_22__ {TYPE_1__* sockaddr; } ;
typedef  TYPE_9__ ngx_addr_t ;
typedef  int in_addr_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;
struct TYPE_14__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 int INADDR_NONE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_geo_addr (TYPE_6__*,TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_geo_range_variable(ngx_http_request_t *r, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    ngx_http_geo_ctx_t *ctx = (ngx_http_geo_ctx_t *) data;

    in_addr_t              inaddr;
    ngx_addr_t             addr;
    ngx_uint_t             n;
    struct sockaddr_in    *sin;
    ngx_http_geo_range_t  *range;
#if (NGX_HAVE_INET6)
    u_char                *p;
    struct in6_addr       *inaddr6;
#endif

    *v = *ctx->u.high.default_value;

    if (ngx_http_geo_addr(r, ctx, &addr) == NGX_OK) {

        switch (addr.sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            inaddr6 = &((struct sockaddr_in6 *) addr.sockaddr)->sin6_addr;

            if (IN6_IS_ADDR_V4MAPPED(inaddr6)) {
                p = inaddr6->s6_addr;

                inaddr = p[12] << 24;
                inaddr += p[13] << 16;
                inaddr += p[14] << 8;
                inaddr += p[15];

            } else {
                inaddr = INADDR_NONE;
            }

            break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
        case AF_UNIX:
            inaddr = INADDR_NONE;
            break;
#endif

        default: /* AF_INET */
            sin = (struct sockaddr_in *) addr.sockaddr;
            inaddr = ntohl(sin->sin_addr.s_addr);
            break;
        }

    } else {
        inaddr = INADDR_NONE;
    }

    if (ctx->u.high.low) {
        range = ctx->u.high.low[inaddr >> 16];

        if (range) {
            n = inaddr & 0xffff;
            do {
                if (n >= (ngx_uint_t) range->start
                    && n <= (ngx_uint_t) range->end)
                {
                    *v = *range->value;
                    break;
                }
            } while ((++range)->value);
        }
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http geo: %v", v);

    return NGX_OK;
}