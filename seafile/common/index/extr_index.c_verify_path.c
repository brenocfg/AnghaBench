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
 int /*<<< orphan*/  verify_dotfile (char const*) ; 

int verify_path(const char *path)
{
    char c;

    goto inside;
    for (;;) {
        if (!c)
            return 1;
        if (c == '/') {
        inside:
            c = *path++;
            switch (c) {
            default:
                continue;
            case '/': case '\0':
                break;
            case '.':
                if (verify_dotfile(path))
                    continue;
            }
            return 0;
        }
        c = *path++;
    }
}