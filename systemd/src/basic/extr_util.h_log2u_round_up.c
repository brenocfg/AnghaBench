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
 int /*<<< orphan*/  assert (int) ; 
 int log2u (unsigned int) ; 

__attribute__((used)) static inline unsigned log2u_round_up(unsigned x) {
        assert(x > 0);

        if (x == 1)
                return 0;

        return log2u(x - 1) + 1;
}