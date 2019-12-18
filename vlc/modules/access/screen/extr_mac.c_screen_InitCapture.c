#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int rate; scalar_t__ screen_width; scalar_t__ screen_height; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  screen_top; int /*<<< orphan*/  screen_left; scalar_t__ display_id; } ;
typedef  TYPE_4__ screen_data_t ;
struct TYPE_18__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ demux_t ;
struct TYPE_16__ {scalar_t__ i_visible_width; scalar_t__ i_width; scalar_t__ i_visible_height; scalar_t__ i_height; int i_bits_per_pixel; int i_rmask; int i_gmask; int i_bmask; int i_sar_num; int i_sar_den; int i_frame_rate; int i_frame_rate_base; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_13__ {TYPE_3__ video; } ;
struct TYPE_19__ {scalar_t__ i_display_id; unsigned int i_screen_index; scalar_t__ i_width; scalar_t__ i_height; TYPE_10__ fmt; TYPE_4__* p_data; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_15__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_20__ {TYPE_2__ size; TYPE_1__ origin; } ;
typedef  TYPE_7__ CGRect ;
typedef  int /*<<< orphan*/  CGLError ;
typedef  scalar_t__ CGDirectDisplayID ;

/* Variables and functions */
 TYPE_7__ CGDisplayBounds (scalar_t__) ; 
 int /*<<< orphan*/  CGGetOnlineDisplayList (unsigned int,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_RGB32 ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ kCGDirectMainDisplay ; 
 int var_InheritFloat (TYPE_5__*,char*) ; 
 scalar_t__* vlc_alloc (unsigned int,int) ; 

int screen_InitCapture(demux_t *p_demux)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    screen_data_t *p_data;
    CGLError returnedError;

    p_sys->p_data = p_data = calloc(1, sizeof(screen_data_t));
    if (!p_data)
        return VLC_ENOMEM;

    /* fetch the screen we should capture */
    p_data->display_id = kCGDirectMainDisplay;
    p_data->rate = var_InheritFloat(p_demux, "screen-fps");

    unsigned int displayCount = 0;
    returnedError = CGGetOnlineDisplayList(0, NULL, &displayCount);
    if (!returnedError) {
        CGDirectDisplayID *ids;
        ids = vlc_alloc(displayCount, sizeof(CGDirectDisplayID));
        returnedError = CGGetOnlineDisplayList(displayCount, ids, &displayCount);
        if (!returnedError) {
            if (p_sys->i_display_id > 0) {
                for (unsigned int i = 0; i < displayCount; i++) {
                    if (p_sys->i_display_id == ids[i]) {
                        p_data->display_id = ids[i];
                        break;
                    }
                }
            } else if (p_sys->i_screen_index > 0 && p_sys->i_screen_index <= displayCount)
                p_data->display_id = ids[p_sys->i_screen_index - 1];
        }
        free(ids);
    }

    /* Get the device context for the whole screen */
    CGRect rect = CGDisplayBounds(p_data->display_id);
    p_data->screen_left = rect.origin.x;
    p_data->screen_top = rect.origin.y;
    p_data->screen_width = rect.size.width;
    p_data->screen_height = rect.size.height;

    p_data->width = p_sys->i_width;
    p_data->height = p_sys->i_height;
    if (p_data->width <= 0 || p_data->height <= 0) {
        p_data->width = p_data->screen_width;
        p_data->height = p_data->screen_height;
    }

    /* setup format */
    es_format_Init(&p_sys->fmt, VIDEO_ES, VLC_CODEC_RGB32);
    p_sys->fmt.video.i_visible_width   =
    p_sys->fmt.video.i_width           = rect.size.width;
    p_sys->fmt.video.i_visible_height  =
    p_sys->fmt.video.i_height          = rect.size.height;
    p_sys->fmt.video.i_bits_per_pixel  = 32;
    p_sys->fmt.video.i_chroma          = VLC_CODEC_RGB32;
    p_sys->fmt.video.i_rmask           = 0x00ff0000;
    p_sys->fmt.video.i_gmask           = 0x0000ff00;
    p_sys->fmt.video.i_bmask           = 0x000000ff;
    p_sys->fmt.video.i_sar_num         =
    p_sys->fmt.video.i_sar_den         = 1;
    p_sys->fmt.video.i_frame_rate      = 1000 * p_data->rate;
    p_sys->fmt.video.i_frame_rate_base = 1000;

    return VLC_SUCCESS;
}