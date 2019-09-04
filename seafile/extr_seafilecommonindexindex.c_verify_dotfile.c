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

__attribute__((used)) static int verify_dotfile(const char *rest)
{
    /*
     * The first character was '.', but that
     * has already been discarded, we now test
     * the rest.
     */
    switch (*rest) {
        /* "." is not allowed */
    case '\0': case '/':
        return 0;

        /*
         * ".git" followed by  NUL or slash is bad. This
         * shares the path end test with the ".." case.
         */
    case 'g':
        if (rest[1] != 'i')
            break;
        if (rest[2] != 't')
            break;
        rest += 2;
        /* fallthrough */
    case '.':
        if (rest[1] == '\0' || rest[1] == '/')
            return 0;
    }
    return 1;
}