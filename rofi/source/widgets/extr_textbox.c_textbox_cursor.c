#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int blink; int /*<<< orphan*/  cursor; int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ textbox ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int g_utf8_strlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  widget_queue_redraw (int /*<<< orphan*/ ) ; 

void textbox_cursor ( textbox *tb, int pos )
{
    if ( tb == NULL ) {
        return;
    }
    int length = ( tb->text == NULL ) ? 0 : g_utf8_strlen ( tb->text, -1 );
    tb->cursor = MAX ( 0, MIN ( length, pos ) );
    // Stop blink!
    tb->blink = 3;
    widget_queue_redraw ( WIDGET ( tb ) );
}