#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cursorX; int cursorY; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfbUndrawCursor (TYPE_1__*) ; 
 TYPE_1__* server ; 

void
ui_move_pointer(int x, int y)
{
	// TODO: Is there a way to send x,y even if cursor encoding is active?
	rfbUndrawCursor(server);
	server->cursorX = x;
	server->cursorY = y;
}