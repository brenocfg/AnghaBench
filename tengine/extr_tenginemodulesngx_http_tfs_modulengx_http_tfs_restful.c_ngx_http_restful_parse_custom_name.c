#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {char* data; int len; } ;
struct TYPE_10__ {char* data; int len; } ;
struct TYPE_13__ {scalar_t__ file_type; TYPE_4__ file_path_s; void* get_appid; int /*<<< orphan*/  user_id; int /*<<< orphan*/  app_id; void* meta; TYPE_2__ appkey; } ;
typedef  TYPE_5__ ngx_http_tfs_restful_ctx_t ;
struct TYPE_9__ {char* data; int len; } ;
struct TYPE_14__ {scalar_t__ method; TYPE_3__* connection; TYPE_1__ uri; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_TFS_CUSTOM_FT_DIR ; 
 scalar_t__ NGX_HTTP_TFS_CUSTOM_FT_FILE ; 
 int NGX_HTTP_TFS_MAX_FILE_NAME_LEN ; 
 void* NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_INT64_LEN ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_atoull (char*,int,unsigned long long*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_restful_parse_custom_name(ngx_http_request_t *r,
    ngx_http_tfs_restful_ctx_t *ctx, u_char *data)
{
    u_char    *p, ch, *start, *last, *appid, *meta_data;
    ngx_int_t  rc;

    enum {
        sw_appkey = 0,
        sw_metadata,
        sw_appid,
        sw_uid,
        sw_type,
        sw_name,
    } state;

    state = sw_appkey;
    last = r->uri.data + r->uri.len;
    start = data;
    appid = NULL;
    meta_data = NULL;

    for (p = data; p < last; p++) {
        ch = *p;

        switch (state) {
        case sw_appkey:
            if (ch == '/') {
                ctx->appkey.data = start;
                ctx->appkey.len = p - start;

                start = p + 1;
                /* GET /v2/appkey/appid */
                if (start < last) {
                    if (*start == 'a') {
                        state = sw_name;
                        appid = start;
                    } else if (*start == 'm') {
                        state = sw_metadata;
                        meta_data = start;
                    } else {
                        state = sw_appid;
                    }
                }
            }
            break;
        case sw_metadata:
            if (ch == '/') {
                if (ngx_memcmp(meta_data, "metadata", 8) == 0) {
                    if (p + 1 < last) {
                        ctx->meta = NGX_HTTP_TFS_YES;
                        start = p + 1;
                        state = sw_appid;

                    } else {
                        return NGX_ERROR;
                    }
                }
            }
            break;
        case sw_appid:
            if (ch == '/') {
                rc = ngx_http_tfs_atoull(start, p - start,
                                         (unsigned long long *)&ctx->app_id);
                if (rc == NGX_ERROR || ctx->app_id == 0) {
                    return NGX_ERROR;
                }

                start = p + 1;
                state = sw_uid;
                break;
            }

            if (ch < '0' || ch > '9') {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "appid is invalid");
                return NGX_ERROR;
            }

            if ((size_t) (p - start) > (NGX_INT64_LEN - 1)) {
                return NGX_ERROR;
            }

            break;
        case sw_uid:
            if (ch == '/') {
                rc = ngx_http_tfs_atoull(start, p - start,
                                         (unsigned long long *)&ctx->user_id);
                if (rc == NGX_ERROR || ctx->user_id == 0) {
                    return NGX_ERROR;
                }
                start = p + 1;
                state = sw_type;
                break;
            }

            if (ch < '0' || ch > '9') {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "userid is invalid");
                return NGX_ERROR;
            }

            if ((size_t) (p - start) > NGX_INT64_LEN - 1) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "userid is too big");
                return NGX_ERROR;
            }
            break;
        case sw_type:
            if (ch == '/') {
                if (ngx_strncmp(start, "file", p - start) == 0) {
                    ctx->file_type = NGX_HTTP_TFS_CUSTOM_FT_FILE;

                } else if (ngx_strncmp(start, "dir", p - start) == 0) {
                    ctx->file_type = NGX_HTTP_TFS_CUSTOM_FT_DIR;

                } else {
                    return NGX_ERROR;
                }
                ctx->file_path_s.data = p;
                state = sw_name;
            }
            break;
        case sw_name:
            break;
        }
    }

    if (r->method == NGX_HTTP_GET && appid != NULL) {
        if (ngx_memcmp(appid, "appid", 5) == 0) {
            ctx->get_appid = NGX_HTTP_TFS_YES;
            ctx->file_path_s.data = appid;
            ctx->file_path_s.len = 5;
            return NGX_OK;
        }
        return NGX_ERROR;
    }

    ctx->file_path_s.len = p - ctx->file_path_s.data;
    if (ctx->file_path_s.len < 1
        || ctx->file_path_s.len > NGX_HTTP_TFS_MAX_FILE_NAME_LEN)
    {
        return NGX_ERROR;
    }

    /* forbid file actions on "/" */
    if (ctx->file_type == NGX_HTTP_TFS_CUSTOM_FT_FILE
        && ctx->file_path_s.len == 1)
    {
        return NGX_ERROR;
    }

    return NGX_OK;
}