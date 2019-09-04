#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  payload_type; int /*<<< orphan*/  friend_number; int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ RTPSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  m_callback_rtp_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int rtp_stop_receiving(RTPSession *session)
{
    if (session == NULL)
        return -1;

    m_callback_rtp_packet(session->m, session->friend_number, session->payload_type, NULL, NULL);

    LOGGER_DEBUG("Stopped receiving on session: %p", session);
    return 0;
}