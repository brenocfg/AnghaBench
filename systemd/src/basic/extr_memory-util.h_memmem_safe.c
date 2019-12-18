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
 int /*<<< orphan*/  assert (void const*) ; 
 void* memmem (void const*,size_t,void const*,size_t) ; 

__attribute__((used)) static inline void *memmem_safe(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen) {

        if (needlelen <= 0)
                return (void*) haystack;

        if (haystacklen < needlelen)
                return NULL;

        assert(haystack);
        assert(needle);

        return memmem(haystack, haystacklen, needle, needlelen);
}