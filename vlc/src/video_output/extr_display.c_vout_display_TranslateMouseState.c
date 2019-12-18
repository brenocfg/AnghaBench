#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int orientation; int i_x_offset; int i_visible_width; int i_y_offset; int i_visible_height; } ;
struct TYPE_10__ {TYPE_8__ source; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_11__ {int const width; int const height; int x; int y; } ;
typedef  TYPE_2__ vout_display_place_t ;
struct TYPE_12__ {int i_x; int i_y; int /*<<< orphan*/  b_double_click; int /*<<< orphan*/  i_pressed; } ;
typedef  TYPE_3__ vlc_mouse_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  ORIENT_BOTTOM_LEFT 135 
#define  ORIENT_BOTTOM_RIGHT 134 
#define  ORIENT_LEFT_BOTTOM 133 
#define  ORIENT_LEFT_TOP 132 
#define  ORIENT_RIGHT_BOTTOM 131 
#define  ORIENT_RIGHT_TOP 130 
#define  ORIENT_TOP_LEFT 129 
#define  ORIENT_TOP_RIGHT 128 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vout_display_PlacePicture (TYPE_2__*,TYPE_8__*,int /*<<< orphan*/ ) ; 

void vout_display_TranslateMouseState(vout_display_t *vd, vlc_mouse_t *video,
                                      const vlc_mouse_t *window)
{
    vout_display_place_t place;

    /* Translate window coordinates to video coordinates */
    vout_display_PlacePicture(&place, &vd->source, vd->cfg);

    if (place.width <= 0 || place.height <= 0) {
        memset(video, 0, sizeof (*video));
        return;
    }

    const int wx = window->i_x, wy = window->i_y;
    int x, y;

    switch (vd->source.orientation) {
        case ORIENT_TOP_LEFT:
            x = wx;
            y = wy;
            break;
        case ORIENT_TOP_RIGHT:
            x = place.width - wx;
            y = wy;
            break;
        case ORIENT_BOTTOM_LEFT:
            x = wx;
            y = place.height - wy;
            break;
        case ORIENT_BOTTOM_RIGHT:
            x = place.width - wx;
            y = place.height - wy;
            break;
        case ORIENT_LEFT_TOP:
            x = wy;
            y = wx;
            break;
        case ORIENT_LEFT_BOTTOM:
            x = wy;
            y = place.width - wx;
            break;
        case ORIENT_RIGHT_TOP:
            x = place.height - wy;
            y = wx;
            break;
        case ORIENT_RIGHT_BOTTOM:
            x = place.height - wy;
            y = place.width - wx;
            break;
        default:
            vlc_assert_unreachable();
    }

    video->i_x = vd->source.i_x_offset
        + (int64_t)(x - place.x) * vd->source.i_visible_width / place.width;
    video->i_y = vd->source.i_y_offset
        + (int64_t)(y - place.y) * vd->source.i_visible_height / place.height;
    video->i_pressed = window->i_pressed;
    video->b_double_click = window->b_double_click;
}