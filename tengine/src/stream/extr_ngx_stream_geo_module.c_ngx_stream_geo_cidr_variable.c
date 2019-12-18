#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct in6_addr {int* s6_addr; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
typedef  int /*<<< orphan*/  ngx_stream_variable_value_t ;
struct TYPE_18__ {TYPE_5__* connection; } ;
typedef  TYPE_6__ ngx_stream_session_t ;
struct TYPE_15__ {int /*<<< orphan*/  tree; int /*<<< orphan*/  tree6; } ;
struct TYPE_16__ {TYPE_3__ trees; } ;
struct TYPE_19__ {TYPE_4__ u; } ;
typedef  TYPE_7__ ngx_stream_geo_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {TYPE_1__* sockaddr; } ;
typedef  TYPE_8__ ngx_addr_t ;
typedef  int in_addr_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
struct TYPE_13__ {int sa_family; } ;

/* Variables and functions */
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 int INADDR_NONE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_radix128tree_find (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ngx_radix32tree_find (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_stream_geo_addr (TYPE_6__*,TYPE_7__*,TYPE_8__*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_geo_cidr_variable(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    ngx_stream_geo_ctx_t *ctx = (ngx_stream_geo_ctx_t *) data;

    in_addr_t                     inaddr;
    ngx_addr_t                    addr;
    struct sockaddr_in           *sin;
    ngx_stream_variable_value_t  *vv;
#if (NGX_HAVE_INET6)
    u_char                       *p;
    struct in6_addr              *inaddr6;
#endif

    if (ngx_stream_geo_addr(s, ctx, &addr) != NGX_OK) {
        vv = (ngx_stream_variable_value_t *)
                  ngx_radix32tree_find(ctx->u.trees.tree, INADDR_NONE);
        goto done;
    }

    switch (addr.sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        inaddr6 = &((struct sockaddr_in6 *) addr.sockaddr)->sin6_addr;
        p = inaddr6->s6_addr;

        if (IN6_IS_ADDR_V4MAPPED(inaddr6)) {
            inaddr = p[12] << 24;
            inaddr += p[13] << 16;
            inaddr += p[14] << 8;
            inaddr += p[15];

            vv = (ngx_stream_variable_value_t *)
                      ngx_radix32tree_find(ctx->u.trees.tree, inaddr);

        } else {
            vv = (ngx_stream_variable_value_t *)
                      ngx_radix128tree_find(ctx->u.trees.tree6, p);
        }

        break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
    case AF_UNIX:
        vv = (ngx_stream_variable_value_t *)
                  ngx_radix32tree_find(ctx->u.trees.tree, INADDR_NONE);
        break;
#endif

    default: /* AF_INET */
        sin = (struct sockaddr_in *) addr.sockaddr;
        inaddr = ntohl(sin->sin_addr.s_addr);

        vv = (ngx_stream_variable_value_t *)
                  ngx_radix32tree_find(ctx->u.trees.tree, inaddr);

        break;
    }

done:

    *v = *vv;

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                   "stream geo: %v", v);

    return NGX_OK;
}