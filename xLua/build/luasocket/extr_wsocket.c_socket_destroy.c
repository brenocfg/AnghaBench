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
typedef  scalar_t__* p_socket ;

/* Variables and functions */
 scalar_t__ SOCKET_INVALID ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  socket_setblocking (scalar_t__*) ; 

void socket_destroy(p_socket ps) {
    if (*ps != SOCKET_INVALID) {
        socket_setblocking(ps); /* close can take a long time on WIN32 */
        closesocket(*ps);
        *ps = SOCKET_INVALID;
    }
}