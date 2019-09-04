#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {scalar_t__ status_alive; } ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {scalar_t__ check_type_conf; TYPE_4__ code; TYPE_3__ send; } ;
typedef  TYPE_5__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_12__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_17__ {TYPE_1__ peers; } ;
typedef  TYPE_6__ ngx_http_upstream_check_peers_t ;
struct TYPE_18__ {TYPE_5__* conf; TYPE_2__* peer_addr; scalar_t__ delete; } ;
typedef  TYPE_7__ ngx_http_upstream_check_peer_t ;
struct TYPE_19__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_8__ ngx_addr_t ;
struct TYPE_13__ {int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; } ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_uint_t
ngx_http_upstream_check_unique_peer(ngx_http_upstream_check_peers_t *peers,
    ngx_addr_t *peer_addr, ngx_http_upstream_check_srv_conf_t *peer_conf)
{
    ngx_uint_t                           i;
    ngx_http_upstream_check_peer_t      *peer;
    ngx_http_upstream_check_srv_conf_t  *opeer_conf;

    peer = peers->peers.elts;
    for (i = 0; i < peers->peers.nelts; i++) {

        if (peer[i].delete) {
            continue;
        }

        if (peer[i].peer_addr->socklen != peer_addr->socklen) {
            continue;
        }

        if (ngx_memcmp(peer[i].peer_addr->sockaddr,
                       peer_addr->sockaddr, peer_addr->socklen) != 0) {
            continue;
        }

        opeer_conf = peer[i].conf;

        if (opeer_conf->check_type_conf != peer_conf->check_type_conf) {
            continue;
        }

        if (opeer_conf->send.len != peer_conf->send.len) {
            continue;
        }

        if (ngx_strncmp(opeer_conf->send.data,
                        peer_conf->send.data, peer_conf->send.len) != 0) {
            continue;
        }

        if (opeer_conf->code.status_alive != peer_conf->code.status_alive) {
            continue;
        }

        return i;
    }

    return NGX_ERROR;
}