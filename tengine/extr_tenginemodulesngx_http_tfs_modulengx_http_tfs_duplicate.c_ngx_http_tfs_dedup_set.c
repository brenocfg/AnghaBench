#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int md5_sumed; int /*<<< orphan*/  dup_version; int /*<<< orphan*/  tair_instance; int /*<<< orphan*/  file_ref_count; TYPE_3__ dup_file_name; int /*<<< orphan*/ * tair_key; int /*<<< orphan*/  file_data; } ;
typedef  TYPE_1__ ngx_http_tfs_dedup_ctx_t ;
struct TYPE_9__ {int len; void* type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_http_tair_data_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 void* NGX_HTTP_TAIR_BYTEARRAY ; 
 int NGX_HTTP_TFS_DUPLICATE_KEY_SIZE ; 
 int NGX_HTTP_TFS_DUPLICATE_VALUE_BASE_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_MD5_RESULT_LEN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_tfs_dedup_set_handler ; 
 scalar_t__ ngx_http_tfs_sum_md5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_tfs_tair_put_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ *,int) ; 

ngx_int_t
ngx_http_tfs_dedup_set(ngx_http_tfs_dedup_ctx_t *ctx,
    ngx_pool_t *pool, ngx_log_t * log)
{
    u_char               *p;
    ssize_t               data_len;
    ngx_int_t             rc;
    ngx_http_tair_data_t  tair_key, tair_value;

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

    tair_key.len = NGX_HTTP_TFS_DUPLICATE_KEY_SIZE;
    tair_key.data = ctx->tair_key;
    tair_key.type = NGX_HTTP_TAIR_BYTEARRAY;

    tair_value.len =
        NGX_HTTP_TFS_DUPLICATE_VALUE_BASE_SIZE + ctx->dup_file_name.len;
    tair_value.data = ngx_pcalloc(pool, tair_value.len);
    if (tair_value.data == NULL) {
        return NGX_ERROR;
    }
    ngx_memcpy(tair_value.data, &ctx->file_ref_count,
               NGX_HTTP_TFS_DUPLICATE_VALUE_BASE_SIZE);
    ngx_memcpy(tair_value.data + NGX_HTTP_TFS_DUPLICATE_VALUE_BASE_SIZE,
               ctx->dup_file_name.data, ctx->dup_file_name.len);
    tair_value.type = NGX_HTTP_TAIR_BYTEARRAY;
    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, log, 0,
                   "set duplicate info: "
                   "file name: %V, file ref count: %d, dup_version: %d",
                   &ctx->dup_file_name,
                   ctx->file_ref_count,
                   ctx->dup_version);

    rc = ngx_http_tfs_tair_put_helper(ctx->tair_instance, pool, log,
                                      &tair_key, &tair_value, 0/*expire*/,
                                      ctx->dup_version,
                                      ngx_http_tfs_dedup_set_handler, ctx);

    return rc;
}