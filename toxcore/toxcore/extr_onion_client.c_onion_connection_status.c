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
struct TYPE_3__ {scalar_t__ onion_connected; scalar_t__ UDP_connected; } ;
typedef  TYPE_1__ Onion_Client ;

/* Variables and functions */
 scalar_t__ ONION_CONNECTION_SECONDS ; 

unsigned int onion_connection_status(const Onion_Client *onion_c)
{
    if (onion_c->onion_connected >= ONION_CONNECTION_SECONDS) {
        if (onion_c->UDP_connected) {
            return 2;
        } else {
            return 1;
        }
    }

    return 0;
}