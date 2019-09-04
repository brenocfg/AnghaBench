#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_reqstat_rbnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_REQSTAT_REQ_FIELD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_atomic_fetch_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ngx_http_reqstat_count(void *data, off_t offset, ngx_int_t incr)
{
    ngx_http_reqstat_rbnode_t    *node = data;

    (void) ngx_atomic_fetch_add(NGX_HTTP_REQSTAT_REQ_FIELD(node, offset), incr);
}