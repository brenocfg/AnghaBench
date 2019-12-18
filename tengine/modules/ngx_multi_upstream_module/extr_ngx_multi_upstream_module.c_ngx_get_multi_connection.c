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
typedef  int /*<<< orphan*/  ngx_multi_connection_t ;
struct TYPE_3__ {int /*<<< orphan*/ * multi_c; } ;
typedef  TYPE_1__ ngx_connection_t ;

/* Variables and functions */

ngx_multi_connection_t* 
ngx_get_multi_connection(ngx_connection_t *c)
{
    ngx_multi_connection_t  *multi_c;

    multi_c = c->multi_c;

    return multi_c;
}