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
 int unit_name_to_instance (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int unit_name_classify(const char *n) {
        return unit_name_to_instance(n, NULL);
}