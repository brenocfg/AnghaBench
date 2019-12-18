#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int value; } ;
struct TYPE_12__ {TYPE_1__ request; } ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Messenger ;
typedef  TYPE_2__ MSISession ;
typedef  TYPE_3__ MSIMessage ;
typedef  int /*<<< orphan*/  MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*) ; 
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int /*<<< orphan*/ * get_call (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_init (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  handle_pop (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  handle_push (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int msg_parse_in (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_EInvalidMessage ; 
 int /*<<< orphan*/  msi_EStrayMessage ; 
 int /*<<< orphan*/  msi_ESystem ; 
 int /*<<< orphan*/ * new_call (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
#define  requ_init 130 
#define  requ_pop 129 
#define  requ_push 128 
 int /*<<< orphan*/  send_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void handle_msi_packet (Messenger *m, uint32_t friend_number, const uint8_t *data, uint16_t length, void *object)
{
    LOGGER_DEBUG("Got msi message");

    MSISession *session = object;
    MSIMessage msg;

    if (msg_parse_in (&msg, data, length) == -1) {
        LOGGER_WARNING("Error parsing message");
        send_error(m, friend_number, msi_EInvalidMessage);
        return;
    } else {
        LOGGER_DEBUG("Successfully parsed message");
    }

    pthread_mutex_lock(session->mutex);
    MSICall *call = get_call(session, friend_number);

    if (call == NULL) {
        if (msg.request.value != requ_init) {
            send_error(m, friend_number, msi_EStrayMessage);
            pthread_mutex_unlock(session->mutex);
            return;
        }

        call = new_call(session, friend_number);

        if (call == NULL) {
            send_error(m, friend_number, msi_ESystem);
            pthread_mutex_unlock(session->mutex);
            return;
        }
    }

    switch (msg.request.value) {
        case requ_init:
            handle_init(call, &msg);
            break;

        case requ_push:
            handle_push(call, &msg);
            break;

        case requ_pop:
            handle_pop(call, &msg); /* always kills the call */
            break;
    }

    pthread_mutex_unlock(session->mutex);
}