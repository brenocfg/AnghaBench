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
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  SHUT_RD ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  setmode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int vlc_pipe (int fds[2])
{
    if (vlc_socketpair (AF_LOCAL, SOCK_STREAM, 0, fds, false))
        return -1;

    shutdown (fds[0], SHUT_WR);
    shutdown (fds[1], SHUT_RD);

    setmode (fds[0], O_BINARY);
    setmode (fds[1], O_BINARY);

    return 0;
}