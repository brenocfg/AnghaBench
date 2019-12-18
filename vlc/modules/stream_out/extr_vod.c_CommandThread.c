#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vod_t ;
struct TYPE_12__ {int /*<<< orphan*/  p_fifo_cmd; } ;
typedef  TYPE_2__ vod_sys_t ;
struct TYPE_13__ {int i_type; int /*<<< orphan*/  psz_arg; int /*<<< orphan*/  p_media; } ;
typedef  TYPE_3__ rtsp_cmd_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_14__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  MediaDel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MediaSetup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RTSP_CMD_TYPE_ADD 130 
#define  RTSP_CMD_TYPE_DEL 129 
#define  RTSP_CMD_TYPE_STOP 128 
 int /*<<< orphan*/  VOD_MEDIA_STOP ; 
 TYPE_4__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vod_MediaControl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* CommandThread( void *obj )
{
    vod_t *p_vod = (vod_t*)obj;
    vod_sys_t *p_sys = p_vod->p_sys;

    for( ;; )
    {
        block_t *p_block_cmd = block_FifoGet( p_sys->p_fifo_cmd );
        rtsp_cmd_t cmd;

        if( !p_block_cmd )
            break;

        int canc = vlc_savecancel ();
        memcpy( &cmd, p_block_cmd->p_buffer, sizeof(cmd) );
        block_Release( p_block_cmd );

        /* */
        switch( cmd.i_type )
        {
        case RTSP_CMD_TYPE_ADD:
            MediaSetup(p_vod, cmd.p_media, cmd.psz_arg);
            break;
        case RTSP_CMD_TYPE_DEL:
            MediaDel(p_vod, cmd.p_media);
            break;
        case RTSP_CMD_TYPE_STOP:
            vod_MediaControl( p_vod, cmd.p_media, cmd.psz_arg, VOD_MEDIA_STOP );
            break;

        default:
            break;
        }

        free( cmd.psz_arg );
        vlc_restorecancel (canc);
    }

    return NULL;
}