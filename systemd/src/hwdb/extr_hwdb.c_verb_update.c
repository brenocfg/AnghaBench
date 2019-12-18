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
 int /*<<< orphan*/  arg_hwdb_bin_dir ; 
 int /*<<< orphan*/  arg_root ; 
 int /*<<< orphan*/  arg_strict ; 
 int hwdb_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int verb_update(int argc, char *argv[], void *userdata) {
        return hwdb_update(arg_root, arg_hwdb_bin_dir, arg_strict, false);
}