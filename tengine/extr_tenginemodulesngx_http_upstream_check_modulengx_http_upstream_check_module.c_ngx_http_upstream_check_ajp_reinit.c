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
struct TYPE_8__ {TYPE_4__* check_data; } ;
typedef  TYPE_3__ ngx_http_upstream_check_peer_t ;
struct TYPE_7__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_6__ {int /*<<< orphan*/  end; int /*<<< orphan*/  last; int /*<<< orphan*/  start; int /*<<< orphan*/  pos; } ;
struct TYPE_9__ {TYPE_2__ recv; TYPE_1__ send; } ;
typedef  TYPE_4__ ngx_http_upstream_check_ctx_t ;

/* Variables and functions */

__attribute__((used)) static void
ngx_http_upstream_check_ajp_reinit(ngx_http_upstream_check_peer_t *peer)
{
    ngx_http_upstream_check_ctx_t  *ctx;

    ctx = peer->check_data;

    ctx->send.pos = ctx->send.start;
    ctx->send.last = ctx->send.end;

    ctx->recv.pos = ctx->recv.last = ctx->recv.start;
}