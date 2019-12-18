#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {scalar_t__ p_data; } ;
struct TYPE_5__ {scalar_t__ i_chunk_size; } ;
struct TYPE_7__ {TYPE_2__ strd; TYPE_1__ common; } ;
typedef  TYPE_3__ avi_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_READCHUNK_ENTER ; 
 int /*<<< orphan*/  AVI_READCHUNK_EXIT (int /*<<< orphan*/ ) ; 
 int AVI_ZEROSIZED_CHUNK ; 
 int /*<<< orphan*/  VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ p_buff ; 

__attribute__((used)) static int AVI_ChunkRead_strd( stream_t *s, avi_chunk_t *p_chk )
{
    if ( p_chk->common.i_chunk_size == 0 )
    {
        msg_Dbg( (vlc_object_t*)s, "Zero sized pre-JUNK section met" );
        return AVI_ZEROSIZED_CHUNK;
    }

    AVI_READCHUNK_ENTER;
    p_chk->strd.p_data = malloc( p_chk->common.i_chunk_size );
    if( p_chk->strd.p_data )
        memcpy( p_chk->strd.p_data, p_buff + 8, p_chk->common.i_chunk_size );
    AVI_READCHUNK_EXIT( p_chk->strd.p_data ? VLC_SUCCESS : VLC_EGENERIC );
}