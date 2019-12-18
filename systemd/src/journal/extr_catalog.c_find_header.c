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
 int /*<<< orphan*/  NEWLINE ; 
 int /*<<< orphan*/  WHITESPACE ; 
 int /*<<< orphan*/  next_header (char const**) ; 
 char* startswith (char const*,char const*) ; 
 int /*<<< orphan*/  strcspn (char const*,int /*<<< orphan*/ ) ; 
 char* strndup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *find_header(const char *s, const char *header) {

        for (;;) {
                const char *v;

                v = startswith(s, header);
                if (v) {
                        v += strspn(v, WHITESPACE);
                        return strndup(v, strcspn(v, NEWLINE));
                }

                if (!next_header(&s))
                        return NULL;
        }
}