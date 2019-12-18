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
 size_t alignc ; 
 void* aligned_alloc (size_t,size_t) ; 
 size_t* alignv ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  test_posix_memalign (size_t,size_t) ; 

int main(void)
{
    void *p;

    /* aligned_alloc() */

    for (size_t i = 0; i < alignc; i++) {
        size_t align = alignv[i];

        assert((align & (align - 1)) == 0); /* must be a power of two */

        p = aligned_alloc(alignv[i], 0);
        free(p); /* must free {aligned_,c,m,c,re}alloc() allocations */

        for (size_t j = 0; j < alignc; j++) {
             size_t size = alignv[j];

             if (size < align)
                 continue; /* size must be a multiple of alignment */

             p = aligned_alloc(align, size);
             assert(p != NULL); /* small non-zero bytes allocation */
             assert(((uintptr_t)p & (align - 1)) == 0);
             free(p);
        }
    }

    /* posix_memalign() */

    for (size_t i = 0; i < 21; i++) {
        size_t align = (size_t)1 << i;

        test_posix_memalign(align, 0);
        test_posix_memalign(align, 1);
        test_posix_memalign(align, align - 1);
        test_posix_memalign(align, align);
        test_posix_memalign(align, align * 2);
    }

    return 0;
}