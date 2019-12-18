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
struct server {int /*<<< orphan*/  serial; int /*<<< orphan*/  local_port; scalar_t__ tunnel_forward; } ;

/* Variables and functions */
 int disable_tunnel_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int disable_tunnel_reverse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
disable_tunnel(struct server *server) {
    if (server->tunnel_forward) {
        return disable_tunnel_forward(server->serial, server->local_port);
    }
    return disable_tunnel_reverse(server->serial);
}