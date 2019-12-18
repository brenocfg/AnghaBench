#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {TYPE_6__ value; TYPE_4__ key; int /*<<< orphan*/  lowcase_key; } ;
typedef  TYPE_7__ ngx_table_elt_t ;
struct TYPE_21__ {size_t nelts; TYPE_7__* elts; struct TYPE_21__* next; } ;
typedef  TYPE_8__ ngx_list_part_t ;
struct TYPE_14__ {TYPE_8__ part; } ;
struct TYPE_15__ {TYPE_1__ headers; } ;
struct TYPE_22__ {TYPE_2__ headers_in; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_18__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_16__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_5__ value; TYPE_3__ key; } ;
typedef  TYPE_10__ ngx_http_lua_ffi_table_elt_t ;

/* Variables and functions */
 int NGX_OK ; 

int
ngx_http_lua_ffi_req_get_headers(ngx_http_request_t *r,
    ngx_http_lua_ffi_table_elt_t *out, int count, int raw)
{
    int                           n;
    ngx_uint_t                    i;
    ngx_list_part_t              *part;
    ngx_table_elt_t              *header;

    if (count <= 0) {
        return NGX_OK;
    }

    n = 0;
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

        if (raw) {
            out[n].key.data = header[i].key.data;
            out[n].key.len = (int) header[i].key.len;

        } else {
            out[n].key.data = header[i].lowcase_key;
            out[n].key.len = (int) header[i].key.len;
        }

        out[n].value.data = header[i].value.data;
        out[n].value.len = (int) header[i].value.len;

        if (++n == count) {
            return NGX_OK;
        }
    }

    return NGX_OK;
}