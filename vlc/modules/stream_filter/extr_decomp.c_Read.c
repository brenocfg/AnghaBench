#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  read_fd; } ;
typedef  TYPE_2__ stream_sys_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ vlc_read_i11e (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static ssize_t Read (stream_t *stream, void *buf, size_t buflen)
{
    stream_sys_t *sys = stream->p_sys;
    ssize_t val = vlc_read_i11e (sys->read_fd, buf, buflen);
    return (val >= 0) ? val : 0;
}