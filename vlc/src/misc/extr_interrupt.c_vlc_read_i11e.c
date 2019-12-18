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
struct iovec {void* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_readv_i11e (int,struct iovec*,int) ; 

ssize_t vlc_read_i11e(int fd, void *buf, size_t count)
{
    struct iovec iov = { .iov_base = buf, .iov_len = count };
    return vlc_readv_i11e(fd, &iov, 1);
}