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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_CAN_SEEK ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ vlc_stream_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int vlc_stream_Seek (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ *) ; 

int MP4_Seek( stream_t *p_stream, uint64_t i_pos )
{
    bool b_canseek = false;
    if ( vlc_stream_Control( p_stream, STREAM_CAN_SEEK, &b_canseek ) != VLC_SUCCESS ||
         b_canseek )
    {
        /* can seek or don't know */
        return vlc_stream_Seek( p_stream, i_pos );
    }
    /* obviously can't seek then */

    int64_t i_current_pos = vlc_stream_Tell( p_stream );
    if ( i_current_pos < 0 || i_pos < (uint64_t)i_current_pos )
        return VLC_EGENERIC;

    size_t i_toread = i_pos - i_current_pos;
    if( i_toread == 0 )
        return VLC_SUCCESS;
    else if( i_toread > (1<<17) )
        return VLC_EGENERIC;

    if( vlc_stream_Read( p_stream, NULL, i_toread ) != (ssize_t)i_toread )
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}