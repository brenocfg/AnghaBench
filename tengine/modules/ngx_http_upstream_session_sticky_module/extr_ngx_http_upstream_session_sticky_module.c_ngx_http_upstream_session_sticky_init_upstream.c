#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {int number; int flag; TYPE_10__* server; } ;
typedef  TYPE_5__ ngx_http_upstream_ss_srv_conf_t ;
struct TYPE_23__ {int /*<<< orphan*/  init; scalar_t__ data; } ;
struct TYPE_25__ {TYPE_4__ peer; } ;
typedef  TYPE_6__ ngx_http_upstream_srv_conf_t ;
struct TYPE_26__ {int number; TYPE_8__* peer; } ;
typedef  TYPE_7__ ngx_http_upstream_rr_peers_t ;
struct TYPE_22__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {TYPE_3__ id; TYPE_1__ name; int /*<<< orphan*/  check_index; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; struct TYPE_27__* next; } ;
typedef  TYPE_8__ ngx_http_upstream_rr_peer_t ;
typedef  int /*<<< orphan*/  ngx_http_ss_server_t ;
struct TYPE_28__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_9__ ngx_conf_t ;
struct TYPE_21__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {TYPE_2__ sid; int /*<<< orphan*/  check_index; TYPE_8__* peer; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_1__* name; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_SESSION_STICKY_PLAIN ; 
 scalar_t__ NGX_OK ; 
 TYPE_5__* ngx_http_conf_upstream_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_init_round_robin (TYPE_9__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_session_sticky_init_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_session_sticky_module ; 
 scalar_t__ ngx_http_upstream_session_sticky_set_sid (TYPE_9__*,TYPE_10__*) ; 
 TYPE_10__* ngx_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_session_sticky_init_upstream(ngx_conf_t *cf,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_uint_t                        number, i;
    ngx_http_upstream_rr_peer_t      *peer;
    ngx_http_upstream_rr_peers_t     *peers;
    ngx_http_upstream_ss_srv_conf_t  *sscf;

    if (ngx_http_upstream_init_round_robin(cf, us) != NGX_OK) {
        return NGX_ERROR;
    }

    sscf = ngx_http_conf_upstream_srv_conf(us,
                                    ngx_http_upstream_session_sticky_module);
    if (sscf == NULL) {
        return NGX_ERROR;
    }

    peers = (ngx_http_upstream_rr_peers_t *) us->peer.data;
    number = peers->number;

    sscf->server = ngx_palloc(cf->pool, number * sizeof(ngx_http_ss_server_t));
    if (sscf->server == NULL) {
        return NGX_ERROR;
    }

    sscf->number = number;

    for (peer = peers->peer, i = 0; peer; peer = peer->next, i++) {

        sscf->server[i].name = &peer->name;
        sscf->server[i].sockaddr = peer->sockaddr;
        sscf->server[i].socklen = peer->socklen;

        sscf->server[i].peer = peer;

#if (NGX_HTTP_UPSTREAM_CHECK)
        sscf->server[i].check_index = peer->check_index;
#endif
        if (sscf->flag & NGX_HTTP_SESSION_STICKY_PLAIN) {
            if (peer->id.len == 0) {
                sscf->server[i].sid.data = peer->name.data;
                sscf->server[i].sid.len = peer->name.len;
                continue;
            }

            sscf->server[i].sid.data = peer->id.data;
            sscf->server[i].sid.len = peer->id.len;

        } else if (ngx_http_upstream_session_sticky_set_sid(
                                                cf, &sscf->server[i]) != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    us->peer.init = ngx_http_upstream_session_sticky_init_peer;

    return NGX_OK;
}