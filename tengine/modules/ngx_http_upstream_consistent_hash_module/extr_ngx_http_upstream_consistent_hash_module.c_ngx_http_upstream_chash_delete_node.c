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
struct TYPE_10__ {TYPE_2__* d_servers; int /*<<< orphan*/  down_servers; int /*<<< orphan*/  number; TYPE_5__* tree; TYPE_4__*** real_node; } ;
typedef  TYPE_3__ ngx_http_upstream_chash_srv_conf_t ;
struct TYPE_11__ {size_t rnindex; int down; size_t index; TYPE_1__* peer; } ;
typedef  TYPE_4__ ngx_http_upstream_chash_server_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* del ) (TYPE_5__*,int,int,int /*<<< orphan*/ ,size_t) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  queue; scalar_t__ timeout; } ;
struct TYPE_8__ {scalar_t__ fail_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_time () ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int,int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
ngx_http_upstream_chash_delete_node(ngx_http_upstream_chash_srv_conf_t *ucscf,
    ngx_http_upstream_chash_server_t *server)
{
    ngx_http_upstream_chash_server_t **servers, *p;
    servers = ucscf->real_node[server->rnindex];

    for (; *servers; servers++) {
        p = *servers;
        if (!p->down) {
            ucscf->tree->del(ucscf->tree, 1, 1, ucscf->number, p->index);
            p->down = 1;
            ucscf->d_servers[p->index].timeout = ngx_time()
                                               + p->peer->fail_timeout;
            ngx_queue_insert_head(&ucscf->down_servers,
                                  &ucscf->d_servers[p->index].queue);
        }
    }
}