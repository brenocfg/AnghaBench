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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  recv (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
net_recv_all(socket_t socket, void *buf, size_t len) {
    return recv(socket, buf, len, MSG_WAITALL);
}