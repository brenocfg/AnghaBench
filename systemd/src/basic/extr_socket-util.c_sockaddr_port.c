#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int svm_port; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_port; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_5__ {int sa_family; } ;
union sockaddr_union {TYPE_4__ vm; TYPE_3__ in6; TYPE_2__ in; TYPE_1__ sa; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_VSOCK 128 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  assert (union sockaddr_union*) ; 
 unsigned int be16toh (int /*<<< orphan*/ ) ; 

int sockaddr_port(const struct sockaddr *_sa, unsigned *ret_port) {
        union sockaddr_union *sa = (union sockaddr_union*) _sa;

        /* Note, this returns the port as 'unsigned' rather than 'uint16_t', as AF_VSOCK knows larger ports */

        assert(sa);

        switch (sa->sa.sa_family) {

        case AF_INET:
                *ret_port = be16toh(sa->in.sin_port);
                return 0;

        case AF_INET6:
                *ret_port = be16toh(sa->in6.sin6_port);
                return 0;

        case AF_VSOCK:
                *ret_port = sa->vm.svm_port;
                return 0;

        default:
                return -EAFNOSUPPORT;
        }
}