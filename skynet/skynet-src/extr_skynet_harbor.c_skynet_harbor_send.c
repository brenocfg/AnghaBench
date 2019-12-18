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
typedef  int /*<<< orphan*/  uint32_t ;
struct remote_message {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTYPE_SYSTEM ; 
 scalar_t__ REMOTE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ invalid_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_context_send (scalar_t__,struct remote_message*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void 
skynet_harbor_send(struct remote_message *rmsg, uint32_t source, int session) {
	assert(invalid_type(rmsg->type) && REMOTE);
	skynet_context_send(REMOTE, rmsg, sizeof(*rmsg) , source, PTYPE_SYSTEM , session);
}