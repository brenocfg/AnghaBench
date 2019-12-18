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
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ _chsize (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
truncate0(int i_fd)
{
#ifndef _WIN32
    return ftruncate(i_fd, 0) == 0 ? VLC_SUCCESS : VLC_EGENERIC;
#else
    return _chsize(i_fd, 0) == 0 ? VLC_SUCCESS : VLC_EGENERIC;
#endif
}