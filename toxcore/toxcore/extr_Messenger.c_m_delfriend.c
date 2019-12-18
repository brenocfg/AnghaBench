#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t int32_t ;
struct TYPE_10__ {scalar_t__ status; int /*<<< orphan*/  friendcon_id; int /*<<< orphan*/  real_pk; } ;
struct TYPE_9__ {int numfriends; TYPE_5__* friendlist; int /*<<< orphan*/  fr_c; int /*<<< orphan*/  fr; int /*<<< orphan*/  friend_connectionstatuschange_internal_userdata; int /*<<< orphan*/  (* friend_connectionstatuschange_internal ) (TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Messenger ;
typedef  int /*<<< orphan*/  Friend ;

/* Variables and functions */
 int FAERR_NOMEM ; 
 scalar_t__ FRIENDCONN_STATUS_CONNECTED ; 
 int /*<<< orphan*/  MESSENGER_CALLBACK_INDEX ; 
 scalar_t__ NOFRIEND ; 
 int /*<<< orphan*/  clear_receipts (TYPE_1__*,size_t) ; 
 scalar_t__ friend_con_connected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  friend_connection_callbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_not_valid (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  kill_friend_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc_friendlist (TYPE_1__*,int) ; 
 int /*<<< orphan*/  remove_request_received (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_offline_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int m_delfriend(Messenger *m, int32_t friendnumber)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    if (m->friend_connectionstatuschange_internal)
        m->friend_connectionstatuschange_internal(m, friendnumber, 0, m->friend_connectionstatuschange_internal_userdata);

    clear_receipts(m, friendnumber);
    remove_request_received(&(m->fr), m->friendlist[friendnumber].real_pk);
    friend_connection_callbacks(m->fr_c, m->friendlist[friendnumber].friendcon_id, MESSENGER_CALLBACK_INDEX, 0, 0, 0, 0, 0);

    if (friend_con_connected(m->fr_c, m->friendlist[friendnumber].friendcon_id) == FRIENDCONN_STATUS_CONNECTED) {
        send_offline_packet(m, m->friendlist[friendnumber].friendcon_id);
    }

    kill_friend_connection(m->fr_c, m->friendlist[friendnumber].friendcon_id);
    memset(&(m->friendlist[friendnumber]), 0, sizeof(Friend));
    uint32_t i;

    for (i = m->numfriends; i != 0; --i) {
        if (m->friendlist[i - 1].status != NOFRIEND)
            break;
    }

    m->numfriends = i;

    if (realloc_friendlist(m, m->numfriends) != 0)
        return FAERR_NOMEM;

    return 0;
}