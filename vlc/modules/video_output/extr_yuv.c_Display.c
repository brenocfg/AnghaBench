#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int i_sar_num; int i_sar_den; int i_visible_width; int i_visible_height; int i_frame_rate; int i_frame_rate_base; int i_x_offset; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_10__ {int i_sar_den; int i_sar_num; int /*<<< orphan*/  orientation; } ;
struct TYPE_11__ {TYPE_4__ fmt; TYPE_1__ source; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_12__ {int is_first; int /*<<< orphan*/  f; scalar_t__ is_yuv4mpeg2; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  TYPE_4__ video_format_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int i_visible_pitch; int i_visible_lines; int /*<<< orphan*/  i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_5__ plane_t ;
struct TYPE_15__ {int i_planes; TYPE_5__* p; scalar_t__ b_top_field_first; scalar_t__ b_progressive; } ;
typedef  TYPE_6__ picture_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ ORIENT_IS_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fwrite (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *picture)
{
    vout_display_sys_t *sys = vd->sys;

    /* */
    video_format_t fmt = vd->fmt;

    if (ORIENT_IS_SWAP(vd->source.orientation))
    {
        fmt.i_sar_num = vd->source.i_sar_den;
        fmt.i_sar_den = vd->source.i_sar_num;
    }
    else
    {
        fmt.i_sar_num = vd->source.i_sar_num;
        fmt.i_sar_den = vd->source.i_sar_den;
    }

    /* */
    char type;
    if (picture->b_progressive)
        type = 'p';
    else if (picture->b_top_field_first)
        type = 't';
    else
        type = 'b';

    if (type != 'p') {
        msg_Warn(vd, "Received a non progressive frame, "
                     "it will be written as progressive.");
        type = 'p';
    }

    /* */
    if (!sys->is_first) {
        const char *header;
        char buffer[5];
        if (sys->is_yuv4mpeg2) {
            /* MPlayer compatible header, unfortunately it doesn't tell you
             * the exact fourcc used. */
            header = "YUV4MPEG2";
        } else {
            snprintf(buffer, sizeof(buffer), "%4.4s",
                     (const char*)&fmt.i_chroma);
            header = buffer;
        }

        fprintf(sys->f, "%s W%d H%d F%d:%d I%c A%d:%d\n",
                header,
                fmt.i_visible_width, fmt.i_visible_height,
                fmt.i_frame_rate, fmt.i_frame_rate_base,
                type,
                fmt.i_sar_num, fmt.i_sar_den);
        sys->is_first = true;
    }

    /* */
    fprintf(sys->f, "FRAME\n");
    for (int i = 0; i < picture->i_planes; i++) {
        const plane_t *plane = &picture->p[i];
        const uint8_t *pixels = plane->p_pixels;

        pixels += (vd->fmt.i_x_offset * plane->i_visible_pitch)
                  / vd->fmt.i_visible_height;

        for( int y = 0; y < plane->i_visible_lines; y++) {
            const size_t written = fwrite(pixels, 1, plane->i_visible_pitch,
                                          sys->f);
            if (written != (size_t)plane->i_visible_pitch)
                msg_Warn(vd, "only %zd of %d bytes written",
                         written, plane->i_visible_pitch);

            pixels += plane->i_pitch;
        }
    }
    fflush(sys->f);
}