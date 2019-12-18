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
 int /*<<< orphan*/  arg_system ; 
 int /*<<< orphan*/  console_setup () ; 
 int getpid_cached () ; 
 int /*<<< orphan*/  release_terminal () ; 
 int /*<<< orphan*/  setsid () ; 

__attribute__((used)) static void setup_console_terminal(bool skip_setup) {

        if (!arg_system)
                return;

        /* Become a session leader if we aren't one yet. */
        (void) setsid();

        /* If we are init, we connect stdin/stdout/stderr to /dev/null and make sure we don't have a controlling
         * tty. */
        (void) release_terminal();

        /* Reset the console, but only if this is really init and we are freshly booted */
        if (getpid_cached() == 1 && !skip_setup)
                (void) console_setup();
}