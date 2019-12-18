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
 int /*<<< orphan*/  UNIT_NAME_PLAIN ; 
 char* cg_unescape (char*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int unit_name_is_valid (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool valid_slice_name(const char *p, size_t n) {

        if (!p)
                return false;

        if (n < STRLEN("x.slice"))
                return false;

        if (memcmp(p + n - 6, ".slice", 6) == 0) {
                char buf[n+1], *c;

                memcpy(buf, p, n);
                buf[n] = 0;

                c = cg_unescape(buf);

                return unit_name_is_valid(c, UNIT_NAME_PLAIN);
        }

        return false;
}