#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int journal_file_rotate (TYPE_1__**,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error_errno (int,char*,...) ; 

__attribute__((used)) static int do_rotate(JournalFile **f, bool compress, bool seal) {
        int r = journal_file_rotate(f, compress, (uint64_t) -1, seal, NULL);
        if (r < 0) {
                if (*f)
                        log_error_errno(r, "Failed to rotate %s: %m", (*f)->path);
                else
                        log_error_errno(r, "Failed to create rotated journal: %m");
        }

        return r;
}