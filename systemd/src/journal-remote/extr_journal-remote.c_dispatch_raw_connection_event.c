#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_3__ {int size; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SocketAddress ;
typedef  int /*<<< orphan*/  RemoteServer ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept_connection (char*,int,TYPE_1__*,char**) ; 
 int journal_remote_add_source (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static int dispatch_raw_connection_event(
                sd_event_source *event,
                int fd,
                uint32_t revents,
                void *userdata) {

        RemoteServer *s = userdata;
        int fd2;
        SocketAddress addr = {
                .size = sizeof(union sockaddr_union),
                .type = SOCK_STREAM,
        };
        char *hostname = NULL;

        fd2 = accept_connection("raw", fd, &addr, &hostname);
        if (fd2 == -EAGAIN)
                return 0;
        if (fd2 < 0)
                return fd2;

        return journal_remote_add_source(s, fd2, hostname, true);
}