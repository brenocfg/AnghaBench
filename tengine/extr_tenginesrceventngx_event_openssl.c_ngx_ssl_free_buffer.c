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
struct TYPE_7__ {TYPE_2__* ssl; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_6__ {TYPE_1__* buf; } ;
struct TYPE_5__ {int /*<<< orphan*/ * start; } ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ngx_ssl_free_buffer(ngx_connection_t *c)
{
    if (c->ssl->buf && c->ssl->buf->start) {
        if (ngx_pfree(c->pool, c->ssl->buf->start) == NGX_OK) {
            c->ssl->buf->start = NULL;
        }
    }
}