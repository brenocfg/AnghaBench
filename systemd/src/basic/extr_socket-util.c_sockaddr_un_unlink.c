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
struct sockaddr_un {scalar_t__ sun_family; scalar_t__* sun_path; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  assert (struct sockaddr_un const*) ; 
 int errno ; 
 char* memchr (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 char* memdupa_suffix0 (char*,int) ; 
 scalar_t__ unlink (char const*) ; 

int sockaddr_un_unlink(const struct sockaddr_un *sa) {
        const char *p, * nul;

        assert(sa);

        if (sa->sun_family != AF_UNIX)
                return -EPROTOTYPE;

        if (sa->sun_path[0] == 0) /* Nothing to do for abstract sockets */
                return 0;

        /* The path in .sun_path is not necessarily NUL terminated. Let's fix that. */
        nul = memchr(sa->sun_path, 0, sizeof(sa->sun_path));
        if (nul)
                p = sa->sun_path;
        else
                p = memdupa_suffix0(sa->sun_path, sizeof(sa->sun_path));

        if (unlink(p) < 0)
                return -errno;

        return 1;
}