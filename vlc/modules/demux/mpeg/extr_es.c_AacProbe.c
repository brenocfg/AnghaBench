#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ demux_IsForced (TYPE_1__*,char*) ; 
 scalar_t__ demux_IsPathExtension (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AacProbe( demux_t *p_demux, uint64_t *pi_offset )
{
    bool   b_forced;
    bool   b_forced_demux;

    uint64_t i_offset;
    const uint8_t *p_peek;

    b_forced = demux_IsPathExtension( p_demux, ".aac" ) ||
               demux_IsPathExtension( p_demux, ".aacp" );
    b_forced_demux = demux_IsForced( p_demux, "m4a" ) ||
                     demux_IsForced( p_demux, "aac" ) ||
                     demux_IsForced( p_demux, "mp4a" );

    if( !b_forced_demux && !b_forced )
        return VLC_EGENERIC;

    i_offset = vlc_stream_Tell( p_demux->s );

    /* peek the begining (10 is for adts header) */
    if( vlc_stream_Peek( p_demux->s, &p_peek, 10 ) < 10 )
    {
        msg_Dbg( p_demux, "cannot peek" );
        return VLC_EGENERIC;
    }
    if( !strncmp( (char *)p_peek, "ADIF", 4 ) )
    {
        msg_Err( p_demux, "ADIF file. Not yet supported. (Please report)" );
        return VLC_EGENERIC;
    }

    *pi_offset = i_offset;
    return VLC_SUCCESS;
}