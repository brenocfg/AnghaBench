#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_10__ {int valid; int not_found; int len; int /*<<< orphan*/ * data; scalar_t__ no_cacheable; } ;
typedef  TYPE_3__ ngx_stream_variable_value_t ;
struct TYPE_11__ {int first_byte_time; int connect_time; int response_time; } ;
typedef  TYPE_4__ ngx_stream_upstream_state_t ;
struct TYPE_12__ {TYPE_2__* upstream_states; TYPE_1__* connection; } ;
typedef  TYPE_5__ ngx_stream_session_t ;
typedef  int ngx_msec_int_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int nelts; TYPE_4__* elts; } ;
struct TYPE_8__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_TIME_T_LEN ; 
 int ngx_max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_upstream_response_time_variable(ngx_stream_session_t *s,
    ngx_stream_variable_value_t *v, uintptr_t data)
{
    u_char                       *p;
    size_t                        len;
    ngx_uint_t                    i;
    ngx_msec_int_t                ms;
    ngx_stream_upstream_state_t  *state;

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    if (s->upstream_states == NULL || s->upstream_states->nelts == 0) {
        v->not_found = 1;
        return NGX_OK;
    }

    len = s->upstream_states->nelts * (NGX_TIME_T_LEN + 4 + 2);

    p = ngx_pnalloc(s->connection->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    v->data = p;

    i = 0;
    state = s->upstream_states->elts;

    for ( ;; ) {

        if (data == 1) {
            ms = state[i].first_byte_time;

        } else if (data == 2) {
            ms = state[i].connect_time;

        } else {
            ms = state[i].response_time;
        }

        if (ms != -1) {
            ms = ngx_max(ms, 0);
            p = ngx_sprintf(p, "%T.%03M", (time_t) ms / 1000, ms % 1000);

        } else {
            *p++ = '-';
        }

        if (++i == s->upstream_states->nelts) {
            break;
        }

        *p++ = ',';
        *p++ = ' ';
    }

    v->len = p - v->data;

    return NGX_OK;
}