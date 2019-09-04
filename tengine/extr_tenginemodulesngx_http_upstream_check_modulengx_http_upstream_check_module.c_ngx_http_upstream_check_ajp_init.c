#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int len; scalar_t__ data; } ;
struct TYPE_11__ {TYPE_2__ send; } ;
typedef  TYPE_4__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_12__ {TYPE_4__* conf; TYPE_6__* check_data; } ;
typedef  TYPE_5__ ngx_http_upstream_check_peer_t ;
struct TYPE_10__ {int /*<<< orphan*/ * last; int /*<<< orphan*/  end; int /*<<< orphan*/ * pos; int /*<<< orphan*/  start; } ;
struct TYPE_8__ {int /*<<< orphan*/ * start; int /*<<< orphan*/ * last; int /*<<< orphan*/ * end; int /*<<< orphan*/ * pos; } ;
struct TYPE_13__ {TYPE_3__ recv; TYPE_1__ send; } ;
typedef  TYPE_6__ ngx_http_upstream_check_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_ajp_init(ngx_http_upstream_check_peer_t *peer)
{
    ngx_http_upstream_check_ctx_t       *ctx;
    ngx_http_upstream_check_srv_conf_t  *ucscf;

    ctx = peer->check_data;
    ucscf = peer->conf;

    ctx->send.start = ctx->send.pos = (u_char *)ucscf->send.data;
    ctx->send.end = ctx->send.last = ctx->send.start + ucscf->send.len;

    ctx->recv.start = ctx->recv.pos = NULL;
    ctx->recv.end = ctx->recv.last = NULL;

    return NGX_OK;
}