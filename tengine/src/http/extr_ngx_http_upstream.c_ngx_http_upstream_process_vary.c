#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_12__ {int len; char* data; } ;
struct TYPE_14__ {TYPE_3__ value; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_5__* vary; } ;
struct TYPE_15__ {scalar_t__ cacheable; TYPE_1__* conf; TYPE_4__ headers_in; } ;
typedef  TYPE_6__ ngx_http_upstream_t ;
struct TYPE_16__ {TYPE_2__* cache; TYPE_6__* upstream; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_11__ {TYPE_3__ vary; } ;
struct TYPE_10__ {int ignore_headers; } ;

/* Variables and functions */
 int NGX_HTTP_CACHE_VARY_LEN ; 
 int NGX_HTTP_UPSTREAM_IGN_VARY ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_vary(ngx_http_request_t *r,
    ngx_table_elt_t *h, ngx_uint_t offset)
{
    ngx_http_upstream_t  *u;

    u = r->upstream;
    u->headers_in.vary = h;

#if (NGX_HTTP_CACHE)

    if (u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_VARY) {
        return NGX_OK;
    }

    if (r->cache == NULL) {
        return NGX_OK;
    }

    if (h->value.len > NGX_HTTP_CACHE_VARY_LEN
        || (h->value.len == 1 && h->value.data[0] == '*'))
    {
        u->cacheable = 0;
    }

    r->cache->vary = h->value;

#endif

    return NGX_OK;
}