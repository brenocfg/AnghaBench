#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_5__ {int md5_sumed; int /*<<< orphan*/  tair_instance; int /*<<< orphan*/ * tair_key; int /*<<< orphan*/  file_data; } ;
typedef  TYPE_1__ ngx_http_tfs_dedup_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ngx_http_tair_data_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TAIR_BYTEARRAY ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_DUPLICATE_KEY_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_MD5_RESULT_LEN ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_remove_handler ; 
 scalar_t__ ngx_http_tfs_sum_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_tfs_tair_delete_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

ngx_int_t
ngx_http_tfs_dedup_remove(ngx_http_tfs_dedup_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t * log)
{
    u_char                *p;
    ssize_t                data_len;
    ngx_int_t              rc;
    ngx_array_t            tair_keys;
    ngx_http_tair_data_t  *tair_key;

    data_len = 0;

    if (!ctx->md5_sumed) {
        rc = ngx_http_tfs_sum_md5(ctx->file_data, ctx->tair_key, &data_len,
                                  log);
        if (rc == NGX_ERROR) {
            return NGX_ERROR;
        }

        p = ctx->tair_key;
        p += NGX_HTTP_TFS_MD5_RESULT_LEN;

        *(uint32_t *) p = htonl(data_len);
        ctx->md5_sumed = 1;
    }

    rc = ngx_array_init(&tair_keys, pool, 1, sizeof(ngx_http_tair_data_t));
    if (rc == NGX_ERROR) {
        return rc;
    }
    tair_key = (ngx_http_tair_data_t*) ngx_array_push(&tair_keys);

    tair_key->type = NGX_HTTP_TAIR_BYTEARRAY;
    tair_key->data = ctx->tair_key;
    tair_key->len = NGX_HTTP_TFS_DUPLICATE_KEY_SIZE;

    rc = ngx_http_tfs_tair_delete_helper(ctx->tair_instance, pool, log,
                                         &tair_keys,
                                         ngx_http_tfs_dedup_remove_handler,
                                         ctx);

    return rc;
}