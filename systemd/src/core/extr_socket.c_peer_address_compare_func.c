#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int svm_cid; } ;
struct TYPE_11__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_9__ {int sa_family; } ;
struct TYPE_13__ {TYPE_4__ vm; TYPE_3__ in6; TYPE_2__ in; TYPE_1__ sa; } ;
struct TYPE_14__ {TYPE_5__ peer; } ;
typedef  TYPE_6__ SocketPeer ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_VSOCK 128 
 int CMP (int,int) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int peer_address_compare_func(const SocketPeer *x, const SocketPeer *y) {
        int r;

        r = CMP(x->peer.sa.sa_family, y->peer.sa.sa_family);
        if (r != 0)
                return r;

        switch(x->peer.sa.sa_family) {
        case AF_INET:
                return memcmp(&x->peer.in.sin_addr, &y->peer.in.sin_addr, sizeof(x->peer.in.sin_addr));
        case AF_INET6:
                return memcmp(&x->peer.in6.sin6_addr, &y->peer.in6.sin6_addr, sizeof(x->peer.in6.sin6_addr));
        case AF_VSOCK:
                return CMP(x->peer.vm.svm_cid, y->peer.vm.svm_cid);
        }
        assert_not_reached("Black sheep in the family!");
}