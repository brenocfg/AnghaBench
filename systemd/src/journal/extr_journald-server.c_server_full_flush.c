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
typedef  int /*<<< orphan*/  Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_flush_to_var (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  server_space_usage_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_vacuum (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void server_full_flush(Server *s) {
        assert(s);

        (void) server_flush_to_var(s, false);
        server_sync(s);
        server_vacuum(s, false);

        server_space_usage_message(s, NULL);
}