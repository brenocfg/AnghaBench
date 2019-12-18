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
typedef  int /*<<< orphan*/  AskPasswordFlags ;

/* Variables and functions */
 int add_to_keyring (char const*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int log_debug_errno (int,char*) ; 

__attribute__((used)) static int add_to_keyring_and_log(const char *keyname, AskPasswordFlags flags, char **passwords) {
        int r;

        assert(keyname);

        r = add_to_keyring(keyname, flags, passwords);
        if (r < 0)
                return log_debug_errno(r, "Failed to add password to keyring: %m");

        return 0;
}