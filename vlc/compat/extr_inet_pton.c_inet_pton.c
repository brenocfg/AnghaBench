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
#define  AF_INET 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  errno ; 
 int sscanf (char const*,char*,unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 

int inet_pton (int af, const char *src, void *dst)
{
    unsigned char *b = dst;

    switch (af)
    {
        case AF_INET:
            return sscanf (src, "%hhu.%hhu.%hhu.%hhu",
                           b + 0, b + 1, b + 2, b + 3) == 4;
    }
    errno = EAFNOSUPPORT;
    return -1;
}