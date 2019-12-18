#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int rc_servers_count; scalar_t__ rcserver_index; int /*<<< orphan*/  rc_servers; } ;
typedef  TYPE_2__ ngx_http_tfs_upstream_t ;
struct TYPE_9__ {TYPE_1__* loc_conf; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_10__ {scalar_t__ rc_servers_count; int /*<<< orphan*/  rc_servers; } ;
typedef  TYPE_4__ ngx_http_tfs_rcs_info_t ;
struct TYPE_7__ {TYPE_2__* upstream; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_TFS_MAX_RCSERVER_COUNT ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ngx_http_tfs_update_rc_servers(ngx_http_tfs_t *t, const ngx_http_tfs_rcs_info_t *rc_info_node)
{
    ngx_http_tfs_upstream_t       *upstream;

    upstream = t->loc_conf->upstream;
    if (rc_info_node->rc_servers_count > NGX_HTTP_TFS_MAX_RCSERVER_COUNT) {
        upstream->rc_servers_count = NGX_HTTP_TFS_MAX_RCSERVER_COUNT;

    } else {
        upstream->rc_servers_count = rc_info_node->rc_servers_count;
    }

    ngx_memcpy(upstream->rc_servers, rc_info_node->rc_servers, upstream->rc_servers_count * sizeof(uint64_t));
    upstream->rcserver_index = 0;
}