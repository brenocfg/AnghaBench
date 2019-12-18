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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFREG ; 
 int WRITE_STRING_FILE_ATOMIC ; 
 int WRITE_STRING_FILE_CREATE ; 
 int /*<<< orphan*/  mac_selinux_create_file_clear () ; 
 int mac_selinux_create_file_prepare (char const*,int /*<<< orphan*/ ) ; 
 int write_string_file_ts (char const*,char const*,int,struct timespec*) ; 

int write_string_file_atomic_label_ts(const char *fn, const char *line, struct timespec *ts) {
        int r;

        r = mac_selinux_create_file_prepare(fn, S_IFREG);
        if (r < 0)
                return r;

        r = write_string_file_ts(fn, line, WRITE_STRING_FILE_CREATE|WRITE_STRING_FILE_ATOMIC, ts);

        mac_selinux_create_file_clear();

        return r;
}