#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {scalar_t__ hash; TYPE_5__ value; TYPE_3__ key; } ;
typedef  TYPE_4__ ngx_table_elt_t ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_16__ {size_t nelts; TYPE_4__* elts; struct TYPE_16__* next; } ;
typedef  TYPE_6__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_6__ part; } ;
struct TYPE_12__ {TYPE_1__ headers; } ;
struct TYPE_17__ {TYPE_2__ headers_in; } ;
typedef  TYPE_7__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

ngx_int_t
ngx_http_tfs_parse_headerin(ngx_http_request_t *r, ngx_str_t *header_name,
    ngx_str_t *value)
{
    ngx_uint_t        i;
    ngx_list_part_t  *part;
    ngx_table_elt_t  *header;

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

        if (header[i].hash == 0) {
            continue;
        }

        if (header_name->len ==  header[i].key.len
            && ngx_strncasecmp(header[i].key.data, header_name->data,
                               header_name->len) == 0)
        {
            *value = header[i].value;
            return NGX_OK;
        }
    }

    return NGX_DECLINED;
}