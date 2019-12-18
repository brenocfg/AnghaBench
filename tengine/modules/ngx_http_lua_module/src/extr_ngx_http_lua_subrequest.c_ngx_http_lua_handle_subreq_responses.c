#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_31__ {int len; scalar_t__ data; } ;
struct TYPE_30__ {int len; scalar_t__ data; } ;
struct TYPE_32__ {scalar_t__ hash; TYPE_8__ value; TYPE_7__ key; } ;
typedef  TYPE_9__ ngx_table_elt_t ;
struct TYPE_18__ {int len; scalar_t__ data; } ;
typedef  TYPE_10__ ngx_str_t ;
struct TYPE_19__ {size_t nelts; TYPE_9__* elts; struct TYPE_19__* next; } ;
typedef  TYPE_11__ ngx_list_part_t ;
struct TYPE_28__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_20__ {int /*<<< orphan*/  pool; TYPE_5__ uri; TYPE_4__* connection; } ;
typedef  TYPE_12__ ngx_http_request_t ;
struct TYPE_21__ {TYPE_14__* cur_co_ctx; } ;
typedef  TYPE_13__ ngx_http_lua_ctx_t ;
struct TYPE_22__ {size_t nsubreqs; int* sr_flags; TYPE_15__** sr_headers; TYPE_10__* sr_bodies; int /*<<< orphan*/ * sr_statuses; scalar_t__ pending_subreqs; int /*<<< orphan*/ * co; } ;
typedef  TYPE_14__ ngx_http_lua_co_ctx_t ;
struct TYPE_24__ {int len; scalar_t__ data; } ;
struct TYPE_29__ {TYPE_11__ part; } ;
struct TYPE_23__ {scalar_t__ content_length_n; int last_modified_time; scalar_t__ status; int /*<<< orphan*/ * last_modified; TYPE_3__* location; int /*<<< orphan*/ * content_length; TYPE_1__ content_type; TYPE_6__ headers; } ;
typedef  TYPE_15__ ngx_http_headers_out_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_27__ {int /*<<< orphan*/  log; } ;
struct TYPE_25__ {int len; scalar_t__ data; } ;
struct TYPE_26__ {TYPE_2__ value; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_SUBREQ_TRUNCATED ; 
 scalar_t__ NGX_HTTP_NOT_MODIFIED ; 
 scalar_t__ NGX_HTTP_NO_CONTENT ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_PARTIAL_CONTENT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_time (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ngx_http_lua_handle_subreq_responses(ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx)
{
    ngx_uint_t                   i, count;
    ngx_uint_t                   index;
    lua_State                   *co;
    ngx_str_t                   *body_str;
    ngx_table_elt_t             *header;
    ngx_list_part_t             *part;
    ngx_http_headers_out_t      *sr_headers;
    ngx_http_lua_co_ctx_t       *coctx;

    u_char                  buf[sizeof("Mon, 28 Sep 1970 06:00:00 GMT") - 1];

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua handle subrequest responses");

    coctx = ctx->cur_co_ctx;
    co = coctx->co;

    for (index = 0; index < coctx->nsubreqs; index++) {
        dd("summary: reqs %d, subquery %d, pending %d, req %.*s",
           (int) coctx->nsubreqs,
           (int) index,
           (int) coctx->pending_subreqs,
           (int) r->uri.len, r->uri.data);

        /*  {{{ construct ret value */
        lua_createtable(co, 0 /* narr */, 4 /* nrec */);

        /*  copy captured status */
        lua_pushinteger(co, coctx->sr_statuses[index]);
        lua_setfield(co, -2, "status");

        dd("captured subrequest flags: %d", (int) coctx->sr_flags[index]);

        /* set truncated flag if truncation happens */
        if (coctx->sr_flags[index] & NGX_HTTP_LUA_SUBREQ_TRUNCATED) {
            lua_pushboolean(co, 1);
            lua_setfield(co, -2, "truncated");

        } else {
            lua_pushboolean(co, 0);
            lua_setfield(co, -2, "truncated");
        }

        /*  copy captured body */

        body_str = &coctx->sr_bodies[index];

        lua_pushlstring(co, (char *) body_str->data, body_str->len);
        lua_setfield(co, -2, "body");

        if (body_str->data) {
            dd("free body buffer ASAP");
            ngx_pfree(r->pool, body_str->data);
        }

        /* copy captured headers */

        sr_headers = coctx->sr_headers[index];

        part = &sr_headers->headers.part;
        count = part->nelts;
        while (part->next) {
            part = part->next;
            count += part->nelts;
        }

        lua_createtable(co, 0, count + 5); /* res.header */

        dd("saving subrequest response headers");

        part = &sr_headers->headers.part;
        header = part->elts;

        for (i = 0; /* void */; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                header = part->elts;
                i = 0;
            }

            dd("checking sr header %.*s", (int) header[i].key.len,
               header[i].key.data);

#if 1
            if (header[i].hash == 0) {
                continue;
            }
#endif

            header[i].hash = 0;

            dd("pushing sr header %.*s", (int) header[i].key.len,
               header[i].key.data);

            lua_pushlstring(co, (char *) header[i].key.data,
                            header[i].key.len); /* header key */
            lua_pushvalue(co, -1); /* stack: table key key */

            /* check if header already exists */
            lua_rawget(co, -3); /* stack: table key value */

            if (lua_isnil(co, -1)) {
                lua_pop(co, 1); /* stack: table key */

                lua_pushlstring(co, (char *) header[i].value.data,
                                header[i].value.len);
                    /* stack: table key value */

                lua_rawset(co, -3); /* stack: table */

            } else {

                if (!lua_istable(co, -1)) { /* already inserted one value */
                    lua_createtable(co, 4, 0);
                        /* stack: table key value table */

                    lua_insert(co, -2); /* stack: table key table value */
                    lua_rawseti(co, -2, 1); /* stack: table key table */

                    lua_pushlstring(co, (char *) header[i].value.data,
                                    header[i].value.len);
                        /* stack: table key table value */

                    lua_rawseti(co, -2, lua_objlen(co, -2) + 1);
                        /* stack: table key table */

                    lua_rawset(co, -3); /* stack: table */

                } else {
                    lua_pushlstring(co, (char *) header[i].value.data,
                                    header[i].value.len);
                        /* stack: table key table value */

                    lua_rawseti(co, -2, lua_objlen(co, -2) + 1);
                        /* stack: table key table */

                    lua_pop(co, 2); /* stack: table */
                }
            }
        }

        if (sr_headers->content_type.len) {
            lua_pushliteral(co, "Content-Type"); /* header key */
            lua_pushlstring(co, (char *) sr_headers->content_type.data,
                            sr_headers->content_type.len); /* head key value */
            lua_rawset(co, -3); /* head */
        }

        if (sr_headers->content_length == NULL
            && sr_headers->content_length_n >= 0)
        {
            lua_pushliteral(co, "Content-Length"); /* header key */

            lua_pushnumber(co, (lua_Number) sr_headers->content_length_n);
                /* head key value */

            lua_rawset(co, -3); /* head */
        }

        /* to work-around an issue in ngx_http_static_module
         * (github issue #41) */
        if (sr_headers->location && sr_headers->location->value.len) {
            lua_pushliteral(co, "Location"); /* header key */
            lua_pushlstring(co, (char *) sr_headers->location->value.data,
                            sr_headers->location->value.len);
            /* head key value */
            lua_rawset(co, -3); /* head */
        }

        if (sr_headers->last_modified_time != -1) {
            if (sr_headers->status != NGX_HTTP_OK
                && sr_headers->status != NGX_HTTP_PARTIAL_CONTENT
                && sr_headers->status != NGX_HTTP_NOT_MODIFIED
                && sr_headers->status != NGX_HTTP_NO_CONTENT)
            {
                sr_headers->last_modified_time = -1;
                sr_headers->last_modified = NULL;
            }
        }

        if (sr_headers->last_modified == NULL
            && sr_headers->last_modified_time != -1)
        {
            (void) ngx_http_time(buf, sr_headers->last_modified_time);

            lua_pushliteral(co, "Last-Modified"); /* header key */
            lua_pushlstring(co, (char *) buf, sizeof(buf)); /* head key value */
            lua_rawset(co, -3); /* head */
        }

        lua_setfield(co, -2, "header");

        /*  }}} */
    }
}