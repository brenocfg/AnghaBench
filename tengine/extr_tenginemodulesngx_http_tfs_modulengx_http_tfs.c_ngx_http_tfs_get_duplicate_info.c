#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {scalar_t__ code; } ;
struct TYPE_7__ {TYPE_1__ action; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_2__ r_ctx; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  dedup_ctx; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_ACTION_REMOVE_FILE ; 
 scalar_t__ NGX_HTTP_TFS_STATE_REMOVE_DONE ; 
 scalar_t__ NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_dedup_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_finalize_state (TYPE_3__*,scalar_t__) ; 

ngx_int_t
ngx_http_tfs_get_duplicate_info(ngx_http_tfs_t *t)
{
    ngx_int_t  rc;

    rc = ngx_http_tfs_dedup_get(&t->dedup_ctx, t->pool, t->log);
    if (rc == NGX_ERROR) {
        if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_REMOVE_FILE
            && t->state == NGX_HTTP_TFS_STATE_REMOVE_READ_META_SEGMENT)
        {
            /* get dup info from tair failed, do not unlink file */
            t->state = NGX_HTTP_TFS_STATE_REMOVE_DONE;
            rc = NGX_DONE;

        } else {
            /* no dedup */
            rc = NGX_OK;
        }

        ngx_http_tfs_finalize_state(t, rc);
    }

    return NGX_OK;
}