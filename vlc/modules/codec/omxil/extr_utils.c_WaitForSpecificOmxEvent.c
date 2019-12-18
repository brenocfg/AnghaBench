#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  OmxEventQueue ;
typedef  int /*<<< orphan*/  OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_PTR ;
typedef  scalar_t__ OMX_EVENTTYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;

/* Variables and functions */
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_ErrorTimeout ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 scalar_t__ WaitForOmxEvent (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_now () ; 

OMX_ERRORTYPE WaitForSpecificOmxEvent(OmxEventQueue *queue,
    OMX_EVENTTYPE specific_event, OMX_U32 *data_1, OMX_U32 *data_2,
    OMX_PTR *event_data)
{
    OMX_ERRORTYPE status;
    OMX_EVENTTYPE event;
    vlc_tick_t before =  vlc_tick_now();

    while(1)
    {
        status = WaitForOmxEvent(queue, &event, data_1, data_2, event_data);
        if(status != OMX_ErrorNone) return status;

        if(event == specific_event) break;
        if(vlc_tick_now() - before > VLC_TICK_FROM_SEC(1)) return OMX_ErrorTimeout;
    }

    return OMX_ErrorNone;
}