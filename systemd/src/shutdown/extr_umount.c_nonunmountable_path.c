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
 scalar_t__ path_equal (char const*,char*) ; 
 scalar_t__ path_startswith (char const*,char*) ; 

__attribute__((used)) static bool nonunmountable_path(const char *path) {
        return path_equal(path, "/")
#if ! HAVE_SPLIT_USR
                || path_equal(path, "/usr")
#endif
                || path_startswith(path, "/run/initramfs");
}