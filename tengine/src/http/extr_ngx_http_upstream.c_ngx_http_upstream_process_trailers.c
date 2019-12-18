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
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {int /*<<< orphan*/  len; } ;
struct TYPE_18__ {TYPE_4__ key; int /*<<< orphan*/  lowcase_key; int /*<<< orphan*/  hash; } ;
typedef  TYPE_6__ ngx_table_elt_t ;
struct TYPE_19__ {size_t nelts; TYPE_6__* elts; struct TYPE_19__* next; } ;
typedef  TYPE_7__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_7__ part; } ;
struct TYPE_14__ {TYPE_1__ trailers; } ;
struct TYPE_20__ {TYPE_3__* conf; TYPE_2__ headers_in; } ;
typedef  TYPE_8__ ngx_http_upstream_t ;
struct TYPE_17__ {int /*<<< orphan*/  trailers; } ;
struct TYPE_21__ {TYPE_5__ headers_out; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_15__ {int /*<<< orphan*/  hide_headers_hash; int /*<<< orphan*/  pass_trailers; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_list_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_trailers(ngx_http_request_t *r,
    ngx_http_upstream_t *u)
{
    ngx_uint_t        i;
    ngx_list_part_t  *part;
    ngx_table_elt_t  *h, *ho;

    if (!u->conf->pass_trailers) {
        return NGX_OK;
    }

    part = &u->headers_in.trailers.part;
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

        if (ngx_hash_find(&u->conf->hide_headers_hash, h[i].hash,
                          h[i].lowcase_key, h[i].key.len))
        {
            continue;
        }

        ho = ngx_list_push(&r->headers_out.trailers);
        if (ho == NULL) {
            return NGX_ERROR;
        }

        *ho = h[i];
    }

    return NGX_OK;
}