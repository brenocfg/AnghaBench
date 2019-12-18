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
 int /*<<< orphan*/  PROJECT_VERSION ; 
 int /*<<< orphan*/  STRINGIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int print_version(void) {
        /* Dracut relies on the version being a single integer */
        puts(STRINGIFY(PROJECT_VERSION));
        return 0;
}