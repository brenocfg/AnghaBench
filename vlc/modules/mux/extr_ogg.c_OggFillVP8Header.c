#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {TYPE_2__* p_fmt; scalar_t__ p_sys; } ;
typedef  TYPE_5__ sout_input_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_frame_rate_base; int /*<<< orphan*/  i_frame_rate; } ;
struct TYPE_11__ {TYPE_3__ video; } ;
struct TYPE_13__ {TYPE_4__ fmt; } ;
typedef  TYPE_6__ ogg_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_sar_num; int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_width; } ;
struct TYPE_9__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetDWBE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWBE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void OggFillVP8Header( uint8_t *p_buffer, sout_input_t *p_input )
{
    ogg_stream_t *p_stream = (ogg_stream_t *) p_input->p_sys;

    memcpy( p_buffer, "OVP80\x01\x01\x00", 8 );
    SetWBE( &p_buffer[8], p_input->p_fmt->video.i_width );
    SetDWBE( &p_buffer[14], p_input->p_fmt->video.i_sar_den );/* 24 bits, 15~ */
    SetDWBE( &p_buffer[11], p_input->p_fmt->video.i_sar_num );/* 24 bits, 12~ */
    SetWBE( &p_buffer[10], p_input->p_fmt->video.i_height );
    SetDWBE( &p_buffer[18], p_stream->fmt.video.i_frame_rate );
    SetDWBE( &p_buffer[22], p_stream->fmt.video.i_frame_rate_base );
}