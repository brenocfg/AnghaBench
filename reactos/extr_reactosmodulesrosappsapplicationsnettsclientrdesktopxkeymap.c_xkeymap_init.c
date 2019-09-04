#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  min_keycode; int /*<<< orphan*/  keymap_loaded; } ;
struct TYPE_6__ {TYPE_1__ xkeymap; int /*<<< orphan*/  display; int /*<<< orphan*/  keymapname; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XDisplayKeycodes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xkeymap_read (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
xkeymap_init(RDPCLIENT * This)
{
	unsigned int max_keycode;

	if (strcmp(This->keymapname, "none"))
	{
		if (xkeymap_read(This, This->keymapname))
			This->xkeymap.keymap_loaded = True;
	}

	XDisplayKeycodes(This->display, &This->xkeymap.min_keycode, (int *) &max_keycode);
}