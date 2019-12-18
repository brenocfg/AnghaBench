#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ off_t ;
typedef  int ngx_uint_t ;
struct TYPE_10__ {scalar_t__ size; int fs_size; TYPE_3__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_tree_ctx_t ;
struct TYPE_11__ {int len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {int bsize; } ;
typedef  TYPE_3__ ngx_http_file_cache_t ;
typedef  int /*<<< orphan*/  ngx_http_file_cache_header_t ;
struct TYPE_13__ {scalar_t__ length; int fs_size; char* key; } ;
typedef  TYPE_4__ ngx_http_cache_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_CACHE_KEY_LEN ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_hextoi (char*,int) ; 
 scalar_t__ ngx_http_file_cache_add (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_file_cache_add_file(ngx_tree_ctx_t *ctx, ngx_str_t *name)
{
    u_char                 *p;
    ngx_int_t               n;
    ngx_uint_t              i;
    ngx_http_cache_t        c;
    ngx_http_file_cache_t  *cache;

    if (name->len < 2 * NGX_HTTP_CACHE_KEY_LEN) {
        return NGX_ERROR;
    }

    /*
     * Temporary files in cache have a suffix consisting of a dot
     * followed by 10 digits.
     */

    if (name->len >= 2 * NGX_HTTP_CACHE_KEY_LEN + 1 + 10
        && name->data[name->len - 10 - 1] == '.')
    {
        return NGX_OK;
    }

    if (ctx->size < (off_t) sizeof(ngx_http_file_cache_header_t)) {
        ngx_log_error(NGX_LOG_CRIT, ctx->log, 0,
                      "cache file \"%s\" is too small", name->data);
        return NGX_ERROR;
    }

    ngx_memzero(&c, sizeof(ngx_http_cache_t));
    cache = ctx->data;

    c.length = ctx->size;
    c.fs_size = (ctx->fs_size + cache->bsize - 1) / cache->bsize;

    p = &name->data[name->len - 2 * NGX_HTTP_CACHE_KEY_LEN];

    for (i = 0; i < NGX_HTTP_CACHE_KEY_LEN; i++) {
        n = ngx_hextoi(p, 2);

        if (n == NGX_ERROR) {
            return NGX_ERROR;
        }

        p += 2;

        c.key[i] = (u_char) n;
    }

    return ngx_http_file_cache_add(cache, &c);
}