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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {TYPE_1__* mod_map; } ;
struct TYPE_7__ {TYPE_2__ xwin; int /*<<< orphan*/  display; } ;
struct TYPE_5__ {int max_keypermod; scalar_t__* modifiermap; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  scalar_t__ KeyCode ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ NoSymbol ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ XKeysymToKeycode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
get_key_state(RDPCLIENT * This, unsigned int state, uint32 keysym)
{
	int modifierpos, key, keysymMask = 0;
	int offset;

	KeyCode keycode = XKeysymToKeycode(This->display, keysym);

	if (keycode == NoSymbol)
		return False;

	for (modifierpos = 0; modifierpos < 8; modifierpos++)
	{
		offset = This->xwin.mod_map->max_keypermod * modifierpos;

		for (key = 0; key < This->xwin.mod_map->max_keypermod; key++)
		{
			if (This->xwin.mod_map->modifiermap[offset + key] == keycode)
				keysymMask |= 1 << modifierpos;
		}
	}

	return (state & keysymMask) ? True : False;
}