#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_22__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_21__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_23__ {scalar_t__ hash; TYPE_7__ value; TYPE_6__ key; } ;
typedef  TYPE_8__ ngx_table_elt_t ;
struct TYPE_24__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_9__ ngx_str_t ;
struct TYPE_14__ {size_t nelts; TYPE_8__* elts; struct TYPE_14__* next; } ;
typedef  TYPE_10__ ngx_list_part_t ;
struct TYPE_19__ {TYPE_10__ part; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_20__ {TYPE_4__ headers; TYPE_3__* location; TYPE_1__ content_type; int /*<<< orphan*/  content_length_n; int /*<<< orphan*/ * content_length; } ;
struct TYPE_15__ {TYPE_5__ headers_out; } ;
typedef  TYPE_11__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;
struct TYPE_17__ {char* data; scalar_t__ len; } ;
struct TYPE_18__ {int /*<<< orphan*/  key; int /*<<< orphan*/  hash; TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd (char*,...) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  ngx_http_lua_location_hash ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
ngx_http_lua_get_output_header(lua_State *L, ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx, ngx_str_t *key)
{
    ngx_table_elt_t            *h;
    ngx_list_part_t            *part;
    ngx_uint_t                  i;
    unsigned                    found;

    dd("looking for response header \"%.*s\"", (int) key->len, key->data);

    switch (key->len) {
    case 14:
        if (r->headers_out.content_length == NULL
            && r->headers_out.content_length_n >= 0
            && ngx_strncasecmp(key->data, (u_char *) "Content-Length", 14) == 0)
        {
            lua_pushinteger(L, (lua_Integer) r->headers_out.content_length_n);
            return 1;
        }

        break;

    case 12:
        if (ngx_strncasecmp(key->data, (u_char *) "Content-Type", 12) == 0
            && r->headers_out.content_type.len)
        {
            lua_pushlstring(L, (char *) r->headers_out.content_type.data,
                            r->headers_out.content_type.len);
            return 1;
        }

        break;

    default:
        break;
    }

    dd("not a built-in output header");

    found = 0;

#if 1
    if (r->headers_out.location
        && r->headers_out.location->value.len
        && r->headers_out.location->value.data[0] == '/')
    {
        /* XXX ngx_http_core_find_config_phase, for example,
         * may not initialize the "key" and "hash" fields
         * for a nasty optimization purpose, and
         * we have to work-around it here */

        r->headers_out.location->hash = ngx_http_lua_location_hash;
        ngx_str_set(&r->headers_out.location->key, "Location");
    }
#endif

    part = &r->headers_out.headers.part;
    h = part->elts;

    for (i = 0; /* void */; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            h = part->elts;
            i = 0;
        }

        if (h[i].hash == 0) {
            continue;
        }

        if (h[i].hash != 0
            && h[i].key.len == key->len
            && ngx_strncasecmp(key->data, h[i].key.data, h[i].key.len) == 0)
         {
             if (!found) {
                 found = 1;

                 lua_pushlstring(L, (char *) h[i].value.data, h[i].value.len);
                 continue;
             }

             if (found == 1) {
                 lua_createtable(L, 4 /* narr */, 0);
                 lua_insert(L, -2);
                 lua_rawseti(L, -2, found);
             }

             found++;

             lua_pushlstring(L, (char *) h[i].value.data, h[i].value.len);
             lua_rawseti(L, -2, found);
         }
    }

    if (found) {
        return 1;
    }

    lua_pushnil(L);
    return 1;
}