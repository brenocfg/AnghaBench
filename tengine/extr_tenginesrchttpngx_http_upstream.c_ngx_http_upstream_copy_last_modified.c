#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  last_modified_time; int /*<<< orphan*/ * last_modified; int /*<<< orphan*/  headers; } ;
struct TYPE_9__ {TYPE_3__* upstream; TYPE_1__ headers_out; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  last_modified_time; } ;
struct TYPE_8__ {TYPE_2__ headers_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_list_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_copy_last_modified(ngx_http_request_t *r, ngx_table_elt_t *h,
    ngx_uint_t offset)
{
    ngx_table_elt_t  *ho;

    ho = ngx_list_push(&r->headers_out.headers);
    if (ho == NULL) {
        return NGX_ERROR;
    }

    *ho = *h;

    r->headers_out.last_modified = ho;
    r->headers_out.last_modified_time =
                                    r->upstream->headers_in.last_modified_time;

    return NGX_OK;
}