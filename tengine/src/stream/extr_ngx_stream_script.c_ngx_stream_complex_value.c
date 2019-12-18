#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_stream_session_t ;
typedef  scalar_t__ (* ngx_stream_script_len_code_pt ) (TYPE_3__*) ;
struct TYPE_18__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int flushed; TYPE_7__ buf; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * pos; TYPE_2__* session; } ;
typedef  TYPE_3__ ngx_stream_script_engine_t ;
typedef  int /*<<< orphan*/  (* ngx_stream_script_code_pt ) (TYPE_3__*) ;
struct TYPE_17__ {int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; TYPE_7__ value; } ;
typedef  TYPE_6__ ngx_stream_complex_value_t ;
typedef  TYPE_7__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_stream_script_flush_complex_value (TYPE_2__*,TYPE_6__*) ; 

ngx_int_t
ngx_stream_complex_value(ngx_stream_session_t *s,
    ngx_stream_complex_value_t *val, ngx_str_t *value)
{
    size_t                         len;
    ngx_stream_script_code_pt      code;
    ngx_stream_script_engine_t     e;
    ngx_stream_script_len_code_pt  lcode;

    if (val->lengths == NULL) {
        *value = val->value;
        return NGX_OK;
    }

    ngx_stream_script_flush_complex_value(s, val);

    ngx_memzero(&e, sizeof(ngx_stream_script_engine_t));

    e.ip = val->lengths;
    e.session = s;
    e.flushed = 1;

    len = 0;

    while (*(uintptr_t *) e.ip) {
        lcode = *(ngx_stream_script_len_code_pt *) e.ip;
        len += lcode(&e);
    }

    value->len = len;
    value->data = ngx_pnalloc(s->connection->pool, len);
    if (value->data == NULL) {
        return NGX_ERROR;
    }

    e.ip = val->values;
    e.pos = value->data;
    e.buf = *value;

    while (*(uintptr_t *) e.ip) {
        code = *(ngx_stream_script_code_pt *) e.ip;
        code((ngx_stream_script_engine_t *) &e);
    }

    *value = e.buf;

    return NGX_OK;
}