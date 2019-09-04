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
struct TYPE_3__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ IP_Port ;

/* Variables and functions */
 int ip_isset (int /*<<< orphan*/ *) ; 

int ipport_isset(const IP_Port *ipport)
{
    if (!ipport)
        return 0;

    if (!ipport->port)
        return 0;

    return ip_isset(&ipport->ip);
}