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
struct server {int tunnel_forward; int /*<<< orphan*/  local_port; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGW (char*) ; 
 int enable_tunnel_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_tunnel_reverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
enable_tunnel(struct server *server) {
    if (enable_tunnel_reverse(server->serial, server->local_port)) {
        return true;
    }

    LOGW("'adb reverse' failed, fallback to 'adb forward'");
    server->tunnel_forward = true;
    return enable_tunnel_forward(server->serial, server->local_port);
}