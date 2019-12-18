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
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_stream_ReadPartial (int /*<<< orphan*/ *,void*,size_t) ; 

ssize_t vlc_stream_Read(stream_t *s, void *buf, size_t len)
{
    size_t copied = 0;

    while (len > 0)
    {
        ssize_t ret = vlc_stream_ReadPartial(s, buf, len);
        if (ret < 0)
            continue;
        if (ret == 0)
            break;

        if (buf != NULL)
            buf = (char *)buf + ret;
        assert(len >= (size_t)ret);
        len -= ret;
        copied += ret;
    }

    return copied;
}