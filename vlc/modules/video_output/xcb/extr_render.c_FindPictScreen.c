#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_setup_t ;
typedef  int /*<<< orphan*/  xcb_screen_t ;
struct TYPE_7__ {scalar_t__ rem; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ xcb_screen_iterator_t ;
typedef  int /*<<< orphan*/  xcb_render_query_pict_formats_reply_t ;
typedef  int /*<<< orphan*/  xcb_render_pictscreen_t ;
struct TYPE_8__ {scalar_t__ rem; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_2__ xcb_render_pictscreen_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xcb_render_pictscreen_next (TYPE_2__*) ; 
 TYPE_2__ xcb_render_query_pict_formats_screens_iterator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xcb_screen_next (TYPE_1__*) ; 
 TYPE_1__ xcb_setup_roots_iterator (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const xcb_render_pictscreen_t *
FindPictScreen(const xcb_setup_t *setup, const xcb_screen_t *scr,
               const xcb_render_query_pict_formats_reply_t *r)
{
    xcb_screen_iterator_t si = xcb_setup_roots_iterator(setup);
    unsigned n = 0;

    while (si.data != scr) {
        assert(si.rem > 0);
        n++;
        xcb_screen_next(&si);
    }

    xcb_render_pictscreen_iterator_t rsi =
        xcb_render_query_pict_formats_screens_iterator(r);

    while (n > 0) {
        if (unlikely(rsi.rem == 0))
            return NULL; /* buggy server */

        n--;
        xcb_render_pictscreen_next(&rsi);
    }
    return rsi.data;
}