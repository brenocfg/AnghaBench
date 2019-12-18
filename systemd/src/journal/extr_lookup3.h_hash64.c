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
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  jenkins_hashlittle2 (void const*,size_t,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static inline uint64_t hash64(const void *data, size_t length) {
        uint32_t a = 0, b = 0;

        jenkins_hashlittle2(data, length, &a, &b);

        return ((uint64_t) a << 32ULL) | (uint64_t) b;
}