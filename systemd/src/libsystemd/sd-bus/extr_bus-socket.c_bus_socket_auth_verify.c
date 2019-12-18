#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ is_server; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_socket_auth_verify_client (TYPE_1__*) ; 
 int bus_socket_auth_verify_server (TYPE_1__*) ; 

__attribute__((used)) static int bus_socket_auth_verify(sd_bus *b) {
        assert(b);

        if (b->is_server)
                return bus_socket_auth_verify_server(b);
        else
                return bus_socket_auth_verify_client(b);
}