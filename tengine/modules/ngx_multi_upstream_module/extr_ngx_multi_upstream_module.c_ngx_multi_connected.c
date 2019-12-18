#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  connected; } ;
typedef  TYPE_1__ ngx_multi_connection_t ;
typedef  int /*<<< orphan*/  ngx_flag_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;

/* Variables and functions */
 TYPE_1__* ngx_get_multi_connection (int /*<<< orphan*/ *) ; 

ngx_flag_t 
ngx_multi_connected(ngx_connection_t *c)
{
    ngx_multi_connection_t  *multi_c;

    multi_c = ngx_get_multi_connection(c);

    return multi_c->connected;
}