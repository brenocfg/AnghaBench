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
struct demux_sys {int /*<<< orphan*/  sub_packetized; } ;
typedef  int /*<<< orphan*/  es_format_t ;
struct TYPE_4__ {struct demux_sys* p_sys; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 scalar_t__ AppendMockTrack (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VLC_CODEC_SUBT ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
InitSubTracks(demux_t *demux, int group, size_t count)
{
    struct demux_sys *sys = demux->p_sys;

    if (count == 0)
        return VLC_SUCCESS;

    for (size_t i = 0; i < count; ++i)
    {
        es_format_t fmt;
        es_format_Init(&fmt, SPU_ES, VLC_CODEC_SUBT);

        if (AppendMockTrack(demux, &fmt, group, sys->sub_packetized))
            return VLC_ENOMEM;
    }

    return VLC_SUCCESS;
}