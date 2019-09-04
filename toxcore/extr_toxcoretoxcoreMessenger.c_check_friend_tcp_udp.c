#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_7__ {TYPE_1__* friendlist; int /*<<< orphan*/  friend_connectionstatuschange_userdata; int /*<<< orphan*/  (* friend_connectionstatuschange ) (TYPE_2__*,size_t,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int last_connection_udp_tcp; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int CONNECTION_TCP ; 
 int CONNECTION_UDP ; 
 int CONNECTION_UNKNOWN ; 
 int m_get_friend_connectionstatus (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_friend_tcp_udp(Messenger *m, int32_t friendnumber)
{
    int last_connection_udp_tcp = m->friendlist[friendnumber].last_connection_udp_tcp;

    int ret = m_get_friend_connectionstatus(m, friendnumber);

    if (ret == -1)
        return;

    if (ret == CONNECTION_UNKNOWN) {
        if (last_connection_udp_tcp == CONNECTION_UDP) {
            return;
        } else {
            ret = CONNECTION_TCP;
        }
    }

    if (last_connection_udp_tcp != ret) {
        if (m->friend_connectionstatuschange)
            m->friend_connectionstatuschange(m, friendnumber, ret, m->friend_connectionstatuschange_userdata);
    }

    m->friendlist[friendnumber].last_connection_udp_tcp = ret;
}