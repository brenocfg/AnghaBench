#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {size_t len; } ;
struct TYPE_7__ {TYPE_3__** recovering; TYPE_1__ pattern; } ;
typedef  TYPE_2__ ngx_http_lua_socket_compiled_pattern_t ;
struct TYPE_8__ {scalar_t__ chr; int new_state; struct TYPE_8__* next; } ;
typedef  TYPE_3__ ngx_http_lua_dfa_edge_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,size_t,scalar_t__*,scalar_t__,int,size_t,scalar_t__*) ; 
 scalar_t__ ngx_memcmp (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__**,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_compile_pattern(u_char *data, size_t len,
    ngx_http_lua_socket_compiled_pattern_t *cp, ngx_log_t *log)
{
    size_t              i;
    size_t              prefix_len;
    size_t              size;
    unsigned            found;
    int                 cur_state, new_state;

    ngx_http_lua_dfa_edge_t         *edge;
    ngx_http_lua_dfa_edge_t        **last = NULL;

    cp->pattern.len = len;

    if (len <= 2) {
        return NGX_OK;
    }

    for (i = 1; i < len; i++) {
        prefix_len = 1;

        while (prefix_len <= len - i - 1) {

            if (ngx_memcmp(data, &data[i], prefix_len) == 0) {
                if (data[prefix_len] == data[i + prefix_len]) {
                    prefix_len++;
                    continue;
                }

                cur_state = i + prefix_len;
                new_state = prefix_len + 1;

                if (cp->recovering == NULL) {
                    size = sizeof(void *) * (len - 2);
                    cp->recovering = ngx_alloc(size, log);
                    if (cp->recovering == NULL) {
                        return NGX_ERROR;
                    }

                    ngx_memzero(cp->recovering, size);
                }

                edge = cp->recovering[cur_state - 2];

                found = 0;

                if (edge == NULL) {
                    last = &cp->recovering[cur_state - 2];

                } else {

                    for (; edge; edge = edge->next) {
                        last = &edge->next;

                        if (edge->chr == data[prefix_len]) {
                            found = 1;

                            if (edge->new_state < new_state) {
                                edge->new_state = new_state;
                            }

                            break;
                        }
                    }
                }

                if (!found) {
                    ngx_log_debug7(NGX_LOG_DEBUG_HTTP, log, 0,
                                   "lua tcp socket read until recovering point:"
                                   " on state %d (%*s), if next is '%c', then "
                                   "recover to state %d (%*s)", cur_state,
                                   (size_t) cur_state, data, data[prefix_len],
                                   new_state, (size_t) new_state, data);

                    edge = ngx_alloc(sizeof(ngx_http_lua_dfa_edge_t), log);
                    if (edge == NULL) {
                        return NGX_ERROR;
                    }

                    edge->chr = data[prefix_len];
                    edge->new_state = new_state;
                    edge->next = NULL;

                    *last = edge;
                }

                break;
            }

            break;
        }
    }

    return NGX_OK;
}