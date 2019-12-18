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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socket_t ;

/* Variables and functions */
 int send (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
net_send_all(socket_t socket, const void *buf, size_t len) {
    ssize_t w = 0;
    while (len > 0) {
        w = send(socket, buf, len, 0);
        if (w == -1) {
            return -1;
        }
        len -= w;
        buf = (char *) buf + w;
    }
    return w;
}