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
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ isempty (char const*) ; 
 char* strdup (char const*) ; 
 char* strjoin (char*,char const*,char*,char const*,char*) ; 
 scalar_t__ urlify_enabled () ; 

int terminal_urlify(const char *url, const char *text, char **ret) {
        char *n;

        assert(url);

        /* Takes an URL and a pretty string and formats it as clickable link for the terminal. See
         * https://gist.github.com/egmontkob/eb114294efbcd5adb1944c9f3cb5feda for details. */

        if (isempty(text))
                text = url;

        if (urlify_enabled())
                n = strjoin("\x1B]8;;", url, "\a", text, "\x1B]8;;\a");
        else
                n = strdup(text);
        if (!n)
                return -ENOMEM;

        *ret = n;
        return 0;
}