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
struct TYPE_5__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_tree_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_FILE_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_delete_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_delete_file_n ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_http_dav_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_dav_delete_file(ngx_tree_ctx_t *ctx, ngx_str_t *path)
{
    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ctx->log, 0,
                   "http delete file: \"%s\"", path->data);

    if (ngx_delete_file(path->data) == NGX_FILE_ERROR) {

        /* TODO: add to 207 */

        (void) ngx_http_dav_error(ctx->log, ngx_errno, 0, ngx_delete_file_n,
                                  path->data);
    }

    return NGX_OK;
}