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
struct TYPE_6__ {int version; } ;
struct TYPE_7__ {TYPE_1__ r_ctx; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_peer_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_http_tfs_select_peer_v1 (TYPE_2__*) ; 
 int /*<<< orphan*/ * ngx_http_tfs_select_peer_v2 (TYPE_2__*) ; 

ngx_http_tfs_peer_connection_t *
ngx_http_tfs_select_peer(ngx_http_tfs_t *t)
{
    if (t->r_ctx.version == 1) {
        return ngx_http_tfs_select_peer_v1(t);
    }

    if (t->r_ctx.version == 2) {
        return ngx_http_tfs_select_peer_v2(t);
    }

    return NULL;
}