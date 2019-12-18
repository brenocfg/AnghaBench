#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tmuxpeer {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int peerid; scalar_t__ type; } ;
struct imsg {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ MSG_VERSION ; 
 int /*<<< orphan*/  PEER_BAD ; 
 int PROTOCOL_VERSION ; 
 int /*<<< orphan*/  log_debug (char*,struct tmuxpeer*,int) ; 
 int /*<<< orphan*/  proc_send (struct tmuxpeer*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
peer_check_version(struct tmuxpeer *peer, struct imsg *imsg)
{
	int	version;

	version = imsg->hdr.peerid & 0xff;
	if (imsg->hdr.type != MSG_VERSION && version != PROTOCOL_VERSION) {
		log_debug("peer %p bad version %d", peer, version);

		proc_send(peer, MSG_VERSION, -1, NULL, 0);
		peer->flags |= PEER_BAD;

		return (-1);
	}
	return (0);
}