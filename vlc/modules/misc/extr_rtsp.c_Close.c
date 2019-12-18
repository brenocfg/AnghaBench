#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vod_t ;
struct TYPE_13__ {scalar_t__ i_media; struct TYPE_13__* psz_raw_mux; struct TYPE_13__* psz_path; int /*<<< orphan*/  media; int /*<<< orphan*/  p_rtsp_host; int /*<<< orphan*/  p_fifo_cmd; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ vod_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_14__ {scalar_t__ i_type; TYPE_2__* psz_arg; TYPE_2__* psz_session; int /*<<< orphan*/  p_media; } ;
typedef  TYPE_3__ rtsp_cmd_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_15__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommandPush (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MediaDel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RTSP_CMD_TYPE_DEL ; 
 int /*<<< orphan*/  RTSP_CMD_TYPE_NONE ; 
 int /*<<< orphan*/  TAB_CLEAN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ block_FifoCount (int /*<<< orphan*/ ) ; 
 TYPE_4__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  httpd_HostDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  var_Destroy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    vod_t *p_vod = (vod_t *)p_this;
    vod_sys_t *p_sys = p_vod->p_sys;

    /* Stop command thread */
    CommandPush( p_vod, RTSP_CMD_TYPE_NONE, NULL, NULL, 0, 0.0, NULL );
    vlc_join( p_sys->thread, NULL );

    while( block_FifoCount( p_sys->p_fifo_cmd ) > 0 )
    {
        rtsp_cmd_t cmd;
        block_t *p_block_cmd = block_FifoGet( p_sys->p_fifo_cmd );
        memcpy( &cmd, p_block_cmd->p_buffer, sizeof(cmd) );
        block_Release( p_block_cmd );
        if ( cmd.i_type == RTSP_CMD_TYPE_DEL )
            MediaDel(p_vod, cmd.p_media);
        free( cmd.psz_session );
        free( cmd.psz_arg );
    }
    block_FifoRelease( p_sys->p_fifo_cmd );

    httpd_HostDelete( p_sys->p_rtsp_host );
    var_Destroy( p_this, "rtsp-session-timeout" );
    var_Destroy( p_this, "rtsp-throttle-users" );
    var_Destroy( p_this, "rtsp-raw-mux" );

    /* Check VLM is not buggy */
    if( p_sys->i_media > 0 )
        msg_Err( p_vod, "rtsp vod leaking %d medias", p_sys->i_media );
    TAB_CLEAN( p_sys->i_media, p_sys->media );

    free( p_sys->psz_path );
    free( p_sys->psz_raw_mux );
    free( p_sys );
}