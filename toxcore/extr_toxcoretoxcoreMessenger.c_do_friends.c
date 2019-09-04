#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_14__ {size_t numfriends; TYPE_1__* friendlist; int /*<<< orphan*/  userstatus; int /*<<< orphan*/  statusmessage_length; int /*<<< orphan*/  statusmessage; int /*<<< orphan*/  name_length; int /*<<< orphan*/  name; int /*<<< orphan*/  fr_c; } ;
struct TYPE_13__ {scalar_t__ status; int name_sent; int statusmessage_sent; int userstatus_sent; int user_istyping_sent; void* last_seen_time; int /*<<< orphan*/  user_istyping; void* friendrequest_lastsent; int /*<<< orphan*/  info_size; int /*<<< orphan*/  info; int /*<<< orphan*/  friendrequest_nospam; int /*<<< orphan*/  friendcon_id; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FRIEND_ADDED ; 
 scalar_t__ FRIEND_CONFIRMED ; 
 scalar_t__ FRIEND_ONLINE ; 
 scalar_t__ FRIEND_REQUESTED ; 
 int /*<<< orphan*/  check_friend_request_timed_out (TYPE_2__*,size_t,void*) ; 
 int /*<<< orphan*/  check_friend_tcp_udp (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  do_receipts (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  do_reqchunk_filecb (TYPE_2__*,size_t) ; 
 scalar_t__ m_sendname (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_friend_request_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ send_statusmessage (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ send_user_istyping (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ send_userstatus (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_friend_status (TYPE_2__*,size_t,scalar_t__) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 void* unix_time () ; 

void do_friends(Messenger *m)
{
    uint32_t i;
    uint64_t temp_time = unix_time();

    for (i = 0; i < m->numfriends; ++i) {
        if (m->friendlist[i].status == FRIEND_ADDED) {
            int fr = send_friend_request_packet(m->fr_c, m->friendlist[i].friendcon_id, m->friendlist[i].friendrequest_nospam,
                                                m->friendlist[i].info,
                                                m->friendlist[i].info_size);

            if (fr >= 0) {
                set_friend_status(m, i, FRIEND_REQUESTED);
                m->friendlist[i].friendrequest_lastsent = temp_time;
            }
        }

        if (m->friendlist[i].status == FRIEND_REQUESTED
                || m->friendlist[i].status == FRIEND_CONFIRMED) { /* friend is not online. */
            if (m->friendlist[i].status == FRIEND_REQUESTED) {
                /* If we didn't connect to friend after successfully sending him a friend request the request is deemed
                 * unsuccessful so we set the status back to FRIEND_ADDED and try again.
                 */
                check_friend_request_timed_out(m, i, temp_time);
            }
        }

        if (m->friendlist[i].status == FRIEND_ONLINE) { /* friend is online. */
            if (m->friendlist[i].name_sent == 0) {
                if (m_sendname(m, i, m->name, m->name_length))
                    m->friendlist[i].name_sent = 1;
            }

            if (m->friendlist[i].statusmessage_sent == 0) {
                if (send_statusmessage(m, i, m->statusmessage, m->statusmessage_length))
                    m->friendlist[i].statusmessage_sent = 1;
            }

            if (m->friendlist[i].userstatus_sent == 0) {
                if (send_userstatus(m, i, m->userstatus))
                    m->friendlist[i].userstatus_sent = 1;
            }

            if (m->friendlist[i].user_istyping_sent == 0) {
                if (send_user_istyping(m, i, m->friendlist[i].user_istyping))
                    m->friendlist[i].user_istyping_sent = 1;
            }

            check_friend_tcp_udp(m, i);
            do_receipts(m, i);
            do_reqchunk_filecb(m, i);

            m->friendlist[i].last_seen_time = (uint64_t) time(NULL);
        }
    }
}