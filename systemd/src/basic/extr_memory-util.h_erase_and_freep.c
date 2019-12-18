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
 int /*<<< orphan*/  explicit_bzero_safe (void*,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 size_t malloc_usable_size (void*) ; 

__attribute__((used)) static inline void erase_and_freep(void *p) {
        void *ptr = *(void**) p;

        if (ptr) {
                size_t l = malloc_usable_size(ptr);
                explicit_bzero_safe(ptr, l);
                free(ptr);
        }
}