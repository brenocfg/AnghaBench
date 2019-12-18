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

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ load_unix_sockets () ; 
 int /*<<< orphan*/  set_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unix_sockets ; 

__attribute__((used)) static bool unix_socket_alive(const char *fn) {
        assert(fn);

        if (load_unix_sockets() < 0)
                return true;     /* We don't know, so assume yes */

        return !!set_get(unix_sockets, (char*) fn);
}