#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct Messenger {int dummy; } ;
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/  friend_number; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; scalar_t__ messenger; int /*<<< orphan*/  calls_head; scalar_t__ calls; } ;
typedef  TYPE_1__ MSISession ;
typedef  int /*<<< orphan*/  MSIMessage ;
typedef  TYPE_2__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_2__* get_call (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_call (TYPE_2__*) ; 
 int /*<<< orphan*/  m_callback_msi_packet (struct Messenger*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  requ_pop ; 
 int /*<<< orphan*/  send_message (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int msi_kill (MSISession *session)
{
    if (session == NULL) {
        LOGGER_ERROR("Tried to terminate non-existing session");
        return -1;
    }

    m_callback_msi_packet((struct Messenger *) session->messenger, NULL, NULL);

    if (pthread_mutex_trylock(session->mutex) != 0) {
        LOGGER_ERROR ("Failed to aquire lock on msi mutex");
        return -1;
    }

    if (session->calls) {
        MSIMessage msg;
        msg_init(&msg, requ_pop);

        MSICall *it = get_call(session, session->calls_head);

        while (it) {
            send_message(session->messenger, it->friend_number, &msg);
            MSICall *temp_it = it;
            it = it->next;
            kill_call(temp_it); /* This will eventually free session->calls */
        }
    }

    pthread_mutex_unlock(session->mutex);
    pthread_mutex_destroy(session->mutex);

    LOGGER_DEBUG("Terminated session: %p", session);
    free (session);
    return 0;
}