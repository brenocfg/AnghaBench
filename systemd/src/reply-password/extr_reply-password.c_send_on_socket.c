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
union sockaddr_union {int /*<<< orphan*/  sa; int /*<<< orphan*/  un; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  assert (void const*) ; 
 int /*<<< orphan*/  errno ; 
 int log_error_errno (int,char*,...) ; 
 scalar_t__ sendto (int,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sockaddr_un_set_path (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int send_on_socket(int fd, const char *socket_name, const void *packet, size_t size) {
        union sockaddr_union sa = {};
        int salen;

        assert(fd >= 0);
        assert(socket_name);
        assert(packet);

        salen = sockaddr_un_set_path(&sa.un, socket_name);
        if (salen < 0)
                return log_error_errno(salen, "Specified socket path for AF_UNIX socket invalid, refusing: %s", socket_name);

        if (sendto(fd, packet, size, MSG_NOSIGNAL, &sa.sa, salen) < 0)
                return log_error_errno(errno, "Failed to send: %m");

        return 0;
}