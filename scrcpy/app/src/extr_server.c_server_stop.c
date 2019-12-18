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
struct server {scalar_t__ server_socket; scalar_t__ video_socket; scalar_t__ control_socket; scalar_t__ process; scalar_t__ tunnel_enabled; } ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LOGD (char*) ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 scalar_t__ PROCESS_NONE ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  close_socket (scalar_t__*) ; 
 int /*<<< orphan*/  cmd_simple_wait (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_terminate (scalar_t__) ; 
 int /*<<< orphan*/  disable_tunnel (struct server*) ; 

void
server_stop(struct server *server) {
    if (server->server_socket != INVALID_SOCKET) {
        close_socket(&server->server_socket);
    }
    if (server->video_socket != INVALID_SOCKET) {
        close_socket(&server->video_socket);
    }
    if (server->control_socket != INVALID_SOCKET) {
        close_socket(&server->control_socket);
    }

    SDL_assert(server->process != PROCESS_NONE);

    if (!cmd_terminate(server->process)) {
        LOGW("Could not terminate server");
    }

    cmd_simple_wait(server->process, NULL); // ignore exit code
    LOGD("Server terminated");

    if (server->tunnel_enabled) {
        // ignore failure
        disable_tunnel(server);
    }
}