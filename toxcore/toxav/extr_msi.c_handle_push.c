#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  messenger; } ;
struct TYPE_12__ {int state; int /*<<< orphan*/  error; int /*<<< orphan*/  friend_number; TYPE_9__* session; int /*<<< orphan*/  peer_capabilities; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  exists; } ;
struct TYPE_11__ {TYPE_1__ capabilities; } ;
typedef  TYPE_2__ MSIMessage ;
typedef  TYPE_3__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGGER_INFO (char*,...) ; 
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int invoke_callback (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_call (TYPE_3__*) ; 
#define  msi_CallActive 131 
#define  msi_CallInactive 130 
#define  msi_CallRequested 129 
#define  msi_CallRequesting 128 
 int /*<<< orphan*/  msi_EInvalidMessage ; 
 int /*<<< orphan*/  msi_OnCapabilities ; 
 int /*<<< orphan*/  msi_OnStart ; 
 int /*<<< orphan*/  send_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void handle_push (MSICall *call, const MSIMessage *msg)
{
    assert(call);

    LOGGER_DEBUG("Session: %p Handling 'push' friend: %d", call->session, call->friend_number);

    if (!msg->capabilities.exists) {
        LOGGER_WARNING("Session: %p Invalid capabilities on 'push'");
        call->error = msi_EInvalidMessage;
        goto FAILURE;
    }

    switch (call->state) {
        case msi_CallActive: {
            /* Only act if capabilities changed */
            if (call->peer_capabilities != msg->capabilities.value) {
                LOGGER_INFO("Friend is changing capabilities to: %u", msg->capabilities.value);

                call->peer_capabilities = msg->capabilities.value;

                if (invoke_callback(call, msi_OnCapabilities) == -1)
                    goto FAILURE;
            }
        }
        break;

        case msi_CallRequesting: {
            LOGGER_INFO("Friend answered our call");

            /* Call started */
            call->peer_capabilities = msg->capabilities.value;
            call->state = msi_CallActive;

            if (invoke_callback(call, msi_OnStart) == -1)
                goto FAILURE;

        }
        break;

        /* Pushes during initialization state are ignored */
        case msi_CallInactive:
        case msi_CallRequested: {
            LOGGER_WARNING("Ignoring invalid push");
        }
        break;
    }

    return;

FAILURE:
    send_error(call->session->messenger, call->friend_number, call->error);
    kill_call(call);
}