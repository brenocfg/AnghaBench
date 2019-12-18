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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int AskPasswordFlags ;

/* Variables and functions */
 int ASK_PASSWORD_ACCEPT_CACHED ; 
 int ASK_PASSWORD_NO_AGENT ; 
 int ASK_PASSWORD_NO_TTY ; 
 int ENOKEY ; 
 int EUNATCH ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int ask_password_agent (char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int,char***) ; 
 int ask_password_keyring (char const*,int,char***) ; 
 int ask_password_tty (int,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char***) ; 
 int /*<<< orphan*/  assert (char***) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 

int ask_password_auto(
                const char *message,
                const char *icon,
                const char *id,
                const char *keyname,
                usec_t until,
                AskPasswordFlags flags,
                char ***ret) {

        int r;

        assert(ret);

        if ((flags & ASK_PASSWORD_ACCEPT_CACHED) &&
            keyname &&
            ((flags & ASK_PASSWORD_NO_TTY) || !isatty(STDIN_FILENO)) &&
            (flags & ASK_PASSWORD_NO_AGENT)) {
                r = ask_password_keyring(keyname, flags, ret);
                if (r != -ENOKEY)
                        return r;
        }

        if (!(flags & ASK_PASSWORD_NO_TTY) && isatty(STDIN_FILENO))
                return ask_password_tty(-1, message, keyname, until, flags, NULL, ret);

        if (!(flags & ASK_PASSWORD_NO_AGENT))
                return ask_password_agent(message, icon, id, keyname, until, flags, ret);

        return -EUNATCH;
}