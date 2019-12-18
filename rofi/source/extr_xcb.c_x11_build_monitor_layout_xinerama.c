#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ rem; TYPE_1__* data; } ;
typedef  TYPE_2__ xcb_xinerama_screen_info_iterator_t ;
typedef  int /*<<< orphan*/  xcb_xinerama_query_screens_reply_t ;
typedef  int /*<<< orphan*/  xcb_xinerama_query_screens_cookie_t ;
struct TYPE_10__ {int /*<<< orphan*/  monitor_id; struct TYPE_10__* next; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ workarea ;
struct TYPE_11__ {TYPE_3__* monitors; int /*<<< orphan*/  connection; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_org; int /*<<< orphan*/  x_org; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_3__* g_malloc0 (int) ; 
 TYPE_6__* xcb ; 
 int /*<<< orphan*/ * xcb_xinerama_query_screens_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ xcb_xinerama_query_screens_screen_info_iterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_query_screens_unchecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xinerama_screen_info_next (TYPE_2__*) ; 

__attribute__((used)) static void x11_build_monitor_layout_xinerama ()
{
    xcb_xinerama_query_screens_cookie_t screens_cookie = xcb_xinerama_query_screens_unchecked (
        xcb->connection
        );

    xcb_xinerama_query_screens_reply_t *screens_reply = xcb_xinerama_query_screens_reply (
        xcb->connection,
        screens_cookie,
        NULL
        );

    xcb_xinerama_screen_info_iterator_t screens_iterator = xcb_xinerama_query_screens_screen_info_iterator (
        screens_reply
        );

    for (; screens_iterator.rem > 0; xcb_xinerama_screen_info_next ( &screens_iterator ) ) {
        workarea *w = g_malloc0 ( sizeof ( workarea ) );

        w->x = screens_iterator.data->x_org;
        w->y = screens_iterator.data->y_org;
        w->w = screens_iterator.data->width;
        w->h = screens_iterator.data->height;

        w->next       = xcb->monitors;
        xcb->monitors = w;
    }

    int index = 0;
    for ( workarea *iter = xcb->monitors; iter; iter = iter->next ) {
        iter->monitor_id = index++;
    }

    free ( screens_reply );
}