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
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/  friend_number; TYPE_1__* session; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  messenger; } ;
typedef  TYPE_1__ MSISession ;
typedef  int /*<<< orphan*/  MSIMessage ;
typedef  TYPE_2__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/  kill_call (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_CallInactive ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  requ_pop ; 
 int /*<<< orphan*/  send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int msi_hangup (MSICall *call)
{
    if (!call || !call->session)
        return -1;

    LOGGER_DEBUG("Session: %p Hanging up call with friend: %u", call->session, call->friend_number);

    MSISession *session = call->session;

    if (pthread_mutex_trylock(session->mutex) != 0) {
        LOGGER_ERROR ("Failed to aquire lock on msi mutex");
        return -1;
    }

    if (call->state == msi_CallInactive) {
        LOGGER_ERROR("Call is in invalid state!");
        pthread_mutex_unlock(session->mutex);
        return -1;
    }

    MSIMessage msg;
    msg_init(&msg, requ_pop);

    send_message (session->messenger, call->friend_number, &msg);

    kill_call(call);
    pthread_mutex_unlock(session->mutex);
    return 0;
}