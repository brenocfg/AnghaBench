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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  AStreamControlReset (TYPE_1__*) ; 
#define  STREAM_CAN_CONTROL_PACE 147 
#define  STREAM_CAN_FASTSEEK 146 
#define  STREAM_CAN_PAUSE 145 
#define  STREAM_CAN_SEEK 144 
#define  STREAM_GET_CONTENT_TYPE 143 
#define  STREAM_GET_META 142 
#define  STREAM_GET_PRIVATE_ID_STATE 141 
#define  STREAM_GET_PTS_DELAY 140 
#define  STREAM_GET_SEEKPOINT 139 
#define  STREAM_GET_SIGNAL 138 
#define  STREAM_GET_SIZE 137 
#define  STREAM_GET_TAGS 136 
#define  STREAM_GET_TITLE 135 
#define  STREAM_GET_TITLE_INFO 134 
#define  STREAM_SET_PAUSE_STATE 133 
#define  STREAM_SET_PRIVATE_ID_CA 132 
#define  STREAM_SET_PRIVATE_ID_STATE 131 
#define  STREAM_SET_RECORD_STATE 130 
#define  STREAM_SET_SEEKPOINT 129 
#define  STREAM_SET_TITLE 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int) ; 
 int vlc_stream_vaControl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AStreamControl(stream_t *s, int i_query, va_list args)
{
    switch(i_query)
    {
        case STREAM_CAN_SEEK:
        case STREAM_CAN_FASTSEEK:
        case STREAM_CAN_PAUSE:
        case STREAM_CAN_CONTROL_PACE:
        case STREAM_GET_SIZE:
        case STREAM_GET_PTS_DELAY:
        case STREAM_GET_TITLE_INFO:
        case STREAM_GET_TITLE:
        case STREAM_GET_SEEKPOINT:
        case STREAM_GET_META:
        case STREAM_GET_CONTENT_TYPE:
        case STREAM_GET_SIGNAL:
        case STREAM_GET_TAGS:
        case STREAM_SET_PAUSE_STATE:
        case STREAM_SET_PRIVATE_ID_STATE:
        case STREAM_SET_PRIVATE_ID_CA:
        case STREAM_GET_PRIVATE_ID_STATE:
            return vlc_stream_vaControl(s->s, i_query, args);

        case STREAM_SET_TITLE:
        case STREAM_SET_SEEKPOINT:
        {
            int ret = vlc_stream_vaControl(s->s, i_query, args);
            if (ret == VLC_SUCCESS)
                AStreamControlReset(s);
            return ret;
        }

        case STREAM_SET_RECORD_STATE:
        default:
            msg_Err(s, "invalid vlc_stream_vaControl query=0x%x", i_query);
            return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}