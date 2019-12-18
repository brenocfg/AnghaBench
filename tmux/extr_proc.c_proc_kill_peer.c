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
struct tmuxpeer {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEER_BAD ; 

void
proc_kill_peer(struct tmuxpeer *peer)
{
	peer->flags |= PEER_BAD;
}