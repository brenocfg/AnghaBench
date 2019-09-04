#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Messenger ;
typedef  TYPE_1__ MSISession ;
typedef  int /*<<< orphan*/  MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_call (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invoke_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_OnPeerTimeout ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 

void on_peer_status(Messenger *m, uint32_t friend_number, uint8_t status, void *data)
{
    (void)m;
    MSISession *session = data;

    switch (status) {
        case 0: { /* Friend is now offline */
            LOGGER_DEBUG("Friend %d is now offline", friend_number);

            pthread_mutex_lock(session->mutex);
            MSICall *call = get_call(session, friend_number);

            if (call == NULL) {
                pthread_mutex_unlock(session->mutex);
                return;
            }

            invoke_callback(call, msi_OnPeerTimeout); /* Failure is ignored */
            kill_call(call);
            pthread_mutex_unlock(session->mutex);
        }
        break;

        default:
            break;
    }
}