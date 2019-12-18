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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  socket_t ;
typedef  int /*<<< orphan*/  csin ;
typedef  int /*<<< orphan*/  SOCKADDR_IN ;
typedef  int /*<<< orphan*/  SOCKADDR ;

/* Variables and functions */
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

socket_t
net_accept(socket_t server_socket) {
    SOCKADDR_IN csin;
    socklen_t sinsize = sizeof(csin);
    return accept(server_socket, (SOCKADDR *) &csin, &sinsize);
}