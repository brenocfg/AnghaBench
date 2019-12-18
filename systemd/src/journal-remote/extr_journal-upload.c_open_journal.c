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
typedef  int /*<<< orphan*/  sd_journal ;

/* Variables and functions */
 int SD_JOURNAL_LOCAL_ONLY ; 
 char* arg_directory ; 
 scalar_t__ arg_file ; 
 scalar_t__ arg_journal_type ; 
 scalar_t__ arg_machine ; 
 int /*<<< orphan*/  arg_merge ; 
 int /*<<< orphan*/  log_error_errno (int,char*,char*) ; 
 int sd_journal_open (int /*<<< orphan*/ **,scalar_t__) ; 
 int sd_journal_open_container (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_journal_open_directory (int /*<<< orphan*/ **,char*,scalar_t__) ; 
 int sd_journal_open_files (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_journal(sd_journal **j) {
        int r;

        if (arg_directory)
                r = sd_journal_open_directory(j, arg_directory, arg_journal_type);
        else if (arg_file)
                r = sd_journal_open_files(j, (const char**) arg_file, 0);
        else if (arg_machine)
                r = sd_journal_open_container(j, arg_machine, 0);
        else
                r = sd_journal_open(j, !arg_merge*SD_JOURNAL_LOCAL_ONLY + arg_journal_type);
        if (r < 0)
                log_error_errno(r, "Failed to open %s: %m",
                                arg_directory ? arg_directory : arg_file ? "files" : "journal");
        return r;
}