#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_FLAG_NUMLOCK ; 
 int /*<<< orphan*/  XK_Num_Lock ; 
 scalar_t__ get_key_state (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

uint16
ui_get_numlock_state(RDPCLIENT * This, unsigned int state)
{
	uint16 numlock_state = 0;

	if (get_key_state(This, state, XK_Num_Lock))
		numlock_state = KBD_FLAG_NUMLOCK;

	return numlock_state;
}