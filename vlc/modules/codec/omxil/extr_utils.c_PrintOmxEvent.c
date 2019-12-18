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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_STATETYPE ;
typedef  scalar_t__ OMX_PTR ;
typedef  int OMX_EVENTTYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;

/* Variables and functions */
 unsigned int CommandToString (scalar_t__) ; 
 int /*<<< orphan*/  ErrorToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EventToString (int) ; 
#define  OMX_CommandStateSet 130 
#define  OMX_EventCmdComplete 129 
#define  OMX_EventError 128 
 unsigned int StateToString (scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,...) ; 

void PrintOmxEvent(vlc_object_t *p_this, OMX_EVENTTYPE event, OMX_U32 data_1,
    OMX_U32 data_2, OMX_PTR event_data)
{
    switch (event)
    {
    case OMX_EventCmdComplete:
        switch ((OMX_STATETYPE)data_1)
        {
        case OMX_CommandStateSet:
            msg_Dbg( p_this, "OmxEventHandler (%s, %s, %s)", EventToString(event),
                     CommandToString(data_1), StateToString(data_2) );
            break;

        default:
            msg_Dbg( p_this, "OmxEventHandler (%s, %s, %u)", EventToString(event),
                     CommandToString(data_1), (unsigned int)data_2 );
            break;
        }
        break;

    case OMX_EventError:
        msg_Dbg( p_this, "OmxEventHandler (%s, %s, %u, %s)", EventToString(event),
                 ErrorToString((OMX_ERRORTYPE)data_1), (unsigned int)data_2,
                 (const char *)event_data);
        break;

    default:
        msg_Dbg( p_this, "OmxEventHandler (%s, %u, %u)", EventToString(event),
                 (unsigned int)data_1, (unsigned int)data_2 );
        break;
    }
}