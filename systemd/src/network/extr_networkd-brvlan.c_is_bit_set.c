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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  scope ;

/* Variables and functions */
 unsigned int UINT32_C (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bool is_bit_set(unsigned bit, uint32_t scope) {
        assert(bit < sizeof(scope)*8);
        return scope & (UINT32_C(1) << bit);
}