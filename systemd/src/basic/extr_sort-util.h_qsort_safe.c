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
typedef  int /*<<< orphan*/  __compar_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  qsort (void*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qsort_safe(void *base, size_t nmemb, size_t size, __compar_fn_t compar) {
        if (nmemb <= 1)
                return;

        assert(base);
        qsort(base, nmemb, size, compar);
}