#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int state; int /*<<< orphan*/  error; int /*<<< orphan*/  friend_number; int /*<<< orphan*/  session; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; scalar_t__ exists; } ;
struct TYPE_10__ {TYPE_1__ error; } ;
typedef  TYPE_2__ MSIMessage ;
typedef  TYPE_3__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/  LOGGER_INFO (char*) ; 
 int /*<<< orphan*/  LOGGER_WARNING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  invoke_callback (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_call (TYPE_3__*) ; 
#define  msi_CallActive 131 
#define  msi_CallInactive 130 
#define  msi_CallRequested 129 
#define  msi_CallRequesting 128 
 int /*<<< orphan*/  msi_OnEnd ; 
 int /*<<< orphan*/  msi_OnError ; 

void handle_pop (MSICall *call, const MSIMessage *msg)
{
    assert(call);

    LOGGER_DEBUG("Session: %p Handling 'pop', friend id: %d", call->session, call->friend_number);

    /* callback errors are ignored */

    if (msg->error.exists) {
        LOGGER_WARNING("Friend detected an error: %d", msg->error.value);
        call->error = msg->error.value;
        invoke_callback(call, msi_OnError);

    } else switch (call->state) {
            case msi_CallInactive: {
                LOGGER_ERROR("Handling what should be impossible case");
                abort();
            }
            break;

            case msi_CallActive: {
                /* Hangup */
                LOGGER_INFO("Friend hung up on us");
                invoke_callback(call, msi_OnEnd);
            }
            break;

            case msi_CallRequesting: {
                /* Reject */
                LOGGER_INFO("Friend rejected our call");
                invoke_callback(call, msi_OnEnd);
            }
            break;

            case msi_CallRequested: {
                /* Cancel */
                LOGGER_INFO("Friend canceled call invite");
                invoke_callback(call, msi_OnEnd);
            }
            break;
        }

    kill_call (call);
}