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
 int /*<<< orphan*/  assert_cc (int) ; 
 int safe_atolu (char const*,size_t*) ; 

__attribute__((used)) static inline int safe_atozu(const char *s, size_t *ret_u) {
        assert_cc(sizeof(size_t) == sizeof(long unsigned));
        return safe_atolu(s, ret_u);
}