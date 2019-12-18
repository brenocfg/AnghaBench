#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ sp_fail_count; int /*<<< orphan*/  data; int /*<<< orphan*/  sp_curr; int /*<<< orphan*/  log; TYPE_1__* parent; scalar_t__ sp_ready; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
struct TYPE_6__ {scalar_t__ sp_fail_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_request (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_send_response (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_http_tfs_batch_process_next(ngx_http_tfs_t *t)
{
    if (t->sp_ready) {
        if (t->sp_fail_count > 0 || t->parent->sp_fail_count > 0) {
            ngx_log_error(NGX_LOG_ERR, t->log, 0,
                          "(other) sub process failed");

            ngx_http_tfs_finalize_request(t->data, t, NGX_ERROR);
            return NGX_OK;
        }

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                       "segment[%uD] wake up, will output...",
                       t->sp_curr);
        ngx_http_tfs_send_response(t->data, t);
    }

    return NGX_OK;
}