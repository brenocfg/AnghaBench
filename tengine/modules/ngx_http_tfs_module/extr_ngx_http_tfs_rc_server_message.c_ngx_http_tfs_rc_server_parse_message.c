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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ code; } ;
struct TYPE_8__ {TYPE_1__ action; } ;
struct TYPE_9__ {TYPE_2__ r_ctx; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_TFS_ACTION_KEEPALIVE ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_keepalive_message (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_login_message (TYPE_3__*) ; 

ngx_int_t
ngx_http_tfs_rc_server_parse_message(ngx_http_tfs_t *t)
{
    if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_KEEPALIVE) {
        return ngx_http_tfs_parse_keepalive_message(t);
    }

    return ngx_http_tfs_parse_login_message(t);
}