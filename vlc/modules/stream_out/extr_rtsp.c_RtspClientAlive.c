#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* stream; int /*<<< orphan*/  last_seen; } ;
typedef  TYPE_1__ rtsp_session_t ;
struct TYPE_5__ {scalar_t__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  RtspUpdateTimer (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void RtspClientAlive( rtsp_session_t *session )
{
    if (session->stream->timeout == 0)
        return;

    session->last_seen = vlc_tick_now();
    RtspUpdateTimer(session->stream);
}