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
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/ * p_socket ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int IO_DONE ; 
 scalar_t__ bind (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  socket_setblocking (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_setnonblocking (int /*<<< orphan*/ *) ; 

int socket_bind(p_socket ps, SA *addr, socklen_t len) {
    int err = IO_DONE;
    socket_setblocking(ps);
    if (bind(*ps, addr, len) < 0) err = errno; 
    socket_setnonblocking(ps);
    return err;
}