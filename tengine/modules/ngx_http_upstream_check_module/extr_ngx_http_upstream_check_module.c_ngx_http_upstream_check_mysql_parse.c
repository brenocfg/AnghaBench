#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int packet_number; int /*<<< orphan*/  others; int /*<<< orphan*/  protocol_version; } ;
typedef  TYPE_2__ ngx_mysql_handshake_init_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {TYPE_4__* check_data; } ;
typedef  TYPE_3__ ngx_http_upstream_check_peer_t ;
struct TYPE_7__ {size_t last; size_t pos; } ;
struct TYPE_10__ {TYPE_1__ recv; } ;
typedef  TYPE_4__ ngx_http_upstream_check_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_mysql_parse(ngx_http_upstream_check_peer_t *peer)
{
    size_t                         size;
    ngx_mysql_handshake_init_t    *handshake;
    ngx_http_upstream_check_ctx_t *ctx;

    ctx = peer->check_data;

    size = ctx->recv.last - ctx->recv.pos;
    if (size < sizeof(ngx_mysql_handshake_init_t)) {
        return NGX_AGAIN;
    }

    handshake = (ngx_mysql_handshake_init_t *) ctx->recv.pos;

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "mysql_parse: packet_number=%ud, protocol=%ud, server=%s",
                   handshake->packet_number, handshake->protocol_version,
                   handshake->others);

    /* The mysql greeting packet's serial number always begins with 0. */
    if (handshake->packet_number != 0x00) {
        return NGX_ERROR;
    }

    return NGX_OK;
}