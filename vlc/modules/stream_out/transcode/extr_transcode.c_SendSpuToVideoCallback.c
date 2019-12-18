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
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  id_video; } ;
typedef  TYPE_2__ sout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  subpicture_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transcode_video_push_spu (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SendSpuToVideoCallback( void *cbdata, subpicture_t *p_subpicture )
{
    sout_stream_t *p_stream = cbdata;
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    vlc_mutex_lock( &p_sys->lock );
    if( !p_sys->id_video )
        subpicture_Delete( p_subpicture );
    else
        transcode_video_push_spu( p_stream,
                                  p_sys->id_video, p_subpicture );
    vlc_mutex_unlock( &p_sys->lock );
}