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
 int write_string_file_atomic_label_ts (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int write_string_file_atomic_label(const char *fn, const char *line) {
        return write_string_file_atomic_label_ts(fn, line, NULL);
}