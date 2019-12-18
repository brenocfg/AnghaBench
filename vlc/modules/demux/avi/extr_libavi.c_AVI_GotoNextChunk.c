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
typedef  int /*<<< orphan*/  avi_chunk_t ;

/* Variables and functions */
 scalar_t__ AVI_ChunkEnd (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  STREAM_CAN_SEEK ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_stream_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int vlc_stream_Seek (int /*<<< orphan*/ *,scalar_t__ const) ; 
 scalar_t__ const vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int AVI_GotoNextChunk( stream_t *s, const avi_chunk_t *p_chk )
{
    bool b_seekable = false;
    const uint64_t i_offset = AVI_ChunkEnd( p_chk );
    if ( !vlc_stream_Control(s, STREAM_CAN_SEEK, &b_seekable) && b_seekable )
    {
        return vlc_stream_Seek( s, i_offset );
    }
    else
    {
        ssize_t i_read = i_offset - vlc_stream_Tell( s );
        return (i_read >=0 && vlc_stream_Read( s, NULL, i_read ) == i_read) ?
                    VLC_SUCCESS : VLC_EGENERIC;
    }
}