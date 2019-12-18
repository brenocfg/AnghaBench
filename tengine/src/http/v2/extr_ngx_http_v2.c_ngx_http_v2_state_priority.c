#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int ngx_uint_t ;
struct TYPE_18__ {int weight; int /*<<< orphan*/  reuse; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_3__ ngx_http_v2_node_t ;
struct TYPE_17__ {int length; int sid; } ;
struct TYPE_19__ {scalar_t__ priority_limit; int /*<<< orphan*/  closed; int /*<<< orphan*/  closed_nodes; TYPE_2__ state; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_v2_connection_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_ENHANCE_YOUR_CALM ; 
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 int NGX_HTTP_V2_PRIORITY_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_V2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_SIZE_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int* ngx_http_v2_connection_error (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_v2_get_node_by_id (TYPE_4__*,int,int) ; 
 int ngx_http_v2_parse_uint32 (int*) ; 
 scalar_t__ ngx_http_v2_send_rst_stream (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_set_dependency (TYPE_4__*,TYPE_3__*,int,int) ; 
 int* ngx_http_v2_state_complete (TYPE_4__*,int*,int*) ; 
 int* ngx_http_v2_state_save (TYPE_4__*,int*,int*,int* (*) (TYPE_4__*,int*,int*)) ; 
 scalar_t__ ngx_http_v2_terminate_stream (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_queue_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_priority(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    ngx_uint_t           depend, dependency, excl, weight;
    ngx_http_v2_node_t  *node;

    if (h2c->state.length != NGX_HTTP_V2_PRIORITY_SIZE) {
        ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                      "client sent PRIORITY frame with incorrect length %uz",
                      h2c->state.length);

        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_SIZE_ERROR);
    }

    if (--h2c->priority_limit == 0) {
        ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                      "client sent too many PRIORITY frames");

        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_ENHANCE_YOUR_CALM);
    }

    if (end - pos < NGX_HTTP_V2_PRIORITY_SIZE) {
        return ngx_http_v2_state_save(h2c, pos, end,
                                      ngx_http_v2_state_priority);
    }

    dependency = ngx_http_v2_parse_uint32(pos);

    depend = dependency & 0x7fffffff;
    excl = dependency >> 31;
    weight = pos[4] + 1;

    pos += NGX_HTTP_V2_PRIORITY_SIZE;

    ngx_log_debug4(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 PRIORITY frame sid:%ui "
                   "depends on %ui excl:%ui weight:%ui",
                   h2c->state.sid, depend, excl, weight);

    if (h2c->state.sid == 0) {
        ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                      "client sent PRIORITY frame with incorrect identifier");

        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_PROTOCOL_ERROR);
    }

    if (depend == h2c->state.sid) {
        ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                      "client sent PRIORITY frame for stream %ui "
                      "with incorrect dependency", h2c->state.sid);

        node = ngx_http_v2_get_node_by_id(h2c, h2c->state.sid, 0);

        if (node && node->stream) {
            if (ngx_http_v2_terminate_stream(h2c, node->stream,
                                             NGX_HTTP_V2_PROTOCOL_ERROR)
                == NGX_ERROR)
            {
                return ngx_http_v2_connection_error(h2c,
                                                    NGX_HTTP_V2_INTERNAL_ERROR);
            }

        } else {
            if (ngx_http_v2_send_rst_stream(h2c, h2c->state.sid,
                                            NGX_HTTP_V2_PROTOCOL_ERROR)
                == NGX_ERROR)
            {
                return ngx_http_v2_connection_error(h2c,
                                                    NGX_HTTP_V2_INTERNAL_ERROR);
            }
        }

        return ngx_http_v2_state_complete(h2c, pos, end);
    }

    node = ngx_http_v2_get_node_by_id(h2c, h2c->state.sid, 1);

    if (node == NULL) {
        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_INTERNAL_ERROR);
    }

    node->weight = weight;

    if (node->stream == NULL) {
        if (node->parent == NULL) {
            h2c->closed_nodes++;

        } else {
            ngx_queue_remove(&node->reuse);
        }

        ngx_queue_insert_tail(&h2c->closed, &node->reuse);
    }

    ngx_http_v2_set_dependency(h2c, node, depend, excl);

    return ngx_http_v2_state_complete(h2c, pos, end);
}