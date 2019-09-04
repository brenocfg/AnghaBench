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
typedef  int uint32_t ;
struct server {scalar_t__ device_socket; int tunnel_enabled; int /*<<< orphan*/  server_socket; int /*<<< orphan*/  tunnel_forward; int /*<<< orphan*/  local_port; } ;
typedef  scalar_t__ socket_t ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  close_socket (int /*<<< orphan*/ *) ; 
 scalar_t__ connect_to_server (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  disable_tunnel (struct server*) ; 
 scalar_t__ net_accept (int /*<<< orphan*/ ) ; 

socket_t
server_connect_to(struct server *server) {
    if (!server->tunnel_forward) {
        server->device_socket = net_accept(server->server_socket);
    } else {
        uint32_t attempts = 100;
        uint32_t delay = 100; // ms
        server->device_socket = connect_to_server(server->local_port, attempts,
                                                  delay);
    }

    if (server->device_socket == INVALID_SOCKET) {
        return INVALID_SOCKET;
    }

    if (!server->tunnel_forward) {
        // we don't need the server socket anymore
        close_socket(&server->server_socket);
    }

    // we don't need the adb tunnel anymore
    disable_tunnel(server); // ignore failure
    server->tunnel_enabled = false;

    return server->device_socket;
}