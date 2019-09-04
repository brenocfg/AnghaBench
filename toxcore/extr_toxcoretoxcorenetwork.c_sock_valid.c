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
typedef  scalar_t__ sock_t ;

/* Variables and functions */

int sock_valid(sock_t sock)
{
#if defined(_WIN32) || defined(__WIN32__) || defined (WIN32)

    if (sock == INVALID_SOCKET) {
#else

    if (sock < 0) {
#endif
        return 0;
    }

    return 1;
}