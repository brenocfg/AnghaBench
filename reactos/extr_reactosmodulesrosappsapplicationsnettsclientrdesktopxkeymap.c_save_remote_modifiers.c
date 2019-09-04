#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int /*<<< orphan*/  remote_modifier_state; int /*<<< orphan*/  saved_remote_modifier_state; } ;
struct TYPE_5__ {TYPE_1__ xkeymap; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ is_modifier (int /*<<< orphan*/ ) ; 

void
save_remote_modifiers(RDPCLIENT * This, uint8 scancode)
{
	if (is_modifier(scancode))
		return;

	This->xkeymap.saved_remote_modifier_state = This->xkeymap.remote_modifier_state;
}