#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_17__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_16__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_12__ {TYPE_8__ value; TYPE_7__ key; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
struct TYPE_13__ {size_t nelts; TYPE_2__* elts; struct TYPE_13__* next; } ;
typedef  TYPE_3__ ngx_list_part_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {TYPE_3__ part; } ;
struct TYPE_11__ {TYPE_5__ headers; } ;
struct TYPE_14__ {TYPE_1__ headers_in; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dd (char*,int,...) ; 
 scalar_t__ ngx_http_lua_set_input_header (TYPE_4__*,TYPE_7__,TYPE_8__,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_list_init (TYPE_5__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_copy_request_headers(ngx_http_request_t *sr, ngx_http_request_t *r)
{
    ngx_table_elt_t                 *header;
    ngx_list_part_t                 *part;
    ngx_uint_t                       i;

    if (ngx_list_init(&sr->headers_in.headers, sr->pool, 20,
                      sizeof(ngx_table_elt_t)) != NGX_OK)
    {
        return NGX_ERROR;
    }

    dd("before: parent req headers count: %d",
       (int) r->headers_in.headers.part.nelts);

    part = &r->headers_in.headers.part;
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

        dd("setting request header %.*s: %.*s", (int) header[i].key.len,
           header[i].key.data, (int) header[i].value.len,
           header[i].value.data);

        if (ngx_http_lua_set_input_header(sr, header[i].key,
                                          header[i].value, 0) == NGX_ERROR)
        {
            return NGX_ERROR;
        }
    }

    dd("after: parent req headers count: %d",
       (int) r->headers_in.headers.part.nelts);

    return NGX_OK;
}