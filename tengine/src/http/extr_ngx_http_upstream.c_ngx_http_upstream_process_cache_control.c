#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int ngx_uint_t ;
struct TYPE_16__ {char* data; int len; } ;
struct TYPE_18__ {TYPE_3__ value; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_15__ {int /*<<< orphan*/ * x_accel_expires; TYPE_8__ cache_control; } ;
struct TYPE_19__ {scalar_t__ cacheable; TYPE_2__ headers_in; TYPE_1__* conf; } ;
typedef  TYPE_6__ ngx_http_upstream_t ;
struct TYPE_20__ {TYPE_4__* cache; int /*<<< orphan*/  pool; TYPE_6__* upstream; } ;
typedef  TYPE_7__ ngx_http_request_t ;
typedef  TYPE_8__ ngx_array_t ;
struct TYPE_17__ {scalar_t__ valid_sec; scalar_t__ error_sec; scalar_t__ updating_sec; } ;
struct TYPE_14__ {int ignore_headers; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_UPSTREAM_IGN_CACHE_CONTROL ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_8__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__** ngx_array_push (TYPE_8__*) ; 
 char* ngx_strlcasestrn (char*,char*,char*,int) ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_cache_control(ngx_http_request_t *r,
    ngx_table_elt_t *h, ngx_uint_t offset)
{
    ngx_array_t          *pa;
    ngx_table_elt_t     **ph;
    ngx_http_upstream_t  *u;

    u = r->upstream;
    pa = &u->headers_in.cache_control;

    if (pa->elts == NULL) {
        if (ngx_array_init(pa, r->pool, 2, sizeof(ngx_table_elt_t *)) != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    ph = ngx_array_push(pa);
    if (ph == NULL) {
        return NGX_ERROR;
    }

    *ph = h;

#if (NGX_HTTP_CACHE)
    {
    u_char     *p, *start, *last;
    ngx_int_t   n;

    if (u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_CACHE_CONTROL) {
        return NGX_OK;
    }

    if (r->cache == NULL) {
        return NGX_OK;
    }

    if (r->cache->valid_sec != 0 && u->headers_in.x_accel_expires != NULL) {
        return NGX_OK;
    }

    start = h->value.data;
    last = start + h->value.len;

    if (ngx_strlcasestrn(start, last, (u_char *) "no-cache", 8 - 1) != NULL
        || ngx_strlcasestrn(start, last, (u_char *) "no-store", 8 - 1) != NULL
        || ngx_strlcasestrn(start, last, (u_char *) "private", 7 - 1) != NULL)
    {
        u->cacheable = 0;
        return NGX_OK;
    }

    p = ngx_strlcasestrn(start, last, (u_char *) "s-maxage=", 9 - 1);
    offset = 9;

    if (p == NULL) {
        p = ngx_strlcasestrn(start, last, (u_char *) "max-age=", 8 - 1);
        offset = 8;
    }

    if (p) {
        n = 0;

        for (p += offset; p < last; p++) {
            if (*p == ',' || *p == ';' || *p == ' ') {
                break;
            }

            if (*p >= '0' && *p <= '9') {
                n = n * 10 + (*p - '0');
                continue;
            }

            u->cacheable = 0;
            return NGX_OK;
        }

        if (n == 0) {
            u->cacheable = 0;
            return NGX_OK;
        }

        r->cache->valid_sec = ngx_time() + n;
    }

    p = ngx_strlcasestrn(start, last, (u_char *) "stale-while-revalidate=",
                         23 - 1);

    if (p) {
        n = 0;

        for (p += 23; p < last; p++) {
            if (*p == ',' || *p == ';' || *p == ' ') {
                break;
            }

            if (*p >= '0' && *p <= '9') {
                n = n * 10 + (*p - '0');
                continue;
            }

            u->cacheable = 0;
            return NGX_OK;
        }

        r->cache->updating_sec = n;
        r->cache->error_sec = n;
    }

    p = ngx_strlcasestrn(start, last, (u_char *) "stale-if-error=", 15 - 1);

    if (p) {
        n = 0;

        for (p += 15; p < last; p++) {
            if (*p == ',' || *p == ';' || *p == ' ') {
                break;
            }

            if (*p >= '0' && *p <= '9') {
                n = n * 10 + (*p - '0');
                continue;
            }

            u->cacheable = 0;
            return NGX_OK;
        }

        r->cache->error_sec = n;
    }
    }
#endif

    return NGX_OK;
}