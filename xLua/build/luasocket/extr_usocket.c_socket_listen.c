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
typedef  int /*<<< orphan*/ * p_socket ;

/* Variables and functions */
 int IO_DONE ; 
 int errno ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_setblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 

int socket_listen(p_socket ps, int backlog) {
    int err = IO_DONE; 
    socket_setblocking(ps);
    if (listen(*ps, backlog)) err = errno; 
    socket_setnonblocking(ps);
    return err;
}