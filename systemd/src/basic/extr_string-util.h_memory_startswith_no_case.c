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
typedef  void uint8_t ;

/* Variables and functions */
 scalar_t__ ascii_tolower (char const) ; 
 int /*<<< orphan*/  assert (void const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline void *memory_startswith_no_case(const void *p, size_t sz, const char *token) {
        size_t n, i;

        assert(token);

        n = strlen(token);
        if (sz < n)
                return NULL;

        assert(p);

        for (i = 0; i < n; i++) {
                if (ascii_tolower(((char *)p)[i]) != ascii_tolower(token[i]))
                        return NULL;
        }

        return (uint8_t*) p + n;
}