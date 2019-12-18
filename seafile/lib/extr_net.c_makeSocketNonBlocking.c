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
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_SOCKET_ERROR () ; 
 int /*<<< orphan*/  ccnet_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 scalar_t__ evutil_make_socket_nonblocking (scalar_t__) ; 
 int /*<<< orphan*/  evutil_socket_error_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static evutil_socket_t
makeSocketNonBlocking (evutil_socket_t fd)
{
    if (fd >= 0)
    {
        if (evutil_make_socket_nonblocking(fd))
        {
            ccnet_warning ("Couldn't make socket nonblock: %s",
                           evutil_socket_error_to_string(EVUTIL_SOCKET_ERROR()));
            evutil_closesocket(fd);
            fd = -1;
        }
    }
    return fd;
}