#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {scalar_t__ end; scalar_t__ start; } ;
typedef  TYPE_2__ ngx_http_geo_range_t ;
struct TYPE_8__ {scalar_t__* low; } ;
struct TYPE_10__ {TYPE_1__ high; } ;
typedef  TYPE_3__ ngx_http_geo_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_11__ {size_t nelts; TYPE_2__* elts; } ;
typedef  TYPE_4__ ngx_array_t ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_memmove (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static ngx_uint_t
ngx_http_geo_delete_range(ngx_conf_t *cf, ngx_http_geo_conf_ctx_t *ctx,
    in_addr_t start, in_addr_t end)
{
    in_addr_t              n;
    ngx_uint_t             h, i, s, e, warn;
    ngx_array_t           *a;
    ngx_http_geo_range_t  *range;

    warn = 0;

    for (n = start; n <= end; n = (n + 0x10000) & 0xffff0000) {

        h = n >> 16;

        if (n == start) {
            s = n & 0xffff;
        } else {
            s = 0;
        }

        if ((n | 0xffff) > end) {
            e = end & 0xffff;

        } else {
            e = 0xffff;
        }

        a = (ngx_array_t *) ctx->high.low[h];

        if (a == NULL || a->nelts == 0) {
            warn = 1;
            goto next;
        }

        range = a->elts;
        for (i = 0; i < a->nelts; i++) {

            if (s == (ngx_uint_t) range[i].start
                && e == (ngx_uint_t) range[i].end)
            {
                ngx_memmove(&range[i], &range[i + 1],
                            (a->nelts - 1 - i) * sizeof(ngx_http_geo_range_t));

                a->nelts--;

                break;
            }

            if (i == a->nelts - 1) {
                warn = 1;
            }
        }

    next:

        if (h == 0xffff) {
            break;
        }
    }

    return warn;
}