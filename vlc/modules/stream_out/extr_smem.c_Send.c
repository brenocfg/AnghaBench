#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_5__ {scalar_t__ i_cat; } ;
struct TYPE_6__ {TYPE_1__ format; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int SendAudio (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int SendVideo (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *_id, block_t *p_buffer )
{
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    if ( id->format.i_cat == VIDEO_ES )
        return SendVideo( p_stream, id, p_buffer );
    else if ( id->format.i_cat == AUDIO_ES )
        return SendAudio( p_stream, id, p_buffer );
    return VLC_SUCCESS;
}