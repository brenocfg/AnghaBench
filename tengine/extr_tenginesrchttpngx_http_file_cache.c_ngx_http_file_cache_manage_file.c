#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* data; } ;
typedef  TYPE_1__ ngx_tree_ctx_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_msec_int_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_9__ {scalar_t__ files; scalar_t__ loader_files; scalar_t__ loader_threshold; scalar_t__ last; } ;
typedef  TYPE_2__ ngx_http_file_cache_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_abs (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_current_msec ; 
 TYPE_7__* ngx_cycle ; 
 scalar_t__ ngx_http_file_cache_add_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_file_cache_delete_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_file_cache_loader_sleep (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ngx_quit ; 
 scalar_t__ ngx_terminate ; 
 int /*<<< orphan*/  ngx_time_update () ; 

__attribute__((used)) static ngx_int_t
ngx_http_file_cache_manage_file(ngx_tree_ctx_t *ctx, ngx_str_t *path)
{
    ngx_msec_t              elapsed;
    ngx_http_file_cache_t  *cache;

    cache = ctx->data;

    if (ngx_http_file_cache_add_file(ctx, path) != NGX_OK) {
        (void) ngx_http_file_cache_delete_file(ctx, path);
    }

    if (++cache->files >= cache->loader_files) {
        ngx_http_file_cache_loader_sleep(cache);

    } else {
        ngx_time_update();

        elapsed = ngx_abs((ngx_msec_int_t) (ngx_current_msec - cache->last));

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "http file cache loader time elapsed: %M", elapsed);

        if (elapsed >= cache->loader_threshold) {
            ngx_http_file_cache_loader_sleep(cache);
        }
    }

    return (ngx_quit || ngx_terminate) ? NGX_ABORT : NGX_OK;
}