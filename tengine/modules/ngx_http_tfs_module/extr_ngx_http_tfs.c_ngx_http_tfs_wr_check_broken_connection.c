#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_5__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_tfs_check_broken_connection (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_tfs_wr_check_broken_connection(ngx_http_request_t *r)
{
    ngx_http_tfs_check_broken_connection(r, r->connection->write);
}