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

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_SERVER ; 
 int /*<<< orphan*/  socket_server_exit (int /*<<< orphan*/ ) ; 

void
skynet_socket_exit() {
	socket_server_exit(SOCKET_SERVER);
}