#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_7__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_3__ ngx_http_map_t ;

/* Variables and functions */
 void* ngx_hash_find_combined (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_hash_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

void *
ngx_http_map_find(ngx_http_request_t *r, ngx_http_map_t *map, ngx_str_t *match)
{
    void        *value;
    u_char      *low;
    size_t       len;
    ngx_uint_t   key;

    len = match->len;

    if (len) {
        low = ngx_pnalloc(r->pool, len);
        if (low == NULL) {
            return NULL;
        }

    } else {
        low = NULL;
    }

    key = ngx_hash_strlow(low, match->data, len);

    value = ngx_hash_find_combined(&map->hash, key, low, len);
    if (value) {
        return value;
    }

#if (NGX_PCRE)

    if (len && map->nregex) {
        ngx_int_t              n;
        ngx_uint_t             i;
        ngx_http_map_regex_t  *reg;

        reg = map->regex;

        for (i = 0; i < map->nregex; i++) {

            n = ngx_http_regex_exec(r, reg[i].regex, match);

            if (n == NGX_OK) {
                return reg[i].value;
            }

            if (n == NGX_DECLINED) {
                continue;
            }

            /* NGX_ERROR */

            return NULL;
        }
    }

#endif

    return NULL;
}