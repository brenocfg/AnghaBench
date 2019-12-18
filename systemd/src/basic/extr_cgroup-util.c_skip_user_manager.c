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
 size_t STRLEN (char*) ; 
 scalar_t__ isempty (char const*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ parse_uid (char*,int /*<<< orphan*/ *) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 

__attribute__((used)) static const char *skip_user_manager(const char *p) {
        size_t n;

        if (isempty(p))
                return NULL;

        p += strspn(p, "/");

        n = strcspn(p, "/");
        if (n < STRLEN("user@x.service"))
                return NULL;

        if (memcmp(p, "user@", 5) == 0 && memcmp(p + n - 8, ".service", 8) == 0) {
                char buf[n - 5 - 8 + 1];

                memcpy(buf, p + 5, n - 5 - 8);
                buf[n - 5 - 8] = 0;

                /* Note that user manager services never need unescaping,
                 * since they cannot conflict with the kernel's own
                 * names, hence we don't need to call cg_unescape()
                 * here. */

                if (parse_uid(buf, NULL) < 0)
                        return NULL;

                p += n;
                p += strspn(p, "/");

                return p;
        }

        return NULL;
}