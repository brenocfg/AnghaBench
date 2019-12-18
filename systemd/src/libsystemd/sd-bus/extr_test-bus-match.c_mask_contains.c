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
 unsigned int ELEMENTSOF (int*) ; 
 int* mask ; 

__attribute__((used)) static bool mask_contains(unsigned a[], unsigned n) {
        unsigned i, j;

        for (i = 0; i < ELEMENTSOF(mask); i++) {
                bool found = false;

                for (j = 0; j < n; j++)
                        if (a[j] == i) {
                                found = true;
                                break;
                        }

                if (found != mask[i])
                        return false;
        }

        return true;
}