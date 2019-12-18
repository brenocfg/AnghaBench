#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {char* data; int len; } ;
struct TYPE_9__ {char* data; int len; } ;
struct TYPE_11__ {TYPE_3__ appkey; TYPE_2__ file_path_s; int /*<<< orphan*/  meta; } ;
typedef  TYPE_4__ ngx_http_tfs_restful_ctx_t ;
struct TYPE_8__ {char* data; int len; } ;
struct TYPE_12__ {scalar_t__ method; TYPE_1__ uri; } ;
typedef  TYPE_5__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_DELETE ; 
 scalar_t__ NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_HEAD ; 
 scalar_t__ NGX_HTTP_PUT ; 
 int NGX_HTTP_TFS_MAX_FILE_NAME_LEN ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_memcmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_restful_parse_raw(ngx_http_request_t *r,
    ngx_http_tfs_restful_ctx_t *ctx, u_char *data)
{
    u_char  *p, ch, *start, *last, *meta_data;

    enum {
        sw_appkey = 0,
        sw_metadata,
        sw_name,
    } state;

    state = sw_appkey;
    last = r->uri.data + r->uri.len;
    start = data;
    meta_data = NULL;

    for (p = data; p < last; p++) {
        ch = *p;

        switch (state) {

        case sw_appkey:
            if (ch == '/') {
                ctx->appkey.data = start;
                ctx->appkey.len = p - start;

                state = sw_metadata;
                if (p + 1 < last) {
                    meta_data = p + 1;
                }
            }

            break;

        case sw_metadata:
            if (ch == '/') {
                if (ngx_memcmp(meta_data, "metadata", 8) == 0) {
                    if (p + 1 < last) {
                        ctx->meta = NGX_HTTP_TFS_YES;
                        ctx->file_path_s.data = p + 1;
                        state = sw_name;

                    } else {
                        return NGX_ERROR;
                    }
                }
            }
        case sw_name:
            break;
        }
    }

    if (r->method == NGX_HTTP_GET || r->method == NGX_HTTP_DELETE
        || r->method == NGX_HTTP_PUT || r->method == NGX_HTTP_HEAD) {
        if (state == sw_appkey) {
            return NGX_ERROR;
        }

        if (state == sw_metadata) {
            ctx->file_path_s.data = meta_data;
        }

        if (state == sw_name) {
            if (r->method == NGX_HTTP_DELETE || r->method == NGX_HTTP_PUT) {
                return NGX_ERROR;
            }
        }
        ctx->file_path_s.len = p - ctx->file_path_s.data;
        if (ctx->file_path_s.len < 1
            || ctx->file_path_s.len > NGX_HTTP_TFS_MAX_FILE_NAME_LEN)
        {
            return NGX_ERROR;
        }

    } else {
        if (state == sw_appkey) {
            ctx->appkey.len = p - start;
            if (ctx->appkey.len == 0) {
                return NGX_ERROR;
            }
            ctx->appkey.data = start;

        } else {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}