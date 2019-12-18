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
typedef  int /*<<< orphan*/  RemoteServer ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  SOCK_CLOEXEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int make_socket_fd (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setup_microhttpd_server (int /*<<< orphan*/ *,int,char const*,char const*,char const*) ; 

__attribute__((used)) static int setup_microhttpd_socket(RemoteServer *s,
                                   const char *address,
                                   const char *key,
                                   const char *cert,
                                   const char *trust) {
        int fd;

        fd = make_socket_fd(LOG_DEBUG, address, SOCK_STREAM, SOCK_CLOEXEC);
        if (fd < 0)
                return fd;

        return setup_microhttpd_server(s, fd, key, cert, trust);
}