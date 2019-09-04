#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; scalar_t__ count; scalar_t__ code; } ;
typedef  TYPE_2__ ngx_http_status_t ;
struct TYPE_9__ {scalar_t__ state; TYPE_1__* upstream; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  process_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_scgi_module ; 
 int /*<<< orphan*/  ngx_http_scgi_process_status_line ; 

__attribute__((used)) static ngx_int_t
ngx_http_scgi_reinit_request(ngx_http_request_t *r)
{
    ngx_http_status_t  *status;

    status = ngx_http_get_module_ctx(r, ngx_http_scgi_module);

    if (status == NULL) {
        return NGX_OK;
    }

    status->code = 0;
    status->count = 0;
    status->start = NULL;
    status->end = NULL;

    r->upstream->process_header = ngx_http_scgi_process_status_line;
    r->state = 0;

    return NGX_OK;
}