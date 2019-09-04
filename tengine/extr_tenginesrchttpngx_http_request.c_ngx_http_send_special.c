#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  post_action; struct TYPE_8__* main; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/ * next; TYPE_3__* buf; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_10__ {int last_buf; int sync; int last_in_chain; int flush; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_FLUSH ; 
 int NGX_HTTP_LAST ; 
 TYPE_3__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_output_filter (TYPE_1__*,TYPE_2__*) ; 

ngx_int_t
ngx_http_send_special(ngx_http_request_t *r, ngx_uint_t flags)
{
    ngx_buf_t    *b;
    ngx_chain_t   out;

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NGX_ERROR;
    }

    if (flags & NGX_HTTP_LAST) {

        if (r == r->main && !r->post_action) {
            b->last_buf = 1;

        } else {
            b->sync = 1;
            b->last_in_chain = 1;
        }
    }

    if (flags & NGX_HTTP_FLUSH) {
        b->flush = 1;
    }

    out.buf = b;
    out.next = NULL;

    return ngx_http_output_filter(r, &out);
}