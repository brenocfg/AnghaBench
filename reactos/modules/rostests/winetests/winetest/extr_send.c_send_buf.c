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
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int SOCKET_ERROR ; 
 int send (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_buf (SOCKET s, const char *buf, size_t length)
{
    int sent;

    while (length > 0) {
        sent = send (s, buf, length, 0);
        if (sent == SOCKET_ERROR) return 1;
        buf += sent;
        length -= sent;
    }
    return 0;
}