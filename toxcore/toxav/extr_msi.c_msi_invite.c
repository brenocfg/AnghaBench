#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  state; int /*<<< orphan*/  friend_number; TYPE_2__* session; void* self_capabilities; } ;
struct TYPE_13__ {int exists; void* value; } ;
struct TYPE_16__ {TYPE_1__ capabilities; } ;
struct TYPE_15__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_14__ {int /*<<< orphan*/  messenger; } ;
typedef  TYPE_3__ MSISession ;
typedef  TYPE_4__ MSIMessage ;
typedef  TYPE_5__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,...) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/ * get_call (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_init (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_CallRequesting ; 
 TYPE_5__* new_call (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  requ_init ; 
 int /*<<< orphan*/  send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

int msi_invite (MSISession *session, MSICall **call, uint32_t friend_number, uint8_t capabilities)
{
    if (!session)
        return -1;

    LOGGER_DEBUG("Session: %p Inviting friend: %u", session, friend_number);

    if (pthread_mutex_trylock(session->mutex) != 0) {
        LOGGER_ERROR ("Failed to aquire lock on msi mutex");
        return -1;
    }

    if (get_call(session, friend_number) != NULL) {
        LOGGER_ERROR("Already in a call");
        pthread_mutex_unlock(session->mutex);
        return -1;
    }

    (*call) = new_call (session, friend_number);

    if (*call == NULL) {
        pthread_mutex_unlock(session->mutex);
        return -1;
    }

    (*call)->self_capabilities = capabilities;

    MSIMessage msg;
    msg_init(&msg, requ_init);

    msg.capabilities.exists = true;
    msg.capabilities.value = capabilities;

    send_message ((*call)->session->messenger, (*call)->friend_number, &msg);

    (*call)->state = msi_CallRequesting;

    LOGGER_DEBUG("Invite sent");
    pthread_mutex_unlock(session->mutex);
    return 0;
}