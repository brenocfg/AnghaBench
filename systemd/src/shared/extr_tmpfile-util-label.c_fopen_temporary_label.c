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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFREG ; 
 int fopen_temporary (char const*,int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  mac_selinux_create_file_clear () ; 
 int mac_selinux_create_file_prepare (char const*,int /*<<< orphan*/ ) ; 

int fopen_temporary_label(
                const char *target,
                const char *path,
                FILE **f,
                char **temp_path) {

        int r;

        r = mac_selinux_create_file_prepare(target, S_IFREG);
        if (r < 0)
                return r;

        r = fopen_temporary(path, f, temp_path);

        mac_selinux_create_file_clear();

        return r;
}