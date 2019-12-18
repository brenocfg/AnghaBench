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
typedef  scalar_t__ BusTransport ;

/* Variables and functions */
 scalar_t__ BUS_TRANSPORT_LOCAL ; 
 int polkit_agent_open () ; 

int polkit_agent_open_if_enabled(BusTransport transport, bool ask_password) {

        /* Open the polkit agent as a child process if necessary */

        if (transport != BUS_TRANSPORT_LOCAL)
                return 0;

        if (!ask_password)
                return 0;

        return polkit_agent_open();
}