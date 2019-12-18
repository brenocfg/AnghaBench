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
 int /*<<< orphan*/  EPERM ; 
 int O_BINARY ; 
 int O_NOINHERIT ; 
 int _pipe (int*,int,int) ; 
 int /*<<< orphan*/  _set_errno (int /*<<< orphan*/ ) ; 

int vlc_pipe (int fds[2])
{
#if VLC_WINSTORE_APP
    _set_errno(EPERM);
    return -1;
#else
    return _pipe (fds, 32768, O_NOINHERIT | O_BINARY);
#endif
}