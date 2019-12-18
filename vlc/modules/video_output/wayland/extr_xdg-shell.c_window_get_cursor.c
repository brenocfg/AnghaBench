#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_7__ {struct wl_surface* cursor_surface; TYPE_1__* cursor; } ;
typedef  TYPE_3__ vout_window_sys_t ;
struct wl_surface {int dummy; } ;
struct wl_cursor_image {int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {scalar_t__ image_count; struct wl_cursor_image** images; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_cursor_image_get_buffer (struct wl_cursor_image*) ; 
 int /*<<< orphan*/  wl_surface_attach (struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (struct wl_surface*) ; 
 int /*<<< orphan*/  wl_surface_damage (struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct wl_surface *window_get_cursor(vout_window_t *wnd, int32_t *restrict hsx,
                                     int32_t *restrict hsy)
{
    vout_window_sys_t *sys = wnd->sys;

    if (unlikely(sys->cursor == NULL))
        return NULL;

    assert(sys->cursor->image_count > 0);

    /* TODO? animated cursor (more than one image) */
    struct wl_cursor_image *img = sys->cursor->images[0];
    struct wl_surface *surface = sys->cursor_surface;

    if (likely(surface != NULL))
    {
        wl_surface_attach(surface, wl_cursor_image_get_buffer(img), 0, 0);
        wl_surface_damage(surface, 0, 0, img->width, img->height);
        wl_surface_commit(surface);
    }

    *hsx = img->hotspot_x;
    *hsy = img->hotspot_y;
    return surface;
}