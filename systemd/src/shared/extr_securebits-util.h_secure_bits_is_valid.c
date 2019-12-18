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
 int SECURE_ALL_BITS ; 
 int SECURE_ALL_LOCKS ; 

__attribute__((used)) static inline bool secure_bits_is_valid(int i) {
        return ((SECURE_ALL_BITS | SECURE_ALL_LOCKS) & i) == i;
}