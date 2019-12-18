#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  avi_chunk_t ;
struct TYPE_2__ {int /*<<< orphan*/  dwTotalFrames; } ;
typedef  TYPE_1__ avi_chunk_dmlh_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_READ4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVI_READCHUNK_ENTER ; 
 int /*<<< orphan*/  AVI_READCHUNK_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AVI_ChunkRead_dmlh( stream_t *s, avi_chunk_t *p_chk )
{
    avi_chunk_dmlh_t *p_dmlh = (avi_chunk_dmlh_t*)p_chk;

    AVI_READCHUNK_ENTER;

    AVI_READ4BYTES( p_dmlh->dwTotalFrames );

#ifdef AVI_DEBUG
    msg_Dbg( (vlc_object_t*)s, "dmlh: dwTotalFrames %d",
             p_dmlh->dwTotalFrames );
#endif
    AVI_READCHUNK_EXIT( VLC_SUCCESS );
}