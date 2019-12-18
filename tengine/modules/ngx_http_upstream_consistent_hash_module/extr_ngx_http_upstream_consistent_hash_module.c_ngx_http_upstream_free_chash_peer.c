#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
struct TYPE_9__ {TYPE_2__* server; } ;
typedef  TYPE_4__ ngx_http_upstream_chash_peer_data_t ;
struct TYPE_7__ {TYPE_1__* peer; } ;
struct TYPE_6__ {int /*<<< orphan*/  fails; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_PEER_FAILED ; 
 int /*<<< orphan*/  ngx_log_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
ngx_http_upstream_free_chash_peer(ngx_peer_connection_t *pc, void *data,
    ngx_uint_t state)
{
    ngx_http_upstream_chash_peer_data_t *uchpd = data;
    ngx_log_debug(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                  "consistent hash free  peer %ui", state);

    if (uchpd->server == NULL) {
        return;
    }

    if (state & NGX_PEER_FAILED) {
        uchpd->server->peer->fails++;
    }
}