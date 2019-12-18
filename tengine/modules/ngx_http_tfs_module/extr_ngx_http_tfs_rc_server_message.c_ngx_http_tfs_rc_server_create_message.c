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
typedef  int uint16_t ;
struct TYPE_7__ {int code; } ;
struct TYPE_8__ {TYPE_1__ action; } ;
struct TYPE_9__ {TYPE_2__ r_ctx; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
#define  NGX_HTTP_TFS_ACTION_KEEPALIVE 128 
 int /*<<< orphan*/ * ngx_http_tfs_create_keepalive_message (TYPE_3__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_create_login_message (TYPE_3__*) ; 

ngx_chain_t *
ngx_http_tfs_rc_server_create_message(ngx_http_tfs_t *t)
{
    uint16_t  msg_type;

    msg_type = t->r_ctx.action.code;

    switch(msg_type) {
    case NGX_HTTP_TFS_ACTION_KEEPALIVE:
        return ngx_http_tfs_create_keepalive_message(t);
    default:
        return ngx_http_tfs_create_login_message(t);
    }
}