#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_18__ {TYPE_3__* connection; TYPE_2__* variables; } ;
typedef  TYPE_4__ ngx_stream_session_t ;
typedef  scalar_t__ (* ngx_stream_script_len_code_pt ) (TYPE_5__*) ;
struct TYPE_19__ {int flushed; int /*<<< orphan*/ * pos; void* ip; TYPE_4__* session; } ;
typedef  TYPE_5__ ngx_stream_script_engine_t ;
typedef  int /*<<< orphan*/  (* ngx_stream_script_code_pt ) (TYPE_5__*) ;
struct TYPE_15__ {size_t nelts; } ;
struct TYPE_20__ {TYPE_1__ variables; } ;
typedef  TYPE_8__ ngx_stream_core_main_conf_t ;
struct TYPE_21__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_9__ ngx_str_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; } ;
struct TYPE_16__ {scalar_t__ not_found; scalar_t__ valid; scalar_t__ no_cacheable; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 TYPE_8__* ngx_stream_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 

u_char *
ngx_stream_script_run(ngx_stream_session_t *s, ngx_str_t *value,
    void *code_lengths, size_t len, void *code_values)
{
    ngx_uint_t                      i;
    ngx_stream_script_code_pt       code;
    ngx_stream_script_engine_t      e;
    ngx_stream_core_main_conf_t    *cmcf;
    ngx_stream_script_len_code_pt   lcode;

    cmcf = ngx_stream_get_module_main_conf(s, ngx_stream_core_module);

    for (i = 0; i < cmcf->variables.nelts; i++) {
        if (s->variables[i].no_cacheable) {
            s->variables[i].valid = 0;
            s->variables[i].not_found = 0;
        }
    }

    ngx_memzero(&e, sizeof(ngx_stream_script_engine_t));

    e.ip = code_lengths;
    e.session = s;
    e.flushed = 1;

    while (*(uintptr_t *) e.ip) {
        lcode = *(ngx_stream_script_len_code_pt *) e.ip;
        len += lcode(&e);
    }


    value->len = len;
    value->data = ngx_pnalloc(s->connection->pool, len);
    if (value->data == NULL) {
        return NULL;
    }

    e.ip = code_values;
    e.pos = value->data;

    while (*(uintptr_t *) e.ip) {
        code = *(ngx_stream_script_code_pt *) e.ip;
        code((ngx_stream_script_engine_t *) &e);
    }

    return e.pos;
}