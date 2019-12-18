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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u ;

/* Variables and functions */
 int /*<<< orphan*/  random_bytes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline uint64_t random_u64(void) {
        uint64_t u;
        random_bytes(&u, sizeof(u));
        return u;
}