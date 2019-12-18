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
typedef  scalar_t__ socket_t ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LOGW (char*) ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  net_close (scalar_t__) ; 
 int /*<<< orphan*/  net_shutdown (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_socket(socket_t *socket) {
    SDL_assert(*socket != INVALID_SOCKET);
    net_shutdown(*socket, SHUT_RDWR);
    if (!net_close(*socket)) {
        LOGW("Could not close socket");
        return;
    }
    *socket = INVALID_SOCKET;
}