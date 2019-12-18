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
 int /*<<< orphan*/  assert (void const*) ; 
 scalar_t__ memcmp (void const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline void *memory_startswith(const void *p, size_t sz, const char *token) {
        size_t n;

        assert(token);

        n = strlen(token);
        if (sz < n)
                return NULL;

        assert(p);

        if (memcmp(p, token, n) != 0)
                return NULL;

        return (uint8_t*) p + n;
}