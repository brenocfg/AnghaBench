#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_20__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/ * last; } ;
struct TYPE_19__ {TYPE_3__ headers; } ;
struct TYPE_17__ {int status; } ;
struct TYPE_21__ {TYPE_4__ headers_in; TYPE_2__ headers_out; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_16__ {scalar_t__ len; int data; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* handler ) (TYPE_6__*,TYPE_8__*,TYPE_5__*) ;scalar_t__ offset; TYPE_1__ name; } ;
typedef  TYPE_7__ ngx_http_lua_set_header_t ;
struct TYPE_23__ {int no_override; int /*<<< orphan*/  (* handler ) (TYPE_6__*,TYPE_8__*,TYPE_5__*) ;scalar_t__ offset; TYPE_5__ key; int /*<<< orphan*/  hash; } ;
typedef  TYPE_8__ ngx_http_lua_header_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  dd (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_hash_key_lc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_7__* ngx_http_lua_set_handlers ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_8__*,TYPE_5__*) ; 

ngx_int_t
ngx_http_lua_set_input_header(ngx_http_request_t *r, ngx_str_t key,
    ngx_str_t value, unsigned override)
{
    ngx_http_lua_header_val_t         hv;
    ngx_http_lua_set_header_t        *handlers = ngx_http_lua_set_handlers;

    ngx_uint_t                        i;

    dd("set header value: %.*s", (int) value.len, value.data);

    hv.hash = ngx_hash_key_lc(key.data, key.len);
    hv.key = key;

    hv.offset = 0;
    hv.no_override = !override;
    hv.handler = NULL;

    for (i = 0; handlers[i].name.len; i++) {
        if (hv.key.len != handlers[i].name.len
            || ngx_strncasecmp(hv.key.data, handlers[i].name.data,
                               handlers[i].name.len) != 0)
        {
            dd("hv key comparison: %s <> %s", handlers[i].name.data,
               hv.key.data);

            continue;
        }

        dd("Matched handler: %s %s", handlers[i].name.data, hv.key.data);

        hv.offset = handlers[i].offset;
        hv.handler = handlers[i].handler;

        break;
    }

    if (handlers[i].name.len == 0 && handlers[i].handler) {
        hv.offset = handlers[i].offset;
        hv.handler = handlers[i].handler;
    }

#if 1
    if (hv.handler == NULL) {
        return NGX_ERROR;
    }
#endif

    if (r->headers_out.status == 400 || r->headers_in.headers.last == NULL) {
        /* must be a 400 Bad Request */
        return NGX_OK;
    }

    return hv.handler(r, &hv, &value);
}