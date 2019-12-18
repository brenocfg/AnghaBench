#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
struct sockaddr_un {int dummy; } ;
struct TYPE_7__ {scalar_t__* sun_path; } ;
struct TYPE_8__ {TYPE_1__ un; } ;
struct TYPE_9__ {TYPE_2__ sockaddr; } ;
typedef  TYPE_3__ SocketAddress ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 scalar_t__ socket_address_family (TYPE_3__ const*) ; 

const char* socket_address_get_path(const SocketAddress *a) {
        assert(a);

        if (socket_address_family(a) != AF_UNIX)
                return NULL;

        if (a->sockaddr.un.sun_path[0] == 0)
                return NULL;

        /* Note that this is only safe because we know that there's an extra NUL byte after the sockaddr_un
         * structure. On Linux AF_UNIX file system socket addresses don't have to be NUL terminated if they take up the
         * full sun_path space. */
        assert_cc(sizeof(union sockaddr_union) >= sizeof(struct sockaddr_un)+1);
        return a->sockaddr.un.sun_path;
}