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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* p_clip_info; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_4__ {int /*<<< orphan*/  pg_stream_count; int /*<<< orphan*/ * pg_streams; int /*<<< orphan*/  audio_stream_count; int /*<<< orphan*/ * audio_streams; } ;
typedef  int /*<<< orphan*/  BLURAY_STREAM_INFO ;

/* Variables and functions */
#define  BD_EVENT_AUDIO_STREAM 129 
#define  BD_EVENT_PG_TEXTST_STREAM 128 

__attribute__((used)) static uint8_t blurayGetStreamsUnlocked(demux_sys_t *p_sys,
                                        int i_stream_type,
                                        BLURAY_STREAM_INFO **pp_streams)
{
    if(!p_sys->p_clip_info)
        return 0;

    switch(i_stream_type)
    {
        case BD_EVENT_AUDIO_STREAM:
            *pp_streams = p_sys->p_clip_info->audio_streams;
            return p_sys->p_clip_info->audio_stream_count;
        case BD_EVENT_PG_TEXTST_STREAM:
            *pp_streams = p_sys->p_clip_info->pg_streams;
            return p_sys->p_clip_info->pg_stream_count;
        default:
            return 0;
    }
}