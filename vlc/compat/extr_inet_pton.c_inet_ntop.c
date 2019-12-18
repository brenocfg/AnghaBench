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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned char const,unsigned char const,unsigned char const,unsigned char const) ; 

const char *inet_ntop (int af, const void *src, char *dst, socklen_t len)
{
    const unsigned char *b = src;

    switch (af)
    {
        case AF_INET:
            if (snprintf (dst, len, "%hhu.%hhu.%hhu.%hhu",
                          b[0], b[1], b[2], b[3]) >= len)
            {
                errno = ENOSPC;
                return NULL;
            }
            return dst;
    }
    errno = EAFNOSUPPORT;
    return NULL;
}