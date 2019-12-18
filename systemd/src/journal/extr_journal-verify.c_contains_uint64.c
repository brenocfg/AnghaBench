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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  MMapFileDescriptor ;
typedef  int /*<<< orphan*/  MMapCache ;

/* Variables and functions */
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int mmap_cache_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int contains_uint64(MMapCache *m, MMapFileDescriptor *f, uint64_t n, uint64_t p) {
        uint64_t a, b;
        int r;

        assert(m);
        assert(f);

        /* Bisection ... */

        a = 0; b = n;
        while (a < b) {
                uint64_t c, *z;

                c = (a + b) / 2;

                r = mmap_cache_get(m, f, PROT_READ|PROT_WRITE, 0, false, c * sizeof(uint64_t), sizeof(uint64_t), NULL, (void **) &z, NULL);
                if (r < 0)
                        return r;

                if (*z == p)
                        return 1;

                if (a + 1 >= b)
                        return 0;

                if (p < *z)
                        b = c;
                else
                        a = c;
        }

        return 0;
}