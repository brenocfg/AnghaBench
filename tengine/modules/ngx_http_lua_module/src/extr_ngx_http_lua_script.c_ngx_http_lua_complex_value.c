#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  pool; TYPE_2__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
typedef  scalar_t__ (* ngx_http_lua_script_len_code_pt ) (TYPE_5__*) ;
struct TYPE_17__ {int ncaptures; int* captures; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * captures_data; int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_http_lua_script_engine_t ;
typedef  int /*<<< orphan*/  (* ngx_http_lua_script_code_pt ) (TYPE_5__*) ;
struct TYPE_13__ {size_t len; scalar_t__ data; } ;
struct TYPE_18__ {int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; TYPE_1__ value; } ;
typedef  TYPE_8__ ngx_http_lua_complex_value_t ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_OK ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

ngx_int_t
ngx_http_lua_complex_value(ngx_http_request_t *r, ngx_str_t *subj,
    size_t offset, ngx_int_t count, int *cap,
    ngx_http_lua_complex_value_t *val, luaL_Buffer *luabuf)
{
    size_t                            len;
    u_char                           *p;
    ngx_http_lua_script_code_pt       code;
    ngx_http_lua_script_len_code_pt   lcode;
    ngx_http_lua_script_engine_t      e;

    if (val->lengths == NULL) {
        luaL_addlstring(luabuf, (char *) &subj->data[offset], cap[0] - offset);
        luaL_addlstring(luabuf, (char *) val->value.data, val->value.len);

        return NGX_OK;
    }

    ngx_memzero(&e, sizeof(ngx_http_lua_script_engine_t));

    e.log = r->connection->log;
    e.ncaptures = count * 2;
    e.captures = cap;
    e.captures_data = subj->data;

    e.ip = val->lengths;

    len = 0;

    while (*(uintptr_t *) e.ip) {
        lcode = *(ngx_http_lua_script_len_code_pt *) e.ip;
        len += lcode(&e);
    }

    p = ngx_pnalloc(r->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    e.ip = val->values;
    e.pos = p;

    while (*(uintptr_t *) e.ip) {
        code = *(ngx_http_lua_script_code_pt *) e.ip;
        code((ngx_http_lua_script_engine_t *) &e);
    }

    luaL_addlstring(luabuf, (char *) &subj->data[offset], cap[0] - offset);
    luaL_addlstring(luabuf, (char *) p, len);

    ngx_pfree(r->pool, p);

    return NGX_OK;
}