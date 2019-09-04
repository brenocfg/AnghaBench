#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  friend_number; void* self_capabilities; TYPE_2__* session; } ;
struct TYPE_9__ {int exists; void* value; } ;
struct TYPE_11__ {TYPE_1__ capabilities; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  messenger; } ;
typedef  TYPE_2__ MSISession ;
typedef  TYPE_3__ MSIMessage ;
typedef  TYPE_4__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/  msg_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ msi_CallActive ; 
 scalar_t__ msi_CallRequested ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  requ_push ; 
 int /*<<< orphan*/  send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int msi_answer (MSICall *call, uint8_t capabilities)
{
    if (!call || !call->session)
        return -1;

    LOGGER_DEBUG("Session: %p Answering call from: %u", call->session, call->friend_number);

    MSISession *session = call->session;

    if (pthread_mutex_trylock(session->mutex) != 0) {
        LOGGER_ERROR ("Failed to aquire lock on msi mutex");
        return -1;
    }

    if (call->state != msi_CallRequested) {
        /* Though sending in invalid state will not cause anything wierd
         * Its better to not do it like a maniac */
        LOGGER_ERROR("Call is in invalid state!");
        pthread_mutex_unlock(session->mutex);
        return -1;
    }

    call->self_capabilities = capabilities;

    MSIMessage msg;
    msg_init(&msg, requ_push);

    msg.capabilities.exists = true;
    msg.capabilities.value = capabilities;

    send_message (session->messenger, call->friend_number, &msg);

    call->state = msi_CallActive;
    pthread_mutex_unlock(session->mutex);

    return 0;
}