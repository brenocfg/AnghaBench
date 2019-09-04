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
struct server {scalar_t__ server_socket; scalar_t__ device_socket; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_socket (scalar_t__*) ; 

void
server_destroy(struct server *server) {
    if (server->server_socket != INVALID_SOCKET) {
        close_socket(&server->server_socket);
    }
    if (server->device_socket != INVALID_SOCKET) {
        close_socket(&server->device_socket);
    }
    SDL_free(server->serial);
}