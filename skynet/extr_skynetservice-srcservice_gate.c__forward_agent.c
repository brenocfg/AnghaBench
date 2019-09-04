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
typedef  void* uint32_t ;
struct gate {struct connection* conn; int /*<<< orphan*/  hash; } ;
struct connection {void* client; void* agent; } ;

/* Variables and functions */
 int hashid_lookup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
_forward_agent(struct gate * g, int fd, uint32_t agentaddr, uint32_t clientaddr) {
	int id = hashid_lookup(&g->hash, fd);
	if (id >=0) {
		struct connection * agent = &g->conn[id];
		agent->agent = agentaddr;
		agent->client = clientaddr;
	}
}