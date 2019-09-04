#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  payload_type; int /*<<< orphan*/  friend_number; int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ RTPSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int /*<<< orphan*/  handle_rtp_packet ; 
 int m_callback_rtp_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

int rtp_allow_receiving(RTPSession *session)
{
    if (session == NULL)
        return -1;

    if (m_callback_rtp_packet(session->m, session->friend_number, session->payload_type,
                              handle_rtp_packet, session) == -1) {
        LOGGER_WARNING("Failed to register rtp receive handler");
        return -1;
    }

    LOGGER_DEBUG("Started receiving on session: %p", session);
    return 0;
}