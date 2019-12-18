#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_setup_t ;
struct TYPE_8__ {scalar_t__ root; } ;
typedef  TYPE_2__ xcb_screen_t ;
struct TYPE_9__ {scalar_t__ rem; TYPE_1__* data; } ;
typedef  TYPE_3__ xcb_screen_iterator_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_7__ {scalar_t__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xcb_get_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_screen_next (TYPE_3__*) ; 
 TYPE_3__ xcb_setup_roots_iterator (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int xcb_screen_num(xcb_connection_t *conn, const xcb_screen_t *screen)
{
    const xcb_setup_t *setup = xcb_get_setup(conn);
    unsigned snum = 0;

    for (xcb_screen_iterator_t i = xcb_setup_roots_iterator(setup);
         i.rem > 0; xcb_screen_next(&i))
    {
        if (i.data->root == screen->root)
            return snum;
        snum++;
    }
    return -1;
}