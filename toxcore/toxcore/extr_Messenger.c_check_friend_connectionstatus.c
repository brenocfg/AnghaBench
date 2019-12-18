#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  friend_connectionstatuschange_internal_userdata; int /*<<< orphan*/  (* friend_connectionstatuschange_internal ) (TYPE_2__*,size_t,scalar_t__ const,int /*<<< orphan*/ ) ;TYPE_1__* friendlist; } ;
struct TYPE_8__ {scalar_t__ status; scalar_t__ user_istyping_sent; scalar_t__ statusmessage_sent; scalar_t__ userstatus_sent; scalar_t__ name_sent; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FRIEND_ONLINE ; 
 scalar_t__ NOFRIEND ; 
 int /*<<< orphan*/  break_files (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  check_friend_tcp_udp (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  clear_receipts (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,scalar_t__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_friend_connectionstatus(Messenger *m, int32_t friendnumber, uint8_t status)
{
    if (status == NOFRIEND)
        return;

    const uint8_t was_online = m->friendlist[friendnumber].status == FRIEND_ONLINE;
    const uint8_t is_online = status == FRIEND_ONLINE;

    if (is_online != was_online) {
        if (was_online) {
            break_files(m, friendnumber);
            clear_receipts(m, friendnumber);
        } else {
            m->friendlist[friendnumber].name_sent = 0;
            m->friendlist[friendnumber].userstatus_sent = 0;
            m->friendlist[friendnumber].statusmessage_sent = 0;
            m->friendlist[friendnumber].user_istyping_sent = 0;
        }

        m->friendlist[friendnumber].status = status;

        check_friend_tcp_udp(m, friendnumber);

        if (m->friend_connectionstatuschange_internal)
            m->friend_connectionstatuschange_internal(m, friendnumber, is_online,
                    m->friend_connectionstatuschange_internal_userdata);
    }
}