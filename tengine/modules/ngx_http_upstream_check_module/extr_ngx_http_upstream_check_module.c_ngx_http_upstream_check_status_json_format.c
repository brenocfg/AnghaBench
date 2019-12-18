#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_16__ {TYPE_1__ peers; } ;
typedef  TYPE_6__ ngx_http_upstream_check_peers_t ;
struct TYPE_17__ {TYPE_5__* conf; TYPE_3__* shm; TYPE_2__* peer_addr; int /*<<< orphan*/  upstream_name; scalar_t__ delete; } ;
typedef  TYPE_7__ ngx_http_upstream_check_peer_t ;
struct TYPE_18__ {void* last; void* end; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_15__ {int /*<<< orphan*/  port; TYPE_4__* check_type_conf; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  fall_count; int /*<<< orphan*/  rise_count; scalar_t__ down; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t NGX_CHECK_STATUS_DOWN ; 
 size_t NGX_CHECK_STATUS_UP ; 
 int /*<<< orphan*/  ngx_http_upstream_check_shm_generation ; 
 void* ngx_snprintf (void*,void*,char*,...) ; 

__attribute__((used)) static void
ngx_http_upstream_check_status_json_format(ngx_buf_t *b,
    ngx_http_upstream_check_peers_t *peers, ngx_uint_t flag)
{
    ngx_uint_t                       count, i, last;
    ngx_http_upstream_check_peer_t  *peer;

    peer = peers->peers.elts;

    count = 0;

    for (i = 0; i < peers->peers.nelts; i++) {

        if (peer[i].delete) {
            continue;
        }

        if (flag & NGX_CHECK_STATUS_DOWN) {

            if (!peer[i].shm->down) {
                continue;
            }

        } else if (flag & NGX_CHECK_STATUS_UP) {

            if (peer[i].shm->down) {
                continue;
            }
        }

        count++;
    }

    b->last = ngx_snprintf(b->last, b->end - b->last,
            "{\"servers\": {\n"
            "  \"total\": %ui,\n"
            "  \"generation\": %ui,\n"
            "  \"server\": [\n",
            count,
            ngx_http_upstream_check_shm_generation);

    last = 0;
    for (i = 0; i < peers->peers.nelts; i++) {

        if (peer[i].delete) {
            continue;
        }

        if (flag & NGX_CHECK_STATUS_DOWN) {

            if (!peer[i].shm->down) {
                continue;
            }

        } else if (flag & NGX_CHECK_STATUS_UP) {

            if (peer[i].shm->down) {
                continue;
            }
        }

        last++;

        b->last = ngx_snprintf(b->last, b->end - b->last,
                "    {\"index\": %ui, "
                "\"upstream\": \"%V\", "
                "\"name\": \"%V\", "
                "\"status\": \"%s\", "
                "\"rise\": %ui, "
                "\"fall\": %ui, "
                "\"type\": \"%V\", "
                "\"port\": %ui}"
                "%s\n",
                i,
                peer[i].upstream_name,
                &peer[i].peer_addr->name,
                peer[i].shm->down ? "down" : "up",
                peer[i].shm->rise_count,
                peer[i].shm->fall_count,
                &peer[i].conf->check_type_conf->name,
                peer[i].conf->port,
                (last == count) ? "" : ",");
    }

    b->last = ngx_snprintf(b->last, b->end - b->last,
            "  ]\n");

    b->last = ngx_snprintf(b->last, b->end - b->last,
            "}}\n");
}