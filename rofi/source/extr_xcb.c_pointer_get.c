#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_5__ {int root_x; int root_y; } ;
typedef  TYPE_1__ xcb_query_pointer_reply_t ;
typedef  int /*<<< orphan*/  xcb_query_pointer_cookie_t ;
struct TYPE_6__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_3__* xcb ; 
 int /*<<< orphan*/  xcb_query_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_query_pointer_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pointer_get ( xcb_window_t root, int *x, int *y )
{
    *x = 0;
    *y = 0;
    xcb_query_pointer_cookie_t c  = xcb_query_pointer ( xcb->connection, root );
    xcb_query_pointer_reply_t  *r = xcb_query_pointer_reply ( xcb->connection, c, NULL );
    if ( r ) {
        *x = r->root_x;
        *y = r->root_y;
        free ( r );
        return TRUE;
    }

    return FALSE;
}