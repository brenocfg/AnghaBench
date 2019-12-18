#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int i_stream_type; } ;
typedef  TYPE_2__ tsmux_stream_t ;
struct TYPE_6__ {int i_visible_height; int i_visible_width; } ;
struct TYPE_8__ {TYPE_1__ video; } ;
typedef  TYPE_3__ es_format_t ;

/* Variables and functions */
 int VIDEO_ES ; 

__attribute__((used)) static void UpdateServiceType( uint8_t *pi_service_cat, uint8_t *pi_service_type,
                               const tsmux_stream_t *p_ts, const es_format_t *fmt )
{
    uint8_t i_type = 0x00;

    switch( p_ts->i_stream_type )
    {
        case 0x01: /* MPEG1 */
        case 0x02: /* MPEG2 */
        case 0x80:
            i_type = 0x01;
            break;

        case 0x24: /* HEVC */
        case 0x10: /* MPEG4 */
        case 0x1b: /* H264 */
        case 0xA0: /* private */
        case 0xd1: /* dirac */
            i_type = 0x16;
            break;

        default:
            break;
    }

    if( i_type == 0x01 && fmt->video.i_visible_height > 468 &&
                          fmt->video.i_visible_width > 720 ) /* MPEG2 SD -> HD */
    {
         i_type = 0x11;
    }
    else if( i_type == 0x16 && fmt->video.i_visible_height > 468 &&
                               fmt->video.i_visible_width > 720 ) /* Advanced codec SD -> HD */
    {
         i_type = 0x19;
    }

    if( i_type != 0x00 )
    {
        if( *pi_service_cat != VIDEO_ES || i_type > *pi_service_type )
        {
            *pi_service_type = i_type;
            *pi_service_cat = VIDEO_ES;
        }
        return;
    }

    if( *pi_service_cat != VIDEO_ES ) /* Don't overwrite video */
    {
        /* Not video, try audio */
        switch( p_ts->i_stream_type )
        {
            case 0x03: /* MPEG1 audio */
            case 0x04: /* MPEG2 audio */
                i_type = 0x02;
                break;

            case 0x06:
            case 0x0f:
            case 0x81:
            case 0x83:
                i_type = 0x0A; /* Avanced codec digital radio */
                break;

            default:
                break;
        }

        if( i_type > *pi_service_type )
            *pi_service_type = i_type;
    }
}