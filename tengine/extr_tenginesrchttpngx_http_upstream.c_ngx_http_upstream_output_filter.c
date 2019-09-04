#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  aio; TYPE_1__* upstream; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  aio; } ;
typedef  TYPE_3__ ngx_event_pipe_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_5__ {TYPE_3__* pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_output_filter (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_output_filter(void *data, ngx_chain_t *chain)
{
    ngx_int_t            rc;
    ngx_event_pipe_t    *p;
    ngx_http_request_t  *r;

    r = data;
    p = r->upstream->pipe;

    rc = ngx_http_output_filter(r, chain);

    p->aio = r->aio;

    return rc;
}