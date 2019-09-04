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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {scalar_t__ use_rdp5; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_KEYRELEASE ; 
 int /*<<< orphan*/  SCANCODE_CHAR_LWIN ; 
 int /*<<< orphan*/  rdp_send_scancode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reset_winkey(RDPCLIENT * This, uint32 ev_time)
{
	if (This->use_rdp5)
	{
		/* For some reason, it seems to suffice to release
		 *either* the left or right winkey. */
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LWIN);
	}
}