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
 int read_full_file_full (char const*,int /*<<< orphan*/ ,char**,size_t*) ; 

__attribute__((used)) static inline int read_full_file(const char *filename, char **contents, size_t *size) {
        return read_full_file_full(filename, 0, contents, size);
}