#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_12__ {TYPE_2__* shm; TYPE_1__* upstream_name; } ;
typedef  TYPE_5__ ngx_http_upstream_check_peer_t ;
struct TYPE_10__ {size_t nelts; TYPE_5__* elts; } ;
struct TYPE_13__ {TYPE_3__ peers; } ;
struct TYPE_9__ {int /*<<< orphan*/  down; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 TYPE_7__* check_peers_ctx ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_uint_t
ngx_http_upstream_check_upstream_down(ngx_str_t *upstream)
{
    ngx_uint_t i;
    ngx_http_upstream_check_peer_t *peers;

    if (check_peers_ctx == NULL) {
        return 0;
    }

    peers = check_peers_ctx->peers.elts;
    for (i = 0; i < check_peers_ctx->peers.nelts; i++) {
        if (peers[i].upstream_name->len == upstream->len
            && ngx_strncmp(peers[i].upstream_name->data, upstream->data, upstream->len) == 0)
        {
            if (!peers[i].shm->down) {
                return 0;
            }
        }
    }

    return 1;
}