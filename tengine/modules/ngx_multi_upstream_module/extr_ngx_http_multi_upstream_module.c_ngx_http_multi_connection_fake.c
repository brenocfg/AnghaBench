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
struct TYPE_7__ {scalar_t__ connection; TYPE_2__* upstream; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int ngx_flag_t ;
struct TYPE_5__ {scalar_t__ connection; } ;
struct TYPE_6__ {TYPE_1__ peer; } ;

/* Variables and functions */

ngx_flag_t
ngx_http_multi_connection_fake(ngx_http_request_t *r) 
{
    return r->upstream->peer.connection == r->connection;
}