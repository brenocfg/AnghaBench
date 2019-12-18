#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vod_t ;
struct TYPE_13__ {int /*<<< orphan*/  p_fifo_cmd; } ;
typedef  TYPE_2__ vod_sys_t ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ vod_media_t ;
typedef  int /*<<< orphan*/  rtsp_cmd_type_t ;
struct TYPE_15__ {double f_arg; void* psz_arg; int /*<<< orphan*/  i_arg; void* psz_session; int /*<<< orphan*/  i_media_id; TYPE_3__* p_media; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_4__ rtsp_cmd_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_16__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 TYPE_5__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_FifoPut (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static void CommandPush( vod_t *p_vod, rtsp_cmd_type_t i_type, vod_media_t *p_media, const char *psz_session, int64_t i_arg,
                         double f_arg, const char *psz_arg )
{
    rtsp_cmd_t cmd;
    block_t *p_cmd;

    memset( &cmd, 0, sizeof(cmd) );
    cmd.i_type = i_type;
    cmd.p_media = p_media;
    if( p_media )
        cmd.i_media_id = p_media->id;
    if( psz_session )
        cmd.psz_session = strdup(psz_session);
    cmd.i_arg = i_arg;
    cmd.f_arg = f_arg;
    if( psz_arg )
        cmd.psz_arg = strdup(psz_arg);

    p_cmd = block_Alloc( sizeof(rtsp_cmd_t) );
    memcpy( p_cmd->p_buffer, &cmd, sizeof(cmd) );

    vod_sys_t *p_sys = p_vod->p_sys;
    block_FifoPut( p_sys->p_fifo_cmd, p_cmd );
}