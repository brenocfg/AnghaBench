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
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 

void kill_sock(sock_t sock)
{
#if defined(_WIN32) || defined(__WIN32__) || defined (WIN32)
    closesocket(sock);
#else
    close(sock);
#endif
}